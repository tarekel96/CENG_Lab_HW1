#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define NRECORDS 100
typedef struct {
  int integer;
  char string[24];
} RECORD;

extern int errnum;

int main() {
  int errnum = errno;
  int nread; // number of bytes read by read()

  const char RECORD_FORMAT[] = "RECORD-%d";
  const int BUFFER_SIZE = sizeof(RECORD_FORMAT);
  FILE* fp;
  char* userBuffer;
  userBuffer = (char *) malloc(100 * sizeof(char));
  int userResponse = 0;

  fp = fopen("records.dat", "w");
  
  if(fp == NULL) {
    fprintf(stderr, "Error in opening the file.\nValue of errno: %d\n", errnum);
    exit(EXIT_FAILURE);
  }

  printf("Populating records.dat with Records...\n");

  for(int i = 1; i < 101; ++i){
    RECORD currRecord;
    currRecord.integer = i;

    sprintf(currRecord.string, "RECORD-%d\n", i);
    
    fwrite(currRecord.string, 1, BUFFER_SIZE, fp);
    //fwrite(currRecord, sizeof(currRecord), 100, fp);
  }

  printf("Success: Finished populating records.dat\n");

  /*printf("Enter the Record Number you would like to change: \n");

  nread = read(0, userBuffer, 128);
  userBuffer[nread] = '\0';
  */
  if(nread == -1 ){
    fprintf(stderr, "Error occured in reading user input, errno value is: %d\n", errnum);
    fclose(fp);
    exit(EXIT_FAILURE);
  }

  //printf("User Input: %d\n", userBuffer);

  fclose(fp);

  exit(EXIT_SUCCESS);
}
