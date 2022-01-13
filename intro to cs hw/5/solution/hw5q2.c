#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//========================================= Declarations and Documentations: =========================================//

//gets the size of the array from user
void getLengthOfArray(int* length);

//print a massage which asks the user to enter requested size for array
void printfEnterLength();

//allocates an array in the requested size and returns it.
char* allocateArray(int length);

//gets the array from user
void getArray(char* array, int length);

//print a massage which asks the user to enter array
void printEnterArray();

//combines all the above functions and returns the allocated array.
char* getParameters(int* length);

//recursive function which determines whether the array is a palindrome or not
//parameters - array - the array to check, first - first indicator array, last - last indicator of array
bool isPalindrome(char* array, int first, int last);

//prints if the array is a palindrome
void printIsPalindrome(char* array, int length);


void getLengthOfArray(int* length){
    scanf(" %d",length);
}

void printfEnterLength(){
    printf("Enter the length of the array:\n");
}

char* allocateArray(int length){
    char* array=(char*)malloc(sizeof(char)*length);
    return array;
}

void getArray(char* array, int length){
    for(int i=0 ; i<length; i++){
        scanf(" %c", &array[i]);
    }
}

void printEnterArray(){
    printf("Enter the array:\n");
}

char* getParameters(int* length){
    printfEnterLength();
    getLengthOfArray(length);
    char* new_array= allocateArray(*length);
    printEnterArray();
    getArray(new_array, *length);
    return new_array;
}

bool isPalindrome(char* array, int first, int last){
    if(first>=last){
        return true;
    }
    if(array[first]!=array[last]){
        return false;
    }
    return isPalindrome(array, first+1, last-1);
}

void printIsPalindrome(char* array, int length){
    if(isPalindrome(array, 0, length-1)){
        printf("A palindrome\n");
        return;
    }
    printf("Not a palindrome\n");
}

int main() {
    int length=0;
    char* array= getParameters(&length);
    if(array==NULL){
        return 1;
    }
    printIsPalindrome(array, length);

    return 0;
}
