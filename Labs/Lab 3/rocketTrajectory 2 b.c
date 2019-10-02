/*-------------------------------------------------
File: RocketTrajectory.c
Author: Gilbert Arbez, Fall 2018
Description: Calculates and displays the change
in velocity of rocket as a function of time.
-------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Define symbolic constant
#define TRUE 1
#define FALSE 0
#define NUM_ROWS 25
#define e M_E



// Function prototypes
void displayTrajectoryTable(double, double);
double computeVelocity(double);
/*----------------------------------------------------
Function: main
Description: Gets valid input from user for start and end
times to create table rows, then
displayTrajectoryTable to display the trajectory
table.
-----------------------------------------------------*/
void  main()
{
    double startTime, endTime; // times for creating table.
    int badInput; // Flag used in loop to get user input

    do
    {
        badInput=TRUE;
        printf("\nPlease enter the start and end time of the rocket(in seconds):");
        scanf("%lf %lf", &startTime, &endTime);
        if (endTime > startTime)
        badInput=FALSE;
        else
        {
    printf("\nThe start time you entered is larger than your end time!\
    \nPlease enter a another start and end time for the rocket\n");
    }
}while (badInput == TRUE);
// Display Table

displayTrajectoryTable(startTime, endTime);
}

/*---------------------------------------------------------------------------------*/
void displayTrajectoryTable(double start, double end)
{
double increment;

    printf("\nTime            Velocity\
            \n-----------------------");
    increment=((end - start)/(NUM_ROWS -1));

for (double vel; start <= end; start += increment)
    {
    vel= computeVelocity(start);
    printf("\n%.2lf          %.2lf", start, vel);
    }
}

/*---------------------------------------------------------------------------------*/
double computeVelocity(double t) //done
{
double vel; // rocket velocity
double x;
    if ((t>=0    &&   t<=10))
        vel= 11*t*t - 5*t;
    else if (( t > 10)   &&   (t <= 20))
        vel= (1100 - (5*t));
    else if ( (t>20) && (t<=30) )
        vel= (50*t) + (2*(t-20)*(t-20));
    else if (t>30)
        {
        x= (-0.2*(t-30));
        vel=  1520 *(pow((e), (x)));
        }
    else
        vel=0;
    return(vel);
}
