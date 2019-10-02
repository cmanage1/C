/*-----------------------------------------------------------------
Author: cmanage1
Date: Oct 20th 2018 (Fall 2018 Semester)
Course: GNG 1106
Description: This program calculates the average velocity of water in a
             in a rectangular open channel with separate functions.
------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#define NUM_VALUES 20
#define NUM_ROWS 2
#define A_I 0
#define Y_I 1
#define TRUE 1
#define FALSE 0



/*-----------------------Defining Structure-----------------------*/
typedef struct
{
    char name[10]; //name of the forest
    double totalAcres; //total number of acres
    double minAcres; //minimum number of acres uncut
    double maxAcres; //maximum number of acres uncut
    double rate; //reforestation rate
} FOREST;

//function prototypes
void getForestInput(FOREST *);
double getPositiveValue();
void calculateTableData(FOREST *ptr, int n, double *, double *);
void displayTable(FOREST *ptr, int n, double *, double *);


/*-------------------------------------------------------------------
                            MAIN FUNCTION
Description: This function calls three functions to get inputs, fill
            fill the arrays, and print out the table at the end. After
            these functions, the main function will ask the user if
            they wish to keep going with the program.
--------------------------------------------------------------------*/
void main()
{
    int endProgram; //defining a flag to quit the loop and end program
    endProgram=FALSE;

    do
    {
        FOREST forest; //declaring the structure variable

        double data[NUM_VALUES][NUM_VALUES]; //declaring a 2D array

        getForestInput(&forest); //calling function to get input
        calculateTableData(&forest, NUM_VALUES, data[A_I], data[Y_I]); //calling function to fill the arrays
        displayTable(&forest, NUM_VALUES, data[A_I], data[Y_I]); //calling function to print the table

        int badInput;  //defining a flag to differentiate a bad input
        badInput=FALSE;

        do
        {
            char input; //declaring the character input variable (y/n)

            printf("\nDo you wish to quit the program(y/n):");
            scanf("%s", &input); //scanning user input
            if (input == 'y')
                {
                endProgram = TRUE; //flag set TRUE to end program (break out of the loop)
                badInput=FALSE; //flag set FALSE to break out of the loop
                printf("\n**PROGRAM TERMINATED**\n");}
            else if (input == 'n')
                {
                fflush(stdin); //clears all the values assigned to variables
                endProgram = FALSE;
                badInput=FALSE;
                printf("\n**This program will now restart**\n\n");}
            else
                {
                printf("\nPlease enter a valid input!\n");
                badInput=TRUE;}
        }while (badInput==TRUE); //loop while keep going when flag is set TRUE

    }while (endProgram == FALSE); //loop will keep going when flag is set FALSE

}


/*----------------------------------------------------------------------
                            FUNCTION TO GET INPUT
Parameters:
            FOREST *ptr- a pointer to the structure FOREST. Used to assign
            input values into the structure.
Description: This function will ask the user to input values and stores them
            in the structure FOREST. The function will also call function
            getPositiveValues in order to check for negatives. The function
            will also check if the minAcres is less than the maxAcres.
----------------------------------------------------------------------*/
void getForestInput(FOREST *ptr)
{
    int flag; //declaring a flag so that loop keeps going at bad inputs
    flag=FALSE;

    printf("Forest name: "); //gets the name of the forest from user
    fgets(ptr->name, 10, stdin); //this functions uses a pointer to store input in structure

    do{
    if (flag== TRUE) //this will prompt the user to enter their values again when the loop starts again
        printf("\nPlease enter all the values again\n\n");

    printf("Total acres: "); //gets the total acres from user
    ptr->totalAcres=getPositiveValue(); //checks if value is greater than or equal to 0

    printf("Areas Uncut Minimum: ");
    ptr->minAcres=getPositiveValue();

    printf("Areas Uncut Maximum: ");
    ptr->maxAcres=getPositiveValue();
        if (ptr->minAcres >= ptr->maxAcres) //makes sure minimum is less than max
        {
            printf("\n**The Areas Uncut Minimum has to be less than Areas Uncut Maximum!**");
            flag = TRUE; //flag set true to keep the loop going
        }
        else if (ptr->totalAcres <= ptr->maxAcres) //makes sure total is more than max
        {
            printf("\n**The Maximum Area Uncut is greater than the Total Area!**");
            flag = TRUE; //flag set true to keep the loop going
        }
        else
            flag =FALSE; //flag turns to FALSE if no bad inputs are found (breaks out of the loop)
    }while (flag == TRUE);

    //flag stays false from the last loop
    //this loop is to  make sure rate stays between 0 and 1
    do
    {
        printf("Reforestation rate: ");
        ptr->rate=getPositiveValue();
        if (ptr->rate >= 1.0 || ptr->rate < 0.0)
        {
            printf("\nThe rate must be between 0 and 1!\n");
            flag=TRUE; //sets flag to TRUE so the loop keeps going
        }
        else
            flag=FALSE; //sets flag to FALSE
    }while (flag == TRUE); //breaks out of loop of flag is FALSE

}


