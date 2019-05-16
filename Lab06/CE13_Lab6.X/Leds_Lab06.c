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
#define TRUE 1
#define FALSE 0

/**
 * LEDS_INIT() initializes the LED bar by doing two things:
 *      1) Use the appropriate SFRs to set each LED pin to "output" mode.
 *      2) Use the appropriate SFRs to set each LED pin's output value to 0 (low voltage).
 * 
 * After calling LEDS_INIT(), the other functions in this file can be used to manipulate the LED bar.
 */
void LEDS_INIT(void)
{
    // Set all pins to Output mode:
    TRISE = 0x00; // 0000 0000
    // Set all pin values to low voltage:
    LATE = 0x00; // 0000 0000

}

/**
 * LEDS_SET() controls the output on the LED bar.  Input values are 8-bit patterns, where each bit 
 * describes the desired state of the corresponding LED.  So, for example, LEDS_SET(0x80) should 
 * leave the first LED on, and the last 7 LEDs off.  LEDS_SET(0x1F) should turn off the first three
 * LEDs and turn on the remaining five LEDs.
 * 
 * @param newPattern:  An 8-bit value describing the desired output on the LED bar.  
 * 
 * LEDS_SET should not change any LED pins to inputs.
 */
void LEDS_SET(char newPattern)
{
    // No need to use TRISE for changing output to input.

    // Convert char newPattern to hexadecimal integer???

    // Set voltage value registers accordingly.
    LATE = newPattern;

}

/**
 * LEDS_GET() returns the current state of the LED bar.  Return values are 8-bit patterns,
 * where each bit describes the current state of the corresponding LED So, for example, if the 
 * led bar's led's are [ON OFF ON OFF   OFF ON OFF ON], LEDS_GET() should return 0xA5.
 * 
 * @return char:  An 8-bit value describing the current output on the LED bar.  
 * 
 * LEDS_GET() should not change the state of the LEDS, or any SFRs.
 */
char LEDS_GET(void)
{
    static char returnPattern;

    // Convert LATE current state from binary int to hexadecimal char???

    returnPattern = LATE;
    return returnPattern;
}
