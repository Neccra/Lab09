/*
 * File:   AgentTest.c
 * Author: liaoh
 *
 * Created on August 27, 2018, 1:37 PM
 */
#include "Field.h"
#include "Agent.h"
#include "xc.h"
Field testField;

int main(void) {
    printf("\nAgent Test Harness, compiled on %s %s", __DATE__, __TIME__);
    AgentInit();
    FieldPrint_UART(ownField,testField);
    
    return 0;
}
