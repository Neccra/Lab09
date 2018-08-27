/*
 * File:   NegotiationTest.c
 * Author: Jake
 *
 * Created on August 25, 2018, 9:49 AM
 */
#include <stdio.h>
#include "Negotiation.h"
#include "BOARD.h"
#include "xc.h"

static NegotiationData testData1 = 0xAAAA;
static NegotiationData testData2 = 0xBBBB;

int main(void) {
    BOARD_Init();
    printf("\nNegotiation Test Harness, compiled on %s %s", __DATE__, __TIME__);

    // input:   secret           output:    commitment
    printf("\n\nNegotiationHash 1: 0x%04x", NegotiationHash(testData1));
    printf("\n\nNegotiationHash 2: 0x%04x", NegotiationHash(testData2));
    
    // secret:  testData1        commitment:    testData1
    if (NegotiationVerify(testData1, NegotiationHash(testData1)) == TRUE) {
        printf("\n\nNegotiationVerify 1: Success");
    } else {
        printf("\n\nNegotiationVerify 1: FAIL");
    }

    // secret:  testData1        commitment:    testData2
    if (NegotiationVerify(testData1, NegotiationHash(testData2)) == FALSE) {
        printf("\n\nNegotiationVerify 2: Success");
    } else {
        printf("\n\nNegotiationVerify 2: FAIL");
    }

    // coin flip
    printf("\nNegotiateCoinFlip 2: 0x%04x", NegotiateCoinFlip(testData1, testData2));

    while (1);
}
