/* 
 * File:   Message_Test.c
 * Author: George
 *
 * Created on August 27, 2018, 12:59 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Message.h"

char CAT [4] = "CAT"; 
char Null = '\0';
uint8_t calculatedChecksum;
BB_Event messageEvent;

int main(void){
	BOARD_Init();
	printf("\nMessage Test Harness, compiled on %s %s\n", __DATE__, __TIME__);

	// Message_CalculateChecksum
	calculatedChecksum = Message_CalculateChecksum(CAT);
	if (calculatedChecksum == 0x56){
		printf("Message_CalculateChecksum Test: Success \n");
	} else {
		printf("Message_CalculateChecksum Test: FAIL \ncalculatedChecksum = %x",
		 calculatedChecksum);
	}


	// Message_ParseMessage
	if(Message_ParseMessage(CAT, "56",  messageEvent) == SUCCESS){
		printf("Message_ParseMessage Test: Success \n");
	} else {
		printf("Message_ParseMessage Test: FAIL \n");
	}


    while (1);
}

