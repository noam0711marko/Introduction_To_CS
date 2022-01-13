#include <stdio.h>

#define DIMENSION 5
#define EMPTY -1

//========================================= Declarations and Documentations: =========================================//

//print a massage which asks the user to enter matrix
void printEnterMatrix();

//gets the matrix from user
void getMatrix(int matrix[DIMENSION][DIMENSION]);

//combines all the above functions and returns the allocated array.
void getParameters(int matrix[DIMENSION][DIMENSION]);

//copies a matrix without specific row and column to another matrix
void copyMatrix(int copy_from[DIMENSION][DIMENSION], int dimension, int copy_to[DIMENSION][DIMENSION], int curr_column);

//counts number of results by using backtracking
int getResult(int matrix[DIMENSION][DIMENSION], int new_dimension);

//prints the number of possibilities counted
void printResult(int res);

//====================================================================================================================//
//================================================ Implementations: ==================================================//

void printEnterMatrix(){
    printf("Enter the matrix:\n");
}

void getMatrix(int matrix[DIMENSION][DIMENSION]){
    for(int i=0; i<DIMENSION; i++){
        for(int j=0; j<DIMENSION; j++){
            scanf(" %d", &matrix[i][j]);
        }
    }
}

void getParameters(int matrix[DIMENSION][DIMENSION]){
    printEnterMatrix();
    getMatrix(matrix);
}

void copyMatrix(int copy_from[DIMENSION][DIMENSION], int dimension, int copy_to[DIMENSION][DIMENSION], int curr_column){
    int new_dimension=dimension-1;
    for(int row=0; row<DIMENSION; row++){
        if(row>=new_dimension){
            for(int col=0; col<DIMENSION; col++){
                copy_to[row][col]=EMPTY;
            }
        }
        int old_col=0;
        int new_col=0;
        while(new_col<new_dimension){
            if(old_col==curr_column){
                old_col++;
                continue;
            }
            copy_to[row][new_col]=copy_from[row+1][old_col];
            new_col++;
            old_col++;
        }
        while(new_col<DIMENSION){
            copy_to[row][new_col]=EMPTY;
            new_col++;
        }
    }
}

int getResult(int matrix[DIMENSION][DIMENSION], int dimension){
    if(dimension == 0) return 0;
    if(dimension == 1 && matrix[0][0] == 1) return 1;
    int counter=0;
    for(int j=0; j < dimension; j++){
        if(matrix[0][j]==0){
            continue;
        }
        else{
            int new_matrix[DIMENSION][DIMENSION];
            copyMatrix(matrix, dimension, new_matrix, j);
            counter+= getResult(new_matrix, dimension - 1);
        }
    }
    return counter;
}

void printResult(int res){
    printf("The result is %d\n", res);
}



//====================================================================================================================//
int main() {
    int matrix[DIMENSION][DIMENSION];
    getParameters(matrix);
    printResult(getResult(matrix, DIMENSION));
    return 0;
}
