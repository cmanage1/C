#include <stdio.h>

void main(void)
{
    int logicVar;
    double p, q;

    p= 39.54;
    q= 18.32;

    logicVar = (p <= q);
       printf("%d", logicVar);
    logicVar = (38.77 + p <q) && ( p> 10.0);
       printf("%d", logicVar);
    logicVar = (p <= 21.3) || (2.1 <=q);
        printf("%d", logicVar);

}
