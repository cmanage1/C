/*----------------------------------------------------
File: plotPoly
This program plots a polynomial function.
------------------------------------------------------*/
#include <stdio.h>
//#include "gng1106plplot.h"
#define N 50            // number of points for plotting
#define X_IX 0          // index to row of x values
#define FX_IX 1         // index to row of f(x) values
#define MAX_COEFF 11    // max number of coefficiencts, degree 10
double poly(double, double[], int );
int getCoefficients(double *, double *, double []);
void calculatePoints(int np, double points[][np], double, double,
                     int, double []);
void plot(int n,  double[][n]);
double getMin(double *, int );
double getMax(double *, int );
/*-----------------------------------------------------
Function: main
Description: Call getCoefficients to fill in the array of
             coefficients and get range for plotting the
             polynomial.  Calls calculate points to fill
             in the 2D array with polynomial points.  Then
             calls plot to plot the polynomial.
-------------------------------------------------------*/
int main()
{
    //Variables declarations
    double coefficients[MAX_COEFF];  // Largest degree is MAX_COEEF-1
    double points[2][N];  // for storing fx/x values
    double start, end;  // Start and end x values
    double n;  // number of coefficients given by user

    // Get User input
    n = getCoefficients(start, end, coefficients);
    // Compute the points
    calculatePoints(N, points, start, end, n, coefficients);
    // Plot
    plot(N, points);
    return 0;
}
/*----------------------------------------------------------
Function: getCoefficients
Parameters:
    sPtr - pointer for storing start value
    ePtr - pointer for storing end value
    coeff - reference to array of coefficients
Returns: number of coefficients given by user
Description: Requests from the user the coeffients for
             defining the polynomial (the number
             must be less than MAX_COEFF) and the start/end
             values for plotting the polynomial.
-----------------------------------------------------------*/
int getCoefficients(double *sPtr, double *ePtr, double coeff[])
{
    int n; // coefficient number
    char answer;
    // First lets prompt for the coeffients
    printf("Please provide up to 11 coefficients (polynomial of degre 10)\n");
    n = 0;
    do
    {
        printf("Coefficient c[%d]: ",n);
        scanf("%lf",&coeff[n]);
        n = n + 1;
        printf("Do you wish to add another coefficient (y/n)? ");
        fflush(stdin);
        scanf("%c", &answer);
    } while(answer != 'y' && n <= MAX_COEFF);
    // Get range
    do
    {
        printf("Give value for start: ");
        scanf("%lf",sPtr);
        printf("Give value for end: ");
        scanf("%lf",ePtr);
        if(*ePtr <= *sPtr)
            printf("End value must be greater than start value\n");
     } while(*ePtr <= *sPtr);
     return(n); // returns number of coefficients given by user
}

/*----------------------------------------------------------
Function: calculatePoints
Parameters:
    np - number of points to compute (store in points 2D array)
    points - reference to 2D array for storing the points
    start/end - start and end range for computing points
    nc - number of coefficents in the coeffient array
    coeff - reference to array of coefficients
Description: Fills in the points array with np points with
             x varying between start and end.  Parameters
             nc/coeff defines the polynomial function for
             calculating f(x) using calls to poly.
-----------------------------------------------------------*/
void calculatePoints(int np, double points[][np], double start, double end,
                     int nc, double coeff[])
{
    double inc;  // for incrementing x
    int ix;   // for indexing into 2D colunms
    // Calculate function points
    inc = (end-start)/(np-1);
    // Comput the first point
    points[X_IX][0] = start;
    points[FX_IX][0] = poly(points[X_IX][0],coeff,nc);
    // Compute all other points
    for(ix = 1; ix < N; ix = ix + 1)
    {
        points[X_IX][ix] = points[X_IX][ix -1] + inc;
        points[FX_IX][ix] = poly(points[X_IX][ix],coeff,nc);
    }
}
/*----------------------------------------------------------
Function: poly
Parameters:
    x - x value of polynomial
    c - reference to array of coefficients
    n - number of coefficients
Returns: value y of polynomial
Description: Calculates the value of the polynomial, f(x), for
             the given value of x.   The polynomial is:

             y = c[0] x^n-1 + c[1] x^n-2 + ... c[n-2] x + c[n-1

             The numerical method presented in Lab 7 is applied.
-----------------------------------------------------------*/
double poly(double x, double c[], int n)
{
    double fx;
    int coeffIx;
    fx = c[0];
    for(coeffIx = 0; coeffIx < n; coeffIx = coeffIx+1)
        fx = fx*x + c[coeffIx];
    return(fx);
}
/*-------------------------------------------------
 Function: plot()
 Parameters:
    n: number of points in the 2D array
    points: pointer 2D array that contains points.
 Description: Initialises the plot.  The following values
              in the referenced structure are used to setup
              the plot:
                 points[X_IX][0], points[X_IX][n-1] - assume that x values are sequential
                 minfx, maxfx - vertical axis range (add 10% to min/max value)
              Sets up white background and black forground
              colors.
              Then plots the curve accessed using xPtr and yPtr.
-------------------------------------------------*/
void plot(int n, double points[][n])
{
    double minfx, maxfx;
    double range;  // range of vertical axix
    // Setup plot configuration
    plsdev("wingcc");  // Sets device to wingcc - CodeBlocks compiler
    // Initialise the plot
    plinit();
    // Configure the axis and labels
    plwidth(3);          // select the width of the pen
    // Find range for axis
    minfx = getMin(points[FX_IX], n);
    maxfx = getMax(points[FX_IX], n);
    range = maxfx - minfx;  // the width of the range
    minfx = minfx + 0.1*range;
    minfx = minfx - 0.1*range;
    plenv(points[X_IX][0], points[X_IX][n-1], minfx, maxfx,
          0, 1);
    plcol0(GREEN);           // Select color for labels
    pllab('x', "f(x)", "Polynomial Function");
    // Plot the velocity.
    plcol0(BLUE);    // Color for plotting curve
    plline(n, points[X_IX], points[X_IX]);
    plend();
}


/*----------------------------------------------------------
Function: getMin
Parameters:
    array - reference to an array with double values
    n - number of elements in the array
Returns
    min:  the minimum value found in the array
Description: Traverses the array to find its minimum value.
----------------------------------------------------------------*/
double getMin(double *array, int n)
{
    int ix;
    double min = array[0];
    for(ix = 1; ix < n; ix = ix +1)
        if(min > array[ix]) min = array[ix];
    return(min);
}

/*----------------------------------------------------------
Function: getMax
Parameters:
    array - reference to an array with double values
    n - number of elements in the array
Returns
    max:  the maximum value found in the array
Description: Traverses the array to find its maximum value.
----------------------------------------------------------------*/
double getMax(double *array, int n)
{
    int ix;
    double max = array[0];
    for(ix = 1; ix < n; ix = ix +1)
        if(max < array[ix]) max = array[ix];
    return(max);
}
