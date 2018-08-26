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
    
}

AgentState AgentGetState(void){
    return Agent_State;
}

void AgentSetState(AgentState newState){
    Agent_State = newState;
    return Agent_State;
}
