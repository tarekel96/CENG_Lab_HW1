#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// RECORD struct definition
#define NRECORDS 100
typedef struct {
  int integer;
  char string[24];
} RECORD;

// var holding errno value
extern int errnum;

int main(int argc, char* argv[]) {
  if(argc != 3){
    printf("ERROR: No arguments were provided.\n Please enter 2 arguments.\n");
    exit(EXIT_FAILURE);
  }

  int errnum = errno;
  int nread; // number of bytes read by read()
  FILE* fp; // file stream pointer
  char recordNumberBuffer[128]; // first user input captured - record they want to change
  int recordNumber = (int)argv[1]; // record number of the record user wants to update
  char newNumberBuffer[128]; // second user input captured - record they want to change
  int newNumber = (int)argv[2]; // new record number value user wants to assign

  fp = fopen("records.dat", "w"); // write mode
  
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
    fwrite(&currRecord, sizeof(RECORD), 1, fp);
    // args: [point where data is being stored, size of object, count, file pointer
  }

  printf("Success: Finished populating records.dat\n");
 
  fclose(fp); // close file to save
 
  fp = fopen("records.dat", "r+"); // read/update mode

  // create the new record struct instance
  RECORD newRecord;
  // assign user input values to struct instance fields
  newRecord.integer = newNumber;
  sprintf(newRecord.string, "RECORD-%d", newNumber);

  // fseek args: [file pointer, number of bytes to offset by, origin]

  fread(&newRecord, sizeof(RECORD), 1, fp); 
  int nfseek = fseek(fp, recordNumber * sizeof(RECORD), SEEK_SET);
  printf("nfseek: %i\n",nfseek);
  //fflush(fp);
  fwrite(&newRecord, sizeof(RECORD), 1, fp);
 
  fclose(fp);
/* 
  printf("newRecord number: %i\n", newRecord.integer);
  printf("newRecord string: %s\n", newRecord.string);
*/
  fp = fopen("records.dat", "r");

  char currentString[8];
  RECORD loopRecord;
  int count = 0;
  while(fread(&loopRecord, sizeof(RECORD), 1, fp)){
    printf("%s\n", loopRecord.string);
    ++count;
  }

  printf("%i\n", count);

  fclose(fp);

  exit(EXIT_SUCCESS);
}
