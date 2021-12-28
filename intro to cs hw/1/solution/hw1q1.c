#include <stdio.h>
#include <math.h>

#define ZERO 0.000001

/*print the message that asks the user to insert coefficients for the polynomial*/
void askForCoefficientsFromUser ()
{
    printf("Enter the coefficients of a polynomial:\n");
}

/*print the message in the case of no roots*/
void printNoRoots ()
{
    printf("There are no roots\n");
}

/*print the message in the case of one root*/
void printTheOnlyRoot (double root)
{
    printf("The root is %.3f\n", root);
}

/*print the message in the case of two roots*/
void printTheTwoRoots (double first_root, double second_root)
{
    if (first_root>second_root)
        printf("The roots are %.3f, %.3f\n", second_root, first_root);
    else
        printf("The roots are %.3f, %.3f\n", first_root, second_root);

}

/*enums that going to help me to check the scanned coefficients from the user*/
typedef enum{
    SCAN_SCANF_FAIL,
    SCAN_SUCCESS
}Scan;

/*scanning the coefficients from the user*/
Scan scanCoefficientsFromUser(double* x)
{
    if(scanf("%lf", x)!=1)
        return SCAN_SCANF_FAIL;

    return SCAN_SUCCESS;
}

/*uses the scanning function from before to scan coefficients from user and check the 'a' value as asked*/
Scan scanCoefficientsFromUserAux(double* a, double* b, double* c)
{
    if(scanCoefficientsFromUser(a)!=SCAN_SUCCESS || scanCoefficientsFromUser(b)!=SCAN_SUCCESS
    || scanCoefficientsFromUser(c)!=SCAN_SUCCESS)
        return SCAN_SCANF_FAIL;
    else if (*a<=ZERO && *a>=-ZERO) {
        askForCoefficientsFromUser();
        scanCoefficientsFromUserAux(a, b, c);
    }

    return SCAN_SUCCESS;
}

/*finds the discriminant of a polynomial given to it*/
double findDiscriminantOfPolynomial(double a, double b, double c)
{
    return (b*b)-(4*a*c);
}

/*finds the only root of a polynomial given to it
 * warning - use only if already know that polynomial has only one root*/
double findTheOnlyRootOfPolynomial(double a, double b, double c)
{
    return (-b+sqrt((double)findDiscriminantOfPolynomial(a,b,c)))/(2*a);
}

/*finds the two roots of a polynomial given to it
 * warning - use only if already know that polynomial has two root*/
void findTheTwoRootsOfPolynomial(double a, double b, double c, double* first_root, double* second_root)
{
    *first_root=(b+sqrt((double) findDiscriminantOfPolynomial(a,b,c)))/(2*(double)a);
    *second_root=(b-sqrt((double) findDiscriminantOfPolynomial(a,b,c)))/(2*(double)a);
}

/*finds the roots of a polynomial given to it by using the functions I wrote before, and prints the result*/
void findPolynomialRoots (double a, double b, double c)
{
    if(findDiscriminantOfPolynomial(a,b,c)<0)
        printNoRoots();
    if(findDiscriminantOfPolynomial(a,b,c)==0)
        printTheOnlyRoot(findTheOnlyRootOfPolynomial(a,b,c));
    if(findDiscriminantOfPolynomial(a,b,c)>0){
        double first_root;
        double second_root;
        findTheTwoRootsOfPolynomial(a, b, c, &first_root, &second_root);
        printTheTwoRoots(first_root,second_root);
    }
}

int main() {
    double a,b,c;
    askForCoefficientsFromUser();
    if(scanCoefficientsFromUserAux(&a,&b,&c)!=SCAN_SUCCESS)
        return 1;
    findPolynomialRoots(a,b,c);

    return 0;
}
