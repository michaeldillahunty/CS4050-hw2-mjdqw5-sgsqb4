#include "input_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define INT_MAX 2147483647
#define MAX_VAL 256
int getLength(FILE* fp);
int* allocate_array(int size);
int* read_file(FILE*fp, char* file_name, int*arr_size);
int partition(int arr[], int left, int right);
int getMedian(int arr[], int n, int k);
int compare(const void*c,const void* d);
void swap(int*a, int*b);
int xthSmallest(int arr[], int left, int right, int x);
void* freeArray(int*);


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
   //intitialzations
   FILE*fp = NULL; 
   int sizz = 0;        
   int* size = &sizz;   
   
   printf("enter a file name with the extension: \n");
   if(argc != 1) 
      exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);

   int* data1 = read_file(fp, argv[0], size); // read integers into array with the beginnging of file(x) 
   printf("%dth smallest is %d\n",data1[0], xthSmallest(data1, 0, *size-1, data1[0]));  // output
   freeArray(data1); // free memory allocated
}
 
   // function that reads file into an int array
int* read_file(FILE*fp, char* file_name, int* arr_size){
   int *tempArray = NULL;  // init temp array to store converted values in
   scanf("%s", file_name); // scanf for user input filename
   
   fp = fopen(file_name, "r");   // open file in read
   // fp = fopen("input_file1.txt", "r");
   if (fp == NULL){  // file ptr check
      exit(INPUT_FILE_FAILED_TO_OPEN);
   }
   
   int size = getLength(fp); // use getLength() function to set the size of the array
   *arr_size = size; // store array size
   tempArray = allocate_array(size); // allocate memory for tempArray
   size_t i = 0;  // counter variable 
   int x;
   char str[MAX_VAL]; // 
   // while(fscanf(fp, "%[^\0]", &tempArray[i]) != EOF){
   while (fgets(str, MAX_VAL, fp)){
      if (isdigit(str[0])){
         x = atoi(str);
         tempArray[i] = x;    
         i++;
      } else if (str[0] == '-' || str[0] == ',' || str[0] == '.' || isalpha(str[0])) {
         exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
      }
   }
   if (fclose(fp) != 0){
      exit(INPUT_FILE_FAILED_TO_CLOSE);
   } else fclose(fp);
   return tempArray;
}

// funciton to get length of file 
int getLength(FILE* fp){
   int lineCount= 0; 
   for(char c = getc(fp); c != EOF; c=getc(fp)){ 
      if(c == '\n'){
         lineCount++;
      }
   }
   rewind(fp);   // put file pointer back at the beginning of file after looping througn
   return lineCount+1;
}

// function that dynamically allocates an int array given a size
int* allocate_array(int size){
   int* temp; 
   temp = (int*)malloc(sizeof(int)*size);
   if (temp == NULL){ // error check malloc
      free(temp);
      return temp;
   }
   return temp;
}

// function that swaps 2 integer values
void swap(int*a, int*b){
   int temp = *a; 
   *a = *b;
   *b = temp; 
}

// find median of an array
int getMedian(int arr[], int n, int x){
   // quickSort(arr,0,n);
   xthSmallest(arr, 0, n-1, x);
   printf("size of array is: %d\n",n);
      return arr[n/2];
}

// comparator function for quick select
int compare(const void*c,const void* d){
   int* a = (int*)c;
   int* b = (int*)d;
   return *a-*b;
}


int xthSmallest(int arr[], int left, int right, int x){
   if (x>0 && x<=right-left+1){
      int curr = partition(arr, left, right);
      if (curr - left == x - 1){
         return arr[curr];         
      }
      if (curr-left > x-1){
         return xthSmallest(arr, left, curr-1,x);
      } 
      return xthSmallest(arr, curr+1, right, x-curr+left-1);
    }
    return -1;
}

int partition(int arr[], int left, int right){
   int temp_arr = arr[right];
   int i = left;
    for (int j = left; j <= right - 1; j++) {
        if (arr[j] <= temp_arr) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

// function that frees our malloced a
void* freeArray(int* a){
   free(a);
   a = NULL;  // ;)
   return NULL;
}
