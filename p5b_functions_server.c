/* Name: Dilan Samarasinghe
   ID:DS697678
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "p5b_constants.h"
#include "p5b_struct_def.h"


STUDENT* createStudentDB(FILE *initdb){
  STUDENT *head; // pointer to first node
  STUDENT *current; // pointer to traverse the list
  STUDENT *temp; // temp node
  int i; // temp variable
  int k;//temp variable
  char *token;
  int numStudents; // number of student records
  char line[MAX_LINE]; // buffer to hold a line
  head = NULL;
  // get the first line which tells how many students and store in numStudents
  if(fgets(line,MAX_LINE,initdb) == NULL){
    fprintf(stderr,"Error occured with reading initial database file.\n");
    exit(1);

  }
  numStudents = atoi(line);
  // printf("%d\n",numStudents);
  // loop through as many student records as there are
  for(i = 0; i < numStudents; i++){
    if( fgets(line,MAX_LINE,initdb) == NULL){
      fprintf(stderr,"Error occured with reading from initial database.\n");
      exit(1);
    }
    //printf("%s",line);
    // malloc space for a student node
    if((temp = malloc(sizeof(STUDENT))) == NULL){
      fprintf(stderr,"Error occured with malloc\n.");
      exit(1);
    }
    // loop through the class id list for the current student node and set it to -1, since the value will never be -1 we can test for the end of the array with this
    for(k = 0; k < MAX_CLASSES;k++){
      temp->courseIds[k] = -1;
    }
    // get the name and the number of courses taken and store in the node
    token = strtok(line,"\t ");
    strcpy(temp->name,token);
    token = strtok(NULL,"\t\n ");
    temp->numCourses = atoi(token); 
    temp->next = NULL; // set next to be null
    k = 0;
    // get the first class id and then loop through until there are no more ids
    token = strtok(NULL," \t\n");
    while(token !=NULL){
      // populate the course id array of the node using the tokens 
      temp->courseIds[k] = atoi(token);
      k++;
      token = strtok(NULL,"\t \n ");
    }
    if(head == NULL){
      head = temp;
    }
    else{
      current = head;
      while(current->next !=NULL){
	current = current->next;
      }
      current->next = temp;
    }
  }
  return head;
}

COURSES* createCoursesDB(FILE *initDB){
  COURSES *head; // pointer to first node
  COURSES *current; // pointer to traverse the list
  COURSES *temp; // temp node
  int i; // temp variable
  char *token;
  int numCourses; // number of student records
  char line[MAX_LINE]; // buffer to hold a line
  head = NULL;
  if(fgets(line,MAX_LINE,initDB)== NULL){
    fprintf(stderr,"Error occured with reading initial database file.\n");
    exit(1);
  }
  numCourses = atoi(line);
  // printf("Number of courses:%d\n",numCourses);
  for(i = 0; i < numCourses;i++){
    if(fgets(line,MAX_LINE,initDB)== NULL){
      fprintf(stderr,"Error occured with reading initial database file.\n");
      exit(1);
    }
    if((temp = malloc(sizeof(COURSES))) == NULL){
      fprintf(stderr,"Error occured with malloc.\n");
      exit(1);
    }
    temp->next = NULL;
    token = strtok(line,"\t\n ");
    temp->courseID = atoi(token);
    token = strtok(NULL,"\t \n ");
    temp->numCredits =atoi(token);
    token = strtok(NULL,"\t\n ");
    strcpy(temp->schedule,token);

    // printf("course id: %d, number of credits: %d,schedule: %s\n",temp->courseID,temp->numCredits,temp->schedule); 
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
  
  return head;
}

void printLists(STUDENT *head){
  STUDENT *current;
  int k;
  for(current = head; current != NULL; current = current->next){
     printf("Name: %s\t Number of classes: %d\t Class List:",current->name,current->numCourses);
    for(k = 0; k < MAX_CLASSES; k++){
      if(current->courseIds[k] != -1){
	printf("%d ",current->courseIds[k]);
      }
    }
    printf("\n");
  }

}

void printListc(COURSES *head){
  COURSES *current;
  for(current = head; current != NULL; current = current->next){
    printf("Course id: %d \t number of credits: %d\t schedule: %s\n",current->courseID,current->numCredits,current->schedule);
  }

}

int countCourses(COURSES *head){
  COURSES *current;
  int count = 0;
  for(current = head; current !=NULL;current = current->next){
    count++;
  }
  return count;
}

int countStudents(STUDENT *head){
  STUDENT *current;
  int count = 0;
  for(current = head;current != NULL; current = current->next){
    count++;

  }
  return count;
}
int countEnrolled(STUDENT *head,char *name){
  STUDENT *current;
  int count;
  int i;
  for(current = head;current!=NULL; current = current->next){
    if(strcmp(current->name,name)== 0){
      for( i = 0;i < MAX_CLASSES; i++){
	if(current->courseIds[i] != -1){
	  count++;
	}
      }

    }

  }
  if( count < MAX_CLASSES){
    return 1;
  }
  else{
    return 0;
  }
}

COURSES* getCourse(COURSES *chead,int id){
  COURSES *current;
  for(current = chead; current !=NULL;current = current->next){
    if(current->courseID == id){
      return current;
    }
  }
  return NULL;
}

STUDENT* getStudent(STUDENT *shead,char *name){
  STUDENT *current;
  for(current = shead; current !=NULL;current = current->next){
    if(strcmp(current->name,name) == 0){
      return current;
    }
  }
  return NULL;
}

REPLY* runAddc(COMMAND cnode,STUDENT *shead,COURSES *chead){
  REPLY *rtemp;
  int k;
  STUDENT *studentp;
  STUDENT *current;
  STUDENT *temp;
  COURSES *coursep;
  int i;
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc");
    exit(1);
  }
  if((coursep =getCourse(chead,cnode.courseId)) !=NULL){
    if((studentp = getStudent(shead,cnode.string)) !=NULL){
      k = 0;
      while(studentp->courseIds[k] != -1){
	if(k >=MAX_CLASSES){
	  rtemp->status = 0;
	  return rtemp;
	}
	if(studentp->courseIds[k] == cnode.courseId){
	  rtemp->status = 0;
	  return rtemp;
	}
	k++;
      }
      studentp->courseIds[k] = cnode.courseId;
      studentp->numCourses++;
      rtemp->status = 1;
      return rtemp;
    }
    else if(studentp == NULL){
      if((countStudents(shead))+1 >100){
	rtemp->status = 0;
	return rtemp;
      }
      else{
	current = shead;
	while(current->next !=NULL){
	  current = current->next;
	}
	if((temp = malloc(sizeof(STUDENT))) == NULL){
	  fprintf(stderr,"Error occured with maloc\n");
	  exit(1);
	}
	strcpy(temp->name,cnode.string);
	temp->numCourses = 1;
	temp->next = NULL;
	current->next = temp;
	for(i = 1; i < MAX_CLASSES;i++){
	  temp->courseIds[i] = -1;
	}
	temp->courseIds[0] = cnode.courseId;
	rtemp->status = 1;
	return rtemp;
      }
    }
  }
  else if(coursep == NULL){
    rtemp->status = 0;
    return rtemp;
  }
  rtemp->status = 1;
  return rtemp;
 
}

REPLY* runDrpc(COMMAND cnode,STUDENT *shead,COURSES *chead){
  STUDENT *spointer;
  REPLY *rtemp;
  int i;
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }
  if((spointer = getStudent(shead,cnode.string)) !=NULL){
    for(i = 0; i < MAX_CLASSES; i ++){
      if(spointer->courseIds[i] == cnode.courseId){
	spointer->courseIds[i] = -1;
	spointer->numCourses--;
	rtemp->status = 1;
	return rtemp;
      }
    }
    rtemp->status = 0;
    return rtemp;
  }
  rtemp->status = 0;
  return rtemp;

}


REPLY* runWdrw(COMMAND cnode,STUDENT *shead,COURSES *chead){
  STUDENT *spointer;
  REPLY *rtemp;
  int i;
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }
  if((spointer = getStudent(shead,cnode.string)) !=NULL){
    if(spointer->courseIds[0] == -1){
      rtemp->status = 0;
      return rtemp;
    }
    else{
      for(i = 0; i < MAX_CLASSES; i ++){
	spointer->courseIds[i] = -1;
      }
      spointer->numCourses = 0;
      rtemp->status = 1;
      return rtemp;
    }
  }
  
  rtemp->status = 0;
  return rtemp;
  
}
REPLY* runTcre(COMMAND cnode,STUDENT *shead,COURSES *chead){
  STUDENT *spointer;
  COURSES *cpointer;
  int i;
  REPLY *rtemp;
  int total = 0;
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }
  if((spointer = getStudent(shead,cnode.string)) !=NULL){
    for(i = 0; i <MAX_CLASSES; i++){
      if(spointer->courseIds[i] != -1){
	//printf("index:%d,courseid:%d ",i,spointer->courseIds[i]);
	if((cpointer = getCourse(chead,spointer->courseIds[i])) != NULL){
	  total += cpointer->numCredits;
	  // printf("numcredits:%d,total:%d\n",cpointer->numCredits,total);
	}
      }
    }
    rtemp->status = 1;
    rtemp->intValues = total;
    return rtemp;
  }
 
  rtemp->status = 0;
  rtemp->intValues = -1;
  return rtemp;
  
}

REPLY* runNewc(COMMAND cnode,STUDENT *shead,COURSES *chead){
  REPLY *rtemp;
  COURSES *cpointer;
  COURSES *temp;
  if((temp = malloc(sizeof(COURSES))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }

  if(cnode.numCredits <= 0){
    rtemp->status = 0;
    return rtemp;
  }
  else if((getCourse(chead,cnode.courseId)) !=NULL){
    rtemp->status = 0;
    return rtemp;
  }
  else{
    temp->courseID = cnode.courseId;
    temp->numCredits = cnode.numCredits;
    temp->next = NULL;
    strcpy(temp->schedule,cnode.string);
    if(chead == NULL){
      chead = temp;
    }
    else{
      cpointer = chead;
      while(cpointer->next!=NULL){
	cpointer = cpointer->next;
      }
      cpointer->next = temp;
    }
    
  }
  rtemp->status = 1;
  return rtemp;
  

}
REPLY* runCsch(COMMAND cnode,STUDENT *shead,COURSES *chead){
  REPLY *rtemp;
  COURSES *cpointer;
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }
  
  if((cpointer = getCourse(chead,cnode.courseId)) !=NULL){
    strcpy(cpointer->schedule,cnode.string);
    rtemp->status = 1;
    return rtemp;
  }
  rtemp->status = 0;
  return rtemp;
  
  
}

REPLY* runCcre(COMMAND cnode,STUDENT *shead,COURSES *chead){
   REPLY *rtemp;
   COURSES *cpointer;
   if((rtemp = malloc(sizeof(REPLY))) == NULL){
     fprintf(stderr,"Error occured with malloc.\n");
     exit(1);
   }

   if((cpointer = getCourse(chead,cnode.courseId)) !=NULL){
     cpointer->numCredits = cnode.numCredits;
     rtemp->status = 1;
     return rtemp;
   }
   rtemp->status = 0;
   return rtemp;

}

REPLY* runGsch(COMMAND cnode,STUDENT *shead,COURSES *chead){
  REPLY *rtemp;
  COURSES *cpointer;
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }
  if((cpointer = getCourse(chead,cnode.courseId)) !=NULL){
    rtemp->status = 1;
    strcpy(rtemp->string,cpointer->schedule);
    return rtemp;

  }
  rtemp->status = 0;
  strcpy(rtemp->string,"Error");
  return rtemp;
}
REPLY* runGcre(COMMAND cnode,STUDENT *shead,COURSES *chead){
  REPLY *rtemp;
  COURSES *cpointer;
  if((rtemp = malloc(sizeof(REPLY))) == NULL){
    fprintf(stderr,"Error occured with malloc.\n");
    exit(1);
  }
  if((cpointer = getCourse(chead,cnode.courseId)) !=NULL){
    rtemp->status = 1;
    rtemp->intValues = cpointer->numCredits;
    return rtemp;

  }
  rtemp->status = 0;
  rtemp->intValues = -1;
  return rtemp;
}
