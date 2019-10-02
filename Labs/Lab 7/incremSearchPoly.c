/*----------------------------------------------------
File: incremSearch.c
Description: This program plots a polynomial function, asks the user to select
             an interval for finding roots.
             Function: f(x) = x^3 - 4.65x^2 - 24.73x + 1.248
             An incremental search root finding method is used.
             Use 100 points to plot.
------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "gng1106plplot.h"
#include "plplot.h"
#define N 50  // number of points
#define N_COEFF 4 // number of coefficiencts
#define MAX_ROOTS 3 // Maximum number of roots
#define TRUE 1
#define FALSE 0
#define ALMOST_0  1e-5   // For testing zero values
#define SI_RESOLUTION 1000  // Subinterval resolution
// Function Prototypes
void findInterval(double *, double *, int, double []);
int findAllRoots(double, double, int, double [], double []);
int findRoot(double, double, int, double [], double *);
void plotPoly(double, double, int, double [], int, double[]);
double poly(double, double[], int );
void plot(int,  double[], double[], int, double[], double[]);
double getMin(double *, int );
double getMax(double *, int );
/*--------------------------------------------------------
Function: main()
Description: Creates an array of coefficients for root finding.
             Calls findInterval to allow the user to select
             the interval for searching by plotting the function.
             Displays the results to the users.
---------------------------------------------------------*/
int main()
{
    double coefficients[N_COEFF] = { 1.0, -4.65, -24.73, 1.248};
    double start, end;
    double roots[MAX_ROOTS];
    int n;  // number of roots found
    int ix;
    // Get intervals from user
    findInterval(&start, &end, N_COEFF, coefficients);
    printf("Finding roots for intervals between %.4f and %.4f\n",
           start, end);
    n = findAllRoots(start, end, N_COEFF, coefficients, roots);
    printf("Found %d roots: \n",n);
    for(ix = 0; ix < n; ix = ix+1)
        printf("  %.8f (f(x) = %.8f)\n",roots[ix], poly(roots[ix],coefficients,N_COEFF));
    plotPoly(start, end, N_COEFF,coefficients, n, roots);
    return 0;
}
/*----------------------------------------------------------
Function: findAllRoots
Parameters:
    start, end:  start and end of interval (x values) for seaching roots
    n - number of coefficients
    coefficients - reference to array of coefficients
    roots - reference to array for storing roots
Returns:
    The number of roots found (value of rootIx at the end of the loop)
Description: Find the roots between the interval for the
             polynomial defined by coefficients.
---------------------------------------------------------------*/
int findAllRoots(double start, double end, int n, double coefficients[], double roots[])
{
    double subinter = (end-start)/SI_RESOLUTION;
    int cntr; // for counting subintervals
    double ak, bk;  // values at the borders of the subinterval
    double root;    // for getting root values
    int rootIx;  // for indexing into roots
    rootIx = 0;
    for(cntr = 0; cntr < SI_RESOLUTION; cntr = cntr + 1)
    {
        ak = start + (cntr*subinter);
        bk = start + ((cntr + 1)*subinter);
        if(bk > end) bk = end;
        if(findRoot(ak, bk, n, coefficients, &root))
        {
            roots[rootIx] = root;
            rootIx = rootIx + 1;
        }
    }
    return(rootIx);
}
/*----------------------------------------------------------
Function: findRoot
Parameters:
    left, right:  values of x at the edges of the subinterval
    n - number of coefficients
    coeffs - reference to array of coefficients
Description: Check if a root exists in the subinterval for the
             polynomial defined by coefficients.
---------------------------------------------------------------*/
int findRoot(double left, double right, int n, double coeffs[], double *root)
{
    double func_left, func_right;  // values of function at border of interval
    double factor;  // for storing func_left*func_right
    func_left = poly(left, coeffs, n);
    func_right = poly(right, coeffs, n);
    factor = func_left*func_right;
    int retVal = FALSE;
    if(fabs(factor) < ALMOST_0)  // About zero
    {
        if(fabs(func_left) < ALMOST_0)
        {
            *root = left;
            retVal = TRUE;
        }
    }
    else if( factor < 0.0)
    {
        *root = (left+right)/2.0;
        retVal = TRUE;
    }
    return(retVal);
}

