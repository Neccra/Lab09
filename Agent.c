// George Leece gleece@ucsc.edu

#include <stdio.h>
#include <xc.h>
#include <stdlib.h>

#include "Agent.h"
#include "Field.h"
#include "Message.h"
#include "Negotiation.h"
#include "FieldOled.h"


Field oppField;
Field ownField;
uint8_t result, row, col, turnCounter, ownBoatStatus, oppBoatStatus, prevSmallLives, prevMediumLives,
        prevLargeLives, prevHugeLives;
BoatDirection direction;
int huge, large, medium, small;
AgentState Agent_State;
AgentState prevState;
NegotiationData A;
NegotiationData B;
NegotiationData hashA;
Message message;
GuessData guess;
SquareStatus squareStatus;
char display[100];
FieldOledTurn turn;

void AgentInit(void){
    FieldInit(&ownField, &oppField);            // Initializes the Fields, places all the boats and sets the state to 
    result = FieldAIPlaceAllBoats(&ownField);   // START and resets the turnCounter to 0
    Agent_State = AGENT_STATE_START;
    turnCounter = 0;
}

Message AgentRun(BB_Event event){
    switch(Agent_State){
    case AGENT_STATE_START:
        if(event.type == BB_EVENT_START_BUTTON){        // If the battleboat event type is  the Start Button being pressed and state is START
            A = rand();                                 // A random number is generated and the hash of that number is calculated
            hashA = NegotiationHash(A);                 // and is loaded into param0 of the message and the message type CHA is loaded into the
            message.type = MESSAGE_CHA;                 // message type. While transitioning into the Challenging state. Updates display and breaks
            message.param0 = hashA;                     // returning the loaded message.
            Agent_State = AGENT_STATE_CHALLENGING;
            FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_NONE, turnCounter);
            
        } else if(event.type == BB_EVENT_CHA_RECEIVED){ // If the battleboat event type is a Challenged received, then a random number is generated
            B = rand();                                 // The random number is loaded in message's parameter 0 and the type is ACCEPTED and the 
            message.type = MESSAGE_ACC;                 // state advances to the ACCEPTING. Updates display and breaks returning the loaded message.
            message.param0 = B;
            Agent_State = AGENT_STATE_ACCEPTING;
            FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_NONE, turnCounter);
        } else {                                        // Displays an error message notifying that the improper battleboat event type was 
            message.type = MESSAGE_NONE;                // received while in the START state causing an error. 
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Start, but not Start Button or CHA Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_CHALLENGING:
        if(event.type == BB_EVENT_ACC_RECEIVED){            // The hash A sent before is revealed by loading the REV into message's type
            message.type = MESSAGE_REV;                     // and the random number A is loaded into parameter 0. If the Coin Flip is revealed
            message.param0 = A;                             // to be heads via parity then the turn is mine, otherwise tails leads to Defending
            if(NegotiateCoinFlip(A, B) == HEADS){           // The field is updated and then breaks out returning the message
                turn = FIELD_OLED_TURN_MINE;
                Agent_State = AGENT_STATE_WAITING_TO_SEND;
            } else {
                Agent_State = AGENT_STATE_DEFENDING;
                turn = FIELD_OLED_TURN_THEIRS;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
        } else if(event.type == BB_EVENT_MESSAGE_SENT){
            message.type = MESSAGE_NONE;
        } else if(event.type == BB_EVENT_RESET_BUTTON){
            message.type = MESSAGE_NONE;
            AgentInit();
        } else {
            message.type = MESSAGE_NONE;                    // Error message when the wrong event type is received while in the Challenging field
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Challenging, but not ACC Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_ACCEPTING:
        if(event.type == BB_EVENT_REV_RECEIVED){            // When the random number of the hash is revealed and the coin flip is determined
            if(NegotiateCoinFlip(A, B) == TAILS){           // If tails, I generate a guess and load the row and col into parameter 0 and 1 
                row = rand();                               // respectively while the type is of SHO. The turn is transferred to the opponents
                col = rand();                               // and the state moves into ATTACKING. If heads then the turn is the opponents and 
                message.type = MESSAGE_SHO;                 // the state becomes Defending. The OLED updates and breaks to return the properly
                guess = FieldAIDecideGuess(&oppField);      // prepared message.
                message.param0 = guess.row;
                message.param1 = guess.col;
                turn = FIELD_OLED_TURN_MINE;
                Agent_State = AGENT_STATE_ATTACKING;
            } else if(NegotiateCoinFlip(A, B) == HEADS){    
                message.type = MESSAGE_NONE;
                turn = FIELD_OLED_TURN_THEIRS;
                Agent_State = AGENT_STATE_DEFENDING;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
//                else if(Cheating)
//                Agent_State = AGENT_STATE_END_SCREEN;
        } else if(event.type == BB_EVENT_RESET_BUTTON){
            message.type = MESSAGE_NONE;
            AgentInit();
        } else {
            turn = FIELD_OLED_TURN_NONE;                    // If the improper battleboat event is received while in the Accepting field,
            message.type = MESSAGE_NONE;                    // then the message display is explains that.
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Accepting, but not REV Received");
            OledDrawString(display);
            OledUpdate();        
        }
        break;
    case AGENT_STATE_WAITING_TO_SEND:
        if(event.type == BB_EVENT_MESSAGE_SENT){                // While in the waiting to send state and the battleboat event is message sent,
            turnCounter++;                                      // the turn counter increments 1, a guess is generated and the row and col,
            guess = FieldAIDecideGuess(&oppField);              // and the are loaded into the message parameter 0 and 1. The message type is 
            message.type = MESSAGE_SHO;                         // SHO to send a shot, the turn is changed and the state is updated to Attacking
            message.param0 = guess.row;                         // The OLED updates and then breaks and returns the message with the loaded 
            message.param1 = guess.col;                         // parametes.
            turn = FIELD_OLED_TURN_MINE;
            Agent_State = AGENT_STATE_ATTACKING;
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
        } else if(event.type == BB_EVENT_RESET_BUTTON){
            message.type = MESSAGE_NONE;
            AgentInit();
        } else {
            message.type = MESSAGE_NONE;                        // If the incorrect event is received while in the waiting to send state an error
            OledClear(OLED_COLOR_BLACK);                        // message is displayed notifying of the state and that an incorrect type was received
            sprintf(display, "Error! In Waiting to Send, but no Message Sent Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_ATTACKING:
        if(event.type == BB_EVENT_RES_RECEIVED){                // While in the attacking state and the battleboat event received is RESULT,
            guess.row = event.param0;                           // the event parameters 0 and 1 are the row and col to be loaded into the guess and
            guess.col = event.param1;                           // the result is in event parameter 2. The message type is NONE, because no message is sent
            guess.result = event.param2;                        // to the opponent. Agent's own field updates with the guess. Then the status of the opponent
            message.type = MESSAGE_NONE;                        // boats and if all are sunk then changes to the end screen otherwise will go to Defending
            squareStatus = FieldUpdateKnowledge(&oppField, &guess); // The OLED updates and then breaks and returns the message which is none.
            if(FieldGetBoatStates(&oppField) == 0){
                turn = FIELD_OLED_TURN_NONE;
                Agent_State = AGENT_STATE_END_SCREEN;
            } else {
                turn = FIELD_OLED_TURN_THEIRS;
                Agent_State = AGENT_STATE_DEFENDING;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
        } else if(event.type == BB_EVENT_MESSAGE_SENT){
            message.type = MESSAGE_NONE;
        } else if(event.type == BB_EVENT_RESET_BUTTON){
            message.type = MESSAGE_NONE;
            AgentInit();
        } else {                                                // If the improper battleboat event is receieved while in the attacking state,
            message.type = MESSAGE_NONE;                        // an appropriate error message is displayed notifying of the state and improper message
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Attacking, but no RES Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_DEFENDING:
        if(event.type == BB_EVENT_SHO_RECEIVED){                // While in the Defending state and the battleboat event SHO is received, then
            guess.row = event.param0;                           // the parameters 0 and 1 are the row and col of the shot received so the guess
            guess.col = event.param1;                           // is loaded with the guess. The shot is registered and the result is loaded into the
            squareStatus = FieldRegisterEnemyAttack(&ownField, &guess); // guess's result. The status of our own boats is evaluated. If the all boats 
            if(FieldGetBoatStates(&ownField) == 0){             // sunk then the state is changed to the end screen for a defeat. If the not then
                message.type = MESSAGE_NONE;                    // the message's type is set to RES and the row, col and result are set to the guess.
                turn = FIELD_OLED_TURN_NONE;                    // The OLED is then updated, breaks out and then returns the message loaded.
                Agent_State = AGENT_STATE_END_SCREEN;
            } else {
                message.type = MESSAGE_RES;
                message.param0 = guess.row;
                message.param1 = guess.col;
                message.param2 = guess.result;
                turn = FIELD_OLED_TURN_MINE;
                Agent_State = AGENT_STATE_WAITING_TO_SEND;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
        } else if(event.type == BB_EVENT_MESSAGE_SENT){
            message.type = MESSAGE_NONE;
        } else if(event.type == BB_EVENT_RESET_BUTTON){
            message.type = MESSAGE_NONE;
            AgentInit();
        } else {
            turn = FIELD_OLED_TURN_NONE;                // If the incorrect battleboat event is received while in the Defending state, then an
            OledClear(OLED_COLOR_BLACK);                // appropriate message is displayed notifying the user.
            sprintf(display, "Error! In Defending, but no SHO Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_END_SCREEN:                        // the status of the boats is called and evaluated to determine who won/lost or a draw.
        ownBoatStatus = FieldGetBoatStates(&ownField);
        oppBoatStatus = FieldGetBoatStates(&oppField);
        if(event.type == BB_EVENT_RESET_BUTTON){
            message.type = MESSAGE_NONE;
            AgentInit();
        } else if(ownBoatStatus == 0 && oppBoatStatus != 0){
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "YOU LOSE!\n PLAY AGAIN?\n Press Button 4 to Replay!\n");
            OledDrawString(display);
            OledUpdate();
        } else if(ownBoatStatus != 0 && oppBoatStatus != 0){
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "YOU WIN!\n PLAY AGAIN?\n Press Button 4 to Replay!\n");
            OledDrawString(display);
            OledUpdate();
        } else {
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "IT'S A DRAW!\n PLAY AGAIN?");
        }
        break;
    }
    return message;
}

AgentState AgentGetState(void){
    return Agent_State;
}

void AgentSetState(AgentState newState){
    Agent_State = newState;
}
