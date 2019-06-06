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

#define CAT_CHECKSUM 0x4A //Not standard message code
#define CHA_CHECKSUM 0x56 //check sum with ,0,0,0
#define ACC_CHECKSUM 0x5D //"            " ,0,0,0
#define REV_CHECKSUM 0x5D //"            " ,0,0,0
#define SHO_CHECKSUM 0x54 //"            " ,0,0,0
#define RES_CHECKSUM 0x58 //"            " ,0,0,0

//String version of above checksume values
#define CAT_CHECKSUM_STRING "4A" 
#define CHA_CHECKSUM_STRING "56"
#define ACC_CHECKSUM_STRING "5D"
#define REV_CHECKSUM_STRING "5D"
#define SHO_CHECKSUM_STRING "54"
#define RES_CHECKSUM_STRING "58"

//Max lengths of test string
#define LENGTH_OF_ACC_TEST_STRING 10
#define LENGTH_OF_RES_TEST_STRING 14
#define LENGTH_OF_NONE_TEST_STRING 0

//starting index
#define FIRST_INDEX 0
//arbitrary index 
#define MIDDLE_CHAR 3

//tset params
#define PARAM1 1
#define PARAM2 2
#define PARAM3 3


static int passed, tried; //test success vs failed variables

//test variables
static BB_Event message_event_fake;
static BB_Event *message_event;
static Message message_to_encode;


