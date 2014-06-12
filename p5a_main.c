/* Name: Dilan Samarasinghe
   ID: DS697678

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "p5a_constants.h"
#include "p5a_struct_def.h"
#include "p5a_prototypes.h"

/* This main function will check for the number of command line arguments and if they are valid flags. If the flag is c it will open the archive file for writing and call the writing functions. If the flag is x it will call the write function.
 */
int main(int argc,char *argv[]){
  unsigned char numFiles = argc - NUMTOREMOVE; // number of files = number of arguments - p5a,flag and archive name
  int fd;// holds one file descriptor
  int i;//temp variable
  int checkWrite; // check the return value from writing
  HEADER *head;
  // first check if we have atleast 2 values because we need p5a and the flag
  if(argc < 2){
    fprintf(stderr,"Illegal parameters for this program, use is: p5a flag fileName(s)\n");
    exit(1);
  }
  // check if its -c flag
  if(strcmp(argv[FLAG],"-c") == 0){
    // if it is check if we have atleast the archive name and one file
    if(argc < NUM_ARGS_C){
      fprintf(stderr,"Wrong number of inputs for archiving, use is : p5a -c archiveName file1...filek\n");
      exit(1);
    }
  }
  // if its -x flag see if we have atleast an archive name
  else if(strcmp(argv[FLAG],"-x")== 0){
    if(argc < NUM_ARGS_X){
      fprintf(stderr,"Wrong number of inputs for extracting, use is: p5a -x archiveName\n");
      exit(1);
    }
  }
  else{
    fprintf(stderr,"Illegal flag, available flags are: -c -x\n");
    exit(1);
  }
  //printf("%d\n",numFiles);
  // if the flag was c open the archive file with full permission for everyone and open it for writing. If it doesnt exist create it otherwise truncate it.
  if(strcmp(argv[FLAG],"-c") == 0){
     if((fd = open(argv[ARCHIVE_NAME],O_WRONLY | O_TRUNC | O_CREAT,S_IRWXU | S_IRWXG| S_IRWXO )) == -1){
       fprintf(stderr,"Error occured with opening of archive file, %s.\n",argv[ARCHIVE_NAME]);
       exit(1);
      
     }
     // write the number of files into the archive file
     if((checkWrite = write(fd,&numFiles,1)) == -1){
       fprintf(stderr,"Error occured with wriring the numbre of files\n");
     }
     // loop through the arugment list getting each file name then pass that and the archive file to the write functions.
     // we have to do this in two seperate for loops because we need the header done before we do the files
     for(i = 3; i < numFiles+3;i++){
       // printf("%s\n",argv[i]);
       writeHeader(fd,argv[i]);
     }

     for( i = 3;i < numFiles+3;i++){
       writeFiles(fd,argv[i]);
     }

     // return the file descriptor back to the kernal
     if(close(fd) == -1){
       fprintf(stderr,"Error occured with closing of archive file, %s\n",argv[ARCHIVE_NAME]);
       exit(1);
     }
  }
  // if the flag was x call the read header function which will do the full extraction from the archive
  else if(strcmp(argv[FLAG],"-x") == 0){
    // the return was stored so we can test the linked list
    head = readHeader(argv[ARCHIVE_NAME]);
   // printList(head);
   // readFiles(head,argv[ARCHIVE_NAME]);

  }
  return 0;
}
