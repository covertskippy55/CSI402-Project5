/* Name: Dilan Samarasinghe
   ID: DS697678
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "p5b_constants.h"
#include "p5b_struct_def.h"
#include "p5b_prototypes.h"


int main(int argc, char* argv[]){
  int readFromServer;// file descriptor for the FIFO that the server sends info to client
  int writeToServer; // file descriptor for the FIFO that client sends info to server
  // printf("This is the child\n");
  FILE *commandfp; // holds the command file
  FILE *logfp; // holds the log file
  char line[MAX_LINE]; // holds a line from the command file
  char lineCopy[MAX_LINE]; // this will hold the original line to be passed to one of the functions
  char *token;//token pointer for tokenizing
  COMMAND cnodeExit; //the command node to be written to the FIFO
  COMMAND *cnode;
  int lineNum = 0;
  REPLY rnode;
  if(argc != MAX_CLIENT_ARGS){
    fprintf(stderr,"Incorrect number of client parameters.\n");
    exit(1);
  }
  if((readFromServer = open("ServerFifo",O_RDWR)) == -1){
    fprintf(stderr,"Client: ServerFifo opening failed.\n");
    exit(1);
  }
  if((writeToServer = open("ClientFifo",O_RDWR)) == -1){
    fprintf(stderr,"Client: ClientFifo opening failed.\n");
    exit(1);
  }
  if((commandfp = fopen(argv[INIT_DB],"r")) == NULL){
    fprintf(stderr,"Error occured with opening of command file.\n");
    exit(1);
  }
  if((logfp = fopen(argv[FINAL_DB],"w")) == NULL){
    fprintf(stderr,"Error occured with opening of log file.\n");
    exit(1);
  }

  while(fgets(line,MAX_LINE,commandfp) != NULL){
    strcpy(lineCopy,line);
    token = strtok(line,"\t \n ");
    // printf("%s\n",token);
    if(strcmp(token,"addc") == 0){
      cnode = addc(lineCopy);
      // printf("Client: %s has following: %s %d\n",cnode->command,cnode->string,cnode->courseId);
      //fflush(stdout);
      fprintf(logfp,"%d \t %s\t",lineNum,cnode->command);
      // printf(lineCopy);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
	fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
	exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
	fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
	exit(1);
      }
      fprintf(logfp,"%d\n",rnode.status);
    }
    else if(strcmp(token,"drpc") == 0){
      cnode = drpc(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      //printf("Client: %s has following: %s %d\n",cnode->command,cnode->string,cnode->courseId);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d\n",rnode.status);
    }
    else if(strcmp(token,"wdrw") == 0){
      cnode = wdrw(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d\n",rnode.status);
    }
    else if(strcmp(token,"tcre") == 0){
      cnode = tcre(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d \t %d\n",rnode.status,rnode.intValues);
    }
    else if(strcmp(token,"newc") == 0){
      cnode = newc(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d\n",rnode.status);
    }
    else if(strcmp(token,"csch") == 0){
      cnode = csch(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d\n",rnode.status);
    }
    else if(strcmp(token,"ccre") == 0){
      cnode = ccre(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d\n",rnode.status);
    }
    else if(strcmp(token,"gsch") == 0){
      cnode = gsch(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d\t %s\n",rnode.status,rnode.string);
    }
    else if(strcmp(token,"gcre") == 0){
      cnode = gcre(lineCopy);
      fprintf(logfp,"%d \t %s \t",lineNum,cnode->command);
      if(write(writeToServer,cnode,sizeof(COMMAND)) == -1 ){
        fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
        exit(1);
      }
      if(read (readFromServer,&rnode,sizeof(REPLY)) == -1){
        fprintf(stderr,"Client:Error occured with reading from FIFO.\n");
        exit(1);
      }
      fprintf(logfp,"%d\t %d\n",rnode.status,rnode.intValues);
    }
    
    lineNum++;
  }
  strcpy(cnodeExit.command,"exit");
  if(write(writeToServer,&cnodeExit,sizeof(COMMAND)) == -1 ){
    fprintf(stderr,"Client: Error occured with writing to FIFO.\n");
    exit(1);
  }
   
  // printf("The client will exit now.\n");
  //fflush(stdout);
  return 0;
}


