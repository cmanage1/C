#include <stdio.h>
#include <math.h>
#define FALSE 0
#define TRUE 1

double getNumTerms();
double coshyper(double, int);

/*----------------------------------main function-------------------------------------------*/
void main()
{

    double coshx, x, n; //declaring variables for answer, input for x and input for terms
    int badInput, keepGoing, endProgram, N; //defining the logical variables
    badInput=TRUE; //a flag used to differentiate between a valid input for y/n
    keepGoing=TRUE; //a flag used to break out of the Yes or NO loop
    endProgram=FALSE; //a flag used to end the program
    char decision;

    do{
    printf("\nPlease enter a real value for x:");
    scanf("%lf", &x); //gets x value from the user

    N = getNumTerms(); //calls the function that gets the value for number of terms
    coshx= coshyper(x, N); //calls the function that calculates coshx
    printf("cosh(%lf) is %.5e", x, coshx); //prints the output

    /*-----------------------YES OR NO LOOP--------------------------*/
    do{
        printf("\nDo you want to quit (y/n):"); //asks user if they want to exit the program
        scanf("%s", &decision);
        if (decision == 'y') //if user types y program quits
            {
            printf("Program Terminated");
            keepGoing = FALSE; //used to break out of the yes or no loop
            endProgram = FALSE; //used to break out of loop AND end the program
            }
        else if (decision == 'n') //if user types n program goes back to beginning
            {
                fflush(stdin); //clears all variables
                keepGoing = FALSE; //used to break out of the yes or no loop
                badInput=TRUE; //used to define a value for badInput once again since all values got cleared
                endProgram=TRUE; //defines another value foe EndProgram because all values g
            }
        else
            {
                printf("Please enter a valid input"); //goes back to beginning of loop
            }
        }while (keepGoing == TRUE); //the loop will continue if the user does not input "y" or "n"
       /*-----------------------------------------------------------*/

    }while (badInput == TRUE && endProgram == TRUE); //the loop will continue if badInput is set as TRUE and end program is not set as FALSE
}


/*---------------------Function to get  number of terms--------------*/
double getNumTerms()
{
    double terms; //defines variable for terms
    int badTerms; //defines variable for logical variable badTerms
    badTerms= TRUE; //flag to break out of the loop

    do{
    printf("\nHow many terms to use:");
    scanf("%lf", &terms); //gets the number of terms from the user

    if (terms > 0) //if the user enters a valid value for terms the loop breaks and returns a value to the main function
        {
        badTerms=FALSE;
        return (terms);

        }
    else
        printf("\nThe number of terms you entered is invalid\
             \nPlease enter a value greater than 0 for terms"); //prints a warning when wrong value is entered

    }while (badTerms == TRUE); //loop continues while a bad value is entered
    }


/*-------------------Function to calculate cosh(x)------------------*/

double coshyper(double x,int terms)
{

    double t; //variable for final answer
    double tPrevious; //variable for calculating previous t
    int i; //counter

    t= (pow(x,2))/(2); //equation for t
    tPrevious= (pow(x,2))/(2); //equation for previous t (same as regular t)
    for (i=2; i <= terms; i ++) //loop for calculating t
    {
        t = t+(tPrevious*(((x*x)/((2*i)*(2*i-1))))); //calculates a value for t using previous t
        tPrevious= tPrevious*(pow(x,2)); //updates the previous value from the loop before
        tPrevious= tPrevious/((2*i)*(2*i-1));
    }
    t= t+1; //this adds on the 0th term (which =1) at the end of the function
    return(t);
}
