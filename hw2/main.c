#include "input_error.h"
#include <stdlib.h>


//driver code
int main(int argc, char*argv[]){
    
   FILE*fp = NULL; 
   int sizz = 0;
   int* size = &sizz;
   int* intArr;

   printf("enter a file name with the extension: \n");
   if(argc != 1){
      exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);

   char*data_char = read_file(fp, argv[0], size);
   
   intArr = convert_array(data_char, *size);
   for(int k = 0;k<*size;k++){
      printf("%d\n",intArr[k]);
   }
   // int converted[];
   //int convert[] = string_to_int(data, &converted);
   //data++;
   printf("xth smallest is %d\n", xth_smallest(intArr, 0, *size-1, intArr[0]));
}