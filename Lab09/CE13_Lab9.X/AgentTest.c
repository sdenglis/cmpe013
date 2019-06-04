/*****************
 *Samuel English *
 *Austin Dymont  *
 *CMPE13/L       *
 *Lab 04         *
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
#include "Agent.h"
#include "Message.h"
#include "BattleBoats.h"
#include "Buttons.h"
#include "Oled.h"


//Some variables for use:
static int points_correct;
static AgentState agent_get;
static AgentState agent_set;

static BB_Event agent_event;
static Message agent_message;

int main()
{
    BOARD_Init();
    ButtonsInit();
    OledInit();
    AgentInit();

    printf("\n\n\n###### Beginning adymont and sdenglis' agent test harness: ######\n\n");

    agent_get = AgentGetState();
    //get current state without initializing.

    printf("Starting get_state value (un-initialized): ");
    switch (agent_get) {
    case 0:
        printf("AGENT_STATE_START\n");
        points_correct++;
        //state of agent_get should default to zero
        //when AgentInit has not yet been called.
        break;
    case 1:
        printf("AGENT_STATE_CHALLENGING ||INVALID||\n");
        break;
    case 2:
        printf("AGENT_STATE_ACCEPTING ||INVALID||\n");
        break;
    case 3:
        printf("AGENT_STATE_ATTACKING ||INVALID||\n");
        break;
    case 4:
        printf("AGENT_STATE_DEFENDING ||INVALID||\n");
        break;
    case 5:
        printf("AGENT_STATE_WAITING_TO_SEND ||INVALID||\n");
        break;
    case 6:
        printf("AGENT_STATE_END_SCREEN ||INVALID||\n");
        break;
    case 7:
        printf("AGENT_STATE_SETUP_BOATS ||HumanAgent.o||\n");
        points_correct++;
        //only set when doing extra credit.
        break;
    }





    //AgentInit();
    //initialize Agent.c functions.
    //defaults to AGENT_STATE_SETUP_BOATS
    //because of HumanAgent.o provided.

    agent_set = AGENT_STATE_START;
    //set current state to AGENT_STATE_START.
    AgentSetState(agent_set);
    agent_get = AgentGetState();
    //double check to ensure that AgentGetState()
    //properly returns values when previously edited with AgentSetState().
    if (agent_get == AGENT_STATE_START) {
        points_correct++;
    }





    printf("\nAgent_message value after AgentRun(BB_EVENT_CHA_RECIEVED): ");
    agent_event.type = BB_EVENT_CHA_RECEIVED;
    agent_message = AgentRun(agent_event);
    //return some value after processing input event.

    switch (agent_message.type) {
    case MESSAGE_ACC:
        printf("\nMESSAGE_ACC\n");
        points_correct++;
        //we should enter this block of code,
        //since CHA_RECIEVED triggers an accept message.
        break;
    case MESSAGE_CHA:
        printf("\nMESSAGE_CHA ||INVALID||\n");
        break;
    case MESSAGE_RES:
        printf("\nMESSAGE_RES ||INVALID||\n");
        break;
    case MESSAGE_REV:
        printf("\nMESSAGE_REV ||INVALID||\n");
        break;
    case MESSAGE_SHO:
        printf("\nMESSAGE_SHO ||INVALID||\n");
        break;
    default: //MESSAGE_NONE:
        printf("\nMESSAGE_NONE ||INVALID||\n");
        break;
    }

    agent_get = AgentGetState();
    //get current state without initializing.

    printf("get_state value (initialized): ");
    switch (agent_get) {
    case 0:
        printf("AGENT_STATE_START ||INVALID||\n");
        break;
    case 1:
        printf("AGENT_STATE_CHALLENGING ||INVALID||\n");
        break;
    case 2:
        printf("AGENT_STATE_ACCEPTING\n");
        points_correct++;
        //state of agent_get should now be ACCEPTING,
        //after AgentRun(MESSAGE_ACC) execution.
        break;
    case 3:
        printf("AGENT_STATE_ATTACKING ||INVALID||\n");
        break;
    case 4:
        printf("AGENT_STATE_DEFENDING ||INVALID||\n");
        break;
    case 5:
        printf("AGENT_STATE_WAITING_TO_SEND ||INVALID||\n");
        break;
    case 6:
        printf("AGENT_STATE_END_SCREEN ||INVALID||\n");
        break;
    case 7:
        printf("AGENT_STATE_SETUP_BOATS ||INVALID||\n");
        break;
    }






    printf("\nAgent_message value after AgentRun(BB_EVENT_REV_RECIEVED): ");
    agent_event.type = BB_EVENT_REV_RECEIVED;
    agent_message = AgentRun(agent_event);

    switch (agent_message.type) {
    case MESSAGE_ACC:
        printf("\nMESSAGE_ACC ||INVALID||\n");
        break;
    case MESSAGE_CHA:
        printf("\nMESSAGE_CHA ||INVALID||\n");
        break;
    case MESSAGE_RES:
        printf("\nMESSAGE_RES ||INVALID||\n");
        break;
    case MESSAGE_REV:
        printf("\nMESSAGE_REV ||INVALID||\n");
        break;
    case MESSAGE_SHO:
        printf("\nMESSAGE_SHO\n");
        points_correct++;
        //as first attacker, we send SHOT.
        break;
    default: //MESSAGE_NONE:
        printf("\nMESSAGE_NONE\n");
        points_correct++;
        //If defending,.
        break;
    }

    agent_get = AgentGetState();
    //get current state without initializing.

    printf("get_state value (initialized): ");
    switch (agent_get) {
    case 0:
        printf("AGENT_STATE_START ||INVALID||\n");
        break;
    case 1:
        printf("AGENT_STATE_CHALLENGING ||INVALID||\n");
        break;
    case 2:
        printf("AGENT_STATE_ACCEPTING ||INVALID||\n");
        break;
    case 3:
        printf("AGENT_STATE_ATTACKING\n");
        points_correct++;
        //could also be attacking,
        //as represented by the random
        //chance of flipping heads versus tails.
        break;
    case 4:
        printf("AGENT_STATE_DEFENDING\n");
        points_correct++;
        //state of agent_get should now be DEFENDING,
        //after AgentRun(MESSAGE_REV) execution.
        //This should be randomized.
        break;
    case 5:
        printf("AGENT_STATE_WAITING_TO_SEND ||INVALID||\n");
        break;
    case 6:
        printf("AGENT_STATE_END_SCREEN ||INVALID||\n");
        break;
    case 7:
        printf("AGENT_STATE_SETUP_BOATS ||INVALID||\n");
        break;
    }


    if (agent_get == AGENT_STATE_ATTACKING) {
        printf("\nAgent_message value after AgentRun(BB_EVENT_RES_RECIEVED): ");
        agent_event.type = BB_EVENT_RES_RECEIVED;
        agent_message = AgentRun(agent_event);
        //return some value after processing input event.

        switch (agent_message.type) {
        case MESSAGE_ACC:
            printf("\nMESSAGE_ACC ||INVALID||\n");
            break;
        case MESSAGE_CHA:
            printf("\nMESSAGE_CHA ||INVALID||\n");
            break;
        case MESSAGE_RES:
            printf("\nMESSAGE_RES ||INVALID||\n");
            break;
        case MESSAGE_REV:
            printf("\nMESSAGE_REV ||INVALID||\n");
            break;
        case MESSAGE_SHO:
            printf("\nMESSAGE_SHO ||INVALID||\n");
            break;
        default: //MESSAGE_NONE:
            printf("\nMESSAGE_NONE\n");
            points_correct++;
            //should return nothing.
            break;
        }

        agent_get = AgentGetState();
        //get current state without initializing.

        printf("get_state value (initialized): ");
        switch (agent_get) {
        case 0:
            printf("AGENT_STATE_START ||INVALID||\n");
            break;
        case 1:
            printf("AGENT_STATE_CHALLENGING ||INVALID||\n");
            break;
        case 2:
            printf("AGENT_STATE_ACCEPTING ||INVALID||\n");
            break;
        case 3:
            printf("AGENT_STATE_ATTACKING ||INVALID||\n");
            break;
        case 4:
            printf("AGENT_STATE_DEFENDING\n");
            points_correct++;
            //should now be in DEFENDING STATE.
            //previously attacked.
            break;
        case 5:
            printf("AGENT_STATE_WAITING_TO_SEND ||INVALID||\n");
            break;
        case 6:
            printf("AGENT_STATE_END_SCREEN ||INVALID||\n");
            break;
        case 7:
            printf("AGENT_STATE_SETUP_BOATS ||INVALID||\n");
            break;
        }





        printf("\nAgent_message value after AgentRun(BB_EVENT_SHO_RECIEVED): ");

        agent_event.type = BB_EVENT_SHO_RECEIVED;
        agent_message = AgentRun(agent_event);

        switch (agent_message.type) {
        case MESSAGE_ACC:
            printf("\nMESSAGE_ACC ||INVALID||\n");
            break;
        case MESSAGE_CHA:
            printf("\nMESSAGE_CHA ||INVALID||\n");
            break;
        case MESSAGE_RES:
            printf("\nMESSAGE_RES\n");
            points_correct++;
            //resolve message.
            break;
        case MESSAGE_REV:
            printf("\nMESSAGE_REV ||INVALID||\n");
            break;
        case MESSAGE_SHO:
            printf("\nMESSAGE_SHO ||INVALID||\n");
            break;
        default: //MESSAGE_NONE:
            printf("\nMESSAGE_NONE ||INVALID||\n");
            break;
        }
        agent_get = AgentGetState();
        //get current state without initializing.

        printf("get_state value (initialized): ");
        switch (agent_get) {
        case 0:
            printf("AGENT_STATE_START ||INVALID||\n");
            break;
        case 1:
            printf("AGENT_STATE_CHALLENGING ||INVALID||\n");
            break;
        case 2:
            printf("AGENT_STATE_ACCEPTING ||INVALID||\n");
            break;
        case 3:
            printf("AGENT_STATE_ATTACKING ||INVALID||\n");
            break;
        case 4:
            printf("AGENT_STATE_DEFENDING ||INVALID||\n");
            break;
        case 5:
            printf("AGENT_STATE_WAITING_TO_SEND\n");
            points_correct++;
            //should be here, after sending res.
            break;
        case 6:
            printf("AGENT_STATE_END_SCREEN ||BOATS NEVER PLACES (HumanAgent.o)||\n");
            points_correct++;
            break;
        case 7:
            printf("AGENT_STATE_SETUP_BOATS ||INVALID||\n");
            break;
        }
    }
    if (agent_get == AGENT_STATE_DEFENDING) {
        printf("\nAgent_message value after AgentRun(BB_EVENT_SHO_RECIEVED): ");
        agent_event.type = BB_EVENT_SHO_RECEIVED;
        agent_message = AgentRun(agent_event);
        //return some value after processing input event.

        switch (agent_message.type) {
        case MESSAGE_ACC:
            printf("\nMESSAGE_ACC ||INVALID||\n");
            break;
        case MESSAGE_CHA:
            printf("\nMESSAGE_CHA ||INVALID||\n");
            break;
        case MESSAGE_RES:
            printf("\nMESSAGE_RES \n");
            points_correct++;
            //should return RESPONSE.
            break;
        case MESSAGE_REV:
            printf("\nMESSAGE_REV ||INVALID||\n");
            break;
        case MESSAGE_SHO:
            printf("\nMESSAGE_SHO ||INVALID||\n");
            break;
        default: //MESSAGE_NONE:
            printf("\nMESSAGE_NONE ||INVALID||\n");
            break;
        }

        agent_get = AgentGetState();
        //get current state without initializing.

        printf("get_state value (initialized): ");
        switch (agent_get) {
        case 0:
            printf("AGENT_STATE_START ||INVALID||\n");
            break;
        case 1:
            printf("AGENT_STATE_CHALLENGING ||INVALID||\n");
            break;
        case 2:
            printf("AGENT_STATE_ACCEPTING ||INVALID||\n");
            break;
        case 3:
            printf("AGENT_STATE_ATTACKING ||INVALID||\n");
            break;
        case 4:
            printf("AGENT_STATE_DEFENDING ||INVALID||\n");
            break;
        case 5:
            printf("AGENT_STATE_WAITING_TO_SEND\n");
            points_correct++;
            //should now be in WAITING STATE.
            //would go to end screen if all boats were dead.
            break;
        case 6:
            printf("AGENT_STATE_END_SCREEN ||BOATS NEVER PLACES (HumanAgent.o)||\n");
            points_correct++;
            break;
        case 7:
            printf("AGENT_STATE_SETUP_BOATS ||INVALID||\n");
            break;
        }


        agent_set = AGENT_STATE_WAITING_TO_SEND;
        AgentSetState(agent_set);


        printf("\nAgent_message value after AgentRun(BB_EVENT_MESSAGE_SENT): ");

        agent_event.type = BB_EVENT_MESSAGE_SENT;
        agent_message = AgentRun(agent_event);

        switch (agent_message.type) {
        case MESSAGE_ACC:
            printf("\nMESSAGE_ACC ||INVALID||\n");
            break;
        case MESSAGE_CHA:
            printf("\nMESSAGE_CHA ||INVALID||\n");
            break;
        case MESSAGE_RES:
            printf("\nMESSAGE_RES ||INVALID||\n");
            break;
        case MESSAGE_REV:
            printf("\nMESSAGE_REV ||INVALID||\n");
            break;
        case MESSAGE_SHO:
            printf("\nMESSAGE_SHO\n");
            points_correct++;
            //shot message.
            break;
        default: //MESSAGE_NONE:
            printf("\nMESSAGE_NONE ||HumanAgent.o||\n");
            points_correct++;
            break;
        }
        agent_get = AgentGetState();
        //get current state without initializing.

        printf("get_state value (initialized): ");
        switch (agent_get) {
        case 0:
            printf("AGENT_STATE_START ||INVALID||\n");
            break;
        case 1:
            printf("AGENT_STATE_CHALLENGING ||INVALID||\n");
            break;
        case 2:
            printf("AGENT_STATE_ACCEPTING ||INVALID||\n");
            break;
        case 3:
            printf("AGENT_STATE_ATTACKING\n");
            points_correct++;
            //should be here, after sending shot.
            break;
        case 4:
            printf("AGENT_STATE_DEFENDING ||INVALID||\n");
            break;
        case 5:
            printf("AGENT_STATE_WAITING_TO_SEND ||HumanAgent.o||\n");
            points_correct++;
            break;
        case 6:
            printf("AGENT_STATE_END_SCREEN ||BOATS NEVER PLACES (HumanAgent.o)||\n");
            points_correct++;
            break;
        case 7:
            printf("AGENT_STATE_SETUP_BOATS ||INVALID||\n");
            break;
        }
    }

    agent_event.type = BB_EVENT_ERROR;
    agent_message = AgentRun(agent_event);
    if (agent_message.type == MESSAGE_ERROR) {
        printf("\nAgentRun(BB_EVENT_ERROR): ERROR SUCCESSFULLY DETECTED!\n");
        points_correct++;
    } else {
        printf("\nAgentRun(BB_EVENT_ERROR): ERROR FLAG FAILED.\n");
    }

    agent_event.type = BB_EVENT_RESET_BUTTON;
    agent_message = AgentRun(agent_event);
    agent_set = AGENT_STATE_START;
    AgentSetState(agent_set);
    agent_get = AgentGetState();

    if (agent_message.type == MESSAGE_NONE && agent_get == AGENT_STATE_START) {
        printf("\nAgentRun(BB_EVENT_RESET_BUTTON): RESET SUCCESSFUL!\n");
        points_correct++;
    } else {
        printf("\nAgentRun(BB_EVENT_RESET_BUTTON): RESET FAILED.\n");
    }



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

    printf("\n\nTotal number of points scored: %d out of 12", points_correct);
    printf("\nNOTE: Oled should display 'SHOULDN'T PRINT THIS!'\n");





    while (1);
    return 0;
}