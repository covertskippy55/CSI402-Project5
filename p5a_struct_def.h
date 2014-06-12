/* Name: Dilan Samarasinghe
   ID: DS697678
*/

typedef struct header{
  char name[MAX_FILE_LENGTH];
  int fileSize;
  struct header *next;
}HEADER;
