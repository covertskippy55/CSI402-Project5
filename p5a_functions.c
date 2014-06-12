/* Name:Dilan Samarasinghe
   ID: DS697678
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "p5a_constants.h"
#include "p5a_struct_def.h"

/* This function takes in a file descriptor of the archive file and the name of a file to be copied. it returns a 0 if sucessful
 */
int writeHeader(int fd,char *fileName){
  int file; // file descriptor for reading file
  int fileSize; // stores the size of the file
  unsigned char length = strlen(fileName);// stores the length of the file name
  // open the file to be read and check for errors
    if((file = open(fileName,O_RDONLY)) == -1){
      fprintf(stderr,"Error occured with opening of file, %s.\n",fileName);
       exit(1);
    }
    // printf("name:%s length:%d\n",fileName,length);
    // write the length of the file name which we figured out earlier
    if(write(fd,&length,1) == -1){
      fprintf(stderr,"Error occured with writing file name length\n");
    }
    // write the file name which was passed into this function next
    if( write(fd,fileName,length) == -1){
      fprintf(stderr,"Error occured with writing file name \n");
    }
    // get the file size by seeking to the end of the file and catching the return value
    fileSize = lseek(file,0,SEEK_END);
    //printf("%d\n",fileSize);
    // write this value into the next 4 bytes 
    if(write(fd,&fileSize,4) == -1){
      fprintf(stderr,"Error occured with writing file size\n");
    }
    // close the file
    close(file);
  
  return 0;
}
/* This function takes in the archive file descriptor and the file name. It returns a 0 if the copying of file was sucessful
 */
int writeFiles(int fd,char *fileName){
  int file; // holds the file for reading
  char buffer[LINE_SIZE]; // holds a 512 bytes of the file being read
  int nread; // check the return value from reading
  int nwrite; // check the return value from writing
  // open the file for reading and check for errors
  if((file = open(fileName,O_RDONLY)) == -1){
    fprintf(stderr,"Error occured with opening of file, %s.\n",fileName);
    exit(1);
  }
  // loop through the file being read until the return value from reading is less than or equal to zero meaning weve reached EOF

  while((nread = read(file,buffer,LINE_SIZE)) > 0 ){
    // write to the archive file and store the amount written
   nwrite = write(fd,buffer,nread);
   // if the amount written is less than the amount read then an error occured somewhere so exit and close the file
    if(nwrite<nread){
      fprintf(stderr,"Error occured while writing.\n");
      close(file);
      exit(1);
    }
  }
  close(file);
  return 0;
}
/* This function takes in the archive file name. It will extract the files in the archive. It returns the pointer to a linked list of header nodes.
 */
HEADER* readHeader(char *fileName){
  HEADER *temp; // a temp header pointer node 
  HEADER *head = NULL; // pointer to the start of the linked list
  HEADER *current; // another pointer to loop through the list
  int i; // temp variable
  int fd; // holds the archive file descriptor
  int file; // holds the file to be created and written to
  unsigned char size; // holds the size of the file name
  unsigned char numFiles; // holds the number of files in the archive
  int fileSize; // holds the file size of each file
  char *buffer; // a buffer to copy the data in the file so we can write it into the correct file

  // open the archive file and check for errors
  if((fd = open(fileName,O_RDONLY)) == -1){
    fprintf(stderr,"Error occured with opening of archive file, %s for reading.\n",fileName);
    exit(1);

  }
  // read from the header section the number of files
  if(read(fd,&numFiles,1) == -1){
    fprintf(stderr,"Error occured with reading from file\n");
    exit(1);
  }
  // printf("num files:%d\n",numFiles);
  // loop through the header creating a node for each file header block
  for(i = 0; i <numFiles;i++){
    temp = malloc(sizeof(HEADER));
    // read the length of the file name
    if(read(fd,&size,1)==-1){
      fprintf(stderr,"Error occured with reading from file\n");
      exit(1);
    }
    //printf("number of character: %d\n",size);
    // read the name of the file and store it in the temp node
    if(read(fd,temp->name,size)==-1){
      fprintf(stderr,"Error occured with reading\n");
	exit(1);
    }
    //printf("%s\n",temp->name);
    // read the file size 
    if(read(fd,&fileSize,4)== -1){
      fprintf(stderr,"Error occured with reading\n");
      exit(1);
    }
    // set the file size and the next pointer of the temp node
    temp->fileSize = fileSize;
    temp->next = NULL;
    // either add the node to the start of the list or add it to the end if the list already exists
    if(head == NULL){
      head = temp;
    }
    else{
      current = head;
      while(current->next != NULL){
	current = current->next;
      }
      current->next = temp;
    }
  }
  // loop through the linked list we made earlier and create files of the file name. Then read the entire file from the archive file and write it to the file we created
  for(current = head;current!=NULL;current = current->next){
    if((file = open(current->name,O_CREAT | O_WRONLY | O_TRUNC,S_IRWXU | S_IRWXG | S_IRWXO)) == -1){
      fprintf(stderr,"Error occured with opening of file.\n");
      exit(1);

    }

    if(( buffer = malloc(current->fileSize)) == NULL){
      fprintf(stderr,"Error occured with malloc\n");
      exit(1);
    }
    
    if(read(fd,buffer,current->fileSize) == -1){
      fprintf(stderr,"Error occured with reading\n");
    }
    //printf("%s\n",buffer);
    write(file,buffer,current->fileSize);
  }


  return head;
}

/* This function is a test function that loops through the linked list and prints the information
 */
void printList(HEADER *head){
  HEADER *current;
  
  for(current = head; current!=NULL; current = current->next){
    printf("name: %s fileSize: %d \n",current->name,current->fileSize);
  }

}
