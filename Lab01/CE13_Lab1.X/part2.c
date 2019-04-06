// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    // Declare Variables
    float fahr, celsius, kelvin;
    int lower, upper, step;

    // Initialize Variables
    lower = 0; // lower limit of temperature
    upper = 300; // upper limit
    step = 20; // step size
    fahr = lower;
    kelvin = lower;

    // Print out column headers
    printf("    F    C\n");

    // Print out table for fahr to celsius conversion
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%7.1f %04.0f\n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }

    // Print out column headers
    printf("    K      F\n");

    // Print out table for kelvin to fahr conversion
    while (kelvin <= upper) {
        fahr = (1.80) * (kelvin - 273.15) + 32.0;
        printf("%03.3f %5f\n", (double) kelvin, (double) fahr);
        kelvin = kelvin + step;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}
