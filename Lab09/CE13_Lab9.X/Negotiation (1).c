// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

#include "Negotiation.h"


/*squares the value passed to*/
#define square(value) ((value) * (value))

/*Bits Mask for first bit*/
#define FIRST_BIT 0b1
#define ODD_VALUE 0b1
#define BITS_16 16
#define EMPTY 0

NegotiationData NegotiationHash(NegotiationData secret)
{
    uint32_t tempHolder = square(secret); //square value
    
    NegotiationData myHashValue = ((tempHolder) % (PUBLIC_KEY)); //take modulus with public key
    return myHashValue;
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment)
{
    if (NegotiationHash(secret) == commitment) {
        return TRUE;
    } else {
        return FALSE;
    }
}

NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B)
{
    static NegotiationData parity;
    parity = (A ^ B); //First holds bitstring

    static int i; //index variable
    unsigned numberOfOnes = 0; //counter for number of 1's in bitstring

    //Shift through all of parity's bitstring and check if LSB is 1, increase numberOfOnes
    for (i = 0; i < BITS_16 && (parity != EMPTY); i++, (parity >>= 1)) {
        if (parity & FIRST_BIT) {
            numberOfOnes++;
        }
    }

    //Determine if numberOfOnes is even or odd.
    parity = (numberOfOnes & ODD_VALUE) ? 1 : 0; //now holds final parity value

    if (parity == 1) {
        return HEADS;
    } else {
        return TAILS;
    }
}

/*EC*/
NegotiationData NegotiateGenerateBGivenHash(NegotiationData hash_a)
{
    return NULL;
}

NegotiationData NegotiateGenerateAGivenB(NegotiationData B)
{
    return NULL;
}
