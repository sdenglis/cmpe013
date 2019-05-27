// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
//------don't include BinaryTree.h or Morse.h!-----
#include "Morse.h"

static int initCheck;
static MorseEvent morseEvent;

//Helper functions:
void OledAddToTopLine(MorseEvent event);
void OledClearTopLine(MorseEvent event);
void OledAddToBottomLine(MorseEvent event);

int main()
{
    BOARD_Init();

    // <editor-fold defaultstate="collapsed" desc="Configure Timer">


    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // </editor-fold>

    printf("\nWelcome to CRUZID's Lab8 Morse decoder!  Compiled on %s %s\n", __DATE__, __TIME__);

    //initialization code
    BOARD_Init();
    OledInit(); //initialize the OLED display.
    initCheck = MorseInit();

    if (initCheck) {

        while (1) {
            //poll for morse events:
            if (morseEvent) {
                //update OLED, if appropriate
                //decode morseEvent
                //update OLED, if appropriate
                //consume morseEvent
            }
        };
    } else {
        OledDrawString("FATAL_ERROR!");
        OledUpdate();

        FATAL_ERROR() //board.h macro.
    }
}

/* Timer2 is used to check for Morse events.
 * 
 * You shouldn't need to modify this ISR!
 */
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    IFS0CLR = 1 << 8;
    morseEvent = MorseCheckEvents();
}

//Helper functions:

void OledAddToTopLine(MorseEvent event)
{
    //when MORSE_DOT || MORSE_DASH
    //print corresponding symbol onto top line.
}

void OledClearTopLine(MorseEvent event)
{
    // when new_letter || new_word || error
    //clear top line.
}

void OledAddToBottomLine(MorseEvent event)
{
    // appends new characters onto the bottom line.
    //when CHAR_DECODED append decoded char to line 2.
    //when NEW_WORD, append space char and then decoded char.
    //when ERROR, append BAD_CHAR char.
}