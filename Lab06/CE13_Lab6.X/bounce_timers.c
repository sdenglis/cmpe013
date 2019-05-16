/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 06         *
 *5/15/2019      *
 *****************/

// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "LEDS_Lab06.h"


// **** Declare any datatypes here ****
#define TRUE  1
#define FALSE 0

//* These correspond to the tick-rate of the program (38 ticks/sec) * desired speed
// of each timer. 
// EX: TimerA (an event every two seconds): 38 [ticks/sec] * 2 [sec/event]
// This yields 76 ticks per event. *//
#define TIME_REMAINING_A 76
#define TIME_REMAINING_B 114
#define TIME_REMAINING_C 190

#define TOGGLE_LED1 0x01
#define TOGGLE_LED2 0x02
#define TOGGLE_LED3 0x04

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static struct Timer TimerA; // Define three module-level instances of Timer.
static struct Timer TimerB;
static struct Timer TimerC;

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
    printf("Welcome to sdenglis's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);

    LEDS_INIT(); // Initialize LEDS!

    TimerA.timeRemaining = TIME_REMAINING_A;
    TimerB.timeRemaining = TIME_REMAINING_B;
    TimerC.timeRemaining = TIME_REMAINING_C;
    // Initialize Timer.timeRemaining to respective values.

    static char returnPattern; // Stores hexadecimal output from LEDS_GET().

    while (1) {
        //poll timer A
        if (TimerA.event) {
            //react to timer A events
            printf("A ");

            returnPattern = LEDS_GET(); // Store current LEDS configuration.
            returnPattern ^= TOGGLE_LED1; // XOR with LED1 bit mask to toggle.

            LEDS_SET(returnPattern); // Set LEDS to updated configuration.

            //clear timer A event flag
            TimerA.event = FALSE;
        }
        //poll timer B
        if (TimerB.event) {
            //react to timer B events
            printf("B ");

            returnPattern = LEDS_GET(); // Store current LEDS configuration.
            returnPattern ^= TOGGLE_LED2; // XOR with LED2 bit mask to toggle.

            LEDS_SET(returnPattern); // Set LEDS to updated configuration.

            //clear timer B event flag
            TimerB.event = FALSE;
        }
        //poll timer C
        if (TimerC.event) {
            //react to timer C events
            printf("C ");

            returnPattern = LEDS_GET(); // Store current LEDS configuration.
            returnPattern ^= TOGGLE_LED3; // XOR with LED3 bit mask to toggle.

            LEDS_SET(returnPattern); // Set LEDS to updated configuration.

            //clear timer C event flag
            TimerC.event = FALSE;
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

    //update timerA
    TimerA.timeRemaining--; // Decrement the value member of each Timer by 1.
    TimerB.timeRemaining--;
    TimerC.timeRemaining--;

    //if timerA has counted down,
    if (TimerA.timeRemaining == 0) {
        //generate timerA event
        TimerA.event = TRUE; // If timeRemaining == 0, then set event flag to TRUE.

        //reset timerA to 76 ticks.
        TimerA.timeRemaining = TIME_REMAINING_A;
    }
    if (TimerB.timeRemaining == 0) {
        TimerB.event = TRUE; // If timeRemaining == 0, then set event flag to TRUE.

        //reset timerB to 114 ticks.
        TimerB.timeRemaining = TIME_REMAINING_B;
    }
    if (TimerC.timeRemaining == 0) {
        TimerC.event = TRUE; // If timeRemaining == 0, then set event flag to TRUE.

        //reset timerC to 190 ticks.
        TimerC.timeRemaining = TIME_REMAINING_C;
    }



    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}