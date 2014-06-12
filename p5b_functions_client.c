/* Name: Dilan Samarasinghe
   ID:DS697678
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

COMMAND* addc(char *line){
  char *token;
  COMMAND *temp;
  if(( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);

  }
  token = strtok(line," \t \n");
  token = strtok(NULL," \t\n");
  strcpy(temp->command,"addc");
  strcpy(temp->string,token);
  //printf(temp->string);
  token = strtok(NULL," \t\n");
  temp->courseId = atoi(token);
  // printf("command: %s, string: %s, courseid: %d\n",temp->command,temp->string,temp->courseId);
  return temp;

}

COMMAND* drpc(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);
  }
  strcpy(temp->command,"drpc");
  token = strtok(line,"\t\n ");
  token = strtok(NULL,"\t\n ");
  strcpy(temp->string,token);
  token = strtok(NULL,"\t\n ");
  temp->courseId = atoi(token);
  // printf("command: %s, string: %s, courseId:%d\n",temp->command,temp->string,temp->courseId);
  return temp;
}

COMMAND* wdrw(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);
  }
  strcpy(temp->command,"wdrw");
  token = strtok(line,"\t\n ");
  token = strtok(NULL," \t\n ");
  strcpy(temp->string,token);
  // printf("command: %s, string: %s\n",temp->command,temp->string);
  return temp;
}
COMMAND* tcre(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);
  }

  strcpy(temp->command,"tcre");
  token = strtok(line,"\t\n ");
  token = strtok(NULL," \t\n");
  strcpy(temp->string,token);
  // printf("command: %s, string: %s\n",temp->command,temp->string);
  return temp;
}

COMMAND* newc(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);
  }
  strcpy(temp->command,"newc");
  token = strtok(line,"\t\n ");
  token = strtok(NULL," \t\n ");
  temp->courseId = atoi(token);
  token = strtok(NULL,"\t\n ");
  temp->numCredits = atoi(token);
  token = strtok(NULL,"\t\n ");
  strcpy(temp->string,token);
  // printf("command: %s, string: %s, courseid: %d, numcredits:%d \n",temp->command,temp->string,temp->courseId,temp->numCredits);
  return temp;
}

COMMAND* csch(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);
  }
  strcpy(temp->command,"csch");
  token = strtok(line,"\t\n ");
  token = strtok(NULL,"\t \n ");
  temp->courseId = atoi(token);
  token = strtok(NULL,"\t\n ");
  strcpy(temp->string,token);
  //printf("command: %s, string: %s, courseid: %d\n",temp->command,temp->string,temp->courseId);
  return temp;
}


COMMAND* ccre(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
  fprintf(stderr,"Error occured with malloc\n");
  exit(1);
  }
  strcpy(temp->command,"ccre");
  token = strtok(line,"\t\n ");
  token = strtok(NULL,"\t \n ");
  temp->courseId = atoi(token);
  token = strtok(NULL,"\t\n ");
  temp->numCredits = atoi(token);
  //printf("command: %s, courseId:%d, numCredits:%d\n",temp->command,temp->courseId,temp->numCredits);
  return temp;
}

COMMAND* gsch(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);
  }
  strcpy(temp->command,"gsch");
  token = strtok(line,"\t\n ");
  token = strtok(NULL,"\t \n ");
  temp->courseId = atoi(token);
  // printf("command: %s, courseid: %d\n",temp->command,temp->courseId);
  return temp;
}

COMMAND* gcre(char *line){
  char *token;
  COMMAND *temp;
  if (( temp = malloc(sizeof(COMMAND))) == NULL){
    fprintf(stderr,"Error occured with malloc\n");
    exit(1);
  }
  strcpy(temp->command,"gcre");
  token = strtok(line,"\t\n ");
  token = strtok(NULL,"\t \n ");
  temp->courseId = atoi(token);
  //printf("command: %s, courseid: %d\n",temp->command,temp->courseId);
return temp;
}
