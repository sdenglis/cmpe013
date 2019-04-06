/*
 * File:   part3.c
 * Author: samde
 *
 * Created on April 3, 2019, 5:39 PM
 */

#include "xc.h"
#include "BOARD.h"
#include "Ascii.h"
#include "Oled.h"
#include "OledDriver.h"

// Basically identical to part0.c

int main(void)
{
    BOARD_Init();

    OledInit();
    // Acts as replacement for printf function
    OledDrawString("Hello World! My name is Sam English.\n");
    OledUpdate();

    while (1);
}
