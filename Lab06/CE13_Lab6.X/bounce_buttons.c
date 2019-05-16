// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
static int caseHolder = 0;
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
    printf("Welcome to CRUZID's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);

    if (caseHolder % 2 == 0) { //EVEN amount of switches set ON.
        // BUTTON DOWN should toggle LED registers.

    }
    if (casHolder % 2 == 1) { //ODD number of switches set ON.
        // BUTTON UP should toggle LED registers instead.

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
    uint8_t switchesState = SWITCH_STATES();
    caseHolder = 0; // reset this variable each cycle __ISR call.
    
    if (switchesState & SWITCH_STATE_SW1) {
        //adjust speed of LED blink depending on switch configuration
        //TimerSwitch.timeRemaining -= TICK_CHANGE;
        caseHolder++;
    }
    if (switchesState & SWITCH_STATE_SW2) {
        //adjust speed of LED blink depending on switch configuration
        //TimerSwitch.timeRemaining -= TICK_CHANGE;
        caseHolder++;
    }
    if (switchesState & SWITCH_STATE_SW3) {
        //adjust speed of LED blink depending on switch configuration
        //TimerSwitch.timeRemaining -= TICK_CHANGE;
        caseHolder++;
    }
    if (switchesState & SWITCH_STATE_SW4) {
        //adjust speed of LED blink depending on switch configuration
        //TimerSwitch.timeRemaining -= TICK_CHANGE;
        caseHolder++;
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}