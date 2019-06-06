/**
 * Agent.c
 * Author: Austin Dymont
 * Co-Author: Sam English
 * CMPE 13
 * Lab 09
 */

//standard libraries
#include <stdio.h>
#include <stdlib.h>

//user libraries
#include "Field.h"
#include "FieldOled.h"
#include "Message.h"
#include "Agent.h"
#include "Buttons.h"
#include "BattleBoats.h"
#include "Negotiation.h"

//Define constants
#define ODD_VALUE 1
#define NO_BOATS 0


//defined macros
#define setPlayerTurn(value) (((value) & (ODD_VALUE)) ? FIELD_OLED_TURN_MINE : FIELD_OLED_TURN_THEIRS)


//typedef variable

typedef enum {
    END_CONDIDTION_NONE = 0,
    END_CONDITION_ERROR, //Some error occured and you have errored out
    END_CONDIDTION_VICTORY, //You have won the game end condition
    END_CONDIDTION_LOSS //You have lost the game end condition
} EndConditional;

typedef struct {
    //current state of state machine
    AgentState state;

    //message sent out to tranmission
    Message myMessage;

    //My Negotiation Data
    NegotiationData mySecretNumber;
    NegotiationData myHash;

    //Opponents Negotiation Data
    NegotiationData oppSecretNumber;
    NegotiationData oppHash;

    //My guess data
    GuessData guessShot;

    //Opponents guess
    GuessData oppGuess;

    //Turn count and current player's turn
    uint16_t turnCount;
    FieldOledTurn playerTurn;

    //Why end state was reached.
    EndConditional endCondition;

} Agent;

void AgentErrorDisplayUpdate(EndConditional);

static Field myField_var, oppField_var;
static Field *myField, *oppField;
static Agent agent;

void AgentInit(void)
{
    //seed machine 
    char seed1[] = __TIME__;
    //borrowed from BOARD
    unsigned seed2 = (((unsigned) (seed1[0] ^ seed1[9])) << 8) | ((unsigned) (seed1[4] ^ seed1[8]));
    srand(seed2);

    //Init State Machine
    agent.state = AGENT_STATE_START;
    agent.myMessage.type = MESSAGE_NONE;

    //Initialize fields
    myField = &myField_var;
    oppField = &oppField_var;
    FieldInit(myField, oppField);
    FieldAIPlaceAllBoats(myField); 

    //Negotiation data
    agent.mySecretNumber = NULL;
    agent.myHash = NULL;
    agent.oppSecretNumber = NULL;

    //guess data
    agent.guessShot.col = NULL;
    agent.guessShot.row = NULL;
    agent.guessShot.result = NULL;

    //opp guess data
    agent.oppGuess.col = NULL;
    agent.oppGuess.row = NULL;
    agent.oppGuess.result = NULL;

    //turn count
    agent.turnCount = NULL;
    agent.playerTurn = FIELD_OLED_TURN_NONE;

    //clear end state conditional
    agent.endCondition = END_CONDIDTION_NONE;
}

