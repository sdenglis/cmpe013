/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 04         *
 *5/01/2019      *
 *****************/



// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning sdenglis's rpn test harness: ######\n\n");

    /******************************************************************************
     * RPN Testing - RPN Evaluate()
     *****************************************************************************/

    // Should return NO_ERRORS.
    char test0[] = "3.5 4.5 +";
    double result0;
    // (3.5) + (4.5) = 8.
    double expected0 = 8;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }

    // Should return NO_ERRORS.
    // (1 + 4) * (6 - 4) / 8 = 1.25
    char test2[] = "1 4 + 6 4 - * 8 /";
    double result2;
    double expected2 = 1.25;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result2 != expected2) {
        printf("   Failed, expected = %f , result = %f\n", expected2, result2);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }

    /******************************************************************************
     * RPN Testing - RPN_ERROR_STACK_OVERFLOW
     *****************************************************************************/

    // Should return RPN_ERROR_STACK_OVERFLOW.
    char test3[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21";
    double result3;
    double expected3 = NULL;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test3);
    error = RPN_Evaluate(test3, &result3);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result3 != expected3) {
        printf("   Failed, expected = %f , result = %f\n", expected3, result3);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }

    /******************************************************************************
     * RPN Testing - RPN_ERROR_STACK_UNDERFLOW
     *****************************************************************************/

    // Should return RPN_ERROR_STACK_UNDERFLOW.
    char test1[] = "+";
    double result1;
    double expected1 = NULL;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result1 != expected1) {
        printf("   Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }

    /******************************************************************************
     * RPN Testing - RPN_ERROR_INVALID_TOKEN
     *****************************************************************************/

    // Should return RPN_ERROR_INVALID_TOKEN.
    char test4[] = "this lab is great!";
    double result4;
    double expected4 = NULL;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test4);
    error = RPN_Evaluate(test4, &result4);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result4 != expected4) {
        printf("   Failed, expected = %f , result = %f\n", expected4, result4);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }

    /******************************************************************************
     * RPN Testing - RPN_DIVIDE_BY_ZERO
     *****************************************************************************/

    // Should return RPN_DIVIDE_BY_ZERO.
    // (10 / 0) = DNE, error.
    char test5[] = "10 0 /";
    double result5;
    double expected5 = NULL;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test5);
    error = RPN_Evaluate(test5, &result5);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result5 != expected5) {
        printf("   Failed, expected = %f , result = %f\n", expected5, result5);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }

    /******************************************************************************
     * RPN Testing - RPN_ERROR_TOO_FEW_ITEMS_REMAIN
     *****************************************************************************/

    // Should return RPN_ERROR_TOO_FEW_ITEMS_REMAIN.
    char test6[] = "1 + +";
    double result6;
    double expected6 = NULL;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test6);
    error = RPN_Evaluate(test6, &result6);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result6 != expected6) {
        printf("   Failed, expected = %f , result = %f\n", expected6, result6);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }

    /******************************************************************************
     * RPN Testing - RPN_ERROR_TOO_MANY_ITEMS_REMAIN
     *****************************************************************************/

    // Should return RPN_ERROR_TOO_MANY_ITEMS_REMAIN.
    char test7[] = "1 1 1 +";
    double result7;
    double expected7 = NULL;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test7);
    error = RPN_Evaluate(test7, &result7);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
        if (error == RPN_ERROR_STACK_OVERFLOW) {
            printf("Too many items in the stack: overflow!\n");
        } else if (error == RPN_ERROR_STACK_UNDERFLOW) {
            printf("Too few items in the stack.\n");
        } else if (error == RPN_ERROR_INVALID_TOKEN) {
            printf("Invalid character(s)!\n");
        } else if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
            printf("Divide by zero error!\n");
        } else if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
            printf("Not enough operators left to interact with operand.\n");
        } else if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
            printf("Too many operators left with no operands.\n");
        }
    } else if (result7 != expected7) {
        printf("   Failed, expected = %f , result = %f\n", expected7, result7);
    } else {
        printf("   Success! Expected = %f , Result = %f\n");
    }



    /******************************************************************************
     * RPN Testing - ProcessBackspace()
     *****************************************************************************/

    printf("\nTesting ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");

    while (1);
}