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
Message testMessage;
char encodedMessage [MESSAGE_MAX_LEN];

int main(void){
	BOARD_Init();
	printf("\nMessage Test Harness, compiled on %s %s\n", __DATE__, __TIME__);

	// Message_CalculateChecksum
	calculatedChecksum = Message_CalculateChecksum(CAT);
	if (calculatedChecksum == 0x56){
		printf("Message_CalculateChecksum Test: Success \n");
	} else {
		printf("Message_CalculateChecksum Test: FAIL \ncalculatedChecksum = %x\n",
		 calculatedChecksum);
	}


	// Message_ParseMessage
	if(Message_ParseMessage(CAT, "56", &messageEvent) == SUCCESS){
		printf("Message_ParseMessage Test: Success \n");
	} else {
		printf("Message_ParseMessage Test: FAIL \n");
	}
        
    // Message Encode
    testMessage.type = MESSAGE_RES;
    testMessage.param0 = 10 ;
    testMessage.param1 = 6 ;
    testMessage.param2 = 9 ;

    Message_Encode(encodedMessage, testMessage);
    printf("Message_Encode Test Output:%s \n", encodedMessage);

    // Message Decode
    char inputChar = '$';
    if(SUCCESS == Message_Decode(inputChar, &messageEvent)){
    	printf("Message_Decode Test : SUCCESS");
    } else {
    	printf("Message_Decode Test : FAIL");
    }
    //		pass full NMEA

    //		$, ',' , 



    while (1);
}

