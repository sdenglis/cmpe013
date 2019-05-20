// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
//#include "Oled.h"
#include "Leds.h"
#include "Ascii.h"
#include "Adc.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)

//should be one second, may be equivalent to 5 clock cycles.
#define LONG_PRESS 1

//set default values for OLED display.
#define DEFAULT_TEMP 300
#define DEFAULT_TIME 1

//comparison values for boolean expressions.
#define TRUE  1
#define FALSE 0

//set conversion value for 5HZ __ISR.
#define TICKS_PER_SECOND 5

//define hexadecimal values for sprintf() use.
#define TOP_OVEN_ON      0x01
#define TOP_OVEN_OFF     0x02
#define BOTTOM_OVEN_ON   0x03
#define BOTTOM_OVEN_OFF  0x04

#define DEGREE           0xF8

// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING //total of four states.
} OvenState;

typedef enum {
    BROIL, BAKE, TOAST //only three possible cook modes.
} OvenMode;

typedef enum {
    TEMP, TIME //only two possible choices for the selector.
} OvenSelect;

typedef struct {
    OvenState state; //holds the current state of the FSM [const].
    OvenSelect temperature; //stores temperature value in degrees F [Fahr].
    OvenMode cooking_mode; //which mode: broil, bake, or toast [const].

    OvenState broil_mode; //how many states are there supposed to be???
    OvenState bake_mode; //these might be taken care of by the enum now!?
    OvenState toast_mode;

    OvenState button_press_time; //how long button has been held [ticks->seconds].
    OvenState cooking_initial_time; //user-defined value for cook time [seconds->ticks].
    OvenState cooking_remaining_time; //time remaining.

    OvenState input_selector; //which variable the ADC should affect [const].

    uint8_t event; //allows use of an event flag [bool].

} OvenData;

// **** Declare any datatypes here ****
//OvenData.cooking_mode.BAKE
//OvenData.state.COOKING etc.


// **** Define any module-level, global, or external variables here ****
static OvenState ovenState; //declare module-level instance of OvenState.
static OvenData ovenData; //declare module-level instance of ovenData.

static char printAssist[100]; //used for sprintf() calls.
//is const okay here?

static unsigned int timeStart; //variable used to determine elapsed time.

static unsigned int time_minutes; //used when printing to the OLED display.
static unsigned int time_seconds;

static uint16_t freeRunningCounter; //declare free-running counter for use in FSM.

uint8_t ButtonsEvent; //allows use of an event flag [bool].
uint8_t ADCEvent; //allows use of an event flag [bool].
uint8_t TickEvent; //allows use of an event flag [bool].

// **** Put any helper functions here ****

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData)
{
    OledClear(0); //clear current OLED configuration.

    time_minutes = (ovenData.cooking_remaining_time / 60); //convert cooking_remaining_time to minutes.
    time_seconds = (ovenData.cooking_remaining_time % 60); //convert cooking_remaining_time to seconds.

    if (ovenData.cooking_mode == BAKE) {
        if (ovenData.state == COOKING) {
            switch (ovenData.input_selector) {
            case TIME:
                sprintf(printAssist, "|\x1\x1\x1\x1\x1|   Mode: Bake\n"
                        "|     |  >Time: %d:%d\n"
                        "|-----|   Temp: %d\xF8 F\n"
                        "|\x3\x3\x3\x3\x3|   \n", time_minutes, time_seconds, ovenData.temperature);
                //create a formatted string using the function input.
                break;
            case TEMP:
                sprintf(printAssist, "|\x1\x1\x1\x1\x1|   Mode: Bake\n"
                        "|     |   Time: %d:%d\n"
                        "|-----|  >Temp: %d\xF8 F\n"
                        "|\x3\x3\x3\x3\x3|   \n", time_minutes, time_seconds, ovenData.temperature);
                break;
            default:
                sprintf(printAssist, "FATAL ERROR!");
                break;
            }
        } else {
            switch (ovenData.input_selector) {
            case TIME:
                sprintf(printAssist, "|\x2\x2\x2\x2\x2|   Mode: Bake\n"
                        "|     |  >Time: %d:%d\n"
                        "|-----|   Temp: %d\xF8 F\n"
                        "|\x4\x4\x4\x4\x4|   \n", time_minutes, time_seconds, ovenData.temperature);
                //create a formatted string using the function input.
                break;
            case TEMP:
                sprintf(printAssist, "|\x2\x2\x2\x2\x2|   Mode: Bake\n"
                        "|     |   Time: %d:%d\n"
                        "|-----|  >Temp: %d\xF8 F\n"
                        "|\x4\x4\x4\x4\x4|   \n", time_minutes, time_seconds, ovenData.temperature);
                break;
            default:
                sprintf(printAssist, "FATAL ERROR!");
                break;
            }
        }
    }
    if (ovenData.cooking_mode == BROIL) {
        if (ovenData.state == COOKING) {
            sprintf(printAssist, "|\x1\x1\x1\x1\x1|   Mode: Broil\n"
                    "|     |   Time: %d:%d\n"
                    "|-----|   Temp: 500\xF8 F\n"
                    "|     |   \n", time_minutes, time_seconds);
            //create a formatted string using the function input.
        } else {
            sprintf(printAssist, "|\x2\x2\x2\x2\x2|   Mode: Broil\n"
                    "|     |   Time: %d:%d\n"
                    "|-----|   Temp: 500\xF8 F\n"
                    "|     |   \n", time_minutes, time_seconds);
        }
    }
    if (ovenData.cooking_mode == TOAST) {
        if (ovenData.state == COOKING) {
            sprintf(printAssist, "|     |   Mode: Toast\n"
                    "|     |   Time: %d:%d\n"
                    "|-----|   \n"
                    "|\x1\x1\x1\x1\x1|   \n", time_minutes, time_seconds);
            //create a formatted string using the function input.
        } else {
            sprintf(printAssist, "|     |   Mode: Toast\n"
                    "|     |   Time: %d:%d\n"
                    "|-----|   \n"
                    "|\x4\x4\x4\x4\x4|   \n", time_minutes, time_seconds);
        }
    }
}

