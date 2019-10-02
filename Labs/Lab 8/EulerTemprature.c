/*-------------------------------------------------
 File: EulerTemperature.c
 Description: Calculates change in temperature of
              using Euler's numerical method
              to solving differential equations.
-------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gng1106plplot.h"
// Define symbolic constants
#define MAX_SIZE 500  // maximum size of arrays
// Structure definitions
typedef struct
{
    // INPUT from the user
    double tempAmbiant;  // Ambiant temperature
    double k;    // propotionality constant
    double tempInitial;  // initial temperature
    double deltat;  // time step for Euler method
    double tfinal;   // final time for plotting
    // Calculated values
    int n;  // number of values to compute must
    // be less than MAX_SIZE
    double t[MAX_SIZE];    // time values
    double temp[MAX_SIZE]; // temperature from analytical equation
    double tempEuler[MAX_SIZE]; // temperature from Euler method
}  NEWTON;

// function prototypes
void getUserInput(NEWTON *);
double getPositiveValue(char *);
double getValue(char *);
void calculateTemperatureAnalytical(NEWTON *);
void calculateTemperatureEuler(NEWTON *);
void plot(NEWTON *);
double getMin(double *, int);
double getMax(double *, int);

/*--------------------------------------------
Function: main
Description:  Overall control of the program.
Gets the input from the user, calculates temperatures
using analytical solution and using Euler's method,
and plot the 2 curves.
----------------------------------------------*/
void main()
{
    NEWTON newton;  // Input and output data
    // Get the user input
    getUserInput(&newton);
    // Calculations
    calculateTemperatureAnalytical(&newton);
    calculateTemperatureEuler(&newton);
    // Plotting
    plot(&newton);
    printf("All done.");
}

/*----------------------------------------------------------
Function: getUserInput
Parameters:
    nPtr - reference to NEWTON structure variable.  Members used
            deltat - delta t variable
            tempAmbiant - ambiant temperature
            k - proportionality constant
            tempInitial - initial temperature
            n - number of elements used in time/velocity arrays
Description: Gets from the user values for ambiant temperature,
             proportionality constant, initial temperature,
             and time step (delta t) and store in
             appropriate variables.  Also computes n and ensures
             that it is less than MAX_SIZE.
-------------------------------------------------------------*/
void getUserInput(NEWTON *nPtr)
{
    // Get weight and drag values
    nPtr->tempAmbiant = getValue("the ambiant temperature");
    nPtr->k = getPositiveValue("the proportionalty constant");
    nPtr->tempInitial = getValue("the initial temperature");
    // Get time values
    do
    {
        nPtr->tfinal = getPositiveValue("final time");
        nPtr->deltat = getPositiveValue("time step");
        nPtr->n = nPtr->tfinal/nPtr->deltat;
        if(nPtr->n > MAX_SIZE)
            printf("Time step too small for final time (%d)\n", nPtr->n);
    }
    while(nPtr->n > MAX_SIZE);
}

/*----------------------------------------------------------
Function: getPositiveValue
Parameters:
    prompt - reference to string to include in the user prompt
Return value: positive value obtained from the user.
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
Function: getValue
Parameters:
    prompt - reference to string to include in the user prompt
Return value: value obtained from the user (may be positive or negative)
Description: Prompt the user for a value (using the prompt string)
    and checks that the value is positive.
-------------------------------------------------------------*/
double getValue(char *prompt)
{
    double value; // Value entered by the user.
    printf("Please enter a value for %s: ", prompt);
    scanf("%lf",&value);
    return(value);
}

/*----------------------------------------------------------
Function: calculateTemperatureAnalytical
Parameters:
    nPtr - reference to NEWTON structure variable.  Members used
            tempAmbiant - ambiant temperature
            k - proportionality constant
            tempInitial - initial temperature
            deltat - delta t variable
            n - number of elements used in time/velocity arrays
            t - array for saving time values
Description: Fills in the arrays with n points of
    time/temperature values using the analytical solution for the
    temperature.
-------------------------------------------------------------*/
void calculateTemperatureAnalytical(NEWTON *nPtr)
{
    double time = 0.0;
    int ix;
    for(ix = 0; ix < nPtr->n; ix = ix + 1)
    {
        nPtr->t[ix] = time;
        nPtr->temp[ix] = nPtr->tempAmbiant +
                         (nPtr->tempInitial - nPtr->tempAmbiant)*exp(-nPtr->k*time);
        time = time + nPtr->deltat;
    }
}

/*----------------------------------------------------------
Function: calculateTemperatureEuler
Parameters:
    nPtr - reference to NEWTON structure variable.  Members used
            tempAmbiant - ambiant temperature
            k - proportionality constant
            tempInitial - initial temperature
            deltat - delta t variable
            n - number of elements used in time/velocity arrays
            t - array for saving time values
            tempEuler - array for saving temperature values calculated
                        using Euler's method
Description: Fills in the arrays with n points of
    time/temperature values using the Euler's method for the
    velocity.
-------------------------------------------------------------*/
void calculateTemperatureEuler(NEWTON *nPtr)
{
	// Complete this function
}

/*----------------------------------------------------------
Function: plot
Parameters:
    pPtr - reference to NEWTON structure variable.  Members used
            tempAmbiant - ambiant temperature
            k - proportionality constant
            tempInitial - initial temperature
            deltat - delta t variable
            n - number of elements used in time/velocity arrays
            t - array for saving time values
            tempEuler - array for saving temperature values calculated
                        using Euler's method
Description: Initilialises the plot device,pen width,
             and plots both curves for the analytical and the
             Euler method.
----------------------------------------------------------------*/
void plot(NEWTON *nPtr)
{
    double maxTemp;   // maximum temperature
    double hold;
    char plotLabel[100];

    // Find the maximum temperature to scale the temperature axis
    maxTemp = getMax(nPtr->temp, nPtr->n);
    hold = getMax(nPtr->tempEuler, nPtr->n);
    if(hold > maxTemp) maxTemp = hold;
    maxTemp = 1.1*maxTemp;
    // Initiliaise the PLplot page
    plsdev("wingcc");  // Sets device to wingcc - CodeBlocks compiler
    // Initialise the plot
    plinit();
    plwidth(2);    // pen width
    plenv(0, nPtr->tfinal, 0, maxTemp, 0, 0);
    plcol0(GREEN);           // Select color for labels
    sprintf(plotLabel, "Temperature (k= %.3f tAmbiant = %.3f deltat = %.3f)",
            nPtr->k, nPtr->tempAmbiant, nPtr->deltat);
    pllab("Time t", "Temperature T(t)", plotLabel);
    // Plot the analytical curve
    plcol0(RED);
    pllsty(SOLID);
    plline(nPtr->n, nPtr->t, nPtr->temp);
    plptex(0.1*nPtr->tfinal, 0.9*maxTemp, 0, 0, 0, "Analytical");
    // Plot the euler curve
    plcol0(BLUE);
    pllsty(LNGDASH_LNGGAP);
    plline(nPtr->n, nPtr->t, nPtr->tempEuler);
    plptex(0.3*nPtr->tfinal, 0.9*maxTemp, 0, 0, 0, "Euler");
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




