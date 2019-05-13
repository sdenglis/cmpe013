
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>



//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

#define LEFT  0x80
#define RIGHT 0x01

#define LEFT_PREVIOUS  -1
#define RIGHT_PREVIOUS  1

#define TRUE  1
#define FALSE 0

// 38 [tick/sec] * 5 [sec/event]
#define TICK_RATE 190
// defined tick amount for switch manipulation
#define TICK_CHANGE 38


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
struct Timer TimerSwitch; // Declare module-level instance of timer.

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
    printf("Welcome to sdenglis's lab6 part2 (bounce_switch).  Compiled on %s %s.\n", __TIME__, __DATE__);

    LEDS_INIT(); // Initialize LEDS!
    TimerSwitch.timeRemaining = TICK_RATE; // Initialize tick count of TimerSwitch to 190.
    char returnPattern; // Stores hexadecimal output from LEDS_GET().
    int previousState = 0; // Tracks the previous state of RIGHT or LEFT.

    LEDS_SET(0x01); // Start by setting pin configuration to 0000 0001.

    while (1) {
        //poll timer events and react if any occur
        if (TimerSwitch.event) {
            returnPattern = LEDS_GET(); // set returnPattern to current LED configuration.

            if (returnPattern == LEFT) { //if reached LEFT END:
                //reverse direction
                previousState = LEFT_PREVIOUS; //keep track of orientation.
                //trigger next LED
                returnPattern >> 1; //shift LED configuration RIGHT 1.

            } else if (returnPattern == RIGHT) { //if reached RIGHT END.
                //reverse direction
                previousState = RIGHT_PREVIOUS; //keep track of orientation.
                //trigger next LED
                returnPattern << 1; //shift LED configuration LEFT 1.


            } else if (previousState == RIGHT_PREVIOUS) {
                // trigger next LED
                returnPattern << 1; //continue shifting LEFT.

            } else if (previousState == LEFT_PREVIOUS) {
                // trigger next LED
                returnPattern >> 1; //continue shifting RIGHT.

            } else {
                return STANDARD_ERROR;
            }

            TimerSwitch.event = FALSE; // Clear TimerSwitch event flag.
        }

    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    TimerSwitch.timeRemaining--; //update TimerSwitch every clock cycle.

    //how to alter the speed of the blinking LED's with the switches?
    T1CONbits.TCKPS = 1; // reset before exiting __ISR

    if (SWITCH_STATES(SW1)) {
        //adjust speed of LED blink depending on switch configuration
        TimerSwitch.timeRemaining -= TICK_CHANGE;
        T1CONbits.TCKPS += 1; // 1:8 prescaler
    }
    if (SWITCH_STATES(SW2)) {
        //adjust speed of LED blink depending on switch configuration
        TimerSwitch.timeRemaining -= TICK_CHANGE;
        T1CONbits.TCKPS += 1; // 1:8 prescaler
    }
    if (SWITCH_STATES(SW3)) {
        //adjust speed of LED blink depending on switch configuration
        TimerSwitch.timeRemaining -= TICK_CHANGE;
        T1CONbits.TCKPS += 1; // 1:8 prescaler
    }
    if (SWITCH_STATES(SW4)) {
        //adjust speed of LED blink depending on switch configuration
        TimerSwitch.timeRemaining -= TICK_CHANGE;
        T1CONbits.TCKPS += 1; // 1:8 prescaler
    }

    if (TimerSwitch.timeRemaining == 0) { //once countdown ends:
        TimerSwitch.event = TRUE; //set TimerSwitch event flag,

        TimerSwitch.timeRemaining = TICK_RATE; //re-initialize TimerSwitch.timeRemaining.
    }




    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}