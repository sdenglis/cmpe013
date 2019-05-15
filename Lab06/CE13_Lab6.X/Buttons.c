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

uint8_t ButtonsCheckEvents(void)
{
    uint8_t buttonsState = BUTTON_STATES();
    int bitMask = 0x00;
    

    if (buttonsState) { // If BUTTON_STATES()
        if (debounceTimer > 0) {

            debounceTimer--; // Decrement debounceTimer only when active.
            printf("don't come in here!");
            return BUTTON_EVENT_NONE;
        }

        if ((buttonsState & BUTTON_STATE_1) && (debounceTimer == 0)) {
            // Buttons 1 is pressed down.
            bitMask |= BUTTON_EVENT_1DOWN;
            debounceTimer = 0;

        }
        if ((buttonsState & BUTTON_STATE_2) && (debounceTimer == 0)) {
            // Buttons 2 is pressed down.
            bitMask |= BUTTON_EVENT_2DOWN;
            debounceTimer = 0;

        }
        if ((buttonsState & BUTTON_STATE_3) && (debounceTimer == 0)) {
            // Buttons 3 is pressed down.
            bitMask |= BUTTON_EVENT_3DOWN;
            debounceTimer = 0;

        }
        if ((buttonsState & BUTTON_STATE_4) && (debounceTimer == 0)) {
            // Buttons 4 is pressed down.
            bitMask |= BUTTON_EVENT_4DOWN;
            debounceTimer = 0;

        } else {
            return bitMask; // Return OR'd combination of button events.
        }
    }
}