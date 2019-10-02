#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SMALL_NUMBER 1e-10
#define N 25
#define TRUE 1
#define FALSE 0
#define two 2.0
#define F_LO 0.008
#define F_HI 0.08

typedef struct
{
    double rough; //pipe roughness in metres
    double pipeMin; //minimum pipe diameter
    double pipeMax; //maximum pipe diameter
    double pipe[N]; //array of pipe diameters
    double friction[N]; //array of friction factors
    double flowRate; //flow rate
    double density; //fluid density
    double viscosity; //viscosity
    double velocity; //for storing the calculated velocity
    int filledArray; // to indicate whether the structure is “complete”
}FLOW;

void getUserInput(FLOW *); //done
double getPositiveValue(char *); //done
void findAllRoots(FLOW *);
double findRoot(FLOW *, double, double, double);
double func(FLOW *, double, double);
double reyn(FLOW *, double); //done
double velo(FLOW *, double); //done
void printArray(FLOW *);
void useStruct(FLOW *, FLOW[],FILE *);
void saveStruct(FLOW *, FLOW[],FILE *);

void main()
{
    FLOW str[5];
    FLOW flow;
    FILE *fp;
    useStruct(&flow,str,fp);
    findAllRoots(&flow);
    printArray(&flow);
    saveStruct(&flow, str,fp);
}

/*-------------------------------------------------------------------
Function: getUserInput
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
Returns:
     none
Description: Prompts the user to input values using statements and stores them inside the structure FLOW. If a value is entered outside of the domain, the statement repeats itself and asks the user for a value inside the domain. The function also calls “double getPositiveValue” in order to check for positive inputs.
--------------------------------------------------------------*/

void getUserInput(FLOW *flow)
{
    double counter=0;
    do
    {

        if(counter>0)
            printf("You have entered invalid values, please try again\n");
        flow->rough=getPositiveValue("What is the pipe roughness in m? ");
        flow->pipeMin=getPositiveValue("What is the minimum pipe diameter in m? ");
        flow->pipeMax=getPositiveValue("What is the maximum pipe diameter in m? ");
        flow->viscosity=getPositiveValue("What is viscosity in N s/m^2? ");
        flow->density=getPositiveValue("What is the fluid density in kg/m^3? ");
        flow->flowRate=getPositiveValue("What is the flow rate in m^3/s? ");
        counter=counter+1;
    }
    while(flow->rough<(1e-7) || flow->rough>(3e-3) || flow->density<(0.5) || flow->density>(2000) || flow->viscosity<(1e-6) || flow->viscosity>(300) || reyn(flow, flow->pipeMax)<(4000));

}

/*--------------------------------------------------------------
Function: getPositiveValue
Parameters:
*prompt: a pointer to a structure that includes prompts to the user which tells the values the user needs to input
Returns:
     value: a positive value that is obtained from the user
Description: Checks if input is less than or equal to 0, alerts the user if it is, then the repeats the question and asks the user again for a valid input.
--------------------------------------------------------------*/

double getPositiveValue(char *prompt)
{
    double value;
    do
    {
        printf(prompt);
        scanf("%lf",&value);
        if(value <= 0.0)
            printf("The value must be greater than zero.\n");
    }
    while(value <= 0.0);
    return(value);
}

/*--------------------------------------------------------------
Function: reyn
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
Parameters:
     dia: the current diameter
Returns:
     re: the calculated reynold’s number
Description: Calculates the reynold’s number when called using they Reynold’s Equation.
--------------------------------------------------------------*/

double reyn(FLOW *flow, double dia)
{
    double re;
    re=velo(flow, dia);
    re=re*flow->density*dia;
    re=re/flow->viscosity;
    return(re);
}

/*--------------------------------------------------------------
Function: velo
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
dia: current diameter
Returns:
     v: the fluid velocity
Description: calculates the fluid velocity using Equation 4 (Refer to Section 2.2 of document).
--------------------------------------------------------------*/

double velo(FLOW *flow, double dia)
{
    double v;
    v=flow->flowRate;
    v=v/(M_PI*pow((0.5*dia),two));
    return(v);
}

/*--------------------------------------------------------------
Function: findAllRoots
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
Returns:
     none
Description: The function fills the array that contains values for the different diameters used. It also fills the array that contains the friction factors by calling function “findRoot”.
--------------------------------------------------------------*/

void findAllRoots(FLOW *flow)
{
    double dia=flow->pipeMin;
    double inc=(flow->pipeMax-flow->pipeMin)/N;
    int i;
    for(i=0;i<(N+1);i++)
    {
        flow->pipe[i]=dia;
        flow->friction[i]=findRoot(flow, dia, F_LO, F_HI);
        dia=dia+inc;
    }
    flow->filledArray=TRUE;
}

