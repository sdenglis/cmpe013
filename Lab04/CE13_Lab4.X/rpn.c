
// Include BOARD.h so we can use the return values and the boolean defines.
#include "BOARD.h"

//Define RPN errors that could occur during execution:

enum rpn_error {
    RPN_NO_ERROR = 0,
    RPN_ERROR_STACK_OVERFLOW,
    RPN_ERROR_STACK_UNDERFLOW,
    RPN_ERROR_INVALID_TOKEN,
    RPN_ERROR_DIVIDE_BY_ZERO,
    RPN_ERROR_TOO_FEW_ITEMS_REMAIN,
    RPN_ERROR_TOO_MANY_ITEMS_REMAIN
};

/* RPN_Evaluate() parses and evaluates a string that contains 
 * a valid Reverse Polish Notation string (no newlines!)  
 * @param:  rpn_string - a string in polish notation.  Tokens must be either 
 *          arithmetic operators or numbers.
 * @param:  result - a pointer to a double that will be modified to contain
 *          the return value of the rpn expression.
 * @return: error - if the rpn expression is invalid, 
 *          an appropriate error value is returned.
 * 
 * RPN_Evaluate supports the following basic arithmetic operations:
 *   + : addition
 *   - : subtraction
 *   * : multiplication
 *   / : division
 * Numeric tokens can be positive or negative, and can be integers or 
 * decimal floats.  RPN_Evaluate should be able to handle strings of 
 * at least 255 length.
 * */
int RPN_Evaluate(char * rpn_string, double * result)
{
    StackInit(Stack * stack);

    int counter = 0;
    // Contains the return pointer found in strtok().
    char *holder;
    // Stores converted number string as a floating point.
    double numberPushed;
    double firstStorage;
    double secondStorage;

    // Run through at least once.
    holder = strtok(rpn_string, " ");
    // Keep track of how many strings were parsed.
    counter++;
    while (holder != NULL) {
        double numberPushed = 0;
        double firstStored = 0;
        double secondStored = 0;

        if (holder == "+") {
            // Pop previous two operands on stack.
            StackPop(Stack *stack, *firstStored);
            StackPop(Stack *stack, *secondStored);

            // Perform operation based on input string.
            numberPushed = (*firstStored) + (*secondStored);

            // Push result back onto the stack.
            StackPush(Stack *stack, numberPushed);

        } else if (holder == "-") {
            // Pop previous two operands on stack.
            StackPop(Stack *stack, *firstStored);
            StackPop(Stack *stack, *secondStored);

            // Perform operation based on input string.
            numberPushed = (*firstStored) - (*secondStored);

            // Push result back onto the stack.
            StackPush(Stack *stack, numberPushed);

        } else if (holder == "*") {
            // Pop previous two operands on stack.
            StackPop(Stack *stack, *firstStored);
            StackPop(Stack *stack, *secondStored);

            // Perform operation based on input string.
            numberPushed = (*firstStored) * (*secondStored);

            // Push result back onto the stack.
            StackPush(Stack *stack, numberPushed);

        } else if (holder == "/") {
            // Pop previous two operands on stack.
            StackPop(Stack *stack, *firstStored);
            StackPop(Stack *stack, *secondStored);

            // Perform operation based on input string.
            numberPushed = (*firstStored) / (*secondStored);

            // Push result back onto the stack.
            StackPush(Stack *stack, numberPushed);

        } else if (isdigit) {
            numberInput = atof(holder);
            StackPush(Stack *stack, numberPushed);
        } else (error) {
            return STANDARD_ERROR;
        }



        holder = strtok(NULL, " ");
        counter++;
    }


}

/**
 * This function should read through an array of characters, checking for backspace characters. 
 * When it encounters a backspace character, it eliminates the backspace, the preceeding character
 * (if such a character exists), and shifts all subsequent characters as appropriate.
 * @param string_to_modify The string that will be processed for backspaces. 
 *        This string is modified "in place", so it is both an input and an output to the function.
 * @return Returns the size of the resulting string in "string_to_modify".
 *
 * ProcessBackspaces() should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings of at least 255 length.
 * 
 * */
int ProcessBackspaces(char *rpn_sentence)
{

}

