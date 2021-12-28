#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_GRADES 50
#define MAX_STD 10

//as asked
double minMaxGrades(const double array[], const int array_size,
                    bool true_for_min){
    double min=array[0];
    double max=array[0];
    for(int i=1; i<array_size; i++){
        if(array[i]<min){
            min=array[i];
        }
        if(array[i]>max){
            max=array[i];
        }
    }
    if(true_for_min){
        return min;
    }
    return max;
}

//as asked
double meanGrades(const double array[], const int array_size){
    double sum=0;
    for(int i=0; i<array_size; i++){
        sum+=array[i];
    }
    return sum/array_size;
}

//as asked
double stdGrades(const double array[], const int array_size, double mean){
    double sum=0;
    for(int i=0; i<array_size; i++){
        sum+=(array[i]-mean)*(array[i]-mean);
    }
    sum/=array_size;
    double res= sqrt(sum);
    return res;
}

//as asked
void printGrades(const double array[], const int array_size){
    int i=0;
    for(; i<array_size-1; i++){
        printf("%.1f ", array[i]);
    }
    printf("%.1f\n", array[i]);
}

//do the calculations needed to update grades after std error
void updateByStd(double array[], const int array_size,
                  const double max_std, const double current_std){
    double multiplication_factor=max_std/current_std;
    for(int i=0; i<array_size; i++){
        array[i]*=multiplication_factor;
    }
}

//abs compare between two numbers
double absCompare(double x, double y){
    double res=x-y;
    if(res<0){
        res=-res;
    }
    return res;
}

//do the calculations needed to update grades after mean error
void updateByMean(double array[], const int array_size,
                  const double expected_mean, const double current_mean){
    for(int i=0; i<array_size; i++){
        array[i]=array[i]-current_mean+expected_mean;
    }
}

//as asked
void updateGrades(double array[], const int array_size,
                     const double expected_mean, const double max_std){
    double current_mean= meanGrades(array,array_size);
    double current_std= stdGrades(array, array_size,current_mean);
    if (current_std>max_std){
        updateByStd(array,array_size,max_std,current_std);
    }
    current_mean=meanGrades(array,array_size);
    if(absCompare(current_mean, expected_mean)>1){
        updateByMean(array,array_size,expected_mean,current_mean);
    }
}

/*from now on it's all your printing functions*/
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

void oldPrint(double* array, int array_size){
    double min= minMaxGrades(array,array_size,true);
    double max= minMaxGrades(array,array_size, false);
    double mean= meanGrades(array,array_size);
    double std= stdGrades(array,array_size,mean);
    printOldGrades(array,array_size);
    printOldGradesStatistics(min,max,mean,std);
}

void newPrint(double* array, int array_size){
    double min= minMaxGrades(array,array_size,true);
    double max= minMaxGrades(array,array_size, false);
    double mean= meanGrades(array,array_size);
    double std= stdGrades(array,array_size,mean);
    printNewGrades(array,array_size);
    printNewGradesStatistics(min,max,mean,std);
}


int main() {
    printGradesOpening();
    double array[MAX_GRADES+1], expected_mean, max_std=MAX_STD;
    int array_size, i=0;
    while(scanf("%lf", &array[i])!=EOF && i<MAX_GRADES){
        i++;
    }
    array_size=i-1;
    expected_mean=array[i-1];
    oldPrint(array,array_size);
    updateGrades(array,array_size,expected_mean,max_std);
    newPrint(array,array_size);
    return 0;
}
