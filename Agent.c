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
    FieldInit(&ownField, &oppField);
    result = FieldAIPlaceAllBoats(&ownField);
    Agent_State = AGENT_STATE_START;
    turnCounter = 0;
//    FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_NONE, turnCounter);
//    while(huge == FALSE && large == FALSE && medium == FALSE && small == FALSE){
//        row = rand() % FIELD_ROWS;
//        col = rand() % FIELD_COLS;
//        direction = rand() % 2;
//        if(huge == FALSE){
//            huge = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_HUGE);
//        } else if(large == FALSE){
//            large = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_LARGE);
//        } else if(medium == FALSE){
//            medium = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_MEDIUM);
//        } else if(small == FALSE){
//            small = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_SMALL);
//        }
//    }
}

Message AgentRun(BB_Event event){
    // Evaluate event type received.
//    if(event.type == BB_EVENT_RESET_BUTTON){
//        Agent_State = AGENT_STATE_START;
//    } else if(event.type == BB_EVENT_START_BUTTON){
//        Agent_State = AGENT_STATE_CHALLENGING;
//    } else if (event.type == BB_EVENT_CHA_RECEIVED){
//        Agent_State = AGENT_STATE_ACCEPTING;
//    } else if(event.type == BB_EVENT_ACC_RECEIVED && event.param0 == HEADS){
//        Agent_State = AGENT_STATE_WAITING_TO_SEND;
//    } else if(event.type == BB_EVENT_ACC_RECEIVED && event.param0 == TAILS){
//        Agent_State = AGENT_STATE_DEFENDING;
//    } else if(event.type == BB_EVENT_REV_RECEIVED && event.param0 == TAILS){
//        Agent_State = AGENT_STATE_WAITING_TO_SEND;  // Unsure about sending to this state b/c diagram states to go to ATTACKING
//    } else if(event.type == BB_EVENT_REV_RECEIVED && event.param0 == HEADS){
//        Agent_State = AGENT_STATE_DEFENDING;
//    } else if(event.type == BB_EVENT_MESSAGE_SENT){
//        Agent_State = AGENT_STATE_ATTACKING;
//    } else if(event.type == BB_EVENT_RES_RECEIVED){
//        if(victory){
//            AgentState = AGENT_STATE_END_SCREEN;
//        } else {
//            Agent_State = AGENT_STATE_DEFENDING;
//        }
//    } else if(event.type == BB_EVENT_SHO_RECEIVED){
//        if(defeat){
//            Agent_State = AGENT_STATE_END_SCREEN;
//        } else {
//            Agent_State = AGENT_STATE_WAITING_TO_SEND;
//        }
//    } else if(event.type == BB_EVENT_ERROR){
//        Agent_State = AGENT_STATE_END_SCREEN;
//    }
//    prevState = Agent_State;
    switch(Agent_State){
    case AGENT_STATE_START:
        if(event.type == BB_EVENT_START_BUTTON){
            A = rand();
            hashA = NegotiationHash(A);
            message.type = MESSAGE_CHA;
            message.param0 = hashA;
            Agent_State = AGENT_STATE_CHALLENGING;
            FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_NONE, turnCounter);
        } else if(event.type == BB_EVENT_CHA_RECEIVED){
            B = rand();
            message.type = MESSAGE_ACC;
            message.param0 = B;
            Agent_State = AGENT_STATE_ACCEPTING;
            FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_NONE, turnCounter);
        } else {
            message.type = MESSAGE_NONE;
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Start, but not Start Button or CHA Received");
            OledDrawString(display);
            OledUpdate();
        }
        
        break;
    case AGENT_STATE_CHALLENGING:
        if(event.type == BB_EVENT_ACC_RECEIVED){
            message.type = MESSAGE_REV;
            message.param0 = A;
            if(NegotiateCoinFlip(A, B) == HEADS){
                turn = FIELD_OLED_TURN_MINE;
                Agent_State = AGENT_STATE_WAITING_TO_SEND;
            } else {
                Agent_State = AGENT_STATE_DEFENDING;
                turn = FIELD_OLED_TURN_THEIRS;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
        } else {
            message.type = MESSAGE_NONE;
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Challenging, but not ACC Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_ACCEPTING:
        if(event.type == BB_EVENT_REV_RECEIVED){
            if(NegotiateCoinFlip(A, B) == TAILS){
                row = rand();
                col = rand();
                message.type = MESSAGE_SHO;
                guess = FieldAIDecideGuess(&oppField);
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
        } else {
            turn = FIELD_OLED_TURN_NONE;
            message.type = MESSAGE_NONE;
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Accepting, but not REV Received");
            OledDrawString(display);
            OledUpdate();        
        }
        
        break;
    case AGENT_STATE_WAITING_TO_SEND:
        if(event.type == BB_EVENT_MESSAGE_SENT){
            turnCounter++;
            guess = FieldAIDecideGuess(&oppField);
            message.type = MESSAGE_SHO;
            message.param0 = guess.row;
            message.param1 = guess.col;
            turn = FIELD_OLED_TURN_MINE;
            Agent_State = AGENT_STATE_ATTACKING;
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
        } else {
            message.type = MESSAGE_NONE;
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Waiting to Send, but no Message Sent Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_ATTACKING:
        if(event.type == BB_EVENT_RES_RECEIVED){
            guess.row = event.param0;
            guess.col = event.param1;
            guess.result = event.param2;
            message.type = MESSAGE_NONE;
            squareStatus = FieldUpdateKnowledge(&oppField, &guess);
            if(FieldGetBoatStates(&oppField) == 0){
                turn = FIELD_OLED_TURN_NONE;
                Agent_State = AGENT_STATE_END_SCREEN;
            } else {
                turn = FIELD_OLED_TURN_THEIRS;
                Agent_State = AGENT_STATE_DEFENDING;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
        } else {
            message.type = MESSAGE_NONE;
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Attacking, but no RES Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_DEFENDING:
        if(event.type == BB_EVENT_SHO_RECEIVED){
//            prevSmallLives = Field.smallBoatLives;
//            prevMediumLives = Field.mediumBoatLives;
//            prevLargeLives = Field.largeBoatLives;
//            prevHugeLives = Field.hugeBoatLives;
            squareStatus = FieldRegisterEnemyAttack(&ownField, &guess);
            if(FieldGetBoatStates(&ownField) == 0){
                message.type = MESSAGE_NONE;
                turn = FIELD_OLED_TURN_NONE;
                Agent_State = AGENT_STATE_END_SCREEN;
            } else {
                message.type = MESSAGE_RES;
                message.param0 = event.param0;
                message.param1 = event.param1;
                message.param2 = guess.result;
                turn = FIELD_OLED_TURN_MINE;
                Agent_State = AGENT_STATE_WAITING_TO_SEND;
            }
            FieldOledDrawScreen(&ownField, &oppField, turn, turnCounter);
//            if(squareStatus == FIELD_SQUARE_MISS){
//                guess.result = RESULT_MISS;
//                message.param0 = event.param0;
//                message.param1 = event.param1;
//                message.param2 = guess.result
//            } else if(squareStatus == FIELD_SQUARE_HIT){
//                message.param0 = event.param0;
//                message.param1 = event.param1;
//                message.param2 = guess.result;
//                if(FieldGetBoatStates(ownField) == 0){
//                    Agent_State = AGENT_STATE_END_SCREEN;
//                } else if(Field.smallBoatLives == 0 && prevSmallLives != Field.smallBoatLives){
//                    guess.result = RESULT_SMALL_BOAT_SUNK;
//                } else if(Field.mediumBoatLives == 0 && prevMediumLives != Field.mediumBoatLives){
//                    guess.result = RESULT_MEDIUM_BOAT_SUNK;
//                } else if(Field.largeBoatLives == 0 && prevLargeLives != Field.largeBoatLives){
//                    guess.result = RESULT_LARGE_BOAT_SUNK;
//                } else if(Field.hugeBoatLives == 0 && prevHugeLives != Field.hugeBoatLives){
//                    guess.result = RESULT_HUGE_BOAT_SUNK;
//                } else {
//                    guess.result = RESULT_HIT;
//                }
//            }
        } else {
            turn = FIELD_OLED_TURN_NONE;
            OledClear(OLED_COLOR_BLACK);
            sprintf(display, "Error! In Defending, but no SHO Received");
            OledDrawString(display);
            OledUpdate();
        }
        break;
    case AGENT_STATE_END_SCREEN:
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
