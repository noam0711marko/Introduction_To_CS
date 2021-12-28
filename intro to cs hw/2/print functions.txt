#include <stdio.h>

void printGradesOpening(){
    printf("Please enter the grades of the examinees");
    printf(" followed by the expected mean\n");
}

void printOldGrades(double grades[], int num_of_grades){
    printf("Old grades: ");
    printGrades(grades, num_of_grades);
}

void printOldGradesStatistics(double min, double max,
                              double mean, double std){
    printf("Old minimum grade: %.1f\n", min);
    printf("Old maximum grade: %.1f\n", max);
    printf("Old mean: %.1f\n", mean);
    printf("Old standard deviation: %.1f\n",std);

}

void printNewGrades(double grades[], int num_of_grades){
    printf("New grades: ");
    printGrades(grades, num_of_grades);
}

void printNewGradesStatistics(double min, double max,
                              double mean, double std){
    printf("New minimum grade: %.1f\n", min);
    printf("New maximum grade: %.1f\n", max);
    printf("New mean: %.1f\n", mean);
    printf("New standard deviation: %.1f\n", std);
}