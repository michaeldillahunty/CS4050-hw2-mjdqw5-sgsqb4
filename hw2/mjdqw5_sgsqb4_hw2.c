#include <stdio.h>
#include "input_error.h"

int main(){
   
}

int input_file(FILE*fp, char*argv[]){
   char filename[100];
   printf("Enter filename to be used as input: ");
   scanf("%s", filename):

   fp = fopen(filename, "wr");
}

/* 
all: queue.o elevator.o
	gcc queue.o elevator.o

queue.o: queue.c queue.h
	gcc -Wall -Werror -g -c queue.c

elevator.o: elevator.c
	gcc -Wall -Werror -g -c elevator.c

clean: 
	rm *.o *.out
*/