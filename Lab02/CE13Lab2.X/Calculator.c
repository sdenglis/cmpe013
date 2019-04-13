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
double Average(double operand1, double operand2);

// Single-input function prototypes
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Tangent(double operand);
double Round(double operand);

void CalculatorRun(void)
{
    printf("\n\nWelcome to Sam's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    // Your code here

    char operation;

    printf("Please choose an operation (*, /, +, -, m, a, c, f, t, r): ");
    scanf("%c", &operation);
    printf("You input '%c'", operation);

    /*
    printf("Enter first operand: ");
    scanf();
    printf("Enter second operand: ");
    scanf();

    printf("Enter operand: ");
    scanf();
     */

    while (1);
}

double Multiply(double operand1, double operand2)
{
    //  Your code here
    double product = (operand1 * operand2);
    return product;
}

double Divide(double operand1, double operand2)
{
    //  Your code here
    double quotient = (operand1 / operand2);
    return quotient;
}

double Add(double operand1, double operand2)
{
    //  Your code here
    double sum = (operand1 + operand2);
    return sum;
}

double Subtract(double operand1, double operand2)
{
    //  Your code here
    double difference = (operand1 - operand2);
    return difference;
}

double Average(double operand1, double operand2)
{
    //  Your code here
    double mean = ((operand1 + operand2) / 2)
    return mean;
}

double AbsoluteValue(double operand)
{
    //  Your code here
    if (operand < 0) {
        double positive = (operand * (-1))
    } else {
        double positive = (operand)
    }
    
    return positive;
}

double FahrenheitToCelsius(double operand)
{
    //  Your code here
    double F2C =
    return 0;
}

double CelsiusToFahrenheit(double operand)
{
    //  Your code here
    double C2F =
    return 0;
}

double Tangent(double operand)
{
    //  Your code here
    double tan =
    return 0;
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    //  Your code here
    double ceiling =
    return 0;
}


