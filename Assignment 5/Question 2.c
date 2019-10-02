/*-----------------------------------------------------------------
Author: cmanage1
Date: Oct 20th 2018 (Fall 2018 Semester)
Course: GNG 1106
Description: This program calculates the average velocity of water in a
             in a rectangular open channel with separate functions.

------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#define NUM_VALUES 25 //the number of values that need to displayed
#define NUM_ROWS 2 //the number of rows in 2D array (depth and velocity)
#define D_IX 0 //index for depth values
#define V_IX 1 //index for velocity values

/*--------------structure for holding the variables---------------*/
typedef struct
{
    char name[10]; //name of the channel
    double n; //roughness coefficient
    double slope; //value of S
    double width; //value of B
    double maxDepth; //maximum water depth possible

} CHANNEL;
/*----------------------------------------------------------------*/

//function prototypes
void getInput(CHANNEL *);
double getPositiveValue();
void fillArray(CHANNEL *, int n, double[][n]);
double computeVelocity(CHANNEL *, double);
double displayTable(CHANNEL *, int n, double *, double *);

/*-----------------------------------------------------------------
                        MAIN FUNCTION
Description: Gets all the inputs from the user, checks for positive
            inputs by calling function "getPositiveValue" and calls the function
            "DisplayTable" to print the outputs.
------------------------------------------------------------------*/
void main()
{
    CHANNEL channel; //defining structure as a variable

    //This is a 2 dimensional array
    //[D_I] contains the depth values
    //[V_I] contains the velocity values
    double values[NUM_ROWS][NUM_VALUES];

    getInput(&channel); //calling function to get inputs
    fillArray(&channel, NUM_VALUES, values); //calling function to fill the 2D array
    displayTable(&channel, NUM_VALUES, values[D_IX], values[V_IX]); //calls the function to display the table
}


/*---------------------------------------------------------------------------
                               FUCNTION GET INPUT
Parameters:
        *ptr- A pointer to structure CHANNEL
Description: This function gets the users input and then assigns it to the
            proper variable in the structure CHANNEL using pointer *ptr
-----------------------------------------------------------------------------*/
void getInput(CHANNEL *ptr)
{
    printf("Give the name of the channel:"); //asks user input for channel name
    fgets(ptr->name, 10, stdin); //scans 10 characters the user inputs and stores it in the variable

    printf("\nGive the coefficient of roughness:"); //asks user input for coefficient of roughness
    ptr->n = getPositiveValue(); //calls function to check for - or 0 values

    printf("\nGive the slope:"); //asks user input for slope
    ptr->slope = getPositiveValue();

    printf("\nGive the channel width:"); //asks user input for the channel width
    ptr->width = getPositiveValue();

    printf("\nGive the maximum depth of the channel:"); //asks user input for max depth
    ptr->maxDepth= getPositiveValue();
}

/*------------------------------------------------------------------------
                     POSITIVE VALUE CHECK FUNCTION
Returns: A positive value that the user input
Description: This function scans the user input and determines if it is
            positive. If 0 or negative, the user is asked to enter an input again.
--------------------------------------------------------------------------*/
double getPositiveValue()
{
    double value; //declares value; the variable inside the function as a double
    do
    {
        scanf("%lf", &value); //scans what the user entered
        if (value <= 0.0) // if user input is 0 or less. another chance to input is give
            printf("\nThe value you entered must be greater zero:"); //prompted message to user
    }while (value <= 0.0); //this loops keeps on going until the user inputs greater than 0

    return value; //returns the input back to main function so it can get assigned to the desired variable
}


/*---------------------------------------------------------------------------
                        FUNCTION THAT FILLS VALUE ARRAYS
Parameters:
        *ptr- A pointer to the structure CHANNEL
        n- the number of values that need to be calculated
            (number of columns in the 2D array)
        mat-a pointer to the 2D array values with n, the number
            of columns
Description: This functions fills 2D array values with depth and velocity values
            calculated using the computeVelocity function
----------------------------------------------------------------------------*/
void fillArray(CHANNEL *ptr, int n, double mat[][n])
{
    int i;
    double incr;
    double depth;
    CHANNEL channel;

    incr= ptr->maxDepth/(NUM_VALUES); //the increment in which the depth value of the table goes up by
    depth= incr; //the first value for density gets set to the increment instead of 0 because the function\
                cannot calculate a value when density is 0

    for (i=0; i<NUM_VALUES; i++)
    {
        mat[D_IX][i]= depth; //the first of 'i' is set to the first value of density in the array
        mat[V_IX][i]= computeVelocity(ptr, depth); //the first value of 'i' gets set to the first value of velocity in the array
        depth += incr; //the density value goes up by the value of the increment
    }
}
/*------------------------------------------------------------------------------
                        DISPLAY TABLE FUNCTION
Parameters:
        channel - structure with all variables stored
Description: This function first calculates the values that need to be printed
            on the table by calling the "computeVelocity" function. Then prints those values
            on a table.
-------------------------------------------------------------------------------*/
double displayTable (CHANNEL *ptr, int n, double *depth, double *velocity)
{
    int i; //variable used as a counter for the 'for' loop

    printf("Channel data for '%s'\
           \n  Coefficient of roughness: %.4lf\
           \n  Slope: %.5lf\
           \n  Width: %.2lf\
           \n  Maximum Depth: %.2lf", ptr->name, \
           ptr->n, ptr->slope, ptr->width, ptr->maxDepth); //prints what the user input

    printf("\nDepth        Average Velocity\
          \n-----------------------------");
           for (i=0; i < NUM_VALUES; i++) //the loop increases by 1 every time until it reaches 25
           {
                printf("\n%.2lf               %.4lf", depth[i], velocity[i]); //prints out arrays
           }
}

/*------------------------------------------------------------------------
                            CALCULATION FUNCTION
Parameters:
        *ptr- a pointer to the structure CHANNEL
        d - the incremented depth value that goes into the equation
Returns:
        vel- the average velocity at a certain density
Description: This function calculates the average velocity and returns it to
        "DisplayTable" where it is being called.
--------------------------------------------------------------------------*/
double computeVelocity(CHANNEL *ptr, double d)
{
    double vel; //declaring variable for velocity
    double x, y; //declaring variables to help write down the equation

    //equations to calculate Average Velocity at a certain density
    vel= (sqrt(ptr->slope))/ptr->n;
    x= ((ptr->width/d)/(ptr->width+ 2.0*d));
    y= 2.0/3.0;
    vel= (pow(x,y) ) * vel;

    return vel;
}