/*----------------------------------------------------------
Function: findInterval
Parameters:
    begin, end: pointers to double variables for storing selected
                begin and end values of x for the desired interval
    n - number of coefficients
    coeffs - reference to array of coefficients
Description: Repeatedly plot the graph of the function for the
             intervals given by the user until the user
             has made a selection of the interval for root
             finding.
---------------------------------------------------------------*/
void findInterval(double *begin, double *end, int n, double coefficients[])
{
    //Variables declarations
    char answer;  // sentinal
    do
    {
        printf("Please give start and end values for plotting: ");
        fflush(stdin);
        scanf("%lf %lf",begin,end);
        plotPoly(*begin, *end, n, coefficients, 0, NULL);
        printf("Are you happy with this interval: ");
        fflush(stdin);
        scanf("%c",&answer);
    }
    while(answer != 'y');
}
/*----------------------------------------------------------
Function: plotPoly
Parameters:
     begin, end:  beginning and end of interval (x values) to plot
     n - number of coefficients
     coefficients - reference to array of coefficients
     nRoots - number of roots
     roots - reference to an array of roots
Description: Plot the polynomial (given with coefficients) on the
             interval between begin and end.  Plots an x at the roots if
             nRoots is none zero.
---------------------------------------------------------------*/
void plotPoly(double begin, double end, int n, double coefficients[], int nRoots, double roots[])
{
    double x[N];
    double y[N];
    double inc; // increment for incrementing x
    double yRoots[nRoots]; // function values at roots
    int ix;
    // Calculate function points
    inc = (end - begin)/N;
    x[0] = begin;
    y[0] = poly(x[0],coefficients,n); // Compute first point
    for(ix = 1; ix < N; ix = ix + 1)
    {
        x[ix] = x[ix -1] + inc;
        y[ix] = poly(x[ix],coefficients,n);
    }
    // Get y values of roots
    for(ix = 0; ix < nRoots; ix = ix + 1) // if nRoots is zero drop out of loop immediately
    {
        yRoots[ix] = poly(roots[ix], coefficients, n);
    }
    // Plot
    plot(N, x, y, nRoots, roots, yRoots);
}

/*----------------------------------------------------------
Function: poly
Parameters:
    x - x value of polynomial
    c - reference to array of coefficients
    n - number of coefficients
Returns: value y of polynomial
Description: Calculates the value of the polynomial, y, for
             the given value of x.   The polynomial is:

             y = c[0] x^n-1 + c[1] x^n-2 + ... c[n-2] x + c[n-1

             The numerical method studied in Module 4 Example 12
             is used here.  Note that the order of the coefficients
             are reversed here from example 12.
-----------------------------------------------------------*/
double poly(double x, double c[], int n)
{
    double fx;
    int coeffIx;
    fx = c[0];
    for(coeffIx = 1; coeffIx < n; coeffIx = coeffIx+1)
    {
        fx = fx*x + c[coeffIx];
    }
    return(fx);
}
/*-------------------------------------------------
 Function: plot()
 Parameters:
    n: number of points in the arrays
    xPtr: pointer to x values (horizontal axis).
    yPtr: pointer to y values (vertical axis).
    nRoots: number of roots (size of xRoots and yRoots arrays)
    xRoots: pointer to x values of roots (horizontal axis).
    yRoots: pointer to y values of roots (vertical axis).
 Description: Initialises the plot.  The following values
              in the referenced structure are used to setup
              the plot:
                 x[0], x[n-1] - assume that x values are sequential
                 miny, maxy - vertical axis range (add 10% to min/max value)
              Then plots the curve accessed using xPtr and yPtr.
              Plots x on the root points if nRoots > 0.
-------------------------------------------------*/
void plot(int n, double *xPtr, double *yPtr, int nRoots, double *xRoots, double *yRoots)
{
    double miny, maxy;
    double range;  // range of vertical axix
        // Setup plot configuration
    plsdev("wingcc");  // Sets device to wingcc - CodeBlocks compiler
    // Initialise the plot
    plinit();
    // Configure the axis and labels
    plwidth(3);          // select the width of the pen
    // Find range for axis
    miny = getMin(yPtr, n);
    maxy = getMax(yPtr, n);
    range = maxy - miny;  // the width of the range
    miny = miny + 0.1*range;
    miny = miny - 0.1*range;
    plenv0(xPtr[0], xPtr[n-1], miny, maxy,
          0, 1);
    plcol0(GREEN);           // Select color for labels
    pllab("x", "f(x)", "Polynomial");
    // Plot the velocity.
    plcol0(BLUE);    // Color for plotting curve
    plline(n, xPtr, yPtr);
    // Plot the points
    if(nRoots > 0)
    {
        plcol0(RED);
        plpoin(nRoots,xRoots, yRoots, 'x');
    }
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
