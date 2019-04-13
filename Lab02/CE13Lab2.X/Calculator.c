/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 02         *
 *4/12/2019      *
 *****************/

// Standard libraries
#include <stdio.h>
#include <math.h>
#include <xc.h>

//User libraries:
#include "BOARD.h"


// **** Declare function prototypes ****
// Double-input function prototypes
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);

// Single-input function prototypes
double Average(double operand);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Tangent(double operand);
double Round(double operand);

void CalculatorRun(void)
{
    printf("\n\nWelcome to Sam's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    // Your code here

    printf("Please choose an operation (*, /, +, -, m, a, c, f, t, r): ");
    scanf();

    printf("Enter first operand: ");
    scanf();
    printf("Enter second operand: ");
    scanf();
    
    printf("Enter operand: ");
    scanf();

    while (1);
}

double Multiply(double operand1, double operand2)
{
    //  Your code here
}

double Divide(double operand1, double operand2)
{
    //  Your code here
}

double Add(double operand1, double operand2)
{
    //  Your code here
}

double Subtract(double operand1, double operand2)
{
    //  Your code here
}

double Average(double operand1, double operand2)
{
    //  Your code here
}

double AbsoluteValue(double operand)
{
    //  Your code here
}

double FahrenheitToCelsius(double operand)
{
    //  Your code here
}

double CelsiusToFahrenheit(double operand)
{
    //  Your code here
}

double Tangent(double operand)
{
    //  Your code here
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    //  Your code here
}