OledDrawString(printAssist); //transfer ovenData input to OLED string.
OledUpdate(); //update actual OLED display.

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    //write your SM logic here.

    if (ovenData.event) { //get an event flag, IF TRUE:
        switch (ovenData.state) { //based on OvenData.state.
        case SETUP: //ADC check, BTN_3DOWN check.
            if (ADCEvent) {
                if (ovenData.input_selector == TEMP) {
                    ovenData.temperature = AdcRead() + DEFAULT_TEMP;
                } //additionally, we want to isolate the top 8 bits from the ADC values.
                if (ovenData.input_selector == TIME) {
                    ovenData.cooking_remaining_time = AdcRead() + DEFAULT_TIME;
                }
                //update time/temp.
                //update OLED display.
                updateOvenOLED(ovenData);
            }
            if (ButtonsCheckEvents() == BUTTON_EVENT_3DOWN) {
                //store free-running time.
                //change state to SELECTOR_CHANGE_PENDING.
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }
            if (ButtonsCheckEvents() == BUTTON_EVENT_4DOWN) {
                //store free-running time.
                //update OLED display.
                //change state to COOKING.
                ovenData.cooking_initial_time = ovenData.cooking_remaining_time; //save the initial time.

                ovenData.state = COOKING;
                updateOvenOLED(ovenData);
            }
            break;

        case SELECTOR_CHANGE_PENDING: //BTN_3UP check: if (long_press): next mode.
            if (ButtonsCheckEvents() == BUTTON_EVENT_3UP) {
                if (ovenData.button_press_time < LONG_PRESS) {
                    //switch to next oven mode.
                    switch (ovenData.cooking_mode) {
                    case BAKE:
                        ovenData.cooking_mode = BROIL;
                        ovenData.state = SETUP;
                        updateOvenOLED(ovenData);
                        break;
                    case BROIL:
                        ovenData.cooking_mode = TOAST;
                        ovenData.state = SETUP;
                        updateOvenOLED(ovenData);
                        break;
                    case TOAST:
                        ovenData.cooking_mode = BAKE;
                        ovenData.state = SETUP;
                        updateOvenOLED(ovenData);
                        break;
                    }
                    //update OLED display.
                    //set state to SETUP.
                }
                if (ovenData.button_press_time >= LONG_PRESS) { //else:
                    // change settings selector. 
                    if (ovenData.input_selector == TIME) { //swap the input_selector.
                        ovenData.input_selector = TEMP;

                        ovenData.state = SETUP;
                        updateOvenOLED(ovenData);
                    }
                    if (ovenData.input_selector == TEMP) {
                        ovenData.input_selector = TIME;

                        ovenData.state = SETUP;
                        updateOvenOLED(ovenData);
                    }
                    //update OLED display.
                    //set state to SETUP.
                }
            }
            break;

        case COOKING: //TIMER check, update cook_remaining_time, BTN_4DOWN check.
            if (TickEvent) { //not yet defined!
                //update LED bar countdown.
                ovenData.cooking_remaining_time--;

                updateOvenOLED(ovenData);
                //update OLED display with cook_remaining_time.
                if (ovenData.cooking_remaining_time == 0) {
                    ovenData.state = SETUP;
                    ovenData.cooking_remaining_time = ovenData.cooking_initial_time;
                    updateOvenOLED(ovenData);
                }
            }
            if (ButtonsCheckEvents() == BUTTON_EVENT_4DOWN) {
                //store free-running time.
                //switch state to RESET_PENDING.
                ovenData.state = RESET_PENDING;
            }
            break;

        case RESET_PENDING: //BTN_4UP check to cancel, TIMER check: if (long_press): reset.
            if (TickEvent) {
                if (ButtonsCheckEvents() == BUTTON_EVENT_4UP) {
                    //return to COOKING state.
                    if (ovenData.button_press_time >= LONG_PRESS) {
                        //end cooking.
                        //reset settings.
                        //update OLED display.
                        //go to SETUP state.
                        ovenData.state = SETUP;
                        ovenData.cooking_remaining_time = ovenData.cooking_initial_time;
                        updateOvenOLED(ovenData);
                    }
                    if (ovenData.button_press_time < LONG_PRESS) {
                        ovenData.state = COOKING;
                    }

                } else {
                    //update LED bar countdown still.
                    ovenData.cooking_remaining_time--;
                    updateOvenOLED(ovenData);
                    //update OLED display still.
                    if (ovenData.cooking_remaining_time == 0) {
                        ovenData.state = SETUP;
                        ovenData.cooking_remaining_time = ovenData.cooking_initial_time;
                        updateOvenOLED(ovenData);
                        //reset settings
                        //update OLED display.
                    }
                }
            }
            break;

        }
    }

    //clear all event flags!!!
    //but these won't work down here because of the break statements :( ????
    TickEvent = FALSE;
    ADCEvent = FALSE;
    ButtonsEvent = FALSE;

    ovenData.event = FALSE;

}

