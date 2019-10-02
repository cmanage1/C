/*-----------------------------------------------------------------
Author: Chethin Manage
Date: Oct 12th 2018 (Fall 2018 Semester)
Course: GNG 1106
Description: This program calculates the average velocity of water in a
             in a rectangular open channel
------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#define NUM_VALUES 25 //the number of rows that needs to be printed out


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
double getPositiveValue();
double DisplayTable(CHANNEL channel);
double computeVelocity(CHANNEL channel, double depth);

/*-----------------------------------------------------------------
                        MAIN FUNCTION
Description: Gets all the inputs from the user, checks for positive
inputs by calling function "getPositiveValue" and calls the function
"DisplayTable" to print the outputs.
------------------------------------------------------------------*/
void main()
{
    CHANNEL channel; //defining structure as a variable

    printf("Give the name of the channel:"); //asks user input for channel name
    fgets(channel.name, 10, stdin); //scans 10 characters the user inputs and stores it in the variable
    printf("\nGive the coefficient of roughness:"); //asks user input for coefficient of roughness
    channel.n = getPositiveValue(); //calls function to check for - or 0 values
    printf("\nGive the slope:"); //asks user input for slop
    channel.slope = getPositiveValue();
    printf("\nGive the channel width:"); //asks user input for the channel width
    channel.width = getPositiveValue();
    printf("\nGive the maximum depth of the channel:"); //asks user input for max depth
    channel.maxDepth= getPositiveValue();

    DisplayTable(channel); //calls the function to display the table
}



/*------------------------------------------------------------------------
                     POSITIVE VALUE CHECK FUNCTION
Returns: A positive value that the user input
Description: This function scans the user input and determines if it is
positive. If 0 or negative, the user is asked to enter their input again.
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


/*------------------------------------------------------------------------------
                        DISPLAY TABLE FUNCTION
Parameters:
        channel - structure with all variables stored
Description: This function first calculates the values that need to be printed
on the table by calling the "computeVelocity" function. Then prints those values
on a table.
-------------------------------------------------------------------------------*/
double DisplayTable (CHANNEL channel)
{
    int i; //variable used as a counter for the 'for' loop
    double incr; //variable for the increment
    double d; //variable for depth for each row of the table
    double depths[NUM_VALUES]; //array of values for depth (stores 25 values)
    double velocity[NUM_VALUES]; //array of values for velocity (stores 25 values)

    incr= channel.maxDepth/(NUM_VALUES); //the increment in which the depth value of the table goes up by
    d= incr; //the first value for density gets set to the increment instead of 0 because the function\
                cannot calculate a value when density is 0

    printf("Channel data for '%s'\
           \n  Coefficient of roughness: %.4lf\
           \n  Slope: %.5lf\
           \n  Width: %.2lf\
           \n  Maximum Depth: %.2lf", channel.name, \
           channel.n, channel.slope, channel.width, channel.maxDepth); //prints what the user input

    printf("\nDepth        Average Velocity\
          \n-----------------------------");
           for (i=0; i < (NUM_VALUES); i++) //the loop increases by 1 every time until it reaches 25
           {
               depths[i]= d; //the first of 'i' is set to the first value of density in the array
               velocity[i]= computeVelocity(channel, d); //the first value of 'i' gets set to the first value of velocity in the array
               printf("\n%.4lf               %.6lf", depths[i], velocity[i]); //prints out the calculated values in this loop
               d += incr; //the density value goes up by the value of the increment
           }
}


/*------------------------------------------------------------------------
                            CALCULATION FUNCTION
Parameters:
        channel- the structure in which all the user inputs are stored
        d- the density value in which the average velocity needs to be
        calculated for
Returns:
        vel= the average velocity at a certain density
Description: This function calculates the average velocity and returns it to
"DisplayTable" where it is being called.
--------------------------------------------------------------------------*/
double computeVelocity(CHANNEL channel, double d)
{
    double vel; //declaring variable for velocity
    double x, y; //declaring variables to help write down the equation

    //equations to calculate Average Velocity at a certain density
    vel= (sqrt(channel.slope))/channel.n;
    x= ((channel.width/d)/(channel.width+ 2.0*d));
    y= 2.0/3.0;
    vel= (pow(x,y) ) * vel;

    return vel;
}
