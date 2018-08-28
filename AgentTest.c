/*
 * File:   AgentTest.c
 * Author: liaoh
 *
 * Created on August 27, 2018, 1:37 PM
 */
#include "Field.h"
#include "Agent.h"
#include "xc.h"
#include "BOARD.h"
#include <stdio.h>

Field oppField;
Field ownField;
AgentState agentState;
uint8_t small;
BB_Event battleBoatEvent;
Message battleBoatMessage;

int main(void) {
    BOARD_Init();
    printf("\nAgent Test Harness, compiled on %s %s\n\n", __DATE__, __TIME__);
    AgentInit();
    small = FieldAddBoat(&ownField, 2, 2, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    if(small == TRUE){
        printf("\nSUCCESS\n");
    } else {
        printf("\nFAILED\n");
    }
    FieldPrint_UART(&ownField, &oppField);
    
    printf("\n\nTESTING BB_EVENT_START_BUTTON\n");
    battleBoatEvent.type = BB_EVENT_START_BUTTON;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_CHA){
        printf("\nSUCCESS! %x", battleBoatMessage.param0);
    } else {
        printf("\nFAILED!");
    }
    if(AgentGetState() == AGENT_STATE_CHALLENGING){
        printf("\nSUCCESS! In Proper State! %d", AgentGetState());
    } else {
        printf("\nFAILED! In Wrong State! %d", AgentGetState());
    }
    
    printf("\n\nTESTING BB_EVENT_START_BUTTON (EXPECTED FAILURE)\n");
    battleBoatEvent.type = BB_EVENT_CHA_RECEIVED;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_ACC){
        printf("\nSUCCESS! In Proper State! %d", battleBoatMessage.param0);
    } else {
        printf("\nFAILED!");
    }
    if(AgentGetState() == AGENT_STATE_ACCEPTING){
        printf("\nSUCCESS! In Proper State! %d", AgentGetState());
    } else {
        printf("\nFAILED! In Wrong State! %d", AgentGetState());
    }
    
    printf("\n\nTESTING BB_EVENT_CHA_RECEIVED\n");
    AgentSetState(AGENT_STATE_START);
    battleBoatEvent.type = BB_EVENT_CHA_RECEIVED;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_ACC){
        printf("\nSUCCESS! In Proper State! %d", battleBoatMessage.param0);
    } else {
        printf("\nFAILED!");
    }
    if(AgentGetState() == AGENT_STATE_ACCEPTING){
        printf("\nSUCCESS! In Proper State! %d", AgentGetState());
    } else {
        printf("\nFAILED! In Wrong State! %d", AgentGetState());
    }
    
    printf("\n\nTESTING BB_EVENT_ACC_RECEIVED\n");
    AgentSetState(AGENT_STATE_CHALLENGING);
    battleBoatEvent.type = BB_EVENT_ACC_RECEIVED;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_REV){
        printf("\nSUCCESS! In Proper State! %d", battleBoatMessage.param0);
    } else {
        printf("\nFAILED!");
    }
    if(AgentGetState() == AGENT_STATE_WAITING_TO_SEND) {
        printf("\nSUCCESS! Coin Flip resulted in HEADS! In Proper State! %d", AgentGetState());
    } else if(AgentGetState() == AGENT_STATE_DEFENDING){
        printf("\nSUCCESS! Coin Flip resulted in TAILS! In Proper State! %d", AgentGetState());
    } else {
        printf("\nFAILED! In Wrong State! %d", AgentGetState());
    }
    
    printf("\n\nTESTING BB_EVENT_REV_RECEIVED\n");
    AgentSetState(AGENT_STATE_ACCEPTING);
    battleBoatEvent.type = BB_EVENT_REV_RECEIVED;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_SHO && agentState == AGENT_STATE_ATTACKING){
        printf("\nSUCCESS! In Proper State! %d, %d", battleBoatMessage.param0, battleBoatMessage.param1);
    } else {
        printf("\nFAILED!");
    }
    if(AgentGetState() == AGENT_STATE_ATTACKING) {
        printf("\nSUCCESS! Coin Flip resulted in TAILS! In Proper State! %d", AgentGetState());
    } else if(AgentGetState() == AGENT_STATE_DEFENDING){
        printf("\nSUCCESS! Coin Flip resulted in HEADS! In Proper State! %d", AgentGetState());
    } else {
        printf("\nFAILED! In Wrong State! %d", AgentGetState());
    }
     
    printf("\n\nTESTING BB_EVENT_MESSAGE_SENT\n");
    AgentSetState(AGENT_STATE_WAITING_TO_SEND);
    battleBoatEvent.type = BB_EVENT_MESSAGE_SENT;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_SHO){
        printf("\nSUCCESS! In Proper State! %d, %d", battleBoatMessage.param0, battleBoatMessage.param1);
    } else {
        printf("\nFAILED!");
    }
    if(AgentGetState() == AGENT_STATE_ATTACKING) {
        printf("\nSUCCESS! In Proper State! %d", AgentGetState());
    } else {
        printf("\nFAILED! In Wrong State! %d", AgentGetState());
    }
    
    printf("\n\nTESTING BB_EVENT_RES_RECEIVED\n");
    AgentSetState(AGENT_STATE_ATTACKING);
    battleBoatEvent.type = BB_EVENT_RES_RECEIVED;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_NONE){
        printf("\nSUCCESS! In Proper State!");
    } else {
        printf("\nFAILED!");
    }
    if(AgentGetState() == AGENT_STATE_DEFENDING) {
        printf("\nSUCCESS! In Proper State! %d", AgentGetState());
    } else {
        printf("\nFAILED! In Wrong State! %d", AgentGetState());
    }
    
    printf("\n\nTESTING BB_EVENT_SHO_RECEIVED\n");
    AgentSetState(AGENT_STATE_DEFENDING);
    battleBoatEvent.type = BB_EVENT_SHO_RECEIVED;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_RES){
        printf("\nSUCCESS! In Proper State! %d, %d, %d", battleBoatMessage.param0, battleBoatMessage.param1, battleBoatMessage.param2);
    } else if(battleBoatMessage.type == MESSAGE_NONE && AgentGetState() == AGENT_STATE_END_SCREEN) {
        printf("\nSUCCESS! In Proper State! But you Lost!");
    } else {
        printf("\nFAILED!");
    }
    
    printf("\n\nTESTING BB_EVENT_RESET_BUTTON\n");
    AgentSetState(AGENT_STATE_END_SCREEN);
    battleBoatEvent.type = BB_EVENT_RESET_BUTTON;
    battleBoatMessage = AgentRun(battleBoatEvent);
    if(battleBoatMessage.type == MESSAGE_NONE){
        printf("\nSUCCESS! In Proper State!");
    } else {
        printf("\nFAILED!");
    }
        
    while (1);
    return 0;
}