Message AgentRun(BB_Event event)
{
    //Start of State Machine
    switch (agent.state) {
    case AGENT_STATE_START:
        //myself started game
        if (event.type == BB_EVENT_START_BUTTON) {

            //Generate A & #a
            agent.mySecretNumber = rand();
            agent.myHash = NegotiationHash(agent.mySecretNumber);

            //Draw fields
            agent.playerTurn = setPlayerTurn(agent.turnCount);
            FieldOledDrawScreen(myField, oppField, agent.playerTurn, agent.turnCount);

            //Send Challenge message
            agent.myMessage.type = MESSAGE_CHA;
            agent.myMessage.param0 = agent.myHash;

            //move to new state
            agent.state = AGENT_STATE_CHALLENGING;

        }

        //opp started game
        if (event.type == BB_EVENT_CHA_RECEIVED) {
            //save opp #a
            agent.oppHash = event.param0;

            //Generate B
            agent.mySecretNumber = rand();

            //Draw fields
            agent.playerTurn = setPlayerTurn(agent.turnCount);
            FieldOledDrawScreen(myField, oppField, agent.playerTurn, agent.turnCount);

            //Send Acknowledged message
            agent.myMessage.type = MESSAGE_ACC;
            agent.myMessage.param0 = agent.mySecretNumber;

            //move to new state
            agent.state = AGENT_STATE_ACCEPTING;
        }

        //Reset Event: restart game
        if (event.type == BB_EVENT_RESET_BUTTON) {
            AgentInit();
        }

        //ERROR CASE: error event to end screen
        if (event.type == BB_EVENT_ERROR) { // does it go back to the same state??
            agent.state = AGENT_STATE_END_SCREEN; //got to end state. stalled out

            //Send error message to other board;
            agent.myMessage.type = MESSAGE_ERROR;

            //Set end state conditional 
            agent.endCondition = END_CONDITION_ERROR;
        }
        break;
    case AGENT_STATE_CHALLENGING:
        //Acceptance event
        if (event.type == BB_EVENT_ACC_RECEIVED) {
            //Create Reveal message
            agent.myMessage.type = MESSAGE_REV;
            agent.myMessage.param0 = agent.mySecretNumber;

            //save opp's B 
            agent.oppSecretNumber = event.param0;

            switch (NegotiateCoinFlip(agent.mySecretNumber, agent.oppSecretNumber)) {
            case HEADS: //won the flip
                agent.state = AGENT_STATE_WAITING_TO_SEND;
                break;
            case TAILS: //lost the flip
                agent.state = AGENT_STATE_DEFENDING;
                break;
            default: //error case!!
                agent.state = AGENT_STATE_END_SCREEN;
                //update screen

                break;
            }
        }

        //Reset Event: restart game
        if (event.type == BB_EVENT_RESET_BUTTON) {
            AgentInit();
        }

        //ERROR
        if (event.type == BB_EVENT_ERROR) { // does it go back to the same state??
            agent.state = AGENT_STATE_END_SCREEN; //got to end state. stalled out

            //Send error message to other board;
            agent.myMessage.type = MESSAGE_ERROR;

            //Set end state conditional 
            agent.endCondition = END_CONDITION_ERROR;
        }


        break;
    case AGENT_STATE_ACCEPTING:
        if (event.type == BB_EVENT_REV_RECEIVED) {
            //save opp secret Number 'A'
            agent.oppSecretNumber = event.param0;

            //check opp            
            if (NegotiationVerify(agent.oppSecretNumber, agent.oppHash)) {
                //No cheating
                switch (NegotiateCoinFlip(agent.mySecretNumber, agent.oppSecretNumber)) {
                case HEADS: //won the flip
                    //move to attack
                    agent.state = AGENT_STATE_ATTACKING;

                    //make guess shot
                    agent.guessShot = FieldAIDecideGuess(oppField);

                    //Create shot message
                    agent.myMessage.type = MESSAGE_SHO;
                    agent.myMessage.param0 = agent.guessShot.row;
                    agent.myMessage.param1 = agent.guessShot.col;

                    break;
                case TAILS: //lost the flip
                    //move to defend
                    agent.state = AGENT_STATE_DEFENDING;

                    //clear message
                    agent.myMessage.type = MESSAGE_NONE;

                    break;
                default: //error case!!
                    agent.state = AGENT_STATE_END_SCREEN;

                    //update screen

                    break;
                }
            } else {
                //Cheated
                agent.state = AGENT_STATE_END_SCREEN;

                //update screen
            }
        }

        //Reset Event: restart game
        if (event.type == BB_EVENT_RESET_BUTTON) {
            AgentInit();
        }

        //ERROR
        if (event.type == BB_EVENT_ERROR) { // does it go back to the same state??
            agent.state = AGENT_STATE_END_SCREEN; //got to end state. stalled out

            //Send error message to other board;
            agent.myMessage.type = MESSAGE_ERROR;

            //Set end state conditional 
            agent.endCondition = END_CONDITION_ERROR;
        }

        break;
    case AGENT_STATE_ATTACKING:
        if (event.type == BB_EVENT_RES_RECEIVED) {
            agent.guessShot.row = event.param0;
            agent.guessShot.col = event.param1;
            agent.guessShot.result = event.param2;

            //Do I need to use the return value for anything???
            FieldUpdateKnowledge(oppField, &agent.oppGuess);

            if (FieldGetBoatStates(oppField) != NO_BOATS) {
                //Move to Defending
                agent.state = AGENT_STATE_DEFENDING;

                //update oled
                agent.playerTurn = setPlayerTurn(agent.turnCount);
                FieldOledDrawScreen(myField, oppField, agent.playerTurn, agent.turnCount);

                //clear message 
                agent.myMessage.type = MESSAGE_NONE;
            } else {
                //Victory. move to end screen
                agent.state = AGENT_STATE_END_SCREEN;

                //message
                agent.myMessage.type = MESSAGE_NONE;

            }
        }

        //Reset Event: restart game
        if (event.type == BB_EVENT_RESET_BUTTON) {
            AgentInit();
        }

        //ERROR
        if (event.type == BB_EVENT_ERROR) { // does it go back to the same state??
            agent.state = AGENT_STATE_END_SCREEN; //got to end state. stalled out

            //Send error message to other board;
            agent.myMessage.type = MESSAGE_ERROR;

            //Set end state conditional 
            agent.endCondition = END_CONDITION_ERROR;
        }
        break;
    case AGENT_STATE_DEFENDING:
        if (event.type == BB_EVENT_SHO_RECEIVED) {
            //save guess data
            agent.oppGuess.row = event.param0;
            agent.oppGuess.col = event.param1;
            agent.oppGuess.result = event.param2;

            //Register attack and update guess field.
            FieldRegisterEnemyAttack(myField, &agent.oppGuess);

            //Encode Message struct with result of attack
            agent.myMessage.param0 = agent.oppGuess.row;
            agent.myMessage.param1 = agent.oppGuess.col;
            agent.myMessage.param2 = agent.oppGuess.result;

            agent.myMessage.type = MESSAGE_RES;

            if (FieldGetBoatStates(myField)) {
                //Move to waiting to send
                agent.state = AGENT_STATE_WAITING_TO_SEND;

                //update oled
                agent.playerTurn = setPlayerTurn(agent.turnCount);
                FieldOledDrawScreen(myField, oppField, agent.playerTurn, agent.turnCount);

            } else {
                //LOSS. move to end screen
                agent.state = AGENT_STATE_END_SCREEN;

                //message
                agent.myMessage.type = MESSAGE_NONE;

                //update screen
            }
        }

        //Reset Event: restart game
        if (event.type == BB_EVENT_RESET_BUTTON) {
            AgentInit();
        }

        //ERROR
        if (event.type == BB_EVENT_ERROR) { // does it go back to the same state??
            agent.state = AGENT_STATE_END_SCREEN; //got to end state. stalled out

            //Send error message to other board;
            agent.myMessage.type = MESSAGE_ERROR;

            //Set end state conditional 
            agent.endCondition = END_CONDITION_ERROR;
        }
        break;
    case AGENT_STATE_WAITING_TO_SEND:
        if (event.type == BB_EVENT_MESSAGE_SENT) {
            //Increment turn counter
            agent.turnCount++;

            //make guess
            agent.guessShot = FieldAIDecideGuess(oppField);

            //encode message
            agent.myMessage.type = MESSAGE_SHO;
            agent.myMessage.param0 = agent.guessShot.row;
            agent.myMessage.param1 = agent.guessShot.col;

            //switch to attacking
            agent.state = AGENT_STATE_ATTACKING;


        }

        //Reset Event: restart game
        if (event.type == BB_EVENT_RESET_BUTTON) {
            AgentInit();
        }


        //ERROR
        if (event.type == BB_EVENT_ERROR) { // does it go back to the same state??
            agent.state = AGENT_STATE_END_SCREEN; //got to end state. stalled out

            //Send error message to other board;
            agent.myMessage.type = MESSAGE_ERROR;

            //Set end state conditional 
            agent.endCondition = END_CONDITION_ERROR;
        }

        break;
    case AGENT_STATE_END_SCREEN:
        if (agent.endCondition != END_CONDIDTION_NONE) {
            //Update screen with error message
            AgentErrorDisplayUpdate(agent.endCondition);

            //Send error message to other board;
            agent.myMessage.type = MESSAGE_ERROR;
        }

        //Reset Event: restart game
        if (event.type == BB_EVENT_RESET_BUTTON) {
            AgentInit();
        }

        break;
    default: //error case
        agent.state = AGENT_STATE_END_SCREEN; //got to end state. stalled out

        //Update screen with error message
        AgentErrorDisplayUpdate(agent.endCondition);

        //Send error message to other board;
        agent.myMessage.type = MESSAGE_ERROR;

        //Set end state conditional 
        agent.endCondition = END_CONDITION_ERROR;
        //Bad
        break;
    };

    return agent.myMessage;
}

AgentState AgentGetState(void)
{
    return agent.state;
}

void AgentSetState(AgentState newState)
{
    agent.state = newState;
}

void AgentErrorDisplayUpdate(EndConditional endCon)
{
    OledClear(NULL);

    switch (endCon) { //Selects which end title screen to display
    default: //Never should happen, if does probably error.
    case END_CONDITION_ERROR:
        OledDrawString("SHOULDN'T PRINT THIS!");
        break;
    case END_CONDIDTION_VICTORY:
        OledDrawString("YOU WIN!");
        break;
    case END_CONDIDTION_LOSS:
        OledDrawString("YOU LOSE!");
        break;
    }
    OledUpdate();
}