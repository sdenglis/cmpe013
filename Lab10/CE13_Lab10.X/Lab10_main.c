// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CMPE13 Support Library
#include "UNIXBOARD.h"



// User libraries


// **** Set any macros or preprocessor directives here ****
#define STRING_LENGTH 50

// **** Declare any data types here ****

// **** Define any global or external variables here ****
static char formatted_directions[STRING_LENGTH];
static char char_input;
static int valid_char;
static int direction_check;

// **** Declare any function prototypes here ****

int main()
{



    /******************************** Your custom code goes below here ********************************/
    if (GameInit()) {
        while (1) {

            printf("\n%s\n", current_room.title); //PRINT TITLE!
            printf("%s\n", current_room.description); //PRINT DESCRIPTION!


            printf("Enter next direction: ");
            if (current_room.exit_north != 0) { //PRINT EXIT OPTIONS!
                sprintf(formatted_directions + strlen(formatted_directions), "N ");
            }
            if (current_room.exit_east != 0) {
                sprintf(formatted_directions + strlen(formatted_directions), "E ");
            }
            if (current_room.exit_south != 0) {
                sprintf(formatted_directions + strlen(formatted_directions), "S ");
            }
            if (current_room.exit_west != 0) {
                sprintf(formatted_directions + strlen(formatted_directions), "W ");
            }

            while (valid_char != 1) {
                if (valid_char == -1) {
                    printf("\nInvalid Character!\n");
                }

                printf("%s\n", formatted_directions);
                printf("Or press 'Q' to quit.\n");

                do {
                    char_input = getchar();
                } while (char_input == '\n');

                switch (char_input) {
                case 'N':
                    if (GameGoNorth() == SUCCESS) {
                        valid_char = 1;
                        break;
                    } else {
                        valid_char = -1;
                        break;
                    }
                case 'E':
                    if (GameGoEast() == SUCCESS) {
                        valid_char = 1;
                        break;
                    } else {
                        valid_char = -1;
                        break;
                    }
                case 'S':
                    if (GameGoSouth() == SUCCESS) {
                        valid_char = 1;
                        break;
                    } else {
                        valid_char = -1;
                        break;
                    }
                case 'W':
                    if (GameGoWest() == SUCCESS) {
                        valid_char = 1;
                        break;
                    } else {
                        valid_char = -1;
                        break;
                    }
                case 'Q':
                    valid_char = 1;
                    exit(SUCCESS); //exit using success code.
                    break;
                default: //ERROR!
                    valid_char = -1;
                    break;
                }
            }
            //loop back to the top continuously, with updated room information.
        }
    } else {
        FATAL_ERROR();
    }

    /**************************************************************************************************/
}

