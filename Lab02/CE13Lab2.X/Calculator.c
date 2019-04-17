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

    while (1) {

        printf("\nPlease choose an operation (*, /, +, -, m, a, c, f, t, r): ");
        scanf(" %1c", &operation);
        // This is temporary, scanf() doesn't function in MPLab X
        while (getchar() != '\n')
            continue;
        // Checks for multiply operation
        if (operation == '*') {
            printf("Enter first operand: ");
            scanf(" %lf", &operand1);

            printf("Enter second operand: ");
            scanf(" %lf", &operand2);

            double result = Multiply(operand1, operand2);
            printf("Result of (%f * %f): %f\n", operand1, operand2, result);
            // Checks for division operation
        } else if (operation == '/') {
            printf("Enter first operand: ");
            scanf(" %lf", &operand1);

            printf("Enter second operand: ");
            scanf(" %lf", &operand2);

            if (operand2 == 0) {
                printf("Divide by zero error!\n");
                continue;
            } else {
                double result = Divide(operand1, operand2);
                printf("Result of (%f / %f): %f\n", operand1, operand2, result);
            }
            // Checks for addition operation
        } else if (operation == '+') {
            printf("Enter first operand: ");
            scanf(" %lf", &operand1);

            printf("Enter second operand: ");
            scanf(" %lf", &operand2);

            double result = Add(operand1, operand2);
            printf("Result of (%f + %f): %f\n", operand1, operand2, result);
            // Checks for subtraction operation
        } else if (operation == '-') {
            printf("Enter first operand: ");
            scanf(" %lf", &operand1);

            printf("Enter second operand: ");
            scanf(" %lf", &operand2);

            double result = Subtract(operand1, operand2);
            printf("Result of (%f - %f): %f\n", operand1, operand2, result);
            // Checks for average value operation
        } else if (operation == 'm') {
            printf("Enter first operand: ");
            scanf(" %lf", &operand1);

            printf("Enter second operand: ");
            scanf(" %lf", &operand2);

            double result = Average(operand1, operand2);
            printf("Result of AVG(%f, %f): %f\n", operand1, operand2, result);
            // Checks for absolute value operation
        } else if (operation == 'a') {
            printf("Enter operand: ");
            scanf(" %lf", &operand);

            double result = AbsoluteValue(operand);
            printf("Result of |%f|: %f\n", operand, result);
            // Checks for F->C conversion operation
        } else if (operation == 'c') {
            printf("Enter operand: ");
            scanf(" %lf", &operand);

            double result = FahrenheitToCelsius(operand);
            printf("Result of (%f degF->C): %f\n", operand, result);
            // Checks for C->F conversion operation
        } else if (operation == 'f') {
            printf("Enter operand: ");
            scanf(" %lf", &operand);

            double result = CelsiusToFahrenheit(operand);
            printf("Result of (%f degC->F): %f\n", operand, result);
            // Checks for tangent operation
        } else if (operation == 't') {
            printf("Enter operand: ");
            scanf(" %lf", &operand);

            double result = Tangent(operand);
            printf("Result of tan(%f deg): %f\n", operand, result);
            // Checks for round operation
        } else if (operation == 'r') {
            printf("Enter operand: ");
            scanf(" %lf", &operand);

            int result = Round(operand);
            printf("Result of round(%f): %d\n", operand, result);
            // Else, prints an error message and repeats prompt
        } else {
            printf("Invalid input type!\n");
        }
    }
}
// Define multiply function

double Multiply(double operand1, double operand2)
{
    double product = (operand1 * operand2);
    return product;
}
// Define divide function

double Divide(double operand1, double operand2)
{

    double quotient = (operand1 / operand2);
    return quotient;
}
// Define add function

double Add(double operand1, double operand2)
{
    double sum = (operand1 + operand2);
    return sum;
}
// Define subtract function

double Subtract(double operand1, double operand2)
{
    double difference = (operand1 - operand2);
    return difference;
}
// Define average function

double Average(double operand1, double operand2)
{
    double mean = ((operand1 + operand2) / 2.0f);
    return mean;
}
// Define absolute value function

double AbsoluteValue(double operand)
{ // Only deal with negative values
    if (operand < 0) {
        double positive = (operand * (-1));
        return positive;
    } else {
        double positive = (operand);
        return positive;
    }
}
// Define FahrenheitToCelsius function

double FahrenheitToCelsius(double operand)
{
    double F2C = ((operand - 32) * (5.0 / 9.0f));
    return F2C;
}
// Define CelsiusToFahrenheit function

double CelsiusToFahrenheit(double operand)
{
    double C2F = ((operand * (9.0 / 5.0f)) + 32);
    return C2F;
}
// Define tangent function

double Tangent(double operand)
{
    //  Converts degree input into radians using M_PI constant
    double tan = tan((operand * M_PI) / 180.0f);
    return tan;
}
// Define round function

double Round(double operand)
{
    //  Takes numbers and increments by 0.5 respective to sign
    double rounded = operand;
    if (operand > 0) {
        rounded += 0.5;
        // printf("positive\n");
    } else {
        rounded -= 0.5;
        // printf("negative\n");
    }
    // Returns double to be truncated after called
    return rounded;
}

