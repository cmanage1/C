#include <stdio.h>
// Prototype
double compute(double, double);
/*------------------------------------------*/
void main()
{
   double v1, v2, v3;
   v1= 36.8;
   v2= 4.6;

   v3= compute(v1, v2);
   printf("For v1= %f and v2= %f\n", v1, v2);
   printf("v3 = %f\n",v3);
}

/*------------------------------------------*/

double compute (double x, double y)

{
   double z;
   z= (3.6/(4.3 + 0.4*x))*y;
   return (z);
}

