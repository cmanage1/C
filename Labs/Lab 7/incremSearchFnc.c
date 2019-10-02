/*----------------------------------------------------
File: incremSearchFncSoln.c
Name: XXX
Student ID: XXX
This program plots function, asks the user to select
an interval for finding roots.
Function: f(x) = 50 - x^2 |cos(x^1/2)| An incremental search
root finding method is used.
------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "gng1106plplot.h"
#define N 100  // number of points
#define MAX_ROOTS 3 // Maximum number of roots
#define TRUE 1
#define FALSE 0
#define ALMOST_0  1e-5   // For testing zero values
#define SI_RESOLUTION 1000  // Subinterval resolution
// Function Prototypes
void findInterval(double *, double *);
int findAllRoots(double, double, double []); //********************
int findRoot(double, double, double *);  //************************
void plotFunc(double, double, int, double []);
double func(double); //**********************************************
void plot(int,  double[], double[], int, double[], double[]);
double getMin(double *, int );
double getMax(double *, int );
/*--------------------------------------------------------
Function: main()
Description: Call findInterval to allow the user to select
             an interval for searching.  Show the results
	     to the user.
---------------------------------------------------------*/
int main()
{
    double start, end;
    double roots[MAX_ROOTS];
    int n;  // number of roots found
    int ix;
    // Get intervals from user
    findInterval(&start, &end);
    printf("Finding roots for intervals between %.4f and %.4f\n",
           start, end);
    n = findAllRoots(start, end, roots);
    printf("Found %d roots: \n",n);
    for(ix = 0; ix < n; ix = ix+1)
        printf("  %.8f (f(x) = %.8f)\n",roots[ix], func(roots[ix]));
    plotFunc(start, end, n, roots);
    return 0;
}


/*----------------------------------------------------------
Function: findInterval
Parameters:
    begin, end: pointers to double variables for storing selected
                begin and end values of x for the desired interval
Description: Repeatedly plot the graph of the function for the
             intervals given by the user until the user
             has made a selection of the interval for root
             finding.
---------------------------------------------------------------*/
void findInterval(double *begin, double *end)
{
    //Variables declarations
    char answer;  // sentinal
    do
    {
        printf("Please give start and end values for plotting: ");
        fflush(stdin);
        scanf("%lf %lf",begin,end);
        plotFunc(*begin, *end, 0, NULL);
        printf("Are you happy with this interval? ");
        fflush(stdin);
        scanf("%c",&answer);
    }
    while(answer != 'y');
}


/*----------------------------------------------------------
Function: findAllRoots
Parameters:
    start, end:  start and end of interval (x values) for seaching roots
    roots - reference to array for storing roots
Returns:
    The number of roots found (value of rootIx at the end of the loop)
Description: Find the roots between the interval for the
             polynomial defined by coefficients.
---------------------------------------------------------------*/
int findAllRoots(double start, double end, double roots[])
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
    root - reference to save the value of the root found.
Description: Check if a root exists in the subinterval for the
             polynomial defined by coefficients.
---------------------------------------------------------------*/
int findRoot(double left, double right, double *root)
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
Function: func
Parameters:
    x - x value function f(x)
Returns: value y of function f(x)
Description: Plots the value of the function:

f(x) = 50 - x^2 |cos(sqrt(x)| , x must be positive, if x
                         negative return 0.
-----------------------------------------------------------*/
double func(double x)
{
    double y;

    if (x >= 0)
    {
        y= 50 - pow(x, 2);
    }
    else
        y=0;

     return y;
}
/*----------------------------------------------------------
Function: plotFunc
Parameters:
     begin, end:  beginning and end of interval (x values) to plot
     nRoots - number of roots in the root array.
     root - value of root when flag is TRUE.
Description: Plot the function on the
             interval between begin and end.  Plots an x at the roots
             if nRoots > 0.
---------------------------------------------------------------*/
void plotFunc(double begin, double end, int nRoots, double roots[])
{
    double x[N];
    double y[N];
    double inc; // increment for incrementing x
    double yRoots[nRoots];
    int ix;
    // Calculate function points
    inc = (end - begin)/N;
    x[0] = begin;
    y[0] = func(x[0]); // Compute first point
    for(ix = 1; ix < N; ix = ix + 1)
    {
        x[ix] = x[ix -1] + inc;
        y[ix] = func(x[ix]);
    }
    // Calculate y points at the root
    for(ix = 0; ix < nRoots; ix = ix +1)
    {
        yRoots[ix] = func(roots[ix]);
    }
    // Plot
    plot(N, x, y, nRoots, roots, yRoots);
}

/*-------------------------------------------------
 Function: plot()
 Parameters:
    n: number of points in the arrays
    xPtr: pointer to x values (horizontal axis).
    yPtr: pointer to y values (vertical axis).
    rRoots: number of roots
    xRoots: x coordinate of roots
    yRoots: y coordinate of roots.
 Return value: none.
 Description: Initialises the plot.  The following values
              in the referenced structure are used to setup
              the plot:
                 x[0], x[n-1] - assume that x values are sequential
                 miny, maxy - vertical axis range (add 10% to min/max value)
              Sets up white background and black forground
              colors.
              Then plots the curve accessed using xPtr and yPtr.
	      Plots x at the root points.
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
    maxy = maxy + 0.1*range;
    miny = miny - 0.1*range;
    plenv0(xPtr[0], xPtr[n-1], miny, maxy,
          0, 1);
    plcol0(GREEN);           // Select color for labels
    pllab("x", "f(x)", "Function");
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
