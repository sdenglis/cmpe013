


/*
 * MessageTest.c
 * Author: Austin Dymont
 * Co-author: Sam English
 * Date: June 1, 2019
 * CMPE13
 */

// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <xc.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>


#include "Message.h"
#include "Field.h"

#define ONE_LESS_LIFE 2
#define TEST_BOAT_STATE 0b00001111



static int tried, passed;

int main(void)
{

    BOARD_Init();

    printf("\n\nWelcome to adymont and sdenglis' FIELD Test Harness. %s; %s\n", __DATE__, __TIME__);

    //FieldInit      

    static Field f1_var, f2_var;
    static Field *f1 = &f1_var;
    static Field *f2 = &f2_var;

    FieldInit(f1, f2);

    static int i, j;
    static uint8_t failed = FALSE;

    for (i = 0; i < FIELD_ROWS && failed != TRUE; i++) {
        for (j = 0; j < FIELD_COLS && failed != TRUE; j++) {
            if (f1->grid[i][j] != FIELD_SQUARE_EMPTY) {
                failed = TRUE;
            }
        }
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("First Field init test: Passed.\n");
    } else {
        printf("First Field init: failed.\n");
    }

    failed = FALSE;
    for (i = 0; i < FIELD_ROWS && failed != TRUE; i++) {
        for (j = 0; j < FIELD_COLS && failed != TRUE; j++) {
            if (f2->grid[i][j] != FIELD_SQUARE_UNKNOWN) {
                failed = TRUE;
            }
        }
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("Second Field init test: Passed.\n");
    } else {
        printf("Second Field init: failed.\n");
    }

    //FieldGetSquareStatus
    failed = FALSE;
    for (i = 0; i < FIELD_ROWS && failed != TRUE; i++) {
        for (j = 0; j < FIELD_COLS && failed != TRUE; j++) {
            if (f1->grid[i][j] != FieldGetSquareStatus(f1, i, j)) {
                failed = TRUE;
            }
        }
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("First Field GetSquareStatus test: Passed.\n");
    } else {
        printf("First Field GetSquareStatus: failed.\n");
    }


    failed = FALSE;
    for (i = 0; i < FIELD_ROWS && failed != TRUE; i++) {
        for (j = 0; j < FIELD_COLS && failed != TRUE; j++) {
            if (f2->grid[i][j] != FieldGetSquareStatus(f2, i, j)) {
                failed = TRUE;
            }
        }
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("Second Field GetSquareStatus test: Passed.\n");
    } else {
        printf("Second Field GetSquareStatus: failed.\n");
    }



    //FieldSetSquareStatus
    failed = FALSE;
    for (i = 0; i < FIELD_ROWS && failed != TRUE; i++) {
        for (j = 0; j < FIELD_COLS && failed != TRUE; j++) {
            FieldSetSquareStatus(f1, i, j, FIELD_SQUARE_HIT);
        }
    }

    for (i = 0; i < FIELD_ROWS && failed != TRUE; i++) {
        for (j = 0; j < FIELD_COLS && failed != TRUE; j++) {
            if (f1->grid[i][j] != FIELD_SQUARE_HIT) {
                failed = TRUE;
            }
        }
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("Set Square Status test: Passed.\n");
    } else {
        printf("Set Square Status: failed.\n");
    }

    //reset fields
    FieldInit(f1, f2);

    //FieldAddBoat
    failed = FALSE;
    static BoatType boat_type = FIELD_BOAT_TYPE_SMALL;
    static BoatDirection dir = FIELD_DIR_EAST;

    if (FieldAddBoat(f1, 0, 0, dir, boat_type) == STANDARD_ERROR) {
        failed = TRUE;
    }
    if (f1->grid[0][0] != FIELD_SQUARE_SMALL_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[0][1] != FIELD_SQUARE_SMALL_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[0][2] != FIELD_SQUARE_SMALL_BOAT) {
        failed = TRUE;
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("Add small boat test: Passed.\n");
    } else {
        printf("Add small boat: failed.\n");
    }

    failed = FALSE;
    boat_type = FIELD_BOAT_TYPE_MEDIUM;
    dir = FIELD_DIR_EAST;

    if (FieldAddBoat(f1, 1, 0, dir, boat_type) == STANDARD_ERROR) {
        failed = TRUE;
    }
    if (f1->grid[1][0] != FIELD_SQUARE_MEDIUM_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[1][1] != FIELD_SQUARE_MEDIUM_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[1][2] != FIELD_SQUARE_MEDIUM_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[1][3] != FIELD_SQUARE_MEDIUM_BOAT) {
        failed = TRUE;
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("Add medium boat test: Passed.\n");
    } else {
        printf("Add medium boat: failed.\n");
    }

    failed = FALSE;
    boat_type = FIELD_BOAT_TYPE_LARGE;
    dir = FIELD_DIR_EAST;

    if (FieldAddBoat(f1, 2, 0, dir, boat_type) == STANDARD_ERROR) {
        failed = TRUE;
    }
    if (f1->grid[2][0] != FIELD_SQUARE_LARGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[2][1] != FIELD_SQUARE_LARGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[2][2] != FIELD_SQUARE_LARGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[2][3] != FIELD_SQUARE_LARGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[2][4] != FIELD_SQUARE_LARGE_BOAT) {
        failed = TRUE;
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("Add large boat test: Passed.\n");
    } else {
        printf("Add large boat: failed.\n");
    }


    failed = FALSE;
    boat_type = FIELD_BOAT_TYPE_HUGE;
    dir = FIELD_DIR_EAST;

    if (FieldAddBoat(f1, 3, 0, dir, boat_type) == STANDARD_ERROR) {
        failed = TRUE;
    }
    if (f1->grid[3][0] != FIELD_SQUARE_HUGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[3][1] != FIELD_SQUARE_HUGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[3][2] != FIELD_SQUARE_HUGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[3][3] != FIELD_SQUARE_HUGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[3][4] != FIELD_SQUARE_HUGE_BOAT) {
        failed = TRUE;
    }
    if (f1->grid[3][5] != FIELD_SQUARE_HUGE_BOAT) {
        failed = TRUE;
    }

    tried++;
    if (failed == FALSE) {
        passed++;
        printf("Add Huge boat test: Passed.\n");
    } else {
        printf("Add Huge boat: failed.\n");
    }

    tried++;
    if (FieldAddBoat(f1, FIELD_ROWS - 1, FIELD_COLS - 1, dir, boat_type) == STANDARD_ERROR) {
        passed++;
        printf("Add half boat test: Passed.\n");
    } else {
        printf("Add half boat: failed.\n");
    }

    printf("\n");
    FieldPrint_UART(f1, f2);
    printf("\n");

    tried++;
    if (FieldAddBoat(f1, FIELD_ROWS, FIELD_COLS, dir, boat_type) == STANDARD_ERROR) {
        passed++;
        printf("Add out of bounds boat test: Passed.\n");
    } else {
        printf("Add out of bounds boat: failed.\n");
    }


    //FieldRegisterEnemyAttack
    static GuessData gData_var;
    static GuessData *gData = &gData_var;
    gData->col = 0;
    gData->row = 0;
    gData->result = NULL;

    tried++;
    FieldRegisterEnemyAttack(f1, gData);
    if (f1->grid[0][0] == FIELD_SQUARE_HIT && f1->smallBoatLives == ONE_LESS_LIFE) {
        passed++;
        printf("Hit test: Passed.\n");
    } else {
        printf("Hit test: failed.\n");
    }

    tried++;
    gData->col = 8;
    gData->row = 5;

    SquareStatus temp = FieldRegisterEnemyAttack(f1, gData);

    if (temp == FIELD_SQUARE_EMPTY) {
        if (FieldGetSquareStatus(f1, gData->row, gData->col) == FIELD_SQUARE_MISS) {
            passed++;
            printf("Miss test: Passed.\n");
        } else {
            printf("Miss test: failed.\n");
        }
    } else {
        printf("Miss test: failed.\n");
    }

    //FieldUpdateKnowledge
    gData->col = 0;
    gData->row = 0;
    gData->result = RESULT_HIT;

    tried++;
    FieldUpdateKnowledge(f2, gData);
    if (f2->grid[0][0] == FIELD_SQUARE_HIT) {
        passed++;
        printf("Hit opp test: Passed.\n");
    } else {
        printf("Hit opp  test: failed.\n");
    }

    //FieldGetBoatStates

    if (FieldGetBoatStates(f2) == TEST_BOAT_STATE) {
        passed++;
        printf("Get Boat State test: Passed.\n");
    } else {
        printf("Get Boat State: failed.\n");
    }

    //FieldAIPlaceAllBoats
    //reset fields
    FieldInit(f1, f2);

    static uint8_t smallBoat = FALSE;
    static uint8_t mediumBoat = FALSE;
    static uint8_t largeBoat = FALSE;
    static uint8_t hugeBoat = FALSE;

    FieldAIPlaceAllBoats(f1);

    for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_COLS; j++) {
            if (f1->grid[i][j] == FIELD_SQUARE_SMALL_BOAT) {
                smallBoat = TRUE;
            }
            if (f1->grid[i][j] == FIELD_SQUARE_MEDIUM_BOAT) {
                mediumBoat = TRUE;
            }
            if (f1->grid[i][j] == FIELD_SQUARE_LARGE_BOAT) {
                largeBoat = TRUE;
            }
            if (f1->grid[i][j] == FIELD_SQUARE_HUGE_BOAT) {
                hugeBoat = TRUE;
            }
        }
    }

    if (smallBoat && mediumBoat && largeBoat && hugeBoat) {
        passed++;
        printf("Add all boats test: Passed.\n");
    } else {
        printf("Add all boats: failed.\n");
    }

    //FieldAIDecideGuess
    static GuessData gData2_var;

    gData_var = FieldAIDecideGuess(f2);
    gData2_var = FieldAIDecideGuess(f2);

    if (gData2_var.row != gData_var.row || gData2_var.col != gData_var.col) {
        passed++;
        printf("AI guess: Passed.\n");
    } else {
        printf("AI guess: failed.\n");
    }

    f1->grid[0][0] = FIELD_SQUARE_EMPTY;

    //result
    if (tried == passed) {
        printf("All tests attempted were passed!\n");
    } else {
        printf("%d of %d tests passed (%.2f%%)\n", passed, tried,
                ((double) passed / (double) tried) * 100.0);
    }
    printf("\n");
    FieldPrint_UART(f1, f2);

    while (1);

}