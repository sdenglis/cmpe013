/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 09         *
 *6/01/2019      *
 *****************/
// Standard libraries:
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <sys/attribs.h>

// User libraries:
#include "BattleBoats.h"
#include "Field.h"
#include "Message.h"

/******************************************************************************
 * MESSAGE - Preprocessor / Definitions / Variables
 *****************************************************************************/

//#define EXTRA_CREDIT_MODE

/**
 * Define the dimensions of the game field. They can be overridden by compile-time specifications.
 * All references to the dimensions of the field should use these constants instead of hard-coding
 * a numeric value so that the field dimensions can be changed with minimal coding changes.
 */
#ifndef FIELD_COLS
#define FIELD_COLS 10
#endif
#ifndef FIELD_ROWS
#define FIELD_ROWS 6
#endif

#define STANDARD_ERROR 0
#define SUCCESS 1

typedef enum {
    GET_FIRST_HIT = 1, //states for message module state machine.
    GO_SOUTH,
    GO_NORTH,
    GO_EAST,
    GO_WEST,
} GuessState;

/******************************************************************************
 * FIELD - Field Print
 *****************************************************************************/

/**
 * This function is optional, but recommended.   It prints a representation of both
 * fields, similar to the OLED display.
 * @param f The field to initialize.
 * @param p The data to initialize the entire field to, should be a member of enum
 *                     SquareStatus.
 */
void FieldPrint_UART(Field *own_field, Field * opp_field)
{

}



/******************************************************************************
 * FIELD - Field Initialize
 *****************************************************************************/

/**
 * FieldInit() will initialize two passed field structs for the beginning of play.
 * Each field's grid should be filled with the appropriate SquareStatus.
 * Additionally, your opponent's field's boatLives parameters should be filled
 *  (your own field's boatLives will be set when boats are added)
 * 
 * FieldAI_PlaceAllBoats() should NOT be called in this function.
 * 
 * @param own_field     //A field representing the agents own ships
 * @param opp_field     //A field representing the opponent's ships
 */
void FieldInit(Field *own_field, Field * opp_field)
{
    static unsigned int i; //arbitrary iterative variables used in for loops.
    static unsigned int j;

    for (i = 0; i < FIELD_ROWS; i++) { //iterate through each row and column:
        for (j = 0; j < FIELD_COLS; j++) {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY; //set your current grid status to empty.
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN; //set opponent's current grid to unknown.
        }
    }

    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE; //set and keep track of opponent's max boat lives.
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;

}




/******************************************************************************
 * FIELD - Get Square Status
 *****************************************************************************/

/**
 * Retrieves the value at the specified field position.
 * @param f     //The Field being referenced
 * @param row   //The row-component of the location to retrieve
 * @param col   //The column-component of the location to retrieve
 * @return  SQUARE_STATUS_INVALID if row and col are not valid field locations
 *          Otherwise, return the status of the referenced square 
 */
SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    static SquareStatus get_square;
    //only concern are the boundaries of this. is it including 0 and max row/col???

    if ((row >= 0 && row < FIELD_ROWS) && (col >= 0 && col < FIELD_COLS)) { //if within bounds of Field grid.
        get_square = f->grid[row][col]; //store value at current grid location.
        return get_square; //return the SquareStatus value.
    } else { //invalid row and column field locations!
        return FIELD_SQUARE_INVALID;
    }
}



/******************************************************************************
 * FIELD - Set Square Status
 *****************************************************************************/

/**
 * This function provides an interface for setting individual locations within a Field struct. This
 * is useful when FieldAddBoat() doesn't do exactly what you need. For example, if you'd like to use
 * FIELD_SQUARE_CURSOR, this is the function to use.
 * 
 * @param f The Field to modify.
 * @param row The row-component of the location to modify
 * @param col The column-component of the location to modify
 * @param p The new value of the field location
 * @return The old value at that field location
 */
SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p)
{
    static SquareStatus set_square;
    //again, concern about the boundaries of row and col???

    if ((row >= 0 && row < FIELD_ROWS) && (col >= 0 && col < FIELD_COLS)) {
        set_square = f->grid[row][col]; //store old value of current grid member.
        f->grid[row][col] = p; //set current grid member to p(SquareStatus).
        return set_square; //return SquareStatus of old.
    } else { //if row and columns not within bounds.
        return FIELD_SQUARE_INVALID; //set square is out of bounds, INVALID.
    }
}



