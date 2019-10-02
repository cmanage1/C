    #include <stdio.h>

  float convertKtoF (float degreeF);

    void main()
  {

    float degreeK;
    float degreeF;

    printf("\nPlease enter the temperature in Degrees Kelvin: ");
    scanf("%f", &degreeK);
    degreeF= convertKtoF (degreeK);
    printf("Kelvin: %0.2f   Fahrenheit; %0.2f", degreeK, degreeF );

  }

  float convertKtoF (float degreeK)

  {
    float degreeC;
    float degreeF;
    degreeC = degreeK - 273.2;
    degreeF = ( degreeC * 9/5 ) + 32;

    return degreeF;

  }
