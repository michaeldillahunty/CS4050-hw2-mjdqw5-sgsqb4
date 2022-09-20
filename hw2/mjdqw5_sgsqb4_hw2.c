#include "input_error.h"
#include <stdio.h>
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

int main(){
   
}

int readFile(FILE* fp,char* a)
{
   int i = 0;
   char [100] fileName;
   printf("input filename: ");
   scanf("%s",fileName);
   fp = fopen(fileName,'r');
   if (fp == NULL) 
      return -1; // return -1 on file open failure
   while (fscanf(fp, "%[^\n] ", a) != EOF) {
        
    }



}


/** Function to find the x-th smallest element
   \param data: current values in the array
   \param target: x-th smallest element in the array
   \param elem_size:  the size of the array
   \param count: number of elements in the array 
*/
int array_locate(void*data, void*target, int size, int count){
   
}