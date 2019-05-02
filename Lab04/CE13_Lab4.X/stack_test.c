/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 04         *
 *5/01/2019      *
 *****************/



// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n\n\n###### Beginning sdenglis's stack test harness: ######\n\n");

    // Pointers are hard, man.
    float percentageCorrect = 0;

    /******************************************************************************
     * StackInit() - WORKING
     *****************************************************************************/

    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);

    if (stack.currentItemIndex == -1) {
        printf("PASSED: the currentItemIndex was set to -1.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\nDoes StackInit() set initialized to TRUE?\n");
    if (stack.initialized == TRUE) {
        printf("PASSED: stack.initialized == TRUE.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\n");

    /******************************************************************************
     * StackPush() - WORKING
     *****************************************************************************/

    printf("\nDoes StackPush() properly check if the stack is initialized?\n");
    struct Stack myStack = {};
    double myValue = 10.0;
    // StackInit(&stack);    STACK NOT INITIALIZED!
    if (StackPush(&myStack, myValue) == STANDARD_ERROR) {
        printf("PASSED: StackPush() gives ERROR when NOT initialized.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\nDoes StackPush() actually push a value onto the stack?\n");
    StackInit(&myStack);
    if (StackPush(&myStack, myValue) == SUCCESS) {
        printf("PASSED: %f, as taken from stack.stackItems[stack.currentItemIndex].", stack.stackItems[stack.currentItemIndex]);
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\n");

    /******************************************************************************
     * StackPop() - WORKING
     *****************************************************************************/

    printf("\nDoes StackPop() properly check if the stack is initialized?\n");
    // Will hold the popped value from the stack.
    struct Stack anotherStack = {};
    double anotherValue = 0;
    // StackInit(&anotherStack);    STACK NOT INITIALIZED!
    if (StackPop(&anotherStack, &anotherValue) == STANDARD_ERROR) {
        printf("PASSED: StackPop() returns ERROR when NOT initialized.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\nDoes StackPop() properly return a pointer to the popped value?\n");
    StackInit(&anotherStack);
    StackPush(&anotherStack, myValue);
    StackPop(&anotherStack, &anotherValue);

    if (anotherValue == 10) {
        printf("PASSED: same value of 10.0 popped from the stack.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\n");

    /******************************************************************************
     * StackIsEmpty() - WORKING
     *****************************************************************************/

    printf("\nDoes StackIsEmpty() actually recognize when the stack has zero elements?\n");
    struct Stack emptyStack = {};
    StackInit(&emptyStack);
    // Stack should be empty since the struct is initialized to zero.
    if (StackIsEmpty(&emptyStack) == TRUE) {
        printf("PASSED: returns TRUE for an empty stack.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\nDoes StackIsEmpty() acknowledge is a stack is NOT empty?\n");
    // Push arbitrary value of 10 onto the stack.
    StackPush(&emptyStack, myValue);
    // Stack should NOT be empty.
    if (StackIsEmpty(&emptyStack) == FALSE) {
        printf("PASSED: StackIsEmpty() returns FALSE for a stack with elements inside.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\n");

    /******************************************************************************
     * StackIsFull() - WORKING
     *****************************************************************************/

    printf("\nDoes StackIsFull() return TRUE given stack is actually full?\n");
    // Maximum stack size is 20 elements.
    struct Stack fullStack = {};
    // Counter for StackPush() loop.
    int i = 0;

    StackInit(&fullStack);
    // Push a value of 10 to the stack 20x with a loop.
    for (i = 0; i < 20; i++) {
        StackPush(&fullStack, myValue);
    }
    if (StackIsFull(&fullStack) == TRUE) {
        printf("PASSED: stack is completely full.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\nDoes StackIsFull() return FALSE given any other stack size?\n");
    if (StackIsFull(&emptyStack) == FALSE) {
        printf("PASSED: stack with single element is not considered full.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\n");

    /******************************************************************************
     * StackGetSize() - 
     *****************************************************************************/

    printf("\nDoes StackGetSize() properly return the size of the stack?\n");
    //printf("%d", StackGetSize(&fullStack));
    // fullStack should be initialized to 20!

    if (StackGetSize(&fullStack) == 20) {
        printf("PASSED: output of StackGetSize() matches with 20 element array.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\nDoes StackGetSize() work with an empty stack?\n");
    struct Stack lastStack = {};
    StackInit(&lastStack);
    if (StackGetSize(&lastStack) == 0) {
        printf("PASSED: output of StackGetSize() matches with ZERO element array.");
        percentageCorrect++;
    } else {
        printf("failed");
    }

    printf("\n");

    /******************************************************************************
     * StackResults - OUTPUT
     *****************************************************************************/

    printf("\nPass Rate: %.3f%%\n", ((percentageCorrect / 12.0) * 100));





    while (1);
    return 0;
}