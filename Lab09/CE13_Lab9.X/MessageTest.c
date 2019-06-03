/*
 * MessageTest.c
 * Author: Austin Dymont
 * Co-author: Sam English
 * Date: June 1, 2019
 * CMPE13
 */

// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>


#include "Message.h"

#define CAT_CHECKSUM 0x4A
#define CHA_CHECKSUM 0x56
#define ACC_CHECKSUM 0x5D
#define REV_CHECKSUM 0x5D
#define SHO_CHECKSUM 0x54
#define RES_CHECKSUM 0x58

#define CAT_CHECKSUM_STRING "4A"
#define CHA_CHECKSUM_STRING "56"
#define ACC_CHECKSUM_STRING "5D"
#define REV_CHECKSUM_STRING "5D"
#define SHO_CHECKSUM_STRING "54"
#define RES_CHECKSUM_STRING "58"



static int passed, tried;
static BB_Event *message_event;
static Message message_to_encode;

int main()
{
    BOARD_Init();
    
    printf("Welcome to adymont and sdenglis' Message Test Harness. %s; %s\n", __DATE__, __TIME__);

    //Message_CalculateChecksum tests
    tried++;
    if (Message_CalculateChecksum("CAT,0,0,0") == CAT_CHECKSUM) {
        passed++;
        printf("CAT checksum test: Passed.\n");
    } else {
        printf("CAT checksum test: failed.\n");
    }

    tried++;
    if (Message_CalculateChecksum("CHA,0") == CHA_CHECKSUM) {
        passed++;
        printf("CHA checksum test: Passed.\n");
    } else {
        printf("CHA checksum test: failed.\n");
    }

    tried++;
    if (Message_CalculateChecksum("ACC,0") == ACC_CHECKSUM) {
        passed++;
        printf("ACC checksum test: Passed.\n");
    } else {
        printf("ACC checksum test: failed.\n");
    }

    tried++;
    if (Message_CalculateChecksum("REV,0") == REV_CHECKSUM) {
        passed++;
        printf("REV checksum test: Passed.\n");
    } else {
        printf("REV checksum test: failed.\n");
    }

    tried++;
    if (Message_CalculateChecksum("SHO,0,0") == SHO_CHECKSUM) {
        passed++;
        printf("SHO checksum test: Passed.\n");
    } else {
        printf("SHO checksum test: failed.\n");
    }

    tried++;
    if (Message_CalculateChecksum("RES,0,0,0") == RES_CHECKSUM) {
        passed++;
        printf("RES checksum test: Passed.\n");
    } else {
        printf("RES checksum test: failed.\n");
    }


    //Message_ParseMessage

    //create dummy variable for message_event
    message_event = malloc(sizeof (BB_Event));

    message_event->type = BB_EVENT_NO_EVENT;
    message_event->param0 = MESSAGE_NONE;
    message_event->param1 = MESSAGE_NONE;
    message_event->param2 = MESSAGE_NONE;

    tried++;

    //    int temp = Message_ParseMessage("CHA,0", CHA_CHECKSUM_STRING, message_event);
    //    printf("%d, %d\n", temp, message_event->type);

    if (Message_ParseMessage("CHA,0", CHA_CHECKSUM_STRING, message_event)) {
        if (message_event->type == BB_EVENT_CHA_RECEIVED) {
            passed++;
            printf("CHA parse message test: Passed.\n");
        } else {
            printf("CHA parse message test: failed.\n");
        }
    } else {
        printf("CHA parse message test: failed.\n");
    }

    tried++;

    if (Message_ParseMessage("ACC,0", ACC_CHECKSUM_STRING, message_event)) {
        if (message_event->type == BB_EVENT_ACC_RECEIVED) {
            passed++;
            printf("ACC parse message test: Passed.\n");
        } else {
            printf("ACC parse message test: failed.\n");
        }
    } else {
        printf("ACC parse message test: failed.\n");
    }

    tried++;

    if (Message_ParseMessage("REV,0", REV_CHECKSUM_STRING, message_event)) {
        if (message_event->type == BB_EVENT_REV_RECEIVED) {
            passed++;
            printf("REV parse message test: Passed.\n");
        } else {
            printf("REV parse message test: failed.\n");
        }
    } else {
        printf("REV parse message test: failed.\n");
    }

    tried++;

    if (Message_ParseMessage("SHO,0,0", SHO_CHECKSUM_STRING, message_event)) {
        if (message_event->type == BB_EVENT_SHO_RECEIVED) {
            passed++;
            printf("SHO parse message test: Passed.\n");
        } else {
            printf("SHO parse message test: failed.\n");
        }
    } else {
        printf("SHO parse message test: failed.\n");
    }

    tried++;

    if (Message_ParseMessage("RES,0,0,0", RES_CHECKSUM_STRING, message_event)) {
        if (message_event->type == BB_EVENT_RES_RECEIVED) {
            passed++;
            printf("RES parse message test: Passed.\n");
        } else {
            printf("RES parse message test: failed.\n");
        }
    } else {
        printf("RES parse message test: failed.\n");
    }

    tried++;

    Message_ParseMessage("CAT,0,0,0", CAT_CHECKSUM_STRING, message_event);
    if (message_event->type == BB_EVENT_ERROR) {
        passed++;
        printf("CAT parse message test: Passed.\n");
    } else {
        printf("CAT parse message test: failed.\n");
    }


    tried++;

    if (Message_ParseMessage("RES,0,0,0", CAT_CHECKSUM_STRING, message_event) == STANDARD_ERROR) {
        if (message_event->type == BB_EVENT_ERROR) {
            passed++;
            printf("Wrong checksum, parse message test: Passed.\n");
        } else {
            printf("Wrong checksum, parse message test: failed.\n");
        }
    } else {
        printf("Wrong checksum, parse message test: failed.\n");
    }

    tried++;
    char *resCheckSum = "WRONG_CHECK_SUM";

    if (Message_ParseMessage("RES,0,0,0", resCheckSum, message_event) == STANDARD_ERROR) {
        if (message_event->type == BB_EVENT_ERROR) {
            passed++;
            printf("Check sum too long test: Passed.\n");
        } else {
            printf("Check sum too long test: failed.\n");
        }
    } else {
        printf("Check sum too long test: failed.\n");
    }

    tried++;
    resCheckSum = RES_CHECKSUM_STRING;

    if (Message_ParseMessage("RES,0,0", resCheckSum, message_event) == STANDARD_ERROR) {
        if (message_event->type == BB_EVENT_ERROR) {
            passed++;
            printf("Wrong format parse message test: Passed.\n");
        } else {
            printf("Wrong format parse message test: failed.\n");
        }
    } else {
        printf("Wrong format parse message test: failed.\n");
    }

    free(message_event);

    //Message_Encode
    static char test_string[MESSAGE_MAX_PAYLOAD_LEN] = "INITIALIZED_MESSAGE";

    
    message_to_encode.type = MESSAGE_CHA;
    message_to_encode.param0 = 0; 
    message_to_encode.param1 = 0;
    message_to_encode.param2 = 0;

//    printf("%p, %p, %d", test_string, &message_to_encode, message_to_encode.type);
    Message_Encode(test_string, message_to_encode);   
    
    if (strncmp(test_string, "$CHA,0*56\n", MESSAGE_MAX_LEN) == 0) {
        passed++;
        printf("Encode CHA message test: Passed.\n");
    } else {
        printf("Encode CHA message test test: failed.\n");
    }



    if (tried == passed) {
        printf("All tests attempted were passed!\n");
    } else {
        printf("%d of %d tests passed (%.2f%%)\n", passed, tried,
                ((double) passed / (double) tried) * 100.0);
    }
    while (1);
}

