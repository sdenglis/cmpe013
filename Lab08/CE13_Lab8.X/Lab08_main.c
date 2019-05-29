/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 08         *
 *5/28/2019      *
 *****************/
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
//------don't include BinaryTree.h or Morse.h!-----
#include "Morse.h" //??????????????

#include "Oled.h"
#include "OledDriver.h"

#define STRING_LENGTH_MAX 25

static int initCheck;
static int reset;
static MorseEvent morseEvent;

static int i; //holds the array location of our morseCode string.
static char morseCode[STRING_LENGTH_MAX] = "";
static int j; //holds converted/decrypted string array location.
static char morseDecrypt[STRING_LENGTH_MAX] = "";

static char printAssist[100]; //used for sprintf() calls.

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

    printf("\nWelcome to sdenglis's Lab8 Morse decoder!  Compiled on %s %s\n", __DATE__, __TIME__);

    //initialization code
    BOARD_Init();
    OledInit(); //initialize the OLED display.
    initCheck = MorseInit();
    reset = 0;

    if (initCheck) {

        //OledDrawString("Please enter a morse sequence:");
        //OledUpdate();

        while (1) {
            //poll for morse events:
            if (morseEvent.type) {
                if (morseEvent.type == MORSE_EVENT_DOT || morseEvent.type == MORSE_EVENT_DASH) {
                    OledAddToTopLine(morseEvent);
                    morseEvent = MorseDecode(morseEvent);
                    reset = 0;
                }
                if (morseEvent.type == MORSE_EVENT_NEW_LETTER || morseEvent.type == MORSE_EVENT_ERROR) {
                    morseEvent = MorseDecode(morseEvent);
                    OledClearTopLine(morseEvent);
                    OledAddToBottomLine(morseEvent);
                    reset = 0;
                }
                if (morseEvent.type == MORSE_EVENT_NEW_WORD) {
                    OledClearTopLine(morseEvent);
                    OledAddToBottomLine(morseEvent);
                    reset = 1;
                }
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
    if (event.type == MORSE_EVENT_DOT) {

        morseCode[i] = MORSE_CHAR_DOT; //set current location in array to '.'
        i++;

    }
    if (event.type == MORSE_EVENT_DASH) {

        morseCode[i] = MORSE_CHAR_DASH; //set current char to '-'
        i++;
    }
    sprintf(printAssist, "%s \n %s", morseCode, morseDecrypt); //combine the two strings into one printable format.
    OledDrawString(printAssist); //draw string onto OLED display.
    OledUpdate(); //update the display.

    //print corresponding symbol onto top line.
}

void OledClearTopLine(MorseEvent event)
{
    static int x;
    for (x = 0; x < STRING_LENGTH_MAX; x++) { //clear the entire array!
        morseCode[x] = ' ';
    }

    i = 0; //reset i counter outside of function as well.

    // when new_letter || new_word || error
    //clear top line.
}

void OledAddToBottomLine(MorseEvent event)
{
    if (event.type == MORSE_EVENT_CHAR_DECODED) {
        morseDecrypt[j] = event.parameter;
        j++; //update array location!
    }

    if (event.type == MORSE_EVENT_ERROR) {
        morseDecrypt[j] = '#'; //set current char to '#'
        j++;
    }
    if (event.type == MORSE_EVENT_NEW_WORD && reset == 1) {
        morseDecrypt[j] = ' '; //add a space after the new word.
        j++; //update array location!
    }

    reset = 0;
    sprintf(printAssist, "%s \n %s", morseCode, morseDecrypt);
    OledDrawString(printAssist);
    OledUpdate();
    // appends new characters onto the bottom line.
    //when CHAR_DECODED append decoded char to line 2.
    //when NEW_WORD, append space char and then decoded char.
    //when ERROR, append BAD_CHAR char.
}