// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

//prototype RunCalculator())
void CalculatorRun(void);

int main(void)
{
    BOARD_Init();
    
    CalculatorRun();

    printf(" CalculatorRun() should not return!\n ");
    while(1);
}

