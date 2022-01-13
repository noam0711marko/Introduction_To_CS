/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>


/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define N 50
#define M 50

#define RECT 4
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3


/* put your #defines and typedefs here*/

/*===================== your asked functions ===================== */

//gets an image and it's dimensions. and an array of integers, and in each place of the array of integers puts
//it's compute integral.
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);

//gets the array of image with the computed integral values, and array which contains dimensions to sum values
// and returns the sum of the values of this part of the image.
int sum_rect(int integral_image[][M], int rect[RECT]);

//gets an image and it's dimensions, dimensions for sliding rectangle and an array of integers, in which in each
//place would be entered the average of the rectangle in the requested dimensions in which the place is the center.
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);

//gets an array and dimensions and prints it
void print_array(int a[N][M], int n, int m);


/*===================== added by me functions ===================== */

//returns the bigger between 2 integers
int max(int a, int b);

//returns the smaller between 2 integers
int min(int a, int b);

//returns the half (rounded down) of an odd number
// example: half of 3 is 1, half of 11 is 5.
int half_of_odd(int x);


/*-------------------------------------------------------------------------
  Your implementation of the functions (describe what each function does)
 -------------------------------------------------------------------------*/

void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i>0 && j>0){
                integral_image[i][j]=image[i][j]+integral_image[i-1][j]+integral_image[i][j-1]-integral_image[i-1][j-1];
            }
            else if(i==0 && j>0){
                integral_image[i][j]=image[i][j]+integral_image[i][j-1];
            }
            else if(i>0 && j==0){
                integral_image[i][j]=image[i][j]+integral_image[i-1][j];
            }
            else{
                integral_image[i][j]=image[i][j];
            }
        }
    }
}

int sum_rect(int integral_image[][M], int rect[RECT]){
    int top=rect[TOP];
    int left=rect[LEFT];
    int bottom=rect[BOTTOM];
    int right=rect[RIGHT];
    if(top>0 && left >0){
        return integral_image[bottom][right]-integral_image[top-1][right]-integral_image[bottom][left-1]+integral_image[top-1][left-1];
    }
    else if(top==0 && left>0){
        return integral_image[bottom][right]-integral_image[bottom][left-1];
    }
    else if(top>0 && left==0){
        return integral_image[bottom][right]-integral_image[top-1][right];
    }
    else{
        return integral_image[bottom][right];
    }
}

void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]){
    for(int i=0; i<n; i++) {
        for (int j = 0; j < m; j++) {
                int top=max(0, i- half_of_odd(h));
                int left=max(0, j-half_of_odd(w));
                int bottom=min(n-1, i+ half_of_odd(h));
                int right=min(m-1, j+ half_of_odd(w));
                int rect[RECT]={top,left,bottom,right};
                average[i][j]= round(sum_rect(integral_image,rect)/(double)(h*w));
        }
    }
}

int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

int min(int a, int b){
    if(a>b){
        return b;
    }
    return a;
}

int half_of_odd(int x){
    return (x-1)/2;
}


/*-------------------------------------------------------------------------
  The main program
 -------------------------------------------------------------------------*/

int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = {{0}};
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M];
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);

    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}

void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
