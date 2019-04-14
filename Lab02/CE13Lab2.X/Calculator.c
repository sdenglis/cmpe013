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

    // More variable declarations
    char operation;
    double operand1;
    double operand2;
    double operand;

    printf("Please choose an operation (*, /, +, -, m, a, c, f, t, r): ");
    scanf(" %c", &operation);
    while (getchar() != '\n')
        continue;

    if (operation == '*') {
        printf("Enter first operand: ");
        scanf(" %lf", &operand1);

        printf("Enter second operand: ");
        scanf(" %lf", &operand2);

        double result = Multiply(operand1, operand2);
        printf("Result of (%f * %f): %f\n", operand1, operand2, result);

    } else if (operation == '/') {
        printf("Enter first operand: ");
        scanf(" %lf", &operand1);

        printf("Enter second operand: ");
        scanf(" %lf", &operand2);

        double result = Divide(operand1, operand2);
        printf("Result of (%f / %f): %f\n", operand1, operand2, result);

    } else if (operation == '+') {
        printf("Enter first operand: ");
        scanf(" %lf", &operand1);

        printf("Enter second operand: ");
        scanf(" %lf", &operand2);

        double result = Add(operand1, operand2);
        printf("Result of (%f + %f): %f\n", operand1, operand2, result);

    } else if (operation == '-') {
        printf("Enter first operand: ");
        scanf(" %lf", &operand1);

        printf("Enter second operand: ");
        scanf(" %lf", &operand2);

        double result = Subtract(operand1, operand2);
        printf("Result of (%f - %f): %f\n", operand1, operand2, result);

    } else if (operation == 'm') {
        printf("Enter first operand: ");
        scanf(" %lf", &operand1);

        printf("Enter second operand: ");
        scanf(" %lf", &operand2);

        double result = Average(operand1, operand2);
        printf("Result of AVG(%f, %f): %f\n", operand1, operand2, result);

    } else if (operation == 'a') {
        printf("Enter operand: ");
        scanf(" %lf", &operand);

        double result = AbsoluteValue(operand);
        printf("Result of |%f|: %f\n", operand, result);

    } else if (operation == 'c') {
        printf("Enter operand: ");
        scanf(" %lf", &operand);

        double result = FahrenheitToCelsius(operand);
        printf("Result of (%f degF->C): %f\n", operand, result);

    } else if (operation == 'f') {
        printf("Enter operand: ");
        scanf(" %lf", &operand);

        double result = CelsiusToFahrenheit(operand);
        printf("Result of (%f degC->F): %f\n", operand, result);

    } else if (operation == 't') {
        printf("Enter operand: ");
        scanf(" %lf", &operand);

        double result = Tangent(operand);
        printf("Result of tan(%f deg): %f\n", operand, result);

    } else {
        printf("Invalid input type!\n");
    }

    while (1);
}

double Multiply(double operand1, double operand2)
{
    double product = (operand1 * operand2);
    return product;
}

double Divide(double operand1, double operand2)
{
    if (operand2 == 0) {
        // Add something here.
        printf("Divide by zero error!\n");
        return 0;
    } else {
        double quotient = (operand1 / operand2);
        return quotient;
    }
}

double Add(double operand1, double operand2)
{
    double sum = (operand1 + operand2);
    return sum;
}

double Subtract(double operand1, double operand2)
{
    double difference = (operand1 - operand2);
    return difference;
}

double Average(double operand1, double operand2)
{
    double mean = ((operand1 + operand2) / 2.0f);
    return mean;
}

double AbsoluteValue(double operand)
{
    if (operand < 0) {
        double positive = (operand * (-1));
        return positive;
    } else {
        double positive = (operand);
        return positive;
    }
}

double FahrenheitToCelsius(double operand)
{
    double F2C = ((operand - 32) * (5.0 / 9.0f));
    return F2C;
}

double CelsiusToFahrenheit(double operand)
{
    double C2F = ((operand * (9.0 / 5.0f)) + 32);
    return C2F;
}

double Tangent(double operand)
{
    //  Converts degree input into radians
    double tan = tan((operand * M_PI) / 180.0f);
    return tan;
}


/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 *******************************************************************************
double Round(double operand)
{
    //  Your code here
    double ceiling =
    return 0;
}
 */

