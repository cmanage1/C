/*-------------------------------------------------
 File: parachutist.c   (Lab 5)
 Author:
 Description: Calculates change in velocity for
 the parachutist over time and displays a table
 showing the results.
-------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define symbolic constant
#define G 9.8   // in m/s^2
#define N 50    // number of data points to compute
#define TRUE 1
#define FALSE 0

// Declaration of a structure for user input
typedef struct
{
    // Add the members to the structure
    double weight;
    double drag;
    double finalTime;
    double times[N+1];
    double velocities[N+1];
} PARACHUTIST;

// Function prototypes
void getInput(PARACHUTIST *);
void computeVelocity(PARACHUTIST *);
void displayTable(PARACHUTIST *);

/*-------------------------------------------------------------
Function: main
Description:  This function controls the overall program.
              It makes three calls, one to get user input, one
              to compute time/velocity data points, and a third
              to display the calculated values in a table.
-------------------------------------------------------------*/
void main()
{
    PARACHUTIST para;  // A structure variable with parachutist data
    PARACHUTIST *pPtr;


    getInput(&para); // Get input from user
    computeVelocity(&para);// Compute time/velocity data points
    displayTable(&para);// Display the results
}

/*---------------------------------------------------------------------------
Function:  getInput
Parameters
   pPrt  - pointer to a PARACHUTIST structure variable
Description: Obtains from the user, the weight, drag and final time
             values and stores in the referenced data structure.
             All values must be greater than zero.
--------------------------------------------------------------------------*/
void getInput(PARACHUTIST *pPtr)
{
    // Declaration of variable

    //Get input from user
    printf("Please enter the weight of the parachutist:");
    do
    {
        scanf("%lf", &pPtr->weight);
        if (pPtr->weight <= 0.0)
            printf("Please enter a value greater than zero:");
    }while (pPtr->weight <= 0.0);



    printf("\nPlease enter the drag coefficient:");
    do
    {
        scanf("%lf", &pPtr->drag);
        if (pPtr->drag <= 0.0)
            printf("Please enter a value greater than zero:");
    }while (pPtr->drag <= 0.0);

    printf("\nPlease enter the final time:");
    do
    {
        scanf("%lf", &pPtr->finalTime);
        if (pPtr->finalTime <= 0.0)
            printf("Please enter a value greater than zero:");
    }while (pPtr->finalTime <= 0.0);
}

/*---------------------------------------------------------------------------
Function:  computeVelocity
Parameters
   pPrt  - pointer to a PARACHUTIST structure variable
Description: Using the weight, drag and final time values in the referenced
             structure, computes and stores N+1 points in the two arrays
             found in the referenced structure variable.
--------------------------------------------------------------------------*/
void computeVelocity(PARACHUTIST *pPtr)
{
    // Declaration of variables
    double vel;
    int i;
    double incr;
    double t;

    incr= pPtr->finalTime/(N);
    t=0.0;

    // Calculate the velocity points and store in the arrays
    for (i=0; i<(N+1); i++)
    {

        pPtr->times[i]=t;
        vel= (1.0-(exp(-( pPtr->drag/pPtr->weight )*t)));
        vel= ((G*pPtr->weight)/(pPtr->drag)*vel);
        pPtr->velocities[i]= vel;
        t+=incr;
    }
}

/*---------------------------------------------------------------------------
Function:  displayTable
Parameters
   pPtr  - pointer to a PARACHUTIST structure variable
Description: Displays a table of the calculated data points.
--------------------------------------------------------------------------*/
void displayTable(PARACHUTIST *pPtr)
{
    // Declaration of variables
    int ix;  // index into arrays

    // Display results
    printf("The change in velocity of the parachutist with weight %.2lf kg\nand a drag coefficient %.2lf kg/s is as follows.\n",
           pPtr->weight, pPtr->drag);
    printf("%10s    %10s\n","Time t", "Velocity v");
    printf("------------------------");
    // Display the contents of the table.

    for (ix=0; ix< (N+1); ix++)
    {
        printf("\n%.2lf         %.2lf", pPtr->times[ix], pPtr->velocities[ix]);
    }

}
