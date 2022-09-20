#include "input_error.h"
#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647

int getLength(FILE* fp);
char* allocate_array(int size);
char* read_file(FILE*fp, char* file_name, int*arr_size);
int partition(int arr[], int left, int right, int x);
int xth_smallest(int arr[], int left, int right, int x);
int getMedian(int arr[], int n);
int compare(const void*c,const void* d);
void swap(int*a, int*b);
int string_to_int(char *str, int *converted_value);
int* convert_array(char* cArr, int size);
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
//driver code
 int main(int argc, char*argv[]){
    
   FILE*fp = NULL; 
   int sizz = 0;
   int* size = &sizz;
   int* intArr;

   printf("enter a file name with the extension: \n");
   if(argc != 1){
      exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
   }
   
   char*data_char = read_file(fp, argv[0], size);
   
   intArr = convert_array(data_char,*size);
   for(int k = 0;k<*size;k++){
      printf("%d\n",intArr[k]);
   }
   // int converted[];
   //int convert[] = string_to_int(data, &converted);
   //data++;
   printf("xth smallest is %d\n", xth_smallest(intArr, 0, *size-1, intArr[0]));
 }

char* read_file(FILE*fp, char* file_name, int* arr_size){
   char *tempArray = NULL;
   scanf("%s", file_name);
   
   fp = fopen(file_name, "r");
   // fp = fopen("input_file1.txt", "r");
   if (fp == NULL){  // file ptr check
      exit(INPUT_FILE_FAILED_TO_OPEN);
   }
   
   int size = getLength(fp);
   *arr_size = size;
   tempArray = allocate_array(size);
   size_t i = 0;
   while(fscanf(fp,"%[^\0]",&tempArray[i]) != EOF){
      // fscanf(fp,"%[^\n]",&tempArray[i]);
     // printf("%s", &tempArray[i]);
      i++;
      
   }
   
   
   
 
   return tempArray;
}

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

int partition(int arr[],int left,int right,int x){
   int i = 0;
   
   while(i<right){
      if (arr[i]==x){
         break;
      }
      i++;
   }
   swap(&arr[i],&arr[right]);
   
   i = right;
   int j = left;
   while(j<=(right-1)){
      if(arr[j]<=x){
         swap(&arr[i], &arr[j]);
         i++;
      }
   }
   swap(&arr[i],&arr[right]);


   return i;
   
}

void swap(int*a, int*b){
   int temp = *a;
   *a = *b;
   *b = temp; 
}

int xth_smallest(int arr[], int left, int right, int x){



   if (x<0 && x<=right-1+1){
      int num = right-+1;  // number of elements in arr
      int median[(num+4)/5]; // split into (n+4)/5 groups
      int i;
      for(i=0; i<(num/5); i++){
         median[i] = getMedian(arr+1+i*5, num%5);
         if(i*5 < num){ // last group with < 5 elements
            median[i] = getMedian(arr+1+i*5, num%5);
            i++;
         }
      }
      /* find median of medians recursively */
      int median_of_medians;
      if (i == 1){ // if median array only has one element, then don't use recursive call
         median_of_medians = median[i-1];
      } else {
         median_of_medians = xth_smallest(median, 0, i-1, i/2);
      }
      
      int position = partition(arr, 1, right, median_of_medians);
      if (position-1 == x-1){ // if current position is same as x
         return arr[position];
      } else if (position-1 > x-1){ // else if the position is greater, recursive call for left subarr
         return xth_smallest(arr, 1, position-1, x);
      }
      return xth_smallest(arr, position+1, right, x-position+1-1); // else recursive call for right subarr
   }
   return INT_MAX; // if x is greater than the # of elements in the arr
}

// find median of an array
int getMedian(int arr[], int n){
   qsort(arr, n, sizeof(int), compare);
   return arr[n/2];
}

// comparator function for quick select
int compare(const void*c,const void* d){
   int* a = (int*)c;
   int* b = (int*)d;
   return *a-*b;
}

/* long int strtol(const char *str, char **endptr, int base)
   str = string containing the representation of an integeral num
   endptr = value is set by the function to the next character in str after the numerical val
   base = must be between 2 and 36 inclusive, or special val 0 
*/
// https://www.ibm.com/docs/en/i/7.1?topic=lf-strtol-strtoll-convert-character-string-long-long-long-integer
// https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm (atoi())
int string_to_int(char *str, int *converted_value){
   if (str && converted_value != NULL){   // first check
      // strtol(const char*nptr, char**endptr, int base);
      if (INT_MAX <= strtol(str, (char**)NULL, 10)){
         return -1; 
      } 
      *converted_value = atoi(str);
      return 0;
   }
   return 1; 
}

int* convert_array(char* cArr, int size){
   
   int *res; 
   res = malloc(sizeof(int)*size); 
   if (res == NULL){
      return NULL;
   }
   for (int i=0; i<size; i++){   
         string_to_int(&cArr[i], res);
   }
   return res;
}