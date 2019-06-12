

#include "UNIXBOARD.h"

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// The initial room that Game should initialize to.
#define STARTING_ROOM 32
#define RPG_SEEK 3
#define EXIT_SEEK 4
#define NULL_TERMINATOR '\0'



// These variable describe the maximum string length of the room title and description respectively.
// Note that they don't account for the trailing '\0' character implicit with C-style strings.
#define GAME_MAX_ROOM_TITLE_LENGTH 21
#define GAME_MAX_ROOM_DESC_LENGTH 255

/**
 * This enum defines flags for checking the return values of GetCurrentRoomExits(). Usage is as
 * follows:
 *
 * if (GetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
 *   // The current room has a west exit.
 * }
 *
 * @see GetCurrentRoomExits
 */
typedef enum {
    GAME_ROOM_EXIT_WEST_EXISTS = 0b0001,
    GAME_ROOM_EXIT_SOUTH_EXISTS = 0b0010,
    GAME_ROOM_EXIT_EAST_EXISTS = 0b0100,
    GAME_ROOM_EXIT_NORTH_EXISTS = 0b1000
} GameRoomExitFlags;

typedef struct {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t exits;
} GameRoom;

static GameRoom current_room;
static FILE * file_pointer;

/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void)
{

}

/**
 * @see GameGoNorth
 */
int GameGoEast(void)
{

}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void)
{

}

/**
 * @see GameGoNorth
 */