/******************************************************************************
 * FIELD - Add Boat
 *****************************************************************************/

/**
 * FieldAddBoat() places a single ship on the player's field based on arguments 2-5. Arguments 2, 3
 * represent the x, y coordinates of the pivot point of the ship.  Argument 4 represents the
 * direction of the ship, and argument 5 is the length of the ship being placed. All spaces that
 * the boat would occupy are checked to be clear before the field is modified so that if the boat
 * can fit in the desired position, the field is modified as SUCCESS is returned. Otherwise the
 * field is unmodified and STANDARD_ERROR is returned. There is no hard-coded limit to how many
 * times a boat can be added to a field within this function.
 *
 * So this is valid test code:
 * {
 *   Field myField;
 *   FieldInit(&myField,FIELD_SQUARE_EMPTY);
 *   FieldAddBoat(&myField, 0, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_SMALL);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_MEDIUM);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_HUGE);
 *   FieldAddBoat(&myField, 0, 6, FIELD_BOAT_DIRECTION_SOUTH, FIELD_BOAT_TYPE_SMALL);
 * }
 *
 * should result in a field like:
 *      0 1 2 3 4 5 6 7 8 9
 *     ---------------------
 *  0 [ 3 3 3 . . . 3 . . . ]
 *  1 [ 4 4 4 4 . . 3 . . . ]
 *  2 [ . . . . . . 3 . . . ]
 *  3 [ . . . . . . . . . . ]
 *  4 [ . . . . . . . . . . ]
 *  5 [ . . . . . . . . . . ]
 *     
 * @param f The field to grab data from.
 * @param row The row that the boat will start from, valid range is from 0 and to FIELD_ROWS - 1.
 * @param col The column that the boat will start from, valid range is from 0 and to FIELD_COLS - 1.
 * @param dir The direction that the boat will face once places, from the BoatDirection enum.
 * @param boatType The type of boat to place. Relies on the FIELD_SQUARE_*_BOAT values from the
 * SquareStatus enum.
 * @return SUCCESS for success, STANDARD_ERROR for failure
 */
