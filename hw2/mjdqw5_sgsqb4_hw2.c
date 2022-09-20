#include "input_error.h"
#include <stdio.h>
#include <stdlib.h>

int getLength(FILE* fp);
char* allocate_array(int size);
char* read_file(FILE*fp, char* file_name);
/* macros to test against an invalid character */
// #define IS_UPPER_LETTER(x) (x >= 'a' && x <= 'z')
// #define IS_LOWER_LETTER(x) (x >= 'A' && x <= 'Z')
/** Compiling
   all: queue.o elevator.o
      gcc queue.o elevator.o

   queue.o: queue.c queue.h
      gcc -Wall -Werror -g -c queue.c

   elevator.o: elevator.c
      gcc -Wall -Werror -g -c elevator.c

   clean: 
      rm *.o *.out
*/

/** function for converting strings to integers
   bool string_to_int(const char *str, int *converted_value){
      if (str && converted_value != NULL){   // first check
         // strtol(const char*nptr, char**endptr, int base);
         if (INT_MAX <= strtol(str, (char**)NULL, 10)){
            return false; 
         } 
         *converted_value = atoi(str);
         return true;
      }
      return false; 
   }
*/

/** RETURN ERRORS:
   enum error {
    INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS = 1,
    INPUT_FILE_FAILED_TO_OPEN,
    INPUT_FILE_FAILED_TO_CLOSE,
    PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED,
    PARSING_ERROR_EMPTY_FILE,
   };
*/

 int main(int argc, char*argv[]){
    
   FILE*fp = NULL; 
   
   printf("enter a file name with the extension: \n");
   if(argc != 1){
      exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
   }
   char*data = read_file(fp, argv[0]);
   data++;
 }

char* read_file(FILE*fp, char* file_name){
   char *tempArray = NULL;
   scanf("%s", file_name);
   fp = fopen(file_name, "r");
   // fp = fopen("input_file1.txt", "r");
   if (fp == NULL){  // file ptr check
      exit(INPUT_FILE_FAILED_TO_OPEN);
   }
   
   int size = getLength(fp);
   tempArray = allocate_array(size);
   size_t i = 0;
   while(fscanf(fp,"%[^\0]",&tempArray[i]) != EOF){
      // fscanf(fp,"%[^\n]",&tempArray[i]);
      printf("%s", &tempArray[i]);
      i++;
      
   }
   if (!fclose(fp)){
      exit(INPUT_FILE_FAILED_TO_CLOSE);
   }
   
   return tempArray;
}


/*fseek(fp,0L,SEEK_END)
long int size = ftell(fp)
*/


int getLength(FILE* fp){
   int lineCount= 0;
   for(char c = getc(fp); c != EOF; c=getc(fp)){
      if(c == '\n'){
         lineCount++;
      }
   }
   rewind(fp);
   
   return lineCount;
}



char* allocate_array(int size){
   char* temp;
   temp = (char*)malloc(sizeof(char)*size);
   if (temp == NULL){
      free(temp);
      return temp;
   }
   return temp;
}