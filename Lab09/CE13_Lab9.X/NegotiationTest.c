/*****************
 *Samuel English *
 *Austin Dymont  *
 *CMPE13/L       *
 *Lab 09         *
 *5/01/2019      *
 *****************/
// **** Include libraries here ****
//CMPE13 Support Library:
#include "BOARD.h"

//Standard libraries:
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//User libraries:
#include "Negotiation.h"
#include "Agent.h"
#include "Message.h"
#include "BattleBoats.h"
#include "Buttons.h"
#include "Oled.h"


//Some variables for use:
static NegotiationData data_packet;
static NegotiationData data_hash;
static int points_correct;

NegotiationOutcome outcome;

int main()
{
    BOARD_Init();
    ButtonsInit();
    OledInit();
    AgentInit();

    printf("\n\n\n###### Beginning adymont and sdenglis' agent test harness: ######\n\n");

    data_packet = 3;
    data_hash = NegotiationHash(data_packet);
    if (data_hash == 9) {
        printf("NegotiationHash(3) = %d\n", data_hash);
        points_correct++;
    } else {
        printf("NegotiationHash(3) = INVALID!\n");
    }
    if (NegotiationVerify(data_packet, data_hash)) {
        points_correct++;
        printf("NegotiationVerify(data_packet, data_hash) = TRUE\n");
    } else {
        printf("NegotiationVerify(data_packet, data_hash) = FALSE\n");
    }

    data_packet = 12345;
    data_hash = NegotiationHash(data_packet);
    if (data_hash == 43182) {
        printf("NegotiationHash(12345) = %d\n", data_hash);
        points_correct++;
    } else {
        printf("NegotiationHash(12345) = INVALID!\n");
    }
    if (NegotiationVerify(data_packet, data_hash)) {
        points_correct++;
        printf("NegotiationVerify(data_packet, data_hash) = TRUE\n");
    } else {
        printf("NegotiationVerify(data_packet, data_hash) = FALSE\n");
    }

    data_packet = 0;
    data_hash = NegotiationHash(data_packet);
    if (data_hash == 0) {
        printf("NegotiationHash(0) = %d\n", data_hash);
        points_correct++;
    } else {
        printf("NegotiationHash(0) = INVALID!\n");
    }
    if (NegotiationVerify(data_packet, data_hash)) {
        points_correct++;
        printf("NegotiationVerify(data_packet, data_hash) = TRUE\n");
    } else {
        printf("NegotiationVerify(data_packet, data_hash) = FALSE\n");
    }

    data_packet = -3;
    data_hash = NegotiationHash(data_packet);
    if (data_hash == 16270) {
        printf("NegotiationHash(-3) = %d\n", data_hash);
        points_correct++;
    } else {
        printf("NegotiationHash(-3) = INVALID!\n");
    }
    if (NegotiationVerify(data_packet, data_hash)) {
        points_correct++;
        printf("NegotiationVerify(data_packet, data_hash) = TRUE\n");
    } else {
        printf("NegotiationVerify(data_packet, data_hash) = FALSE\n");
    }

    printf("\n");

    NegotiationData A;
    NegotiationData B;

    A = 1;
    B = 2;
    outcome = NegotiateCoinFlip(A, B);
    printf("NegotiateCoinFlip(1, 2);\n");
    if (outcome == HEADS) {
        printf("HEADS! ||INVALID||\n");
    } else { //TAILS
        printf("TAILS!\n");
        points_correct++;
    }

    A = 25;
    B = -1;
    outcome = NegotiateCoinFlip(25, -1);
    printf("NegotiateCoinFlip(25, -1);\n");
    if (outcome == HEADS) {
        printf("HEADS!\n");
        points_correct++;
    } else { //TAILS
        printf("TAILS! ||INVALID||\n");
    }

    A = 0;
    B = 0;
    outcome = NegotiateCoinFlip(A, B);
    printf("NegotiateCoinFlip(0, 0);\n");
    if (outcome == HEADS) {
        printf("HEADS! ||INVALID||\n");
    } else { //TAILS
        printf("TAILS!\n");
        points_correct++;
    }

    A = 0xDEAD;
    B = 0xBEEF;
    outcome = NegotiateCoinFlip(A, B);
    printf("NegotiateCoinFlip(0xDEAD, 0xBEEF);\n");
    if (outcome == HEADS) {
        printf("HEADS! ||INVALID||\n");
    } else { //TAILS
        printf("TAILS!\n");
        points_correct++;
    }

    /******************************************************************************
     * NegotiationData NegotiationHash(NegotiationData secret); - WORKING
     *****************************************************************************/
    /**
     * This function implements a one-way hash.  It maps its input, A, 
     * into an image, #a, in a way that is hard to reverse, but easy 
     * to reproduce.
     * @param secret        //A number that a challenger commits to
     * @return hash         //the hashed value of the secret commitment.
     *
     * This function implements the "Beef Hash," a variant of a Rabin hash.
     * The result is ((the square of the input) modulo the constant key 0xBEEF).
     * So, for example, 
     * 
     * NegotiationHash(3) == 9
     * NegotiationHash(12345) == 42182
     */
    /******************************************************************************
     * int NegotiationVerify(NegotiationData secret, NegotiationData commitment); - WORKING
     *****************************************************************************/
    /**
     * Detect cheating.  An accepting agent will receive both a commitment hash
     * and a secret number from the challenging agent.  This function
     * verifies that the secret and the commitment hash agree, hopefully
     * detecting cheating by the challenging agent.
     *
     * @param secret        //the previously secret number that the challenging agent has revealed
     * @param commitment    //the hash of the secret number
     * @return TRUE if the commitment validates the revealed secret, FALSE otherwise
     */
    /******************************************************************************
     * NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B); - WORKING
     *****************************************************************************/
    /**
     * The coin-flip protocol uses random numbers generated by both
     * agents to determine the outcome of the coin flip.
     *
     * The parity of a bitstring is 1 if there are an odd number of one bits,
     *   and 0 otherwise.
     * So, for example, the number 0b01101011 has 5 ones.  If the parity of
     * A XOR B is 1, then the outcome is HEADS.  Otherwise, the outcome is TAILS.
     */
    /******************************************************************************
     * AgentTest.c Results - OUTPUT
     *****************************************************************************/

    printf("\n\nTotal number of points scored: %d out of 12", points_correct);





    while (1);
    return 0;
}