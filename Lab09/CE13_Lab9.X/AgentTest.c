/*****************
 *Samuel English *
 *Austin Dymont  *
 *CMPE13/L       *
 *Lab 04         *
 *5/01/2019      *
 *****************/

// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Standard libraries:
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// User libraries
#include "Agent.h"
#include "Message.h"
#include "BattleBoats.h"

int main()
{
    BOARD_Init();

    printf("\n\n\n###### Beginning adymont and sdenglis' agent test harness: ######\n\n");


    /******************************************************************************
     * void AgentInit(void); - WORKING
     *****************************************************************************/
    /**
     * The Init() function for an Agent sets up everything necessary for an agent before the game
     * starts.  At a minimum, this requires:
     *      Initializing both fields
     *      Placing boats on your field
     *      Setting the start state of the Agent SM
     * If you are using any other persistent data in Agent SM, that should be reset as well.
     * 
     * The agent can assume that stdlib's rand() function has been seeded properly, so it is not needed
     * to call srand() inside AgentInit().
     *  */


    /******************************************************************************
     * Message AgentRun(BB_Event event); - WORKING
     *****************************************************************************/
    /**
     * AgentRun evolves the Agent state machine in response to an event.
     * 
     * @param  The most recently detected event
     * @return Message, a Message struct to send to the opponent. 
     * 
     * If the returned Message struct is a valid message
     * (that is, not of type MESSAGE_NONE), then it will be
     * passed to the transmission module and sent via UART.
     * This is handled at the top level! AgentRun is ONLY responsible 
     * for generating the Message struct, not for encoding or sending it.
     */


    /******************************************************************************
     * AgentState AgentGetState(void); - WORKING
     *****************************************************************************/
    /** * 
     * @return Returns the current state that AgentGetState is in.  
     * 
     * This function is very useful for testing AgentRun.
     */


    /******************************************************************************
     * void AgentSetState(AgentState newState); - WORKING
     *****************************************************************************/
    /** * 
     * @param Force the agent into the state given by AgentState
     * 
     * This function is very useful for testing AgentRun.
     */


    /******************************************************************************
     * AgentTest.c Results - OUTPUT
     *****************************************************************************/







    while (1);
    return 0;
}