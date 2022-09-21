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
    X INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS = 1,
    X INPUT_FILE_FAILED_TO_OPEN,
    X INPUT_FILE_FAILED_TO_CLOSE,
    X PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED,
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
   if(argc != 1){
      printf("ERROR: INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS\n");
      exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
   } 

   int* data1 = read_file(fp, argv[0], size); // read integers into array with the beginnging of file(x) 
   printf("%dth smallest is %d\n",data1[0], xthSmallest(data1, 0, *size-1, data1[0]));  // output
   freeArray(data1); // free memory allocated
}
 
   // function that reads file into an int array
int* read_file(FILE*fp, char* file_name, int* arr_size){
   int *tempArray = NULL;  // init temp array to store converted values in
   scanf("%s", file_name); // scanf for user input filename
   
   fp = fopen(file_name, "r");   // open file in read
   if (fp == NULL){  // valid file ptr check 
      printf("ERROR: INPUT_FILE_FAILED_TO_OPEN\n");
      exit(INPUT_FILE_FAILED_TO_OPEN);
   }
   
   int size = getLength(fp); // use getLength() function to set the size of the array
   *arr_size = size; // store array size
   tempArray = allocate_array(size); // allocate memory for tempArray
   size_t i = 0;  // counter variable 
   int x;
   char str[MAX_VAL]; // 
   // while(fscanf(fp, "%[^\0]", &tempArray[i]) != EOF){
   while (fgets(str, MAX_VAL, fp)){ // read from file and store in str array
      if (isdigit(str[0])){   // check if value is a digit
         x = atoi(str); // convert string to integers
         tempArray[i] = x; // store converted ints in tempArray
         i++;
      } else if (str[0] == '-' || str[0] == ',' || str[0] == '.') { // error check for invalid characters
         printf("ERROR: PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED\n");
         exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
      } else if (fgetc(fp) == EOF) {   // error check if file is empty
         printf("ERROR: PARSING_ERROR_EMPTY_FILE\n");
         exit(PARSING_ERROR_EMPTY_FILE);
      }
   }
   if (fclose(fp) != 0){ // if the file fails to close
      printf("ERROR: INPUT_FILE_FAILED_TO_CLOSE\n");
      exit(INPUT_FILE_FAILED_TO_CLOSE);
   } else fclose(fp);
   return tempArray;
}

// funciton to get length of file 
int getLength(FILE* fp){
   int lineCount= 0; 
   for(char c = getc(fp); c != EOF; c=getc(fp)){ // loop to get next value from file until the end of file
      if(c == '\n'){ // if it's reached the new line char
         lineCount++; // go to next line
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
// reference: https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-3-worst-case-linear-time/
void swap(int*a, int*b){
   int temp = *a; 
   *a = *b;
   *b = temp; 
}

// find median of an array
int getMedian(int arr[], int n, int x){
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

/* function to return x-th smallest value in array */ 
int xthSmallest(int arr[], int left, int right, int x){
   if (x>0 && x<=right-left+1){  // if x < the # of elems in array
      int curr = partition(arr, left, right); // partition the array to get pivot element
      if (curr - left == x - 1){ // check if current node is the same as x
         return arr[curr];         
      }
      if (curr-left > x-1){ // if curr position is > than x
         return xthSmallest(arr, left, curr-1,x); // recursion to get the left sub array
      } 
      return xthSmallest(arr, curr+1, right, x-curr+left-1); // else recursively get right sub array
    }
    return -1; // return on failure 
}

/* partition function to search for x in the array, which then partitions the array around x node */
/* reference: https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-3-worst-case-linear-time/ */
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
   a = NULL; 
   return NULL;
}