uint8_t FieldAddBoat(Field *f, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type)
{
    static unsigned int j; //used to increment through boats.


    if ((row >= 0 && row < FIELD_ROWS) && (col >= 0 && col < FIELD_COLS)) { //check if bounds are valid:
        if (boat_type == FIELD_BOAT_TYPE_HUGE) { //HUGE boat case:
            if (dir == FIELD_DIR_EAST) { //EAST facing:
                for (j = 0; j < FIELD_BOAT_SIZE_HUGE; j++) { //iterate through each grid location:
                    if (FieldGetSquareStatus(f, row, col + j) != FIELD_SQUARE_EMPTY) { //if we ever encounter an invalid grid location:
                        return STANDARD_ERROR; //exit immediately and return an error.
                    } else {
                        f->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
                        f->grid[row][col + j] = FIELD_SQUARE_HUGE_BOAT; //else, set the square to HUGE boat.
                    }
                }
                return SUCCESS;
            } else { //direction == FIELD_DIR_SOUTH
                for (j = 0; j < FIELD_BOAT_SIZE_HUGE; j++) {
                    if (FieldGetSquareStatus(f, row + j, col) != FIELD_SQUARE_EMPTY) {
                        return STANDARD_ERROR;
                    } else {
                        f->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
                        f->grid[row + j][col] = FIELD_SQUARE_HUGE_BOAT;
                    }
                }
                return SUCCESS;
            }
        }
        if (boat_type == FIELD_BOAT_TYPE_LARGE) { //LARGE boat case:
            if (dir == FIELD_DIR_EAST) { //EAST facing:
                for (j = 0; j < FIELD_BOAT_SIZE_LARGE; j++) { //iterate through each grid location:
                    if (FieldGetSquareStatus(f, row, col + j) != FIELD_SQUARE_EMPTY) { //if we ever encounter an invalid grid location:
                        return STANDARD_ERROR; //exit immediately and return an error.
                    } else {
                        f->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
                        f->grid[row][col + j] = FIELD_SQUARE_LARGE_BOAT; //else, set the square to LARGE boat.
                    }
                }
                return SUCCESS;
            } else { //direction == FIELD_DIR_SOUTH
                for (j = 0; j < FIELD_BOAT_SIZE_LARGE; j++) {
                    if (FieldGetSquareStatus(f, row + j, col) != FIELD_SQUARE_EMPTY) {
                        return STANDARD_ERROR;
                    } else {
                        f->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
                        f->grid[row + j][col] = FIELD_SQUARE_LARGE_BOAT;
                    }
                }
                return SUCCESS;
            }
        }
        if (boat_type == FIELD_BOAT_TYPE_MEDIUM) { //MEDIUM boat case:
            if (dir == FIELD_DIR_EAST) { //EAST facing:
                for (j = 0; j < FIELD_BOAT_SIZE_MEDIUM; j++) { //iterate through each grid location:
                    if (FieldGetSquareStatus(f, row, col + j) != FIELD_SQUARE_EMPTY) { //if we ever encounter an invalid grid location:
                        return STANDARD_ERROR; //exit immediately and return an error.
                    } else {
                        f->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                        f->grid[row][col + j] = FIELD_SQUARE_MEDIUM_BOAT; //else, set the square to MEDIUM boat.
                    }
                }
                return SUCCESS;
            } else { //direction == FIELD_DIR_SOUTH
                for (j = 0; j < FIELD_BOAT_SIZE_MEDIUM; j++) {
                    if (FieldGetSquareStatus(f, row + j, col) != FIELD_SQUARE_EMPTY) {
                        return STANDARD_ERROR;
                    } else {
                        f->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                        f->grid[row + j][col] = FIELD_SQUARE_MEDIUM_BOAT;
                    }
                }
                return SUCCESS;
            }
        }
        if (boat_type == FIELD_BOAT_TYPE_SMALL) { //SMALL boat case:
            if (dir == FIELD_DIR_EAST) { //EAST facing:
                for (j = 0; j < FIELD_BOAT_SIZE_SMALL; j++) { //iterate through each grid location:
                    if (FieldGetSquareStatus(f, row, col + j) != FIELD_SQUARE_EMPTY) { //if we ever encounter an invalid grid location:
                        return STANDARD_ERROR; //exit immediately and return an error.
                    } else {
                        f->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                        f->grid[row][col + j] = FIELD_SQUARE_SMALL_BOAT; //else, set the square to SMALL boat.
                    }
                }
                return SUCCESS;
            } else { //direction == FIELD_DIR_SOUTH
                for (j = 0; j < FIELD_BOAT_SIZE_SMALL; j++) {
                    if (FieldGetSquareStatus(f, row + j, col) != FIELD_SQUARE_EMPTY) {
                        return STANDARD_ERROR;
                    } else {
                        f->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                        f->grid[row + j][col] = FIELD_SQUARE_SMALL_BOAT;
                    }
                }
                return SUCCESS;
            }
        }

    } //else {
    return STANDARD_ERROR; //bounds are invalid!

}




/******************************************************************************
 * FIELD - Register Enemy Attack
 *****************************************************************************/

/**
 * This function registers an attack at the gData coordinates on the provided field. This means that
 * 'f' is updated with a FIELD_SQUARE_HIT or FIELD_SQUARE_MISS depending on what was at the
 * coordinates indicated in 'gData'. 'gData' is also updated with the proper HitStatus value
 * depending on what happened AND the value of that field position BEFORE it was attacked. Finally
 * this function also reduces the lives for any boat that was hit from this attack.
 * @param f The field to check against and update.
 * @param gData The coordinates that were guessed. The result is stored in gData->result as an
 *               output.
 * @return The data that was stored at the field position indicated by gData before this attack.
 */
SquareStatus FieldRegisterEnemyAttack(Field *f, GuessData *gData)
{
    static SquareStatus register_attack;

    register_attack = f->grid[gData->row][gData->col]; //set field guess grid location to register_attack SquareStatus.

    switch (register_attack) { //evaluate situation based on current grid SquareStatus type.
    case FIELD_SQUARE_HUGE_BOAT: //if current square is HUGE BOAT:
        (f->hugeBoatLives)--;
        if (f->hugeBoatLives == 0) {
            //huge boat sunk.
            gData->result = RESULT_HUGE_BOAT_SUNK;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        } else {
            gData->result = RESULT_HIT;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        }
        break;
    case FIELD_SQUARE_LARGE_BOAT: //if current square is LARGE BOAT:
        (f->largeBoatLives)--;
        if (f->largeBoatLives == 0) {
            //large boat sunk.
            gData->result = RESULT_LARGE_BOAT_SUNK;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        } else {
            gData->result = RESULT_HIT;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        }
        break;
    case FIELD_SQUARE_MEDIUM_BOAT: //if current square is MEDIUM BOAT:
        (f->mediumBoatLives)--;
        if (f->mediumBoatLives == 0) {
            //medium boat sunk.
            gData->result = RESULT_MEDIUM_BOAT_SUNK;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        } else {
            gData->result = RESULT_HIT;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        }
        break;
    case FIELD_SQUARE_SMALL_BOAT: //if current square is SMALL BOAT:
        (f->smallBoatLives)--;
        if (f->smallBoatLives == 0) {
            //small boat sunk.
            gData->result = RESULT_SMALL_BOAT_SUNK;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        } else {
            gData->result = RESULT_HIT;
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        }
        break;
    default: //current grid guess is NOT A SHIP:
        //do something.
        gData->result = RESULT_MISS;
        f->grid[gData->row][gData->col] = FIELD_SQUARE_MISS;
        break;
    }
    return register_attack; //return the original grid position status.
}




