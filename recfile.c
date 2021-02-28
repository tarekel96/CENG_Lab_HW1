#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
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
  FILE* fp;
  char recordNumberBuffer[128]; // first user input captured - record they want to change
  int recordNumber = 0;
  char newNumberBuffer[128]; // second user input captured - record they want to change
  int newNumber = 0;

  fp = fopen("records.dat", "w");
  
  // terminates program if there is an error open file and returns error message
  if(fp == NULL) {
    fprintf(stderr, "Error in opening the file.\nValue of errno: %d\n", errnum);
    exit(EXIT_FAILURE);
  }

  printf("Populating records.dat with Records...\n");

  // populating records.data with 100 RECORD struct instances
  for(int i = 1; i < 101; ++i){
    RECORD currRecord; // init current record

    // assign values to RECORD struct instance
    currRecord.integer = i; // assign number to record
    sprintf(currRecord.string, "RECORD-%d", i); // assign string to record
    // write out current record to records.dat
    fwrite(&currRecord, sizeof(RECORD), 100, fp);
  }

  printf("Success: Finished populating records.dat\n");
  fclose(fp); // close file to save

  // capture first user input - record number want to change
  printf("Enter the record number you want to update: \n");
  // input error handling
  if(fgets(recordNumberBuffer, sizeof(recordNumberBuffer), stdin) == NULL){
    printf("ERROR: User input was not successfully collected\n");
    exit(EXIT_FAILURE);
  }
  // collect user input
  else{
    sscanf(recordNumberBuffer, "%d", &recordNumber);
    printf("Successfully captured input.\nYou entered %d\n", recordNumber);
  }
  // capture second user input - number want to assign to record
  printf("Enter the new number you want to assign the record: \n");
  // input error handling
  if(fgets(newNumberBuffer, sizeof(newNumberBuffer), stdin) == NULL){
    printf("ERROR: User input was not successfully collected\n");
  }
  // collect user input
  else{
    sscanf(newNumberBuffer, "%d", &newNumber);
    printf("Successfully captured input.\nYou entered: %d\n", newNumber);
  }

  fp = fopen("record.dat", "w+");
  RECORD newRecord;
  newRecord.integer = newNumber;
  sprintf(newRecord.string, "RECORD-%d", newNumber);

  //fseek(fp, recordNumber, SEEK_SET);
  fseek(fp, recordNumber * sizeof(RECORD), SEEK_SET);
  fwrite(&newRecord, sizeof(RECORD), 1, fp);   

  fclose(fp);

  fp = fopen("records.dat", "r");

  char currentString[8];
  RECORD loopRecord;
  int count = 0;
  while(fread(&loopRecord, sizeof(RECORD), 1, fp)){
    printf("%s\n", loopRecord.string);
    ++count;
  }

  printf("%i\n", count);

  exit(EXIT_SUCCESS);
}
