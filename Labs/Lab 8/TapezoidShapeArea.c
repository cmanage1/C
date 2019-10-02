/*-------------------------------------------------
 File: TrapezoidShapeArea.c
 Description: Calculates the area of a shape
              using Trapazoidal rule for integration.
-------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gng1106plplot.h"
#include "plplot.h"
// Define symbolic constant
#define MAX_SIZE 500  // maximum size of arrays
// Structure definitions
typedef struct
{
    // INPUT from the user
    double aStart;  // Initial value of dimension a for plotting
    double aEnd;    // Final value of dimension a for plotting
    double inc;     // incrementation for value of a
    int num_steps;  //  number of steps to determine h (Trapezoidal Rule)
    // Calculated values
    int n;       // number of points a/fA(a) to compute must
    // be less than MAX_SIZE
    double a[MAX_SIZE];  // values  of dimension a
    double area[MAX_SIZE];  // area using analytical equation
    double areaTrap[MAX_SIZE]; // area using Trapezoidal Rule
}  SHAPE;

// function prototypes
void getUserInput(SHAPE *);
double getPositiveValue(char *);
void calculateAreaAnalytical(SHAPE *);
void calculateAreaTrapazoid(SHAPE *);
double computeFa(double, int );
void plot(SHAPE *);
double getMin(double *, int);
double getMax(double *, int);

/*--------------------------------------------
Function: main
Description:  Overall control of the program.
Gets the input from the user, calculates areas
using analytical solution and using Trapazoidal rule,
and plot the 2 curves.
----------------------------------------------*/
void main()
{
    SHAPE shape;  // Input and output data

    // Get the user input
    getUserInput(&shape);
    // Calculations
    calculateAreaAnalytical(&shape);
    calculateAreaTrapazoid(&shape);
    // Plotting
    plot(&shape);
    printf("All done.");
}

/*----------------------------------------------------------
Function: getUserInput
Parameters:
    pPtr - reference to SHAPE structure variable.  Members used
            num_steps - number of steps for determining h
            aStart - starting value for a
            aEnd - end value for a
            inc - incrementation value for dimension a
            n - number of elements used in time/area arrays
Description: Gets from the user values for range of values for
             a, an incremetation value for and the number of steps
             to be used with the Trapezoidal rune (determines h)
             and stores in appropriate variables.
             Ensures that aStart is less than aEnd. Computes n
             and ensures that it is less than MAX_SIZE.
-------------------------------------------------------------*/
void getUserInput(SHAPE *pPtr)
{
    // Get input
    pPtr->num_steps = getPositiveValue("number of steps for defining h");
    do
    {
        pPtr->aStart = getPositiveValue("the start value for a");
        pPtr->aEnd = getPositiveValue("the end value for a");
        pPtr->inc = getPositiveValue("incrementation of a");
        pPtr->n = 1+(pPtr->aEnd - pPtr->aStart)/pPtr->inc;
        if(pPtr->n > MAX_SIZE)
            printf("Incrementation too small for range of dimension a (%d)\n", pPtr->n);
        if(pPtr->n < 0)
            printf("The end value for a must be larger than its start value\n");
    }
    while(pPtr->n > MAX_SIZE || pPtr->n <= 0);
}

/*----------------------------------------------------------
Function: getPositiveValue
Parameters:
    prompt - reference to string to include in the user prompt
Returns
    value: positive value obtained from the user.
Description: Prompt the user for a value (using the prompt string)
    and checks that the value is positive.
-------------------------------------------------------------*/
double getPositiveValue(char *prompt)
{
    double value; // Value entered by the user.
    do
    {
        printf("Please enter a value for %s: ", prompt);
        scanf("%lf",&value);
        if(value <= 0.0)
            printf("The value must be greater than zero.\n");
    }
    while(value <= 0.0);
    return(value);
}

