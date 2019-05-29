// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Oled.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
//------don't include BinaryTree.h or Morse.h!-----
#include "Morse.h"

static MorseEvent morseEvent;
static int initCheck;

static int points;

int main()
{
    BOARD_Init();
    OledInit(); //initialize the OLED display.


    printf("\n\nWelcome to sdenglis's Lab8 Morse.h tester!  Compiled on %s %s\n\n", __DATE__, __TIME__);

    printf("Beginning automatic portion of Morse.h tester:\n");
    //test MorseInit()
    initCheck = MorseInit();
    if (initCheck) {
        printf("Initialization was a success!\n");
        points++;

    } else {
        printf("Initialization ERROR.\n");
    }
    //test MorseDecode()
    morseEvent.type = MORSE_EVENT_DOT;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DOT;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DOT;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_NEW_LETTER;
    morseEvent = MorseDecode(morseEvent);
    printf("we made it, here's the decoded char: %c\n", morseEvent.parameter);
    if (morseEvent.parameter == 'S') { // 'S' == "..."
        points++;
    }

    morseEvent.type = MORSE_EVENT_DASH;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DASH;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DASH;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_NEW_LETTER;
    morseEvent = MorseDecode(morseEvent);
    printf("and the next: %c\n", morseEvent.parameter);
    if (morseEvent.parameter == 'O') { // 'O' == "---"
        points++;
    }

    morseEvent.type = MORSE_EVENT_DOT;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DOT;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DOT;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_NEW_LETTER;
    morseEvent = MorseDecode(morseEvent);
    printf("and lastly: %c\n", morseEvent.parameter);
    if (morseEvent.parameter == 'S') { // 'S' == "..."
        points++;
    }

    morseEvent.type = MORSE_EVENT_DASH;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DASH;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DASH;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_DASH;
    MorseDecode(morseEvent);
    morseEvent.type = MORSE_EVENT_NEW_LETTER;
    morseEvent = MorseDecode(morseEvent);
    printf("this should be invalid: %c\n", morseEvent.parameter);
    if (morseEvent.parameter == '#') { // '#' == "invalid sequence!"
        points++;
    }
    printf("passed %d out of 5 tests!\n", points);


    printf("\nBeginning interactive portion of Morse.h tester:\n");
    printf("Press BTN4 please!\n");

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

    while (1) {
        if (morseEvent.type) {
            if (morseEvent.type == MORSE_EVENT_DOT) {
                printf(".");
                morseEvent = MorseDecode(morseEvent);
            }
            if (morseEvent.type == MORSE_EVENT_DASH) {
                printf("-");
                morseEvent = MorseDecode(morseEvent);
            }
            //poll for MorseEvents and print them when detected
        }
    };
}

/* Timer2 is used to check for Morse events.
 * 
 * You shouldn't need to modify this ISR!
 */
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    morseEvent = MorseCheckEvents();
}
