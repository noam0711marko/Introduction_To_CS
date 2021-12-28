#include <stdio.h>
#include <stdbool.h>

#define N 4

//I wrote a boolian function to every "strong" check - up,down,left and right 
bool biggerThanBelow(int mat[N][N], int row, int column){
    return mat[row][column]>mat[row+1][column];
}

bool biggerThanUpper(int mat[N][N], int row, int column){
    return mat[row][column]>mat[row-1][column];
}

bool biggerThanLeft(int mat[N][N], int row, int column){
    return mat[row][column]>mat[row][column-1];
}

bool biggerThanRight(int mat[N][N], int row, int column){
    return mat[row][column]>mat[row][column+1];
}

/*I wrote boolian function for the exrteme cases:
 * if the number's place is on the edge of the matrix, it doesn't have the 4 "neighbors" that are required
   check. for example: all top row doesn't have any number above them
 *therefore, I made a specific function to each extreme case that needed a different treatment (corners, first
  and last row and column) and than a function to the normal case with all 4 neighbors check.
*/
bool leftUpCorner(int mat[N][N], int row, int column){
    bool res=biggerThanBelow(mat,row,column) &&
        biggerThanRight(mat,row,column);
    return res;
}

bool rightUpCorner(int mat[N][N], int row, int column){
    bool res=biggerThanBelow(mat,row,column) &&
        biggerThanLeft(mat,row,column);
    return res;
}

bool leftDownCorner(int mat[N][N], int row, int column){
    bool res=biggerThanUpper(mat,row,column) &&
        biggerThanRight(mat,row,column);
    return res;
}

bool rightDownCorner(int mat[N][N], int row, int column){
    bool res=biggerThanUpper(mat,row,column) &&
        biggerThanLeft(mat,row,column);
    return res;
}

bool firstRowNotCorner(int mat[N][N], int row, int column){
    bool res=biggerThanBelow(mat,row,column) &&
        biggerThanLeft(mat,row,column) &&
        biggerThanRight(mat,row,column);
    return res;
}

bool lastRowNotCorner(int mat[N][N], int row, int column){
    bool res=biggerThanUpper(mat,row,column) &&
        biggerThanLeft(mat,row,column) &&
        biggerThanRight(mat,row,column);
    return res;
}

bool firstColumnNotCorner(int mat[N][N], int row, int column){
    bool res=biggerThanBelow(mat,row,column) &&
        biggerThanUpper(mat,row,column) &&
        biggerThanRight(mat,row,column);
    return res;
}

bool lastColumnNotCorner(int mat[N][N], int row, int column){
    bool res=biggerThanBelow(mat,row,column) &&
        biggerThanUpper(mat,row,column) &&
        biggerThanLeft(mat,row,column);
    return res;
}

bool atCenterOfMatrix(int mat[N][N], int row, int column){
    bool res=biggerThanBelow(mat,row,column) &&
        biggerThanUpper(mat,row,column) &&
        biggerThanRight(mat,row,column) &&
        biggerThanLeft(mat,row,column);
    return res;
}

// I seperated the check by rows - first, last and inside rows
bool firstRow(int mat[N][N], int row, int column){
    bool res= (column==0 && leftUpCorner(mat,row,column)) ||
            (column==N-1 && rightUpCorner(mat,row,column)) ||
            firstRowNotCorner(mat,row,column);
    return res;
}

bool lastRow(int mat[N][N], int row, int column){
    bool res= (column==0 && leftDownCorner(mat,row,column)) ||
            (column==N-1 && rightDownCorner(mat,row,column)) ||
            lastRowNotCorner(mat,row,column);
    return res;

}

bool insideRows(int mat[N][N], int row, int column){
    bool res= (column==0 && firstColumnNotCorner(mat,row,column)) ||
              (column==N-1 && lastColumnNotCorner(mat,row,column)) ||
            atCenterOfMatrix(mat,row,column);
    return res;
}

//the first function that I was asked to create
int is_strong(int mat[N][N], int row, int column){
    bool res= (row==0 && firstRow(mat,row,column)) ||
              (row==N-1 && lastRow(mat,row,column)) ||
            insideRows(mat,row,column);
    return res;
}


//the second function that I was asked to create
/* explanation:
 * if column is last one - res is 0*something => res=0 (as asked).
 * else, it's 1*expression, and that expression is:
 * if the element is bigger than his neighbor from the right: the expression means 1*(left-right)+0*(right-left).
 * else, the expression means 0*(left-right)+1*(right-left).
 * on total, we get absolute result of the subtraction (and 0 if the subtraction is illegal).
 */
int space_rank (int mat[N][N], int row, int column){
    int res=(column!=N-1)*((mat[row][column]>mat[row][column+1])*
            (mat[row][column]-mat[row][column+1])+
            (mat[row][column]<mat[row][column+1])*
            (mat[row][column+1]-mat[row][column]));

    return res;
}


int main() {
    int mat[N][N];
    printf("Please enter a matrix:\n");
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            scanf("%d", &mat[i][j]);
        }
    }
    int strong_counter=0;
    int space_rank_counter=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            strong_counter+=is_strong(mat,i,j);
            space_rank_counter+= space_rank(mat,i,j);
        }
    }
    printf("Strong elements: %d\n", strong_counter);
    printf("Space rank: %d\n", space_rank_counter);

    return 0;
}
