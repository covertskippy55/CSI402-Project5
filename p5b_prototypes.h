/* Name: Dilan Samarasinghe
   ID:DS697678
*/

STUDENT* createStudentDB(FILE*);
COURSES* createCoursesDB(FILE*);
void printLists(STUDENT*);
void printLIstc(COURSES*);
STUDENT* getStudent(STUDENT*,char*);
COURSES* getCourse(COURSES*,int);
int countStudents(STUDENT*);
int countCourses(COURSES*);
int countEnrolled(STUDENT*,char*);
COMMAND* addc(char*);
COMMAND* drpc(char*);
COMMAND* wdrw(char*);
COMMAND* tcre(char*);
COMMAND* newc(char*);
COMMAND* csch(char*);
COMMAND* ccre(char*);
COMMAND* gsch(char*);
COMMAND* gcre(char*);
REPLY* runAddc(COMMAND,STUDENT*,COURSES*);
REPLY* runDrpc(COMMAND,STUDENT*,COURSES*);
REPLY* runWdrw(COMMAND,STUDENT*,COURSES*);
REPLY* runTcre(COMMAND,STUDENT*,COURSES*);
REPLY* runNewc(COMMAND,STUDENT*,COURSES*);
REPLY* runCsch(COMMAND,STUDENT*,COURSES*);
REPLY* runCcre(COMMAND,STUDENT*,COURSES*);
REPLY* runGsch(COMMAND,STUDENT*,COURSES*);
REPLY* runGcre(COMMAND,STUDENT*,COURSES*);
