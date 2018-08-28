// George Leece gleece@ucsc.edu

#include <stdio.h>
#include "Negotiation.h"
#include "BOARD.h"
//#include "Message.h"

#define DEUCE 2
NegotiationData hash;
NegotiationData parity;
int count;

// Helper function to determine the parity for the Coin Flip
int ParityCount(NegotiationData Input);

NegotiationData NegotiationHash(NegotiationData secret){
    hash = (((uint64_t) secret)*secret) % PUBLIC_KEY;      // creates hash of secret number via A^2 mod 0xBEEF
    return hash;                              // Returns the hash to be used for challenge
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment){
    hash = NegotiationHash(secret);           // ensures that the secret number generates the same hash as the commitment received earlier
    if(hash == commitment){                   // if equal then returns TRUE
        return TRUE;
    } else{                                   // if not equal returns FALSE
        return FALSE;
    }
}

NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B){
    parity = A^B;                             // XORs A and B to find the parity
    if(ParityCount(parity) % DEUCE == 0){     // Helper function call to find the parity 
        return TAILS;                         // Returns Tails if the parity is even
    } else {
        return HEADS;                         // Returns Heads if parity is odd
    }
}


int ParityCount(NegotiationData Input){
    while(Input != 0){
        if((Input%DEUCE) == 1){
            count++;
            Input -= 1;
        } else {
            Input = Input/DEUCE;
        }
    }
    return count;
}