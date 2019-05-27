// Heap size 2048 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "Morse.h"
#include "BinaryTree.h"
#include "Buttons.h"

/**
 * This library implements functions for decoding Morse code. It builds upon the Tree library to use
 * a binary tree data structure for storing the codepoints for all characters. Decoding is then done
 * through simple tree traversal. Additional functionality relies on a 100Hz clock to check the
 * button states for decoding the input of Morse characters through a physical button (BTN4).
 */

#include <stdint.h>

/**
 * This enum declares constants for all of the possible event types that this module can trigger.
 */
typedef enum {
    MORSE_EVENT_NONE,
    MORSE_EVENT_DOT,
    MORSE_EVENT_DASH,
    MORSE_EVENT_NEW_LETTER,
    MORSE_EVENT_NEW_WORD,
    MORSE_EVENT_CHAR_DECODED,
    MORSE_EVENT_ERROR,
} MorseEventType;

typedef enum {
    WAITING_FOR_WORD,
    WAITING_FOR_LETTER,
    WAITING_FOR_PULSE,
    DOT,
    DASH,
} MorseState;

typedef struct {
    MorseEventType type;
    MorseState state; //allows for storage of current state.
    char parameter; //only used for CHAR_DECODED events
} MorseEvent;

/**
 * This enum specifies the characters that should be used to print to the OLED
 */
typedef enum {
    MORSE_CHAR_DOT = '.', /// A Morse DOT.
    MORSE_CHAR_DASH = '-', /// A Morse DASH.
    MORSE_CHAR_BAD_CHAR = '#', /// If the morse string does not correspond to any character, or is empty, use this char to signify an error 
} MorseChar;

/**
 * Define the length of time, in units of .01s, that either button-presses or time between button
 * presses should be.
 */
typedef enum {
    MORSE_DOT_TIMEOUT = 25,
    MORSE_LETTER_TIMEOUT = 100,
    MORSE_WORD_TIMEOUT = 200
} MorseEventLength;

static uint8_t bEvent; //used to collect ButtonsCheckEvents() state.
static uint8_t ButtonsEvent;
static int wordTimer;
static int letterTimer;
static int dashTimer;

#define SUCCESS 1
#define TRUE 1
#define STANDARD_ERROR 0 
#define FALSE 0

/**
 * This function initializes the Morse code decoder. This is primarily the generation of the
 * Morse tree: a binary tree consisting of all of the ASCII alphanumeric characters arranged
 * according to the DOTs and DASHes that represent each character. Traversal of the tree is done by
 * taking the left-child if it is a dot and the right-child if it is a dash. If the morse tree is
 * successfully generated, SUCCESS is returned, otherwise STANDARD_ERROR is returned. This function
 * also initializes the Buttons library so that MorseCheckEvents() can work properly.
 * @return Either SUCCESS if the decoding tree was successfully created or STANDARD_ERROR if not.
 */
