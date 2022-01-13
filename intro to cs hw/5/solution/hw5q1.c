#include <stdio.h>
#include <stdlib.h>

#define NONE -1
#define DUMMY_SIZE 1000000

//========================================= Declarations and Documentations: =========================================//

//gets the size of the array from user
void getArraySize(int* array_size);

//allocates an array in the requested size and returns it.
int* allocateArray(int array_size);

//gets the array from user
void getArray(int* array, int array_size);

//print a massage which asks the user to enter requested size for array
void printEnterLength();

//print a massage which asks the user to enter array
void printEnterArray();

//combines all the above functions and returns the allocated array.
int* getParameters(int* array_size);

//merge function for merge sorting
//parameters: arr - array to sort, l - left verge of array, r - right verge of array, m - middle of the array
void merge(int arr[], int l, int m, int r);

//merge sorting an array - parameters: arr - array to sort, l - left verge of array, r - right verge of array
void mergeSort(int arr[], int l, int r);

//checks if the array is recommended, and if so, returns the x it's recommended for
int isRecommendedFor(int* array, int array_size);

//prints if the array is recommended, and if so, prints also the x it's recommended for
void printRecommended(int* array, int array_size);

//====================================================================================================================//
//================================================ Implementations: ==================================================//

void getArraySize(int* array_size){
    scanf(" %d", array_size);
}

int* allocateArray(int array_size){
    int* array=(int*)malloc(sizeof(int)*array_size);
    return array;
}

void getArray(int* array, int array_size){
    for(int i=0; i<array_size; i++){
        scanf(" %d", &array[i]);
    }
}

void printEnterLength(){
    printf("Enter the length of the array:\n");
}

void printEnterArray(){
    printf("Enter the array:\n");
}

int* getParameters(int* array_size){
    printEnterLength();
    getArraySize(array_size);
    int* new_array=allocateArray( *array_size);
    printEnterArray();
    getArray(new_array, *array_size);
    return new_array;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[DUMMY_SIZE], R[DUMMY_SIZE];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int isRecommendedFor(int* array, int array_size){
    int rec_to_check=0;
    for(int i=array_size-1; i>=0; i--){
        rec_to_check++;
        if(array[i]>=rec_to_check && array[i-1]<rec_to_check){
            return rec_to_check;
        }
    }
    return NONE;
}

void printRecommended(int* array, int array_size){
    int x= isRecommendedFor(array, array_size);
    if(x!=NONE){
        printf("The array is recommended and x = %d\n", x);
        return;
    }
    printf("The array is not recommended\n");
}


//====================================================================================================================//

int main() {
    int array_size;
    int* array=getParameters(&array_size);
    if(array==NULL){
        return 1;
    }
    mergeSort(array,0,array_size-1);
    printRecommended(array, array_size);

    free(array);
    return 0;
}