int GameGoWest(void)
{

}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void)
{
    file_pointer = fopen("RoomFiles/room32.txt", "rb");
    if (file_pointer) {

        GameGetCurrentRoomTitle(current_room.title); //store the title to current room.
        GameGetCurrentRoomDescription(current_room.description); //obtain room description.
        current_room.exits = GameGetCurrentRoomExits(); //set .exits to exit bit-field.


    } else {
        return STANDARD_ERROR; //f-open() command failed!
    }
}

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title)
{
    static uint16_t byte_length; //stores ASCII value for string length.
    static unsigned int i; //skip past RPG characters.
    if (fseek(file_pointer, RPG_SEEK, SEEK_SET) != 0) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    byte_length = fgetc(file_pointer); //set byte_length to title length ASCII.
    if (byte_length == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    while (byte_length != 0) {
        title[i] = fgetc(file_pointer);
        if (title[i] == EOF) {
            return STANDARD_ERROR;
        } //check for any ERRORS!

        byte_length--; //subtract from the ASCII value of byte_length.
        i++; //increment array counter.
    } //once byte_length reaches zero:

    title[i] = NULL_TERMINATOR; //append null-terminator.

    return strlen(title);

}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc)
{
    static uint16_t byte_length_title; //stores ASCII value for string length.
    static uint16_t byte_length_description; //same, but for description.
    static uint16_t byte_length_requirements; //items required.
    static uint16_t byte_length_contained; //items able to obtain.

    static Inventory room_items;
    static Inventory items_contained;
    static unsigned int i; //skip past RPG characters.

    if (fseek(file_pointer, RPG_SEEK, SEEK_SET) != 0) { //skip 'RPG'
        return STANDARD_ERROR;
    } //checking for ERRORS!

    byte_length_title = fgetc(file_pointer); //set byte_length to title length ASCII.
    if (byte_length_title == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    if (fseek(file_pointer, byte_length_title, SEEK_CUR) != 0) { //skip over title from current position.
        return STANDARD_ERROR;
    } //check for ERRORS.

    byte_length_requirements = fgetc(file_pointer); //obtain number of requirements.
    if (byte_length_requirements == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    if (byte_length_requirements != 0) { //there are requirements for the current room!
        room_items.item1 = fgetc(file_pointer); //item1 
        byte_length_requirements--;
        if (byte_length_requirements != 0) {
            room_items.item2 = fgetc(file_pointer); //item2
            byte_length_requirements--;
            if (byte_length_requirements != 0) {
                room_items.item3 = fgetc(file_pointer); //item3
                byte_length_requirements--;
                if (byte_length_requirements != 0) {
                    room_items.item4 = fgetc(file_pointer); //item4
                    byte_length_requirements--;
                }
            }
        }

        //Now we have stored all available item requirements within our structure.
        if (FindInInventory(room_items.item1) && FindInInventory(room_items.item2) &&
                FindInInventory(room_items.item3) && FindInInventory(room_items.item4)) {
            //if the player's inventory contains all of the above items:

            byte_length_description = fgetc(file_pointer); //obtain length of description in ASCII.
            if (byte_length_description == EOF) {
                return STANDARD_ERROR;
            } //checking for ERRORS!

            while (byte_length_description != 0) { //while description length != 0:
                desc[i] = fgetc(file_pointer); //update current index with desc. byte.
                if (desc[i] == EOF) {
                    return STANDARD_ERROR;
                } //check for any ERRORS!

                byte_length_description--; //decrement ASCII value of length.
                i++; //increment array counter.
            } //once byte_length reaches zero:

            desc[i] = NULL_TERMINATOR; //append null-terminator.

            byte_length_contained = fgetc(file_pointer); //obtain number items contained.
            if (byte_length_description == EOF) {
                return STANDARD_ERROR;
            } //checking for ERRORS!

            if (byte_length_contained != 0) {
                items_contained.item1 = fgetc(file_pointer);
                byte_length_contained--;
                AddToInventory(items_contained.item1);
                if (byte_length_contained != 0) {
                    items_contained.item2 = fgetc(file_pointer);
                    byte_length_contained--;
                    AddToInventory(items_contained.item2);
                    if (byte_length_contained != 0) {
                        items_contained.item3 = fgetc(file_pointer);
                        byte_length_contained--;
                        AddToInventory(items_contained.item3);
                        if (byte_length_contained != 0) {
                            items_contained.item4 = fgetc(file_pointer);
                            byte_length_contained--;
                            AddToInventory(items_contained.item4);
                        }
                    }
                }
            } //Now all the inventory items have been added. 
            return strlen(desc);

        } //ELSE, the item requirements have NOT been met:

        byte_length_description = fgetc(file_pointer); //obtain length of description in ASCII.
        if (byte_length_description == EOF) {
            return STANDARD_ERROR;
        } //checking for ERRORS!

        if (fseek(file_pointer, byte_length_description, SEEK_CUR) != 0) { //skip over description from current position.
            return STANDARD_ERROR;
        } //check for ERRORS.

        byte_length_contained = fgetc(file_pointer); //obtain number items contained.
        if (byte_length_description == EOF) {
            return STANDARD_ERROR;
        } //checking for ERRORS!

        if (fseek(file_pointer, byte_length_contained, SEEK_CUR) != 0) { //skip over description from current position.
            return STANDARD_ERROR;
        } //check for ERRORS.

        if (fseek(file_pointer, EXIT_SEEK, SEEK_CUR) != 0) { //skip over EXIT locations.
            return STANDARD_ERROR;
        } //check for ERRORS.

        byte_length_requirements = fgetc(file_pointer); //obtain number of requirements.
        if (byte_length_requirements == EOF) {
            return STANDARD_ERROR;
        } //checking for ERRORS!

        byte_length_description = fgetc(file_pointer); //obtain length of description in ASCII.
        if (byte_length_description == EOF) {
            return STANDARD_ERROR;
        } //checking for ERRORS!

        while (byte_length_description != 0) { //while description length != 0:
            desc[i] = fgetc(file_pointer); //update current index with desc. byte.
            if (desc[i] == EOF) {
                return STANDARD_ERROR;
            } //check for any ERRORS!

            byte_length_description--; //decrement ASCII value of length.
            i++; //increment array counter.
        } //once byte_length reaches zero:

        desc[i] = NULL_TERMINATOR; //append null-terminator.

        byte_length_contained = fgetc(file_pointer); //obtain number items contained.
        if (byte_length_description == EOF) {
            return STANDARD_ERROR;
        } //checking for ERRORS!

        if (byte_length_contained != 0) {
            items_contained.item1 = fgetc(file_pointer);
            byte_length_contained--;
            AddToInventory(items_contained.item1);
            if (byte_length_contained != 0) {
                items_contained.item2 = fgetc(file_pointer);
                byte_length_contained--;
                AddToInventory(items_contained.item2);
                if (byte_length_contained != 0) {
                    items_contained.item3 = fgetc(file_pointer);
                    byte_length_contained--;
                    AddToInventory(items_contained.item3);
                    if (byte_length_contained != 0) {
                        items_contained.item4 = fgetc(file_pointer);
                        byte_length_contained--;
                        AddToInventory(items_contained.item4);
                    }
                }
            }
        } //Now all the inventory items have been added. 
        return strlen(desc);


    } //ELSE, there ARE NO requirements:

    byte_length_description = fgetc(file_pointer); //obtain length of description in ASCII.
    if (byte_length_description == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    while (byte_length_description != 0) { //while description length != 0:
        desc[i] = fgetc(file_pointer); //update current index with desc. byte.
        if (desc[i] == EOF) {
            return STANDARD_ERROR;
        } //check for any ERRORS!

        byte_length_description--; //decrement ASCII value of length.
        i++; //increment array counter.
    } //once byte_length reaches zero:

    desc[i] = NULL_TERMINATOR; //append null-terminator.

    byte_length_contained = fgetc(file_pointer); //obtain number items contained.
    if (byte_length_description == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    if (byte_length_contained != 0) {
        items_contained.item1 = fgetc(file_pointer);
        byte_length_contained--;
        AddToInventory(items_contained.item1);
        if (byte_length_contained != 0) {
            items_contained.item2 = fgetc(file_pointer);
            byte_length_contained--;
            AddToInventory(items_contained.item2);
            if (byte_length_contained != 0) {
                items_contained.item3 = fgetc(file_pointer);
                byte_length_contained--;
                AddToInventory(items_contained.item3);
                if (byte_length_contained != 0) {
                    items_contained.item4 = fgetc(file_pointer);
                    byte_length_contained--;
                    AddToInventory(items_contained.item4);
                }
            }
        }
    } //Now all the inventory items have been added. 
    return strlen(desc);

}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void)
{
    static uint8_t exit_bits; //reset each time, static.

    //where to find markers for each direction???
    static uint16_t byte_length_title;
    static uint16_t byte_length_description;
    static uint16_t byte_length_requirements;
    static uint16_t byte_length_contained;
    static uint16_t byte_length_exits;

    static unsigned int i; //skip past RPG characters.

    if (fseek(file_pointer, RPG_SEEK, SEEK_SET) != 0) { //skip 'RPG'
        return STANDARD_ERROR;
    } //checking for ERRORS!

    byte_length_title = fgetc(file_pointer); //set byte_length to title length ASCII.
    if (byte_length_title == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    if (fseek(file_pointer, byte_length_title, SEEK_CUR) != 0) { //skip over title from current position.
        return STANDARD_ERROR;
    } //check for ERRORS.

    byte_length_requirements = fgetc(file_pointer); //obtain number of requirements.
    if (byte_length_requirements == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    if (fseek(file_pointer, byte_length_requirements, SEEK_CUR) != 0) { //skip over title from current position.
        return STANDARD_ERROR;
    } //check for ERRORS.

    byte_length_description = fgetc(file_pointer); //obtain number of requirements.
    if (byte_length_description == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    if (fseek(file_pointer, byte_length_description, SEEK_CUR) != 0) { //skip over title from current position.
        return STANDARD_ERROR;
    } //check for ERRORS.

    byte_length_contained = fgetc(file_pointer); //obtain number of requirements.
    if (byte_length_contained == EOF) {
        return STANDARD_ERROR;
    } //checking for ERRORS!

    if (fseek(file_pointer, byte_length_contained, SEEK_CUR) != 0) { //skip over title from current position.
        return STANDARD_ERROR;
    } //check for ERRORS.

    //NOW WE ARE AT THE POSITION OF THE EXITS:



    if (fgetc(file_pointer) != 0) { //read north position.
        exit_bits |= GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (fgetc(file_pointer) != 0) { //read east position.
        exit_bits |= GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (fgetc(file_pointer) != 0) { //read south position.
        exit_bits |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (fgetc(file_pointer) != 0) { //read west position.
        exit_bits |= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return exit_bits;
}
