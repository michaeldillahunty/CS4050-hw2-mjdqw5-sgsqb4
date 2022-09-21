#include "input_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

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
   if(argc != 1){
      printf("ERROR: INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS\n");
      exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
   } 
      



   int* data1 = read_file(fp, argv[0], size); // read integers into array with the beginnging of file(x) 
   
   printf("%dth smallest is %d\n",data1[0], xthSmallest(data1, 0, *size-1, data1[0]));  // print data
   freeArray(data1); // free memory allocated
}
 
// function that reads file into an int array
int* read_file(FILE*fp, char* file_name, int* arr_size){
   int *tempArray = NULL;  // init temp array to store converted values in
   scanf("%s", file_name); // scanf for user input filename
   fp = fopen(file_name, "r"); // open file in read only 
   if (fp == NULL){  // file ptr check
      exit(INPUT_FILE_FAILED_TO_OPEN);
   }
   
   int size = getLength(fp); // use getLength() function to set the size of the array
   *arr_size = size; // store array size
   tempArray = allocate_array(size); // allocate memory for tempArray
   size_t i = 0;  // counter variable 
   int x;
   char str[MAX_VAL]; // max number of characters 
   while (fgets(str, MAX_VAL, fp)){ // loop through file reading each line
      if (isdigit(str[0])){   // check if current character is a decmial number
         x = atoi(str); // convert string to integer 
         tempArray[i] = x; // store converted integer into array
         i++;
         /* error check characters for negative, commas, periods, and letters */
      } else if (str[0] == '-' || str[0] == ',' || str[0] == '.' || isalpha(str[0])) { 
         exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED); // if found, exit with given error code for invalid characters
      }
   }

   if (fclose(fp) != 0){ // check if fp is closed 
      exit(INPUT_FILE_FAILED_TO_CLOSE);   // if not, exit and return given error code 
   } else fclose(fp); // else close file 
   return tempArray; // return the array with converted values
}

// funciton to get length of file 
int getLength(FILE* fp){
   int lineCount= 0; 
   for(char c = getc(fp); c != EOF; c = getc(fp)){ // loop through file and get each char until it reaches the end of the file
      if(c == '\n'){ // if it reaches the new line value, increase line count and go to next
         lineCount++;
      }
   }
   rewind(fp);   // put file pointer back at the beginning of file after looping througn
   return lineCount+1;
}

// function that dynamically allocates an int array given a size
int* allocate_array(int size){
   int* temp; 
   temp = (int*)malloc(sizeof(int)*size); // allocate memory for int array
   if (temp == NULL){ // error check malloc
      free(temp); // if it fails, free memory and return temp ptr
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

/* function to find and return the x-th smallest element */
int xthSmallest(int arr[], int left, int right, int x){
   if (x>0 && x<=right-left+1){  // if x is > than 0 and < the # of elements in the array 
      int curr = partition(arr, left, right); // set a variable to partition function to sort arrays
      if (curr - left == x - 1){ // check if current position is the same as x 
         return arr[curr]; // return current index       
      }
      if (curr-left > x-1){ // if current position is greater than x
         return xthSmallest(arr, left, curr-1,x); // use recursion on the sub-array 
      } 
      return xthSmallest(arr, curr+1, right, x-curr+left-1); // else use recursion on right sub-array
    }
    return INT_MAX; // return INT_MAX if x > the # of elements in the array
}

// reference(ONLY SHOWS PSEUDO CODE): https://www.youtube.com/watch?v=UqVxcO4oNXA 
/* function to sort all elements smaller than the pivot on the left side, and larger than the pivot on the right side */
int partition(int arr[], int left, int right){
   int pivot = arr[right]; // set pivot element as the most right element in the array TEMP_ARR
   int i = left;  // index variable that starts at far left element 
    for (int j = left; j <= right - 1; j++) { // create another index variable and loop through till the [last element - 1]
        if (arr[j] <= pivot) { // check if curr element is <= pivot element
            swap(&arr[i], &arr[j]); // if j <= last element, swap elements of i and j 
            i++;  // go to next element
        }
    }
    swap(&arr[i], &arr[right]); // swap i element with the most right element
    return i;  // pivot element is at i-th index, return index
}

// function that frees our malloced a
void* freeArray(int* a){
   a = NULL;
   free(a); 
   return NULL;
}