/*--------------------------------------------------------------
Function: findRoot
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
dia: current diameter
lower: the highest value of the domain that can contain the root
upper: lowest value of the domain that can contain the root
Returns:
     root: the root found
Description: the function finds the root using the bisection method and then calls “double func” in order to use the Colebrook Equation.

--------------------------------------------------------------*/

double findRoot(FLOW *flow, double dia, double lower, double upper)
{
    int i;
    double root;
    double factor;
    double func_lower, func_upper, func_root;

    do
    {
        func_lower=func(flow, dia, lower);
        func_upper=func(flow, dia, upper);
        factor=func_lower*func_upper;
        root=(lower+upper)/two;
        func_root=func(flow, dia, root);
        if((func_lower*func_root)<0)
            upper=root;
        else
            lower=root;

    }while(((fabs(factor))>SMALL_NUMBER));
    return(root);
}

/*--------------------------------------------------------------
Function: func
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
dia: current diameter
friction: current friction
Returns:
     value: the value calculated using the Colebrook Equation
Description: calculates the solution of the Colebrook Equation. Calls “double rey” in order to calculate the Reynold’s number which needs to be plugged into the equation.
--------------------------------------------------------------*/

double func(FLOW *flow, double dia, double friction)
{
    double fx;
    fx=flow->rough/(3.7*dia);
    fx=fx+(2.51/((reyn(flow,dia))*sqrt(friction)));
    fx=two*(log10(fx));
    fx=fx+(1.0/sqrt(friction));
    return(fx);
}

/*--------------------------------------------------------------
Function: printArray
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
Returns:
     none
Description: prints out the filled arrays pipe[] and friction[] which is the pipe diameter and its friction factor respectively, in a table format so it is easy to read for the user.
--------------------------------------------------------------*/

void printArray(FLOW *flow)
{
    int i;
    printf("%10s    %10s\n","Pipe Diameter", "Friction Factor");
    printf("----------------------------------------------------\n");
    for(i=0;i<(N+1);i++)
    {
        printf("%10f,    %10f\n", flow->pipe[i], flow->friction[i]);
    }
}

/*--------------------------------------------------------------
Function: useStruct
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
struct[]: array that contains multiple structures that have filled or empty variables/arrays.
Returns:
     none
Description: asks the user if they wish to read from a binary .txt file that already includes 5 structures. If the user wishes to do so, the current structure in the program will be filled with the data from the file.
If they do not use a pre-existing data set then it calls to getUserInput.
--------------------------------------------------------------*/

void useStruct(FLOW *flow, FLOW str[], FILE *fp)
{
    int i;
    char ch;
    fp=fopen("C:\\Users\\Patrick LeBlanc\\Documents\\GNG1106\\frictiondata.txt", "r");
    if(fopen("C:\\Users\\Patrick LeBlanc\\Documents\\GNG1106\\frictiondata.txt", "r")!=NULL)
    {
        for(i=0;i<5;i++)
        {
            fseek(fp,sizeof(FLOW)*(i+1),SEEK_SET);
            fread(&str[i],sizeof(FLOW),1,fp);
            if(str[i].filledArray==TRUE)
            {
                printf("Do you want to use dataset %d? (y/n)", i);
                scanf("%s", &ch);
                if(ch=='y')
                {
                    fread(&str[i],sizeof(FLOW),1,fp);
                    *flow=str[i];
                }
            }

        }
    if(flow->filledArray!=TRUE)
        getUserInput(flow);
    fclose(fp);
}
    }

/*--------------------------------------------------------------
Function: saveStruct
Parameters:
*flow: a pointer to the structure that contains user input and calculated variables that are used throughout the program
struct[]: array that contains multiple structures that have filled or empty variables/arrays.
Returns:
     none
Description: asks the user if they wish to save to a binary .txt file that already contains filled structures. If the user wishes to do so, the function will write to the existing .txt file
-------------------------------------------------------------------*/

void saveStruct(FLOW *flow, FLOW str[], FILE *fp)
{
    int i;
    char ch;
    fp=fopen("C:\\Users\\Patrick LeBlanc\\Documents\\GNG1106\\frictiondata.txt", "a");
    fseek(fp,sizeof(FLOW)*5,SEEK_SET);
    fread(&str[4],sizeof(FLOW),1,fp);
    if(str[4].filledArray==TRUE)
        str[0]=*flow;
    for(i=0;i<5;i++)
    {
        if(str[i].filledArray==FALSE)
        {
            printf("Do you want to store your data set? (y/n)");
            scanf("%s",&ch);
            if(ch=='y')
            {
                str[i]=*flow;
                fseek(fp,sizeof(FLOW)*(i+1),SEEK_SET);
                fwrite(&str[i],sizeof(FLOW),1, fp);
                i=5;
            }
            else
            {
                printf("Program terminated");
                i=5;
            }


        }



    }
    fclose(fp);
}

