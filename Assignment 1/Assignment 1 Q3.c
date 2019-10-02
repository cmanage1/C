/*---------------------------------- RESISTANCE PROGRAM------------------------*/
#include <stdio.h>
#define Tref 20 //defining the reference temperature
double calculation(double RL, double CL, double alpha, double T); //declaring the function

/*---------------------------------- Main Function-----------------------------*/
void main()
{
    double RL, CL, alpha , T, R; //declaring all the variables in double so it's precise

    printf("\n Please enter the resistance value per unit length (ohms/m): ", RL);
    scanf("%lf", &RL); // the program is taking in a value for resistance value per unit length
    printf("\n Please enter the length of the conductor (m): ", CL);
    scanf("%lf", &CL); // the program is taking in a value for the length of the conductor

    printf("\nMaterial   -->  alpha value \
    \n\
    \n Nickel     --> 0.005866 \
    \n Iron       --> 0.005671 \
    \n Tungsten   --> 0.004403 \
    \n Aluminum   --> 0.004308 \
    \n Copper     --> 0.004041 \
    \n Steel      --> 0.003    \
    \n Constantan --> -0.000074\
    \n Silicon    --> -0.075   \
    \n Germanium  --> -0.048   \
    \n"); //This is the table for the alpha values of all the metals

    printf("\n Please enter the temperature coefficient of the material \n\
using the table above: ", alpha);
    scanf("%lf", &alpha); // The program is taking in the value for alpha

    printf("\nPlease enter the temperature of the material (degrees Celcius):", T);
    scanf("%lf", &T); // The program is taking in the value for the temperature

    R= calculation(RL, CL, alpha, T); // The function is being called to calculate resistance

    printf("\The resistance is %lf ohms when..\n\
           \nResistance value for unit length is %lf\n\
           \nLength of the conductor is %lf\n\
           \nThe resistance temperature coefficient is %lf\n\
           \nThe temperature of the material is %0.2lf\n\
           \nand The reference temperature is 20 degrees Celcius\n", R, RL, CL, alpha, T); //The program outputs all the resistance and all the values the user input
}
/*----------------------------- Calculation function----------------------------*/

double calculation(double RL, double CL, double alpha, double T) // The calculation function is taking in the values from the main function
{
    double Rr, Resistance; // variables are being declared inside the function

    Rr= ((RL)*(CL)); // The function is calculating the resistance at reference
    Resistance = (Rr*(1+(alpha*(T- Tref)))); // The function is calculating the material's reference
    return Resistance; // It is returning the value for resistance
}
