#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
/*
 * @name: recfile.c
 * @authors: Tarek El-Hajjaoui & Tavid Terizan
 * @version: 1.0
*/

// RECORD struct definition
#define NRECORDS 100
typedef struct {
  int integer;
  char string[24];
} RECORD;

// var holding errno value
extern int errnum;

int main(int argc, char* argv[]) {

  int errnum = errno, nread;
  int recordNumber, newNumber; // record number of the record user wants to update
  char recordNumberBuffer[128], newNumberBuffer[128], out[24]; // first user input captured - record they want to change
  bool check = 1;
  FILE* fp; // file stream pointer  
  RECORD currRecord; // init current record
  
  fp = fopen("records.dat", "w"); // write mode
  
  // terminates program if there is an error open file and returns error message
  if(fp == NULL) {
    fprintf(stderr, "Error in opening the file.\nValue of errno: %d\n", errnum);
    exit(EXIT_FAILURE);
  }

  printf("Populating records.dat with Records");
                                                      // populating records.data with 100 RECORD struct instances
  for(int i = 1; i < 101; ++i){
    if(i == 33 || i == 66 || i == 99){
      printf(".");
    }
    currRecord.integer = i;                           // assign number to record
    sprintf(currRecord.string, "RECORD-%d", i);       // assign string to record
    fwrite(&currRecord, sizeof(currRecord), 1, fp);   // write out current record to records.dat
  }
  fclose(fp);                                         // close file to save
  printf("\nSuccess: Finished populating records.dat\n");
  
  if(argc != 3){                                      // if no arguments entered prompt user for information
   while(1){
       printf("Enter the record number you want to update\nRecord Number: ");
       read(0, (void*)recordNumberBuffer, 128);
       sscanf(recordNumberBuffer, "%d", &recordNumber);
       if(recordNumber < 1 || recordNumber > 100){    // check to make sure record is in directory
         printf("Make sure number is between 1 & 100\n");
       }
       else
       {
         break;
       }
    }
    printf("What would you like to update it to?\nEntry: ");
    read(0, (void*)newNumberBuffer, 128);
    sscanf(newNumberBuffer, "%d", &newNumber);
  }
  else                                                // else use arguments provided in command prompt
  {
   recordNumber = atoi(argv[1]);    
   newNumber = atoi(argv[2]);
  }

  fp = fopen("records.dat", "r+");                    // open for read/write
  fseek(fp, (recordNumber-1)*sizeof(RECORD), SEEK_SET);        // find location of record and read into variable
  fread(&currRecord, sizeof(currRecord), 1, fp);
  
  currRecord.integer = newNumber;                        // overwrite variables
  sprintf(currRecord.string, "RECORD-%d", newNumber); 
  fseek(fp, (recordNumber-1)*sizeof(RECORD), SEEK_SET);
  fwrite(&currRecord, sizeof(RECORD), 1, fp);            // write back to file
  
  fseek(fp, 0, SEEK_SET);                                // reset pointer to beginning of file
  for(int i = 0; i < 100; ++i){
   fread(&currRecord, sizeof(RECORD), 1, fp);
   sprintf(out, "%s\n", currRecord.string);
   write(1, out, strlen(out));                           // print entire directory to screen
  }
 
  fclose(fp);

  exit(EXIT_SUCCESS);
}
