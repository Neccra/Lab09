// George Leece gleece@ucsc.edu

#include <stdio.h>
#include <xc.h>
#include <stdlib.h>

#include "Agent.h"
#include "Field.h"
#include "Message.h"
#include "Negotiation.h"
#include "FieldOled.h"


Field * oppField;
Field * ownField;
uint8_t result, row, col;
BoatDirection direction;
int huge, large, medium, small;
AgentState Agent_State;

void AgentInit(void){
    FieldInit(ownField, oppField);
    while(huge == FALSE && large == FALSE && medium == FALSE && small == FALSE){
        row = rand() % FIELD_ROWS;
        col = rand() % FIELD_COLS;
        direction = rand() % 2;
        if(huge == FALSE){
            huge = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_HUGE);
        } else if(large == FALSE){
            large = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_LARGE);
        } else if(medium == FALSE){
            medium = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_MEDIUM);
        } else if(small == FALSE){
            small = FieldAddBoat(ownField, row, col, direction, FIELD_BOAT_TYPE_SMALL);
        }
    }
    Agent_State = AGENT_STATE_START;
}

Message AgentRun(BB_Event event){
    // Evaluate event type received.
    if(event.type == BB_EVENT_START_BUTTON){
        Agent_State = AGENT_STATE_START;
    } else if(event.type == BB_EVENT_RESET_BUTTON){
        Agent_State = AGENT_STATE_CHALLENGING;
    } else if (event.type == BB_EVENT_CHA_RECEIVED){
        Agent_State = AGENT_STATE_ACCEPTING;
    } else if(event.type == BB_EVENT_ACC_RECEIVED && event.param0 == HEADS){
        Agent_State = AGENT_STATE_WAITING_TO_SEND;
    } else if(event.type == BB_EVENT_ACC_RECEIVED && event.param0 == TAILS){
        Agent_State = AGENT_STATE_DEFENDING;
    } else if(event.type == BB_EVENT_REV_RECEIVED && event.param0 == TAILS){
        Agent_State = AGENT_STATE_WAITING_TO_SEND;  // Unsure about sending to this state b/c diagram states to go to ATTACKING
    } else if(event.type == BB_EVENT_REV_RECEIVED && event.param0 == HEADS){
        Agent_State = AGENT_STATE_DEFENDING;
    } else if(event.type == BB_EVENT_MESSAGE_SENT){
        Agent_State = AGENT_STATE_ATTACKING;
    } else if(event.type == BB_EVENT_RES_RECEIVED){
        if(victory){
            AgentState = AGENT_STATE_END_SCREEN;
        } else {
            Agent_State = AGENT_STATE_DEFENDING;
        }
    } else if(event.type == BB_EVENT_SHO_RECEIVED){
        if(defeat){
            Agent_State = AGENT_STATE_END_SCREEN;
        } else {
            Agent_State = AGENT_STATE_WAITING_TO_SEND;
        }
    } else if(event.type == BB_EVENT_ERROR){
        Agent_State = AGENT_STATE_END_SCREEN;
    }
    switch(Agent_State){
    case AGENT_STATE_ACCEPTING:
        //
        //
        break;
    case AGENT_STATE_ATTACKING:
        //
        //
        break;
    case AGENT_STATE_CHALLENGING:
        //
        //
        break;
    case AGENT_STATE_DEFENDING:
        //
        //
        break;
    case AGENT_STATE_END_SCREEN:
        //
        //
        break;
    case AGENT_STATE_START:
        //
        //
        break;
    case AGENT_STATE_WAITING_TO_SEND:
        //
        //
        break;
    }
}

AgentState AgentGetState(void){
    return Agent_State;
}

void AgentSetState(AgentState newState){
    Agent_State = newState;
    return Agent_State;
}
