/* Name: Dilan Samarasinghe
   ID: DS697678
*/

typedef struct students{
  char name[NAME_LENGTH];
  int numCourses;
  int courseIds[MAX_CLASSES];
  struct students *next;
}STUDENT;

typedef struct courses{
  unsigned int courseID;
  unsigned int numCredits;
  char schedule[MAX_SCHED_LENGTH];
  struct courses *next;

}COURSES;

typedef struct commandNode{
  char command[COMMAND_SIZE];
  char string[MAX_STRING_SIZE];
  int courseId;
  int numCredits;
}COMMAND;

typedef struct replyNode{
  int status;
  int intValues;
  char string[MAX_STRING_SIZE];
}REPLY;
