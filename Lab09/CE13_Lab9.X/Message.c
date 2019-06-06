/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 09         *
 *6/01/2019      *
 *****************/
// Standard libraries:
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User libraries:
#include "BattleBoats.h"
#include "Field.h"
#include "Message.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

/******************************************************************************
 * MESSAGE - Preprocessor / Definitions / Variables
 *****************************************************************************/

#define STANDARD_ERROR 0
#define SUCCESS 1



#define ZERO_ASCII '0'
#define NINE_ASCII '9'
#define A_ASCII 'A'
#define F_ASCII 'F'

#define CHECKSUM_MAX_LENGTH 2
#define CHECKSUM_STRING_LENGTH 2
#define HEX_BASE 16
#define DEC_BASE 10

#define CHA_DELIMITER 1
#define ACC_DELIMITER 1
#define REV_DELIMITER 1
#define SHO_DELIMITER 2
#define RES_DELIMITER 3

typedef enum {
    WAITING_FOR_DELIMITER, //states for message module state machine.
    RECORDING_PAYLOAD,
    RECORDING_CHECKSUM,
} MessageState;

static MessageState messageState = WAITING_FOR_DELIMITER;
//declare a MessageState variable for use in FSM.
//This should be initialized to WAITING_FOR_DELIMITER.

static unsigned int payloadLength; //used to track the length of each payload.
static char payload_string[MESSAGE_MAX_PAYLOAD_LEN];
static unsigned int checksumLength; //used to track the length of checksum.
static char checksum_string[MESSAGE_CHECKSUM_LEN];

static int error_check; //used to store return value of parse function.

/******************************************************************************
 * MESSAGE - Calculate Checksum
 *****************************************************************************/

/**
 * Given a payload string, calculate its checksum
 * 
 * @param payload       //the string whose checksum we wish to calculate
 * @return   //The resulting 8-bit checksum 
 */

uint8_t Message_CalculateChecksum(const char* payload)
{
    static uint8_t checksum;
    checksum = 0;
    //initialize to zero when entering function.
    static int i; //some arbitrary counter for XOR process.



    for (i = 0; i < strlen(payload); i++) { //iterate through payload string,
        checksum ^= payload[i]; //store XOR result in checksum uint8_t variable.
    }
    return checksum; //resulting 8-bit checksum.
}


/******************************************************************************
 * MESSAGE - Parse Message
 *****************************************************************************/