/******************************************************************************
 * FIELD - Update Knowledge
 *****************************************************************************/

/**
 * This function updates the FieldState representing the opponent's game board with whether the
 * guess indicated within gData was a hit or not. If it was a hit, then the field is updated with a
 * FIELD_SQUARE_HIT at that position. If it was a miss, display a FIELD_SQUARE_EMPTY instead, as
 * it is now known that there was no boat there. The FieldState struct also contains data on how
 * many lives each ship has. Each hit only reports if it was a hit on any boat or if a specific boat
 * was sunk, this function also clears a boats lives if it detects that the hit was a
 * RESULT_*_BOAT_SUNK.
 * @param f The field to grab data from.
 * @param gData The coordinates that were guessed along with their HitStatus.
 * @return The previous value of that coordinate position in the field before the hit/miss was
 * registered.
 */
SquareStatus FieldUpdateKnowledge(Field *f, const GuessData *gData)
{
    static SquareStatus update_knowledge;

    update_knowledge = f->grid[gData->row][gData->col]; //set field guess grid location to register_attack SquareStatus.

    switch (gData->result) {
    case RESULT_HIT:
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        break;
    case RESULT_HUGE_BOAT_SUNK:
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        f->hugeBoatLives = 0;
        break;
    case RESULT_LARGE_BOAT_SUNK:
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        f->largeBoatLives = 0;
        break;
    case RESULT_MEDIUM_BOAT_SUNK:
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        f->mediumBoatLives = 0;
        break;
    case RESULT_SMALL_BOAT_SUNK:
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        f->smallBoatLives = 0;
        break;
    default: //case RESULT_MISS:
        f->grid[gData->row][gData->col] = FIELD_SQUARE_EMPTY;
        break;
    }

    return update_knowledge; //return the original grid position status.
}




/******************************************************************************
 * FIELD - Get Boat States
 *****************************************************************************/

/**
 * This function returns the alive states of all 4 boats as a 4-bit bitfield (stored as a uint8).
 * The boats are ordered from smallest to largest starting at the least-significant bit. So that:
 * 0b00001010 indicates that the small boat and large boat are sunk, while the medium and huge boat
 * are still alive. See the BoatStatus enum for the bit arrangement.
 * @param f The field to grab data from.
 * @return A 4-bit value with each bit corresponding to whether each ship is alive or not.
 */
uint8_t FieldGetBoatStates(const Field *f)
{
    static uint8_t state_bitfield;

    if (f->hugeBoatLives != 0) { //only toggle 0x08 if HUGE != SUNK
        state_bitfield ^= FIELD_BOAT_STATUS_HUGE;
    }
    if (f->largeBoatLives != 0) { //only toggle 0x04 if LARGE != SUNK
        state_bitfield ^= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->mediumBoatLives != 0) { //only toggle 0x02 if MEDIUM != SUNK
        state_bitfield ^= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->smallBoatLives != 0) { //only toggle 0x01 if SMALL != SUNK
        state_bitfield ^= FIELD_BOAT_STATUS_SMALL;
    }
    return state_bitfield;
}




/******************************************************************************
 * FIELD - AI Place All Boats
 *****************************************************************************/

/**
 * This function is responsible for placing all the boats on a field.
 * 
 * @param f         //agent's own field, to be modified in place.
 * @return SUCCESS if all boats could be placed, STANDARD_ERROR otherwise.
 * 
 * This function should never fail when passed a properly initialized field!
 */
