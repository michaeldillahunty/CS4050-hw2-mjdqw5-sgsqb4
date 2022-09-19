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
