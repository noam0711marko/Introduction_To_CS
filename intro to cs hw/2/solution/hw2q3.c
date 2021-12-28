#include <stdio.h>

#define TWO 2
#define NUM_OF_GRADE_OPTIONS 9

char getChar(){
    char symbol;
    printf("Please enter a character:\n");
    scanf(" %c", &symbol);

    return symbol;
}

char getAxis(char axis){
    if(axis=='U' || axis=='D' || axis=='R' || axis=='L'){
        return axis;
    }
    printf("Please enter histogram axis:(U/D/R/L)");
    scanf(" %c", &axis);
    while (axis!='U' && axis!='D' && axis!='R' && axis!='L'){
        printf("\nWrong direction, try again!\n");
        printf("Please enter histogram axis:(U/D/R/L)");
        scanf(" %c", &axis);
    }
    return axis;
}


void initArray(int array[][TWO]){
    for (int i=0; i<NUM_OF_GRADE_OPTIONS; i++){
        array[i][0]=i+1;
        array[i][1]=0;
    }
}

int maxAmountOfGrade(int array[][TWO]){
    int max=0;
    for (int i=0; i<NUM_OF_GRADE_OPTIONS; i++){
        if(array[i][1]>max){
            max=array[i][1];
        }
    }
    return max;
}

void printNumberInRow(){
    int i=0;
    for( ; i<NUM_OF_GRADE_OPTIONS-1; i++){
        printf("%d ", i+1);
    }
    printf("%d\n", i+1);
}

void printUp(int array[][TWO], char symbol){
    printNumberInRow();
    int max_amount_gotten= maxAmountOfGrade(array);
    int i=0;
    for (int j=1; j<=max_amount_gotten; j++) {
        for (i=0; i < NUM_OF_GRADE_OPTIONS - 1; i++) {
            if (array[i][1] >= j) {
                printf("%c ", symbol);
            } else {
                printf("  ");
            }
        }
        if (array[i][1] == j) {
            printf("%c\n", symbol);
        } else {
            printf(" \n");
        }
    }
}

void printDown(int array[][TWO], char symbol){
    int max_amount_gotten= maxAmountOfGrade(array);
    int i=0;
    for (int j=max_amount_gotten; j>=1; j--) {
        for (i=0; i < NUM_OF_GRADE_OPTIONS - 1; i++) {
            if (array[i][1] >= j) {
                printf("%c ", symbol);
            }
            else {
                printf("  ");
            }
        }
        if (array[i][1] >= j) {
            printf("%c\n", symbol);
        } else {
            printf(" \n");
        }
    }
    printNumberInRow();
}

void printLeft(int array[][TWO], char symbol){
    for (int i=0; i<NUM_OF_GRADE_OPTIONS; i++){
        printf("%d", i+1);
        int num_gotten=array[i][1];
        int max_amount_gotten = maxAmountOfGrade(array);
        int j=0, counter=0;
        for(; j<num_gotten; j++){
            printf(" %c", symbol);
        }
        for(; j<max_amount_gotten; j++){
            printf("  ");
            counter++;
        }
        printf("\n");
    }
}

void printRight(int array[][TWO], char symbol){
    int max_amount_gotten = maxAmountOfGrade(array);
    for (int i=0; i<NUM_OF_GRADE_OPTIONS; i++){
        for(int j=max_amount_gotten; j>=1; j--){
            if (array[i][1] >= j) {
                printf("%c ", symbol);
            }
            else {
                printf("  ");
            }
        }
        printf("%d\n", i+1);
    }
}

void printHistogram(int array[][TWO], char symbol, char axis){
    printf("Histogram:\n");
    if(axis=='U'){
        printUp(array,symbol);
    }
    if(axis=='D'){
        printDown(array,symbol);
    }
    if(axis=='L'){
        printLeft(array,symbol);
    }
    if(axis=='R'){
        printRight(array,symbol);
    }
}



int main() {
    int array[NUM_OF_GRADE_OPTIONS][TWO];
    char symbol=getChar();
    char axis='\n';
    axis= getAxis(axis);
    initArray(array);
    int grade;
    printf("\nPlease enter grades:\n");
    while (scanf("%d", &grade) != EOF){
        array[grade-1][1]+=1;
    }
    printHistogram(array,symbol,axis);
    return 0;
}
