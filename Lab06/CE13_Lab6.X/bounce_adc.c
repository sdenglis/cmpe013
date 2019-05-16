/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 06         *
 *5/15/2019      *
 *****************/

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Leds_Lab06.h"
#include "Oled.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries


// **** Set macros and preprocessor directives ****
#define WINDOW_SIZE 3 //per lab manual's suggestion.

#define TRUE  1
#define FALSE 0

// defined tick amount for switch manipulation
#define TICK_CHANGE 38

/*****************
 *     NOTE      *
 *****************/
// My board was strange, and the voltage capped at around 1150 mV.
// I ignored this, and pretended that the cap was 1023, assuming
// that whoever uses this code has a properly-functioning machine.

#define POTENTIOMETER_MAX 1023.0

// **** Declare any data-types here ****

struct AdcResult {
    uint8_t event;
    int16_t voltage;
};


// **** Define global, module-level, or external variables here ****
static struct AdcResult AdcResult; //declare module-level instance of AdcResult.

static struct AdcResult Average; //variable to store average of 8 buffered ADC values.
static struct AdcResult Previous; //variable to store previous AdcAverage value.

static double AdcPercentage = 0; //variable to hold percentage value of AdcAverage.
static char holder[100]; //used to store formatted sprintf() string

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Enable interrupts for the ADC
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

    // Set B2 to an input so AN2 can be used by the ADC.
    TRISBbits.TRISB2 = 1;

    // Configure and start the ADC
    AD1CHSbits.CH0SA = 2; // add B2 to the mux
    AD1PCFGbits.PCFG2 = 0; // add b2 to the ADC
    AD1CSSLbits.CSSL2 = 1; // and add b2 to the scanner

    AD1CON1 = 0; // start with 0
    AD1CON1bits.SSRC = 0b111; // auto conversion
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0; // start with 0
    AD1CON2bits.SMPI = 7; // one interrupt per 8 samples

    AD1CON3 = 0; // start with 0
    AD1CON3bits.SAMC = 29; // long sample time
    AD1CON3bits.ADCS = 50; // long conversion time

    AD1CON1bits.ADON = 1; // and finally turn it on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to sdenglis's lab6 part3 (bounce_adc).  Compiled on %s %s.\n", __TIME__, __DATE__);
    AdcResult.voltage = WINDOW_SIZE;
    Previous.voltage = 0; // initialize
    OledInit();

    while (1) {
        if (AdcResult.event) {
            OledClear(0);
            //printf("Potentiometer value:\n %d mV\n %6.2f%%", Average.voltage, AdcPercentage);
            sprintf(holder, "Potentiometer value:\n %d mV\n %3.0f%%", Average.voltage, AdcPercentage);
            OledDrawString(holder);
            OledUpdate();

            AdcResult.event = FALSE;
        }
    }





    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the ADC1 peripheral. It will trigger whenever a new ADC reading is available
 * in the ADC buffer SFRs, ADC1BUF0 - ADC1BUF7.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_ADC_VECTOR, ipl2auto) AdcHandler(void)
{
    // Clear the interrupt flag.
    IFS1bits.AD1IF = 0;

    Average.voltage = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8;

    //takes all 8 potentiometer readings and obtains their average.
    AdcPercentage = (Average.voltage / POTENTIOMETER_MAX) * 100;

    //what about when AdcAverage == 0 || POTENTIOMETER_MAX???

    if (abs(Average.voltage - Previous.voltage) > WINDOW_SIZE) {
        Previous.voltage = Average.voltage; //now, update AdcPrevious at the end of AdcHandler().

        AdcResult.event = TRUE;
    }
    if (Average.voltage == 0) {
        //if Average.voltage ever equals 0, create a new event to update the screen to zero as well.
        Previous.voltage = 5;
    }
    if (Average.voltage == 1023) {
        //if Average.voltage ever equals MAX, create a new event to update the screen to MAX as well.
        Previous.voltage = 1018;
    }

}