/*----------------------------------------------------------
Function: calculateAreaAnalytical
Parameters:
    sPtr - reference to SHAPE structure variable.  Members used
            aStart - starting value for a
            inc - incrementation value for dimension a
            n - number of elements used in time/area arrays
            a - array for saving values of a
            area - array for saving area values
Description: Fills in the arrays with n points of
    a/fA(a) values using the analytical solution for the
    area fA(a).
-------------------------------------------------------------*/
void calculateAreaAnalytical(SHAPE *sPtr)
{
    double aValue;
    int ix;
    aValue = sPtr->aStart;
    for(ix = 0; ix < sPtr->n; ix = ix + 1)
    {
        sPtr->a[ix] = aValue;
        sPtr->area[ix] = 4.0*pow(aValue,3)/exp(1);
        aValue = aValue + sPtr->inc;
    }
}

/*----------------------------------------------------------
Function: calculateAreaTrapazoid
Parameters:
    sPtr - reference to SHAPE structure variable.  Members used
            num_steps - number of steps for determining h
            aStart - starting value for a
            inc - incrementation value for dimension a
            n - number of elements used in time/area arrays
            a - array for saving values of a
            areaTrap - array for saving area values
Description: Fills in the arrays with n points of
    a/area values using the Trapezoidal rule for the
    distance.
-------------------------------------------------------------*/
void calculateAreaTrapazoid(SHAPE *sPtr)
{
   // Complete this function
    int ix;
    double area;//area at a given increment
    area = sPtr->aStart;
    for(ix = 0; ix < (sPtr->n) ; ix++)
    {
        sPtr->a[ix]= area;
        sPtr->areaTrap[ix]= computeFa(sPtr->a[ix], sPtr->num_steps);
        area+= sPtr->inc;
    }
}

/*----------------------------------------------------------
Function: computeFa
Parameters:
    a - Dimension a of the scrapper
    num_steps - number of steps for determining h
Description: Computes the value of fA(a) for the dimension a
             by applying the Trapezoidal rule for integrating
             f(x) from -a to +a.
-------------------------------------------------------------*/
double computeFa(double a, int num_steps)
{
    // Complete this function
     double h;
     h=(2*a)/num_steps;
     double f=0;
     double x;
     x=-a+h;
     int i;
     for(i=1; i<(num_steps-1); i++)
     {
         f=f+(pow(a,2)-pow(x,2))*exp(-x/a);
         x=x+h;
     }
     f=f*h;
     return(f);
}

/*----------------------------------------------------------
Function: plot
Parameters:
    sPtr - reference to SHAPE structure variable.  Members used
            aStart - starting value for dimension a
            aEnd - end value for dimension a
            n - number of elements used in time/area arrays
            a - array for saving values of a
            areaTrap - array for saving area values
Description: Initilialises the plot device, pen width,
             and plots both cuvers for the analytical and the
             Euler method.
----------------------------------------------------------------*/
void plot(SHAPE *sPtr)
{
    double maxArea;   // maximum area
    double temp;
    char plotLabel[100];

    // Find the maximum distance to scale the distance axis
    maxArea = getMax(sPtr->area, sPtr->n);
    temp = getMax(sPtr->areaTrap, sPtr->n);
    if(temp > maxArea) maxArea = temp;
    maxArea = 1.1*maxArea;
    // Initiliaise the PLplot page
    plsdev("wingcc");  // Sets device to wingcc - CodeBlocks compiler
    // Initialise the plot
    plinit();
    plwidth(2);    // pen width
    plenv(sPtr->aStart, sPtr->aEnd, 0, maxArea, 0, 0);
    plcol0(GREEN);           // Select color for labels
    sprintf(plotLabel, "Part area (num steps = %d)",
            sPtr->num_steps);
    pllab("Dimension a", "Area fA(a)", plotLabel);
    // Plot the analytical curve
    plcol0(RED);
    pllsty(SOLID);
    plline(sPtr->n, sPtr->a, sPtr->area);
    plptex(0.1*(sPtr->aEnd - sPtr->aStart) + sPtr->aStart, 0.9*maxArea,
           0, 0, 0, "Analytical");
    // Plot the Trapezoidal curve
    plcol0(BLUE);
    pllsty(LNGDASH_LNGGAP);
    plline(sPtr->n, sPtr->a, sPtr->areaTrap);
    plptex(0.3*(sPtr->aEnd - sPtr->aStart) + sPtr->aStart, 0.9*maxArea,
           0, 0, 0, "Trapazoid");
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




