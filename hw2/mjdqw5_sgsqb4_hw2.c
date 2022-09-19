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
   scanf("%s",fileName);

   fp = fopen(fileName,'r');


   while (fp!= EOF) {
      fscanf(fp, "%[^\n] ", a) != EOF);
        
    }
      

   
}