int main()
{
    BOARD_Init();

    printf("Welcome to adymont and sdenglis' Message Test Harness. %s; %s\n", __DATE__, __TIME__);

    //Message_CalculateChecksum tests
    //CAT TEST
    tried++;
    if (Message_CalculateChecksum("CAT,0,0,0") == CAT_CHECKSUM) {
        passed++;
        printf("CAT checksum test: Passed.\n");
    } else {
        printf("CAT checksum test: failed.\n");
    }

    //CHA TEST
    tried++;
    if (Message_CalculateChecksum("CHA,0") == CHA_CHECKSUM) {
        passed++;
        printf("CHA checksum test: Passed.\n");
    } else {
        printf("CHA checksum test: failed.\n");
    }

    //ACC TEST
    tried++;
    if (Message_CalculateChecksum("ACC,0") == ACC_CHECKSUM) {
        passed++;
        printf("ACC checksum test: Passed.\n");
    } else {
        printf("ACC checksum test: failed.\n");
    }

    //REV TEST
    tried++;
    if (Message_CalculateChecksum("REV,0") == REV_CHECKSUM) {
        passed++;
        printf("REV checksum test: Passed.\n");
    } else {
        printf("REV checksum test: failed.\n");
    }

    //SHO TEST
    tried++;
    if (Message_CalculateChecksum("SHO,0,0") == SHO_CHECKSUM) {
        passed++;
        printf("SHO checksum test: Passed.\n");
    } else {
        printf("SHO checksum test: failed.\n");
    }

    //RES TEST
    tried++;
    if (Message_CalculateChecksum("RES,0,0,0") == RES_CHECKSUM) {
        passed++;
        printf("RES checksum test: Passed.\n");
    } else {
        printf("RES checksum test: failed.\n");
    }


    //Message_ParseMessage

    //create dummy variable for message_event
    message_event = &message_event_fake;

    //init message_event
    message_event->type = BB_EVENT_NO_EVENT;
    message_event->param0 = MESSAGE_NONE;
    message_event->param1 = MESSAGE_NONE;
    message_event->param2 = MESSAGE_NONE;
        \
    //CHA TEST
    tried++;
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

    //ACC TEST
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

    //REV TEST
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

    //SHO TEST
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

    //RES TEST
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

    //CAT TEST
    tried++;
    Message_ParseMessage("CAT,0,0,0", CAT_CHECKSUM_STRING, message_event);
    if (message_event->type == BB_EVENT_ERROR) {
        passed++;
        printf("CAT parse message test: Passed.\n");
    } else {
        printf("CAT parse message test: failed.\n");
    }


    //RES TEST W/ WRONG CHECKSUM TEST
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

    //CHECKSUM TOO LONG TEST
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

    //RES TEST WITH WRONG FORMAT
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


    //Message_Encode
    static char test_string[MESSAGE_MAX_PAYLOAD_LEN] = "INITIALIZED_MESSAGE";

    //CHA
    tried++;
    message_to_encode.type = MESSAGE_CHA;
    message_to_encode.param0 = 0;
    message_to_encode.param1 = 0;
    message_to_encode.param2 = 0;

    Message_Encode(test_string, message_to_encode);

    if (strncmp(test_string, "$CHA,0*56\n", MESSAGE_MAX_LEN) == 0) {
        passed++;
        printf("Encode CHA message test: Passed.\n");
    } else {
        printf("Encode CHA message test test: failed.\n");
    }

    //ACC
    tried++;
    message_to_encode.type = MESSAGE_ACC;
    message_to_encode.param0 = 0;
    message_to_encode.param1 = 0;
    message_to_encode.param2 = 0;

    static int testACCLength;
    testACCLength = Message_Encode(test_string, message_to_encode);

    if (strncmp(test_string, "$ACC,0*5D\n", MESSAGE_MAX_LEN) == 0) {
        if (testACCLength == LENGTH_OF_ACC_TEST_STRING) {
            passed++;
            printf("Encode ACC message test: Passed.\n");
        } else {
            printf("Encode ACC message test test: failed.\n");
        }
    } else {
        printf("Encode ACC message test test: failed.\n");
    }

    //RES
    tried++;
    message_to_encode.type = MESSAGE_RES;
    message_to_encode.param0 = 1;
    message_to_encode.param1 = 2;
    message_to_encode.param2 = 3;

    static int testRESLength;
    testRESLength = Message_Encode(test_string, message_to_encode);

    if (strncmp(test_string, "$RES,1,2,3*58\n", MESSAGE_MAX_LEN) == 0) {
        if (testRESLength == LENGTH_OF_RES_TEST_STRING) {
            passed++;
            printf("Encode RES message test: Passed.\n");
        } else {
            printf("Encode RES message test test: failed.\n");
        }
    } else {
        printf("Encode RES message test test: failed.\n");
    }

    //NONE
    tried++;
    message_to_encode.type = MESSAGE_NONE;

    static int testNONELength;
    testNONELength = Message_Encode(test_string, message_to_encode);


    if (testNONELength == LENGTH_OF_NONE_TEST_STRING) {
        passed++;
        printf("Encode NONE message test: Passed.\n");
    } else {
        printf("Encode NONE message test test: failed.\n");
        printf("Note: does not work with _correct.o\n");
    }


    //Message Decode

    //DECODE RES
    tried++;

    static unsigned int truthVariable = SUCCESS; //help determine result of tests

    //init message to be encoded first
    message_to_encode.type = MESSAGE_RES;
    message_to_encode.param0 = PARAM1;
    message_to_encode.param1 = PARAM2;
    message_to_encode.param2 = PARAM3;

    Message_Encode(test_string, message_to_encode); // encode message

    //parse encoded string
    int i = 0;
    for (i = 0; i < LENGTH_OF_RES_TEST_STRING; i++) {
        truthVariable = Message_Decode(test_string[i], message_event);
    }

    //if correct type and all three params: test passed
    if (message_event->type == BB_EVENT_RES_RECEIVED && message_event->param0 == PARAM1 &&
            message_event->param1 == PARAM2 && message_event->param2 == PARAM3) {
        passed++;
        printf("Decode RES message test: Passed.\n");
    } else {
        printf("Decode RES message test test: failed.\n");
    }

    //test2 incomplete decode
    //init message to encode
    message_to_encode.type = MESSAGE_RES;
    message_to_encode.param0 = PARAM1;
    message_to_encode.param1 = PARAM2;
    message_to_encode.param2 = PARAM3;

    Message_Encode(test_string, message_to_encode); //encode message

    //parse into decode, except the last couple
    for (i = 0; i < LENGTH_OF_RES_TEST_STRING - 2; i++) {
        truthVariable = Message_Decode(test_string[i], message_event);
    }

    if (message_event->type == BB_EVENT_NO_EVENT && message_event->param0 == PARAM1 &&
            message_event->param1 == PARAM2 && message_event->param2 == PARAM3) {
        passed++;
        printf("Decode INCOMPLETE message test: Passed.\n");
    } else {
        printf("Decode INCOMPLETE message test: failed.\n");
    }


    //Bad String
    tried++;

    //init message to encode
    message_to_encode.type = MESSAGE_RES;
    message_to_encode.param0 = PARAM1;
    message_to_encode.param1 = PARAM2;
    message_to_encode.param2 = PARAM3;

    Message_Encode(test_string, message_to_encode); //encode message

    test_string[MIDDLE_CHAR] = '\0'; //place NULL char in middle of string

    //parse till STANDARD_ERROR is returned or end of string
    for (i = 0; i < LENGTH_OF_RES_TEST_STRING && (truthVariable == SUCCESS); i++) {
        truthVariable = Message_Decode(test_string[i], message_event);
    }
    if (truthVariable == STANDARD_ERROR) {
        passed++;
        printf("Decode BAD STRING message test: Passed.\n");
    } else {
        printf("Decode BAD STRING message test test: failed.\n");
    }

    //calculate score
    if (tried == passed) {
        printf("All tests attempted were passed!\n");
    } else {
        printf("%d of %d tests passed (%.2f%%)\n", passed, tried,
                ((double) passed / (double) tried) * 100.0);
    }
    while (1);
}