/**
 * Given a payload and its checksum, verify that the payload matches the checksum
 * 
 * @param payload       //the payload of a message
 * @param checksum      //the checksum (in string form) of  a message,
 *                          should be exactly 2 chars long, plus a null char
 * @param message_event //An event corresponding to the parsed message.
 *                      //If the message could be parsed successfully,
 *                          message_event's type will correspond to the message type and 
 *                          its parameters will match the message's data fields.
 *                      //If the message could not be parsed,
 *                          message_events type will be BB_EVENT_ERROR
 * 
 * @return STANDARD_ERROR if:
 *              the payload does not match the checksum
 *              the checksum string is not two characters long
 *              the message does not match any message template
 *          SUCCESS otherwise
 * 
 * Please note!  sscanf() has a couple compiler bugs that make it a very
 * unreliable tool for implementing this function. * 
 */

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event)
{
    static char string_duplicate[MESSAGE_MAX_LEN];
    static char checksum_duplicate[MESSAGE_MAX_LEN];
    static uint8_t checksum_verify;
    static uint8_t checksum_converted;
    static char *token;
    static char token_string[MESSAGE_MAX_LEN];
    static char param_0[MESSAGE_MAX_LEN];
    static unsigned int param0;
    static char param_1[MESSAGE_MAX_LEN];
    static unsigned int param1;
    static char param_2[MESSAGE_MAX_LEN];
    static unsigned int param2;
    static unsigned int format_check;
    static char *convert;
    static char *terminator = "\0";

    format_check = 0;

    //printf("%s\n", payload);
    strcpy(string_duplicate, payload); //don't edit the constant char!
    //strcat(string_duplicate, terminator);
    strcpy(checksum_duplicate, checksum_string);
    //printf("%s\n", string_duplicate);

    checksum_verify = Message_CalculateChecksum(payload); //calculate checksum for ourselves.
    //printf("%X\n", checksum_verify);
    checksum_converted = strtol(checksum_duplicate, &convert, HEX_BASE); //convert hexadecimal value to a string.
    //printf("%X\n", checksum_converted);

    if (strlen(checksum_string) != CHECKSUM_STRING_LENGTH) { //if checksum length not two characters long:
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR; //checksum string is not two characters long.
    }

    if (checksum_verify == checksum_converted) { //check against the received checksum value.
        //parse the message.
        token = strtok(string_duplicate, ","); //get MESSAGE ID, stored in *token.
        sprintf(token_string, "%s", token);

        if (strcmp(token_string, "CHA") == 0) { // CHALLENGE message:
            token = strtok(NULL, ",");
            sprintf(param_0, "%s", token);
            format_check++;

            if (format_check == CHA_DELIMITER) { //one for ID, one for single comma.

                param0 = strtoul(param_0, NULL, DEC_BASE); //convert parameter string to unsigned integer.
                message_event->param0 = param0; //store unsigned integer value inside message_event.
                message_event->type = BB_EVENT_CHA_RECEIVED;

                return SUCCESS;
            } else {
                message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR; //invalid string formatting!
            }
        }
        if (strcmp(token_string, "ACC") == 0) { // ACCEPT message:	 
            token = strtok(NULL, ",");
            sprintf(param_0, "%s", token);

            format_check++;
            if (format_check == ACC_DELIMITER) { //one for ID, one for single comma.
                param0 = strtoul(param_0, NULL, DEC_BASE);
                message_event->param0 = param0;
                message_event->type = BB_EVENT_ACC_RECEIVED;
                return SUCCESS;
            } else {
                message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR; //invalid string formatting!

            }
        }
        if (strcmp(token_string, "REV") == 0) { // REVEAL message: 	
            token = strtok(NULL, ",");
            sprintf(param_0, "%s", token);
            format_check++;

            if (format_check == REV_DELIMITER) { //one for ID, one for single comma.
                param0 = strtoul(param_0, NULL, DEC_BASE);
                message_event->param0 = param0;
                message_event->type = BB_EVENT_REV_RECEIVED;
                return SUCCESS;
            } else {
                message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR; //invalid string formatting!
            }
        }
        if (strcmp(token_string, "SHO") == 0) { // SHOT (guess) message: 

            token = strtok(NULL, ","); //get the first parameter.
            sprintf(param_0, "%s", token);
            format_check++;

            token = strtok(NULL, ",");
            sprintf(param_1, "%s", token);
            format_check++;

            if (format_check == SHO_DELIMITER) { //one for ID, one for first and last comma.
                param0 = strtoul(param_0, NULL, DEC_BASE);
                message_event->param0 = param0;
                param1 = strtoul(param_1, NULL, DEC_BASE);
                message_event->param1 = param1;
                message_event->type = BB_EVENT_SHO_RECEIVED;
                return SUCCESS;
            } else {
                message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR; //invalid string formatting!
            }
        }
        if (strcmp(token_string, "RES") == 0) { // RESULT message: 

            token = strtok(NULL, ","); //get the first parameter.
            sprintf(param_0, "%s", token);
            format_check++;

            token = strtok(NULL, ","); //get the second parameter.
            sprintf(param_1, "%s", token);
            format_check++;

            token = strtok(NULL, ",");
            sprintf(param_2, "%s", token);
            format_check++;

            if (format_check == RES_DELIMITER) { //one for ID, first comma, next and last comma.
                param0 = strtoul(param_0, NULL, DEC_BASE);
                message_event->param0 = param0;
                param1 = strtoul(param_1, NULL, DEC_BASE);
                message_event->param1 = param1;
                param2 = strtoul(param_2, NULL, DEC_BASE);
                message_event->param2 = param2;
                message_event->type = BB_EVENT_RES_RECEIVED;
                return SUCCESS;
            } else {
                message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR; //invalid string formatting!
            }
        } else { //invalid MESSAGE ID!
            message_event->type = BB_EVENT_ERROR;
            return STANDARD_ERROR;
        }

    } else { //something has gone awry!
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR; //payload does not match checksum.
    }
}



/******************************************************************************
 * MESSAGE - Encode Message
 *****************************************************************************/

/**
 * Encodes the coordinate data for a guess into the string `message`. This string must be big
 * enough to contain all of the necessary data. The format is specified in PAYLOAD_TEMPLATE_COO,
 * which is then wrapped within the message as defined by MESSAGE_TEMPLATE. 
 * 
 * The final length of this
 * message is then returned. There is no failure mode for this function as there is no checking
 * for NULL pointers.
 * 
 * @param message            The character array used for storing the output. 
 *                              Must be long enough to store the entire string,
 *                              see MESSAGE_MAX_LEN.
 * @param message_to_encode  A message to encode
 * @return                   The length of the string stored into 'message_string'.
                             Return 0 if message type is MESSAGE_NONE.
 */