uint8_t FieldAIPlaceAllBoats(Field *f)
{
    //srand(__TIME__); //set seed to random, time-variant.
    static uint8_t addBoat_status;
    static unsigned int success_counter;
    static uint8_t row;
    static uint8_t col;
    BoatDirection dir;

    static unsigned int row_modulus;
    static unsigned int col_modulus;

    row_modulus = FIELD_ROWS - 1;
    col_modulus = FIELD_COLS - 1;

    row = rand() % (row_modulus); //generate random row value from 0 to rows-1.
    col = rand() % (col_modulus); //generate random column value from 0 to columns-1.
    dir = rand() % 1; //generate random direction from 0(south) to 1(east).

    //need to randomly generate the input coordinates, and boat direction?
    //places in order of largest to smallest.
    printf("testing!");
    while (addBoat_status != SUCCESS) {
        addBoat_status = FieldAddBoat(f, row, col, dir, FIELD_BOAT_TYPE_HUGE);
        row = rand() % (row_modulus); //generate random row value from 0 to rows-1.
        col = rand() % (col_modulus); //generate random column value from 0 to columns-1.
        dir = rand() % 1; //generate random direction from 0(south) to 1(east).
    }
    success_counter++;
    addBoat_status = 0; //reset to zero.
    while (addBoat_status != SUCCESS) {
        addBoat_status = FieldAddBoat(f, row, col, dir, FIELD_BOAT_TYPE_LARGE);
        row = rand() % (row_modulus); //generate random row value from 0 to rows-1.
        col = rand() % (col_modulus); //generate random column value from 0 to columns-1.
        dir = rand() % 1; //generate random direction from 0(south) to 1(east).
    }
    success_counter++;
    addBoat_status = 0; //reset to zero.
    while (addBoat_status != SUCCESS) {
        addBoat_status = FieldAddBoat(f, row, col, dir, FIELD_BOAT_TYPE_MEDIUM);
        row = rand() % (row_modulus); //generate random row value from 0 to rows-1.
        col = rand() % (col_modulus); //generate random column value from 0 to columns-1.
        dir = rand() % 1; //generate random direction from 0(south) to 1(east).
    }
    success_counter++;
    addBoat_status = 0; //reset to zero.
    while (addBoat_status != SUCCESS) {
        addBoat_status = FieldAddBoat(f, row, col, dir, FIELD_BOAT_TYPE_SMALL);
        row = rand() % (row_modulus); //generate random row value from 0 to rows-1.
        col = rand() % (col_modulus); //generate random column value from 0 to columns-1.
        dir = rand() % 1; //generate random direction from 0(south) to 1(east).
    }
    success_counter++;
    addBoat_status = 0; //reset to zero.

    if (success_counter == 4) {
        success_counter = 0;
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}




/******************************************************************************
 * FIELD - AI Decide Guess
 *****************************************************************************/

/**
 * Given a field, decide the next guess.
 *
 * This function should not attempt to shoot a square which has already been guessed.
 *
 * You may wish to give this function static variables.  If so, that data should be
 * reset when FieldInit() is called.
 * 
 * @param f an opponent's field.
 * @return a GuessData struct whose row and col parameters are the coordinates of the guess.  The 
 *           result parameter is irrelevant.
 */
GuessData FieldAIDecideGuess(const Field * f)
{
    //srand(__TIME__); //set seed to random, time-variant.
    static unsigned int i; //used to randomly generate row value.
    static unsigned int j; //used to randomly generate column value.
    static GuessData gData;
    static unsigned int row_modulus;
    static unsigned int col_modulus;

    row_modulus = FIELD_ROWS;
    col_modulus = FIELD_COLS;

#ifdef EXTRA_CREDIT_MODE

    static GuessState guess_state;
    static GuessData previous_guess;
    static unsigned int exit_check;
    static unsigned south_counter;
    static unsigned north_counter;
    static unsigned east_counter;
    static unsigned west_counter;

    previous_guess = gData;

    if (f->grid[previous_guess.row][previous_guess.col] == FIELD_SQUARE_HIT) {
        //if random number guess resulted in a HIT:
        guess_state = GO_SOUTH;

    }

    switch (guess_state) {
    case GET_FIRST_HIT:
        i = rand() % (row_modulus); //generate random row value from 0 to rows-1.
        j = rand() % (col_modulus); //generate random column value from 0 to columns-1.
        //guess random within bounds of row and column.
        while (f->grid[i][j] != FIELD_SQUARE_UNKNOWN || f->grid[i][j] == FIELD_SQUARE_INVALID) { //while square is not a valid target:
            //generate a new random number for [i] and [j].
            i = rand() % (row_modulus);
            j = rand() % (col_modulus);
        }

        gData.row = i; //return row.
        gData.col = j; //return column.
        return gData; //return variable with stored guess values.

        break;
    case GO_SOUTH:
        if (f->grid[previous_guess.row][previous_guess.col] == FIELD_SQUARE_MISS) {
            guess_state = GO_NORTH;
            gData.row = gData.row - south_counter;
            gData.row = gData.row + 1;
            gData.col = gData.col;
            south_counter = 0;
            return gData;
        }
        if (f->grid[i + south_counter][j] != FIELD_SQUARE_INVALID) {
            south_counter++;
            gData.row = i + south_counter;
            gData.col = j;
            return gData;
        }
        break;
    case GO_NORTH:
        if (f->grid[previous_guess.row][previous_guess.col] == FIELD_SQUARE_MISS) {
            guess_state = GO_EAST;
            gData.row = gData.row + north_counter;
            gData.col = gData.col + 1;
            south_counter = 0;
            return gData;
        }
        if (f->grid[i - north_counter][j] != FIELD_SQUARE_INVALID) {
            north_counter++;
            gData.row = i - north_counter;
            gData.col = j;
            return gData;
        }
        break;
    case GO_EAST:
        if (f->grid[previous_guess.row][previous_guess.col] == FIELD_SQUARE_MISS) {
            guess_state = GO_WEST;
            gData.col = gData.col - east_counter;
            gData.col = gData.col - 1;
            east_counter = 0;
            return gData;
        }
        if (f->grid[i][j + east_counter] != FIELD_SQUARE_INVALID) {
            east_counter++;
            gData.row = i;
            gData.col = j + east_counter;
            return gData;
        }
        break;
    case GO_WEST:
        if (f->grid[previous_guess.row][previous_guess.col] == FIELD_SQUARE_MISS) {
            guess_state = GET_FIRST_HIT;
            west_counter = 0;
            //exit switch statement.
            exit_check = 1;
        }
        if (f->grid[i][j + west_counter] != FIELD_SQUARE_INVALID && exit_check != 1) {
            west_counter++;
            gData.row = i - west_counter;
            gData.col = j;
            return gData;
        }
        break;
    default: //GET_FIRST_HIT
        i = rand() % (row_modulus); //generate random row value from 0 to rows-1.
        j = rand() % (col_modulus); //generate random column value from 0 to columns-1.
        //guess random within bounds of row and column.
        while (f->grid[i][j] != FIELD_SQUARE_UNKNOWN || f->grid[i][j] == FIELD_SQUARE_INVALID) { //while square is not a valid target:
            //generate a new random number for [i] and [j].
            i = rand() % (row_modulus);
            j = rand() % (col_modulus);
        }

        gData.row = i; //return row.
        gData.col = j; //return column.
        return gData; //return variable with stored guess values.
    }

    i = rand() % (row_modulus); //generate random row value from 0 to rows-1.
    j = rand() % (col_modulus); //generate random column value from 0 to columns-1.
    //guess random within bounds of row and column.
    while (f->grid[i][j] != FIELD_SQUARE_UNKNOWN || f->grid[i][j] == FIELD_SQUARE_INVALID) { //while square is not a valid target:
        //generate a new random number for [i] and [j].
        i = rand() % (row_modulus);
        j = rand() % (col_modulus);
    }

    gData.row = i; //return row.
    gData.col = j; //return column.
    return gData; //return variable with stored guess values.


#else

    i = rand() % (row_modulus); //generate random row value from 0 to rows-1.
    j = rand() % (col_modulus); //generate random column value from 0 to columns-1.
    //guess random within bounds of row and column.
    while (f->grid[i][j] != FIELD_SQUARE_UNKNOWN || f->grid[i][j] == FIELD_SQUARE_INVALID) { //while square is not a valid target:
        //generate a new random number for [i] and [j].
        i = rand() % (row_modulus);
        j = rand() % (col_modulus);
    }

    gData.row = i; //return row.
    gData.col = j; //return column.
    return gData; //return variable with stored guess values.

    /** 
     * For Extra Credit:  Make the two "AI" functions above 
     * smart enough to beat our AI in more than 55% of games.
     */

#endif

}