int MorseInit(void)
{
    ButtonsInit();
    Node *morseTree = TreeCreate(6, "#EISH54V#3UF####2ARL#####WP##J#1TNDB6#X##KC##Y##MGZ7#Q##O#8##90"); //full morse tree.
    if (morseTree) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

/**
 * MorseDecode decodes a Morse string by iteratively being passed MORSE_EVENT_DOT or MORSE_EVENT_DASH.
 *
 * If this function is passed a MORSE_EVENT_DOT or MORSE_EVENT_DASH:
 * 		a MORSE_EVENT_NONE type event if the sequence of DOTs and DASHes 
 *                          could still compose a Morse-encoded 
 *                          alphanumeric character (eg, ".." or "..--")
 *      a MORSE_EVENT_ERROR type event if the sequence of DOTs and DASHes has 
 *                          exited the Morse Decoding Tree (eg, "--..--") 
 *              			or has entered a node below which no alphanumeric characters 
 *                          could still be composed (eg, ".-.-")
 *   
 * 	If a MORSE_EVENT_NEW_LETTER is passed, this function attempts 
 *	to complete decoding, and returns either:
 *      a MORSE_EVENT_CHAR_DECODED event with the decoded ASCII character 
 *                              in the "parameter" field
 *      a MORSE_EVENT_ERROR if the previous sequence of DOTs and DASHes 
 *                              do not represent a valid morse string.
 * 
 * On MORSE_EVENT_NEW_LETTER, the internal state should be reset.
 * 
 * @param input_event A MorseEvent, generally an event set by MorseCheckEvents().
 * 
 * @return MorseEvent  This value should be of type MORSE_EVENT_NONE, MORSE_EVENT_CHAR_DECODED,
 *						or MORSE_EVENT_ERROR.  If the return value is of type 
 *						MORSE_EVENT_CHAR_DECODED, then the "parameter" field 
 *						should contain the decoded ascii char.
 */
MorseEvent MorseDecode(MorseEvent input_event)
{
    if (input_event.type == MORSE_EVENT_DOT || MORSE_EVENT_DASH) {
        if () { //an invalid sequence! exits lowest level, or enters a nonexistent node.
            MorseEvent.type = MORSE_EVENT_ERROR;
            return MorseEvent;
        } else { //sequence is valid
            MorseEvent.type = MORSE_EVENT_NONE;
            return MorseEvent;
        }
    }
    if (input_event.type == MORSE_EVENT_NEW_LETTER) { //reset internal state?
        if () { //if previous of morse sequence is invalid,
            MorseEvent.type = MORSE_EVENT_ERROR;
            return MorseEvent;
        } else { //complete decoding.
            MorseEvent.type = MORSE_EVENT_CHAR_DECODED;
            //MorseEvent.parameter = 'C';
            return MorseEvent;

        }
    }




}

/**
 * This function calls ButtonsCheckEvents() once per call and returns an MorseEvent with  type:
 * 		MORSE_EVENT_NONE if no event has been detected
 *		MORSE_EVENT_DASH or MORSE_EVENT_DOT if a pulse has been completed,
 *		MORSE_EVENT_NEW_LETTER if MORSE_LETTER_TIMEOUT has elapsed since the last pulse, or 
 *		MORSE_EVENT_NEW_WORD if MORSE_WORD_TIMEOUT has elapsed since the last pulse. 
 * 
 * Pulses are entered using BTN4. 
 * 
 * @return The MorseEvent that occurred.
 */
MorseEvent MorseCheckEvents(void)
{
    bEvent = ButtonsCheckEvents(); //constantly poll for button changes.

    switch (MorseEvent.state) { //run state machine, TIMEOUT's included within.
    case WAITING_FOR_WORD:
        if (bEvent & BUTTON_EVENT_4DOWN) {
            //set dot countdown.
            dashTimer = MORSE_DOT_TIMEOUT;

            MorseEvent.state = DOT; //switch to DOT.
        } else {
            MorseEvent.type = MORSE_EVENT_NONE;
            return MorseEvent; //ELSE, return NOTHING.
        }
        break;

    case WAITING_FOR_LETTER:
        wordTimer--;
        if (wordTimer == 0) {
            //once word_timeout,
            MorseEvent.type = MORSE_EVENT_NEW_WORD; //generate new_word event.

            MorseEvent.state = WAITING_FOR_WORD; //switch to WAITING_FOR_WORD.
            return MorseEvent;

        } else if (ButtonsEvent == BUTTON_EVENT_4DOWN) {
            //set dot countdown.
            dashTimer = MORSE_DOT_TIMEOUT;

            MorseEvent.state = DOT; //switch to DOT.
        } else {
            MorseEvent.type = MORSE_EVENT_NONE;
            return MorseEvent; //ELSE, return NOTHING.
        }
        break;

    case WAITING_FOR_PULSE:
        letterTimer--;
        if (letterTimer == 0) {
            //once letter_timeout,
            MorseEvent.type = MORSE_EVENT_NEW_LETTER; //generate new_letter event.

            MorseEvent.state = WAITING_FOR_LETTER; //switch to WAITING_FOR_LETTER.
            return MorseEvent;

        } else if (bEvent & BUTTON_EVENT_4DOWN) {
            //set dot countdown.
            dashTimer = MORSE_DOT_TIMEOUT;

            MorseEvent.state = DOT; //switch to DOT.
        } else {
            MorseEvent.type = MORSE_EVENT_NONE;
            return MorseEvent; //ELSE, return NOTHING.
        }
        break;

    case DOT:
        dashTimer--;
        if (dashTimer == 0) {
            //once dot_timeout,
            MorseEvent.state = DASH; //switch to DASH.
        } else if (bEvent & BUTTON_EVENT_4UP) {
            //set word countdown.
            wordTimer = MORSE_WORD_TIMEOUT;
            //set letter countdown.
            letterTimer = MORSE_LETTER_TIMEOUT;

            MorseEvent.type = MORSE_EVENT_DOT; //generate DOT event.

            MorseEvent.state = WAITING_FOR_PULSE; //switch to WAITING_FOR_PULSE.
            return MorseEvent;

        } else {
            MorseEvent.type = MORSE_EVENT_NONE;
            return MorseEvent; //ELSE, return NOTHING.
        }

        break;

    case DASH:
        if (bEvent & BUTTON_EVENT_4UP) {
            //set word countdown.
            wordTimer = MORSE_WORD_TIMEOUT;
            //set letter countdown.
            letterTimer = MORSE_LETTER_TIMEOUT;

            MorseEvent.type = MORSE_EVENT_DASH; //generate DASH event.

            MorseEvent.state = WAITING_FOR_PULSE; //switch to WAITING_FOR_PULSE.
            return MorseEvent;

        } else {
            MorseEvent.type = MORSE_EVENT_NONE;
            return MorseEvent; //ELSE, return NOTHING.
        }
        break;

    }
}
