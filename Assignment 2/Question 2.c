#include <stdio.h>
#include <math.h>
#define pi M_PI //declaring "pi" as 3.1415....


double totalWeight(int n, double density, double thickness, double d2, double d1); //declaring the calculation function

/*----------------------------main function--------------------------------------*/
void main() //main function
{
    // declaration of variables
    int n; //number of washers
    double density; //density of the washer's material in kg/cm^3
    double thickness; // thickness (x) of the washer in cm
    double d2; //external diameter of the washer in cm
    double d1; //the diameter of the hole of the washer in cm
    double weight; //the weight of the washers

    printf("Please enter the number of washers: "); //asking the user for n
    scanf("%d", &n); //scanning user input
    printf("\nPlease enter the density of the washer's material (kg/cm^3):"); //asking the user for d of washer
    scanf("%lf", &density); //scanning user input
    printf("\nPlease enter the thickness of the washer (cm):"); //asking the user for x
    scanf("%lf", &thickness); //scanning user input
    printf("\nPlease enter the external diameter of the washer (cm):"); //asking the user for the external diameter (d2)of the washer
    scanf("%lf", &d2); //scanning user input
    printf("\nPlease enter the diameter of the hole of the washer (cm):"); //asking the user for the diameter of the hoke (d1)
    scanf("%lf", &d1); //scanning user input
    weight = totalWeight(n, density, thickness, d2, d1); //calling the function to calculate weight
    printf("The washer characteristics are");  //printing what the user input at the start of the program
    printf("\n Density : %.5lf kg/cm^3", density); //^
    printf("\n Thickness : %.3lf cm", thickness); //^
    printf("\n External diameter : %.3lf cm", d2); //^
    printf("\n Diameter of the hole : %.3lf cm", d1); //^
    printf("\nThe weight of %d washer(s) is %.2e kg", n, weight); //printing the calculated value\
    for weight of the washer(s) in scientific notation

}

/*----------------------------calculation function--------------------------------------*/
double totalWeight(int n, double d, double x, double d2, double d1) //function to calculate weight
{
    double weight; //defining weight inside the function

    weight= pow(d2, 2) - pow(d1, 2); //equation 1 for calculating weight
    weight= n*x*d*pi*weight; //equation 2 for calculating weight
    weight= weight/4.0; //equation 3 for calculating weight
    return (weight); //returning weight (a double) from the secondary function to the main function where it is being called
}
