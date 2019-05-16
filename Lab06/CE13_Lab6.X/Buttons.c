// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "LEDS_Lab06.h"

// **** Declare any datatypes here ****
#define TRUE 1
#define FALSE 0

/**
 * This function initializes the proper pins such that the buttons 1-4 may be used by modifying
 * the necessary bits in TRISD/TRISF. Only the bits necessary to enable the 1-4 buttons are
 * modified, so that this library does not interfere with other libraries.
 */
void ButtonsInit(void)
{
    TRISD |= 0x00E0;
    TRISF |= 0x0002;

}

/**
 * ButtonsCheckEvents function checks the current button states and returns
 *  any events that have occured since its last
 * call.  This function should be called repeatedly in a Timer ISR, though it can
 * be called in main() during testing.
 *
 * In normal use, this function should only be used after ButtonsInit().
 * 
 * This function should assume that the buttons start in an off state with 
 * value 0. Therefore if no buttons are
 * pressed when ButtonsCheckEvents() is first called, 
 * BUTTONS_EVENT_NONE should be returned. 
 * 
 * @return  Each bit of the return value corresponds to one ButtonEvent flag,
 *          as described in Buttons.h.  If no events are detected, BUTTONS_EVENT_NONE is returned.
 * 
 * Note that more than one event can occur simultaneously, though this situation is rare.
 * To handle this, the output should be a bitwise OR of all applicable event flags. 
 * For example, if button 1 was released at the same time that button 2 was pressed,
 * this function should return (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN) 
 * 
 */
unsigned int debounceTimer = 0;
static int previousState = 0;
static int previousState1 = 0;
static int previousState2 = 0;
static int previousState3 = 0;
static int previousState4 = 0;

uint8_t ButtonsCheckEvents(void)
{
    uint8_t buttonsState = BUTTON_STATES();
    int bitMask = 0x00;

    if (debounceTimer > 0) {
        debounceTimer--; // Decrement debounceTimer only when active.
        return BUTTON_EVENT_NONE;
    }

    if (buttonsState != previousState) {
        if (buttonsState != previousState1) {
            if ((buttonsState & BUTTON_STATE_1) && previousState1 == 0) {
                // Buttons 1 is pressed down.

                bitMask |= BUTTON_EVENT_1DOWN;
                debounceTimer = 0;
                previousState1 = BUTTON_EVENT_1DOWN; // previous is now equal to current.
                previousState = BUTTON_EVENT_1DOWN;

            }
            if (!(buttonsState & BUTTON_STATE_1) && (previousState1 == BUTTON_EVENT_1DOWN)) {
                bitMask |= BUTTON_EVENT_1UP;
                debounceTimer = 0;
                previousState1 = 0;
                previousState = 0;

            }
        }
        if (buttonsState != previousState2) {
            if ((buttonsState & BUTTON_STATE_2) && previousState2 == 0) {
                // Buttons 1 is pressed down.

                bitMask |= BUTTON_EVENT_2DOWN;
                debounceTimer = 0;
                previousState2 = BUTTON_EVENT_2DOWN; // previous is now equal to current.
                previousState = BUTTON_EVENT_2DOWN;

            }
            if (!(buttonsState & BUTTON_STATE_2) && (previousState2 == BUTTON_EVENT_2DOWN)) {
                bitMask |= BUTTON_EVENT_2UP;
                debounceTimer = 0;
                previousState2 = 0;
                previousState = 0;

            }
        }
        if (buttonsState != previousState3) {
            if ((buttonsState & BUTTON_STATE_3) && previousState3 == 0) {
                // Buttons 1 is pressed down.

                bitMask |= BUTTON_EVENT_3DOWN;
                debounceTimer = 0;
                previousState3 = BUTTON_EVENT_3DOWN; // previous is now equal to current.
                previousState = BUTTON_EVENT_3DOWN;

            }
            if (!(buttonsState & BUTTON_STATE_3) && (previousState3 == BUTTON_EVENT_3DOWN)) {
                bitMask |= BUTTON_EVENT_3UP;
                debounceTimer = 0;
                previousState3 = 0;
                previousState = 0;

            }
        }
        if (buttonsState != previousState4) {
            if ((buttonsState & BUTTON_STATE_4) && previousState4 == 0) {
                // Buttons 1 is pressed down.

                bitMask |= BUTTON_EVENT_4DOWN;
                debounceTimer = 0;
                previousState4 = BUTTON_EVENT_4DOWN; // previous is now equal to current.
                previousState = BUTTON_EVENT_4DOWN;

            }
            if (!(buttonsState & BUTTON_STATE_4) && (previousState4 == BUTTON_EVENT_4DOWN)) {
                bitMask |= BUTTON_EVENT_4UP;
                debounceTimer = 0;
                previousState4 = 0;
                previousState = 0;
            }
        }


        //previousState = buttonsState; // previous is now equal to current.
        return bitMask; // Return OR'd combination of button events.
    }
    //previousState = buttonsState; // previous is now equal to current.
    return BUTTON_EVENT_NONE; // Return OR'd combination of button events.

}