/*-----------------------------------------------------------------------
                    FUNCTION TO CHECK POSITIVE VALUES
Returns:
        value - a double value which is the user input
Description: Checks if the user input is greater than or equal to 0 and
            returns "value" to main function.
------------------------------------------------------------------------*/
double getPositiveValue()
{
    double value; //declares variable that the function will return
    do
    {
        scanf("%lf", &value);
        if (value <= 0.0)
            printf("\nPlease enter a value above zero:");
    }while (value <= 0.0 ); //loop keeps going while the user input is less than or equal to 0
    return value; //function return
}

/*------------------------------------------------------------------------
                    FUNCTION TO FILL IN TABLE DATA
Parameters:
        FOREST *ptr- A pointer used to access the values in the structure FOREST
        n- an integer with the number of values (used instead of using symbolic constants)
        *area- a pointer used to access values in the first part of the 2D array
        *years- a pointer used to access values in the second part of the 2D array
Description: This function fills in the arrays using a nested loop
-------------------------------------------------------------------------*/
void calculateTableData(FOREST *ptr, int n, double *area, double *years)
{
    int i; //declaring variable used in the foor
    double unCutA=ptr->minAcres; //declaring and making the first value of the array equal to min acres
    double reforest; //declaring a value used for area that is reforested
    double incr= (ptr->maxAcres - ptr->minAcres)/(n-1); //increment that the first column goes up by

    for (i=0; i< n; i++) //the loop counter goes up untilmax number of values
    {
        years[i]=0; //the number of years to reforest gets set to 0
        area[i]=unCutA; //the first area value is set equal to the min areas uncut
        reforest=unCutA; //sets the reforest
        do
        {
            reforest+= ((ptr->rate)*(reforest)); //the area reforested gets added to the previous value of it multiplied by the rate
            years[i] += 1; //the number of years goes up by 1 every time while loop repeats
        }while (reforest < ptr->totalAcres); // loop repeats while area reforested is less than total area
        unCutA+= incr; //the uncut area goes up by the increment every time for loop repeats
    }
}

/*------------------------------------------------------------------------
                    FUNCTION TO DISPLAY TABLE
Parameters:
        FOREST *ptr- A pointer used to access the values in the structure FOREST
        n- an integer with the number of values (used instead of using symbolic constants)
        *area- a pointer used to access values in the first part of the 2D array
        *years- a pointer used to access values in the second part of the 2D array
Description: This function prints out the with all calculated data
-------------------------------------------------------------------------*/
void displayTable(FOREST *ptr, int n, double *area, double *years)
{
    int i; //an integer to be used in the for loop

    printf("Forest: %s\
           \n     Uncut Area: min = %.2lf, max = %.2lf\
           \n     Reforestation Rate: %.3lf\n"\
           , ptr->name, ptr->minAcres, ptr->maxAcres, ptr->rate); //printing all user inputs

    printf("\nUncut Area Start           Num Years For Total Reforestation");
    for (i=0; i < n; i++) //for loop used to access separate values in the arrays
    {
        printf("\n      %.2lf                     %.0lf", area[i], years[i]); //prints out the arrays
    }

}
