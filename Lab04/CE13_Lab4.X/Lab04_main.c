// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main()
{
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to sdenglis's RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("\nPlease enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);

        if (RPN_Evaluate(rpn_sentence, &result) == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (RPN_Evaluate(rpn_sentence, &result) == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (RPN_Evaluate(rpn_sentence, &result) == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character!\n");
        } else if (RPN_Evaluate(rpn_sentence, &result) == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (RPN_Evaluate(rpn_sentence, &result) == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (RPN_Evaluate(rpn_sentence, &result) == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        } else if (RPN_Evaluate(rpn_sentence, &result) == RPN_NO_ERROR) {
            printf("Result = %f\n", result);
        }



    }

    while (1);
}
