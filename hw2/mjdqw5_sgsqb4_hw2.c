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
<<<<<<< HEAD
   if (fp == NULL) 
      return -1; // return -1 on file open failure
   while (fscanf(fp, "%[^\n] ", a) != EOF) {
=======


   while (fp!= EOF) {
      fscanf(fp, "%[^\n] ", a) != EOF);
>>>>>>> 27ed452c7fe27a8c6556f10954f83197b79909ff
        
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

