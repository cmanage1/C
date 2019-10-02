/*------------------ PLANE SPEED PROGRAM---------------------------*/

#include <stdio.h>

double calculateSpeed (double t); //declaring the function

/*----------------------main function-------------------------------*/

void main()
{
    double v, t; //declaring the two main variables

    printf("Enter the time t(s) after the plane's acceleration:  ");
    scanf("%lf", &t); //The program takes in the value for time
    v= calculateSpeed(t); //The main function is calling the calculation function
    printf("At time %0.2lf, the speed of the aircraft is %0.5lf m/s" , t, v); //The program outputs the time and speed
}

/*-------------------- calculate speed function--------------------*/

double calculateSpeed (double t)
{
    double speed; //the variable for speed inside the secondary function is being defined
    speed = 0.00001*(t*t*t) - 0.00488*(t*t) + 0.75795*(t) + 181.3566 ; //The speed is being calculated through the equation
    return speed; //the secondary function is returning the value for speed

}