int Message_Encode(char *message_string, Message message_to_encode)
{
    static char payload_string[MESSAGE_MAX_LEN];
    static uint8_t checksum_value;

    switch (message_to_encode.type) {
    case MESSAGE_CHA:
        sprintf(payload_string, "CHA,%u", message_to_encode.param0); //store payload string.
        checksum_value = Message_CalculateChecksum(payload_string); //obtain checksum hex value.
        sprintf(message_string, "$%s*%02X\n", payload_string, checksum_value); //store final message string.
        break;
    case MESSAGE_ACC:
        sprintf(payload_string, "ACC,%u", message_to_encode.param0);
        checksum_value = Message_CalculateChecksum(payload_string);
        sprintf(message_string, "$%s*%02X\n", payload_string, checksum_value);
        break;
    case MESSAGE_REV:
        sprintf(payload_string, "REV,%u", message_to_encode.param0);
        checksum_value = Message_CalculateChecksum(payload_string);
        sprintf(message_string, "$%s*%02X\n", payload_string, checksum_value);
        break;
    case MESSAGE_SHO:
        sprintf(payload_string, "SHO,%u,%u", message_to_encode.param0, message_to_encode.param1); //is this meant to be %d identifier???? "SHO,%d,%d"
        checksum_value = Message_CalculateChecksum(payload_string);
        sprintf(message_string, "$%s*%02X\n", payload_string, checksum_value);
        break;
    case MESSAGE_RES:
        sprintf(payload_string, "RES,%u,%u,%u", message_to_encode.param0, message_to_encode.param1, message_to_encode.param2);
        checksum_value = Message_CalculateChecksum(payload_string);
        sprintf(message_string, "$%s*%02X\n", payload_string, checksum_value);
        break;
    default: //MESSAGE_ERROR || MESSAGE_NONE:
        return 0; //completely exit.
    }

    return strlen(message_string); //return length of string stored.

}



/******************************************************************************
 * MESSAGE - Decode Message
 *****************************************************************************/

/**
 * Message_Decode reads one character at a time.  If it detects a full NMEA message,
 * it translates that message into a BB_Event struct, which can be passed to other 
 * services.
 * 
 * @param char_in - The next character in the NMEA0183 message to be decoded.
 * @param decoded_message - a pointer to a message struct, used to "return" a message
 *                          if char_in is the last character of a valid message, 
 *                              then decoded_message
 *                              should have the appropriate message type.
 *                              otherwise, it should have type NO_EVENT.
 * @return SUCCESS if no error was detected
 *         STANDARD_ERROR if an error was detected
 * 
 * note that ANY call to Message_Decode may modify decoded_message.
 */

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event)
{
    //should I reset the checksum and message_strings every time? at end? not at all?

    switch (messageState) {
    case WAITING_FOR_DELIMITER: //initialize to this state.
        if (char_in == '$') {
            messageState = RECORDING_PAYLOAD; //switch state to RECORDING_PAYLOAD.
            decoded_message_event->type = BB_EVENT_NO_EVENT;
        } else {
            decoded_message_event->type = BB_EVENT_NO_EVENT;
            return STANDARD_ERROR;
        }
        break;
    case RECORDING_PAYLOAD:
        if (char_in == '$' || char_in == '\n' || payloadLength > MESSAGE_MAX_PAYLOAD_LEN) { //if unexpected delimiter || max_length exceeded.
            //return ERROR stuff.
            decoded_message_event->type = BB_EVENT_NO_EVENT;
            return STANDARD_ERROR;
        }
        if (char_in == '*') { //checksum delimiter
            messageState = RECORDING_CHECKSUM; //switch state to RECORDING_CHECKSUM.
            decoded_message_event->type = BB_EVENT_NO_EVENT;
        } else { //if any other character as input:
            //record the character.
            payload_string[payloadLength] = char_in; //set current array location in payload to char_in.
            payloadLength++; //for every character decoded, length++;
            decoded_message_event->type = BB_EVENT_NO_EVENT;
        }
        break;
    case RECORDING_CHECKSUM:
        if (checksumLength > CHECKSUM_MAX_LENGTH) { //if checksum length exceeds maximum value.
            //return ERROR stuff.
            decoded_message_event->type = BB_EVENT_NO_EVENT;
            return STANDARD_ERROR;
        }
        if ((char_in >= ZERO_ASCII && char_in <= NINE_ASCII) || (char_in >= A_ASCII && char_in <= F_ASCII)) { //check if in bounds of hexadecimal character.
            //record the character.
            checksum_string[checksumLength] = char_in; //set current array location in checksum to char_in.
            checksumLength++;
        }
        if (char_in == '\n') {
            //parse payload.
            //parse checksum.
            error_check = Message_ParseMessage(payload_string, checksum_string, decoded_message_event); //call parse function.
            if (error_check == STANDARD_ERROR) {
                //ERROR DETECTED!
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                return STANDARD_ERROR;
            } else {
                //decoded_message_event should be updated from the function call.

                messageState = WAITING_FOR_DELIMITER; //refresh FSM, back to starting state.
            }
        } else {
            //any other character,
            //return ERROR stuff.
            decoded_message_event->type = BB_EVENT_NO_EVENT;
            return STANDARD_ERROR;
        }
        break;
    default: //default if other cases don't trigger.
        decoded_message_event->type = BB_EVENT_NO_EVENT;
        return STANDARD_ERROR;
    }
    return SUCCESS; //NO ERROR detected.
}
