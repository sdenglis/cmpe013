/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 06         *
 *5/15/2019      *
 *****************/

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"
#include "Leds_Lab06.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

static int caseHolder = 0; //keeps track of switch number.
static unsigned int buttonEvents; //tracks the output of ButtonsCheckEvents().
static unsigned int LEDMask = 0x00; //holds the bitmask for LED registers.

#define TOGGLE_LED1 0x01
#define TOGGLE_LED2 0x02
#define TOGGLE_LED3 0x04
#define TOGGLE_LED4 0x08
#define TOGGLE_LED5 0x10
#define TOGGLE_LED6 0x20
#define TOGGLE_LED7 0x40
#define TOGGLE_LED8 0x80

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to sdenglis's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);

    LEDS_INIT(); // Initialize LEDS!

    while (1) {
        if (buttonEvents) {
            if (caseHolder % 2 == 0) { //check if number of flipped switches is EVEN.
                if (buttonEvents == (BUTTON_EVENT_1DOWN)) {
                    LEDMask = LEDS_GET(); // Get current LED configuration
                    LEDMask ^= TOGGLE_LED1; // Toggle LED1 bits
                    LEDMask ^= TOGGLE_LED2; // Toggle LED2 bits
                    LEDS_SET(LEDMask); // Set updated configuration to board.

                    printf("EVENT:   4:---- 3:---- 2:---- 1:DOWN\n");
                    buttonEvents = 0; //reset buttonEvents.
                }
            }

            if (caseHolder % 2 == 1) { //check if number of flipped switches is ODD.
                if (buttonEvents == BUTTON_EVENT_1UP) {
                    LEDMask = LEDS_GET();
                    LEDMask ^= TOGGLE_LED1;
                    LEDMask ^= TOGGLE_LED2;
                    LEDS_SET(LEDMask);

                    printf("EVENT:   4:---- 3:---- 2:---- 1:  UP\n");
                    buttonEvents = 0;
                }
            }

            if (caseHolder % 2 == 0) {
                if (buttonEvents == BUTTON_EVENT_2DOWN) {
                    LEDMask = LEDS_GET();
                    LEDMask ^= TOGGLE_LED3;
                    LEDMask ^= TOGGLE_LED4;
                    LEDS_SET(LEDMask);

                    printf("EVENT:   4:---- 3:---- 2:DOWN 1:----\n");
                    buttonEvents = 0;
                }
            }

            if (caseHolder % 2 == 1) {
                if (buttonEvents == BUTTON_EVENT_2UP) {
                    LEDMask = LEDS_GET();
                    LEDMask ^= TOGGLE_LED3;
                    LEDMask ^= TOGGLE_LED4;
                    LEDS_SET(LEDMask);

                    printf("EVENT:   4:---- 3:---- 2:  UP 1:----\n");
                    buttonEvents = 0;
                }
            }

            if (caseHolder % 2 == 0) {
                if (buttonEvents == BUTTON_EVENT_3DOWN) {
                    LEDMask = LEDS_GET();
                    LEDMask ^= TOGGLE_LED5;
                    LEDMask ^= TOGGLE_LED6;
                    LEDS_SET(LEDMask);

                    printf("EVENT:   4:---- 3:DOWN 2:---- 1:----\n");
                    buttonEvents = 0;
                }
            }

            if (caseHolder % 2 == 1) {
                if (buttonEvents == BUTTON_EVENT_3UP) {
                    LEDMask = LEDS_GET();
                    LEDMask ^= TOGGLE_LED5;
                    LEDMask ^= TOGGLE_LED6;
                    LEDS_SET(LEDMask);

                    printf("EVENT:   4:---- 3:  UP 2:---- 1:----\n");
                    buttonEvents = 0;
                }
            }

            if (caseHolder % 2 == 0) {
                if (buttonEvents == BUTTON_EVENT_4DOWN) {
                    LEDMask = LEDS_GET();
                    LEDMask ^= TOGGLE_LED7;
                    LEDMask ^= TOGGLE_LED8;
                    LEDS_SET(LEDMask);

                    printf("EVENT:   4:DOWN 3:---- 2:---- 1:----\n");
                    buttonEvents = 0;
                }
            }

            if (caseHolder % 2 == 1) {
                if (buttonEvents == BUTTON_EVENT_4UP) {
                    LEDMask = LEDS_GET();
                    LEDMask ^= TOGGLE_LED7;
                    LEDMask ^= TOGGLE_LED8;
                    LEDS_SET(LEDMask);

                    printf("EVENT:   4:  UP 3:---- 2:---- 1:----\n");
                    buttonEvents = 0;
                }
            }

        }
    }




    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    uint8_t switchesState = SWITCH_STATES(); //used to help obtain switch state.
    caseHolder = 0; // reset this variable each cycle __ISR call.

    buttonEvents = ButtonsCheckEvents(); //set buttonEvents equal to current ButtonsCheckEvents().

    if (switchesState & SWITCH_STATE_SW1) {
        //add to module variable which checks if ODD vs EVEN amount of switches enabled.
        caseHolder++;
    }
    if (switchesState & SWITCH_STATE_SW2) {
        //add to module variable which checks if ODD vs EVEN amount of switches enabled.
        caseHolder++;
    }
    if (switchesState & SWITCH_STATE_SW3) {
        //add to module variable which checks if ODD vs EVEN amount of switches enabled.
        caseHolder++;
    }
    if (switchesState & SWITCH_STATE_SW4) {
        //add to module variable which checks if ODD vs EVEN amount of switches enabled.
        caseHolder++;
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}