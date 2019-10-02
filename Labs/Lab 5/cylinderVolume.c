/*------------------------------------------------------------------
 File:  cylinderVolume.c  (Lab 5)
 Description: Calculates how the volume changes w.r.t the depth
              of a liquid in a cylinder.
------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
// Define symbolic constant
#define TRUE 1
#define FALSE 0
#define NUM_VALUES 20  // Number of time/velocity values to display
#define NUM_ROWS 2  // Number of rows in 2D array - one for depth and one for volume
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
void getInput(CYLINDER *);
double getPositiveValue(char *);
void fillArray(CYLINDER *, int n, double[][n]);
double computeVolume(CYLINDER *, double);
void displayTable(CYLINDER *, int n, double *, double *);
/*--------------------------------------------------------------------
Function: main
Description:  Gets from the user values for the radius and length of the
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
    double values[NUM_ROWS][NUM_VALUES];  // NUM_VALUES depth/volume value pair
    // Get user input
    getInput(&cyl);
    // Fill in the array with depth/volume values
    fillArray(&cyl, NUM_VALUES, values);
    // Display table on console
    displayTable(&cyl, NUM_VALUES, values[D_IX], values[V_IX]);
    return(0);
}
/*-----------------------------------------------------------------------
Function: getOrientation
Description: Requests from the user the orientation of the
             cylinder: v for vertical and h for horizontal
------------------------------------------------------------------------*/
void getInput(CYLINDER *cylPtr)
{
    int flag;
    // Get the cylinder radius and length
    cylPtr->radius = getPositiveValue("Please enter the value for the cylinder radius: ");
    cylPtr->length = getPositiveValue("Please enter the value for the cylinder length: ");
    // Get the orientation of the cylinder
    do
    {
        flag = FALSE;
        printf("Give the cylinder's orientation, v for vertical, h for horizontal: ");
        fflush(stdin);
        scanf("%c", &cylPtr->orientation);
        if(cylPtr->orientation != 'v' && cylPtr->orientation != 'h')
        {
            printf("Bad input.\n");
            flag = TRUE;
        }
    }
    while(flag);
}
/*------------------------------------------------------------------------
Function: getPositiveValue
Parameter:
    prompt: reference to a prompt message to the user
Returns: A value strictly positive (>0)
Description: Prompts for and reads a real value from the user, checks that it is strickly
             positive, and returns the value.
------------------------------------------------------------------------*/
double getPositiveValue(char *prompt)
{
    double value;
    do
    {
        printf(&prompt);
        scanf("%lf",&value);
        if(value <= 0.0)
            printf("The value must be greater than zero.\n");
    }
    while(value <= 0.0);
    return(value);
}
/*-----------------------------------------------------------------------
Function: fillArray
Parameters:
    cyl: pointer to a variable structure that gives the cylinder characteristics
    n: gives the number of colums in the 2D array and thus the number of depth/volume
        pairs to store in the 2D array
    mat: pointer to a 2D array of double values with n columns.
Descripton: Fills the 2D array (matrix) which contains the depth/volume values.
            The values of the volume are computed with calls to computeVolume.
-------------------------------------------------------------------------*/
void fillArray(CYLINDER *cyl, int n, double mat[][n])
{
   // to fill the array
    double depth; // depth of the liquid
    int cix;   // for indexing the columns in the 2D array
    double inc;  // for incrementing the depth
    // Fill the 2D array with depth/volume values
    depth = 0;
    if(cyl->orientation == 'v') inc = cyl->length/(NUM_VALUES-1);
    else  inc = cyl->radius/(NUM_VALUES-1);
    for(cix = 0; cix < NUM_VALUES; cix = cix + 1)
    {
        mat[cix][D_IX] = depth;
        mat[cix][V_IX] = computeVolume(cyl, depth);
        depth = depth + inc;
    }
}
/*------------------------------------------------------------------------
Function: computeVolume
Parameter
    cyl - pointer to a CYLINDER structure variable
    depth - depth of the liquid in the cylinder
Returns: The volume of the liquid in the cylinder
Description: Computes the volume of a liquid in a cylinder with
             the radius, length and orientation given in cyl.
------------------------------------------------------------------------*/
double computeVolume(CYLINDER *cyl, double depth)
{
    // Declaration of variables
    double vol;   // liquid volume
    // Computation depends on orientation of the cylinder
    if(cyl->orientation == 'v')
        vol = M_PI*cyl->radius*cyl->radius*depth;
    else
    {
        // Utilise plusieurs intructions pour faire le calcule
        // Les valeurs intermédiaires sont accumulées dans vol
        vol = sqrt(2*cyl->radius*depth - depth*depth);
        vol = (cyl->radius - depth)*vol;
        vol = (pow(cyl->radius,2)*acos((cyl->radius - depth)/cyl->radius)) - vol;
        vol = vol*cyl->length;
    }
    return(vol);
}
/*-----------------------------------------------------------------------
Function: displayTable
Parameters:
    cyl - pointer to a variable structure that gives the cylinder characteristics.
    int n - nnumber of elements in the referenced arrays
    depth - pointer to an array that contains the depth values
    volume - pointer to an array that contains the volume values
Description: Displays the characteristics of the cylinder followed by
             a table that shows how the volume varies the depth of a liquide
             in the cylinder.  The data is given  in the arrays referenced
             by the parameters.
------------------------------------------------------------------------*/
void displayTable(CYLINDER *cyl, int n, double *depth, double *volume)
{
    // Declaration of variables
    int ix;  // Index into arrays.
     // Display results
    printf("\nThe change in liquid volume of the cylinder with radius %.2f \nand length %.2f as depth changes when ",
           cyl->radius, cyl->length);
    if(cyl->orientation == 'v') printf("vertical\n");
    else printf("horizontal\n");
    printf("%10s    %10s\n","Depth", "Volume");
    printf("------------------------\n");
    for(ix = 1; ix < n; ix = ix + 1)
        printf("%10.3f    %10.2f\n", depth[ix], volume[ix]);
}
