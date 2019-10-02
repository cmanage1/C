/*------------------------------------------------------------------
 File:  cylinderVolume.c  (Lab 4)
 Description: Calculates how the volume changes w.r.t the depth
              of a liquid in a cylinder.
------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
// Define symbolic constant
#define TRUE 1
#define FALSE 0
#define NUM_VALUES 20  // Number of time/velocity values to display
#define D_IX 0 // Index for elements containing depth values (row 0)
#define V_IX 1 // Index for elements containing volume values (row 0)
// Definition of a structure type for user input
typedef struct
{
    char orientation;  // h for horizontal and v for vertical
    double radius;  // in m
    double length;    // in m
} CYLINDER;
// Prototypes
double getPositiveValue();
char getOrientation();
double computeVolume(CYLINDER, double);
/*--------------------------------------------------------------------
Function: main
Description:  Gets from the user values for the radius and lenght of the
              cylinder as well as it orientation. Fills an array with
              depth/volume values and then displays in a table these values.
----------------------------------------------------------------------*/
int main()
{
    // Variable declarations
    CYLINDER cyl;  // structure variable fo cylinder
    // Note in the following 2D array
    //      points[D_IX] is a 1D array that contains the depth values
    //      points[V_IX] is a 1D array that contains the volume values
    double points[2][NUM_VALUES];  // NUM_VALUES points of depth/volume
    // to fill the arrays
    double depth; // depth of the liquid
    int ix;   // for indexing the columns in the 2D array
    double inc;  // for incrementing the depth

    // Get input from user, the cylinder radius and length
    printf("Please enter the value for the cylinder radius: ");
    cyl.radius = getPositiveValue();
    printf("Please enter the value for the cylinder length: ");
    cyl.length = getPositiveValue();
    cyl.orientation = getOrientation();
    // Fill the 2D array with depth/volume values
    depth = 0;
    if(cyl.orientation == 'v') inc = cyl.length/(NUM_VALUES-1);
    else  inc = cyl.radius/(NUM_VALUES-1);
    for(ix = 0; ix < NUM_VALUES; ix = ix + 1)
    {
        points[D_IX][ix] = depth;
        points[V_IX][ix] = computeVolume(cyl, depth);
        cyl.depth = cyl.depth + inc;
    }
    // Display results
    printf("The change in liquid volume of the cylinder with radius %.2f \nand length %.2f as depth changes when ",
           cyl.radius, cyl.length);
    if(cyl.orientation == 'v') printf("vertical\n");
    else printf("horizontal\n");
    printf("%10s    %10s\n","Depth", "Volume");
    printf("------------------------\n");
    for(ix = 0; ix <= NUM_VALUES; ix = ix + 1)
        printf("%10.3f    %10.2f\n", points[V_IX][ix], points[C_IX][ix]);
    return(0);
}
/*------------------------------------------------------------------------
Function: getPositiveValue
Returns: A value strictly positive (>0)
Description: Reads a real value from the user, checks that it is strickly
             positive, and returns the value.
------------------------------------------------------------------------*/
double getPositiveValue()
{
    double value;
    do
    {
        scanf("%lf",&value);
        if(value <= 0.0)
            printf("The value must be greater than zero: \n");
    }
    while(value <= 0.0);
    return(value);
}
/*-----------------------------------------------------------------------
Function: getOrientation
Returns: 'v' for vertical and 'h' for horizontal.
Description: Requests from the user the orientation of the
             cylinder: v for vertical and h for horizontal
------------------------------------------------------------------------*/
char getOrientation()
{
    char orientation;
    int flag;
    do
    {
        flag = FALSE;
        printf("Give the cylinder's orientation, v for vertical, h for horizontal: ");
        fflush(stdin);
        scanf("%c", &orientation);
        if(orientation != 'v' && orientation != 'h')
        {
            printf("Bad input.\n");
            flag = TRUE;
        }
    }
    while(flag);
    return(orientation);
}
/*------------------------------------------------------------------------
Function: computeVolume
Parameter
    cyl - CYLINDER structure variable
    depth - depth of the liquid in the cylinder
Returns: The volume of the liquid in the cylinder
Description: Computes the volume of a liquid in a cylinder with
             the radius, length and orientation given in cyl.
------------------------------------------------------------------------*/
double computeVolume(CYLINDER cyl, double depth)
{
    // Declaration of variables
    double vol;   // liquid volume
    // Computation depends on orientation of the cylinder
    if(cyl.orientation = 'v')
        vol = M_PI*cyl.radius*cyl.radius*depth;
    else
    {
        // Utilise plusieurs intructions pour faire le calcule
        // Les valeurs intermédiaires sont accumulées dans vol
        vol = sqrt(2*radius*depth - depth*depth);
        vol = (cyl.radius - depth)*vol;
        vol = (pow(cyl.radius,2)*acos((cyl.radius - depth)/cyl.radius)) - vol;
        vol = vol*cyl.length;
    }
    return(vol);
}
