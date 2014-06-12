/* Name: Dilan Samarasinghe
   ID: DS697678
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "p5b_constants.h"
#include "p5b_struct_def.h"
#include "p5b_prototypes.h"

int main(int argc, char *argv[]){
  int childpid; // holds the child process id
  FILE *initDB; // holds the initial database file
  FILE *finalDB;// holds the final database file
  int readFromClient; // file descriptor for the FIFO that reads from the client
  int writeToClient; // file descriptor for the FIFO that writes to the client
  COURSES *cHead; // this is the head of the courses list
  STUDENT *sHead; // this is the head of the students list
  COMMAND cnode;
  STUDENT *spointer;
  COURSES *cpointer;
  REPLY *rnode;
  int count;
  int i;
   if(argc != MAX_ARGS){
    fprintf(stderr,"Wrong number of command line arguments,useage is: p5b_server initdbfile finaldbfile cmdfile logfile\n");
    exit(1);
    }
   if((initDB = fopen(argv[INIT_DB],"r")) == NULL){
     fprintf(stderr,"Error occured with opening of initial database file, %s.\n",argv[INIT_DB]);
     exit(1);
   }
   if((finalDB = fopen(argv[FINAL_DB],"w"))  == NULL){
     fprintf(stderr,"Error occured with opening of final database file, %s.\n",argv[FINAL_DB]);
     exit(1);

   }
   sHead = createStudentDB(initDB);
   cHead = createCoursesDB(initDB);
   // printLists(sHead);
   //printf("\n");
   //printListc(cHead);
   if(mkfifo("ServerFifo",S_IRWXU |S_IRWXG |S_IRWXO) == -1){
    if(errno!=EEXIST){
      fprintf(stderr,"Client: Couldnt create ServerFifo.\n");
      exit(1);
    }

  }
  if(mkfifo("ClientFifo",S_IRWXU |S_IRWXG |S_IRWXO) == -1){
    if(errno!=EEXIST){
      fprintf(stderr,"Client: Couldnt create ClientFifo.\n");
      exit(1);
    }

  }
  if((childpid = fork()) == 0){
    execlp("p5b_client","p5b_client",argv[CMD_FILE],argv[LOG_FILE],NULL);
  }

  if((readFromClient = open("ClientFifo",O_RDWR)) == -1 ){
    fprintf(stderr,"Server: ClientFifo opening failed.\n");
    exit(1);
  }

  if((writeToClient = open("ServerFifo",O_RDWR)) == -1 ){
    fprintf(stderr,"Server: ServerFifo opening failed.\n");
    exit(1);
  }
  // printf("The server will exit now.\n");
  //fflush(stdout);
  while(1){
    if(read(readFromClient,&cnode,sizeof(COMMAND)) == -1){
      fprintf(stderr,"Server:Error occured with reading from client.\n");
      exit(1);
    }
    // printf("Command:%s",cnode.command);
    if(strcmp(cnode.command,"addc") == 0){
      // printf("Server: Recived addc command with following parameters: %s %d\n",cnode.string,cnode.courseId);
      // fflush(stdout);
      rnode = runAddc(cnode,sHead,cHead);
      
      // printf("%d",rnode->status);
      
    }
    else  if(strcmp(cnode.command,"drpc") == 0){
      rnode = runDrpc(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"wdrw") == 0){
      rnode = runWdrw(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"tcre") == 0){
      rnode = runTcre(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"newc") == 0){
      rnode = runNewc(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"csch") == 0){
      rnode = runCsch(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"ccre") == 0){
      rnode = runCcre(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"gsch") == 0){
      rnode = runGsch(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"gcre") == 0){
      rnode = runGcre(cnode,sHead,cHead);
    }
    else if(strcmp(cnode.command,"exit") == 0){
      // printf("Server: Recieved exit command\n");
      // fflush(stdout);
      count = countStudents(sHead);
      fprintf(finalDB,"%d\n",count);
      for(spointer = sHead; spointer !=NULL; spointer = spointer->next){
	fprintf(finalDB,"%s \t %d \t",spointer->name,spointer->numCourses);
	for(i = 0; i < MAX_CLASSES; i++){
	  if(spointer->courseIds[i] != -1){
	    fprintf(finalDB,"%d ",spointer->courseIds[i]);
	  }
	}
	fprintf(finalDB,"\n");
      }
      count = countCourses(cHead);
      fprintf(finalDB,"%d\n",count);
      for(cpointer = cHead; cpointer !=NULL; cpointer = cpointer->next){
	fprintf(finalDB,"%d \t %d \t %s\n",cpointer->courseID,cpointer->numCredits,cpointer->schedule);
      }
      return 0;
    }



   
    if(write(writeToClient,rnode,sizeof(REPLY)) == -1 ){
      fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
      exit(1);
    }
    
  }
  
}