int main()
{
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

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

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to sdenglis's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    OledInit(); //initialize the OLED display.
    AdcInit(); //don't forget the ADC!
    ButtonsInit(); //and the buttons!

    ovenData.state = SETUP; //initialize ovenData.state
    ovenData.cooking_mode = BAKE;
    ovenData.temperature = DEFAULT_TEMP;
    ovenData.cooking_remaining_time = DEFAULT_TIME;
    ovenData.input_selector = TEMP;
    updateOvenOLED(ovenData);
    //initialize state machine (and anything else you need to init) here

    while (1) {
        if (ovenData.event) {
            //might need to pass through variables
            runOvenSM();
        }
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags






    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here

    //Sets a TIMER_TICK event flag ? Increment the free-running timer.  
    TickEvent = TRUE; //not setup yet!
    ovenData.event = TRUE;

    freeRunningCounter++;

    //This timer is never reset, but is instead used as a ?global? timer. 
    //This timer is used to determine whether a button press was a long press or a short press, 
    //and is used to determine cooking progress.  
    //This is a useful technique when you need to time multiple events using a single timer (discussed below). 


    //Elapsed Time = current FreeRunning Time ? start Time; 
    //ovenData.button_press_time = freeRunningCounter - ovenData.cooking_initial_time;



}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //add event-checking code here
    //The 100Hz timer should be used exclusively to check for button events and ADC events.  
    //This ensures the system is very responsive to button presses.  
    if (AdcChanged()) {
        //set adc event flag
        ADCEvent = TRUE;
    }
    if (ButtonsCheckEvents() == BUTTON_EVENT_4UP) {
        //set buttons event flag
        ovenData.button_press_time = freeRunningCounter - timeStart; //current counter minus recorded start.
        ovenData.button_press_time /= TICKS_PER_SECOND; //convert the tick value to seconds.
        ButtonsEvent = TRUE;

        ovenData.event = TRUE;
    }
    if (ButtonsCheckEvents() == BUTTON_EVENT_4DOWN) {
        //set buttons event flag
        timeStart = freeRunningCounter;
        ButtonsEvent = TRUE;

        ovenData.event = TRUE;
    }
    if (ButtonsCheckEvents() == BUTTON_EVENT_3UP) {
        //set buttons event flag
        ovenData.button_press_time = freeRunningCounter - timeStart;
        ovenData.button_press_time /= TICKS_PER_SECOND;
        ButtonsEvent = TRUE;

        ovenData.event = TRUE;
    }
    if (ButtonsCheckEvents() == BUTTON_EVENT_3DOWN) {
        //set buttons event flag
        timeStart = freeRunningCounter; //initialize value on the first event.
        ButtonsEvent = TRUE;

        ovenData.event = TRUE;
    }


}