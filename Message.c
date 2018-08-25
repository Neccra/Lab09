/*
 * File:   Message.c
 * Author: Jake
 *
 * Created on August 23, 2018, 9:28 PM
 */

#include "Message.h"
#include "xc.h"

typedef enum {
    WAITING_FOR_START_DELIMITER,
    RECORDING_PAYLOAD,
    RECORDING_SUM
} DecodeStates;

static DecodeStates currentDecodeState;

uint8_t Message_CalculateChecksum(const char* payload) {
    //  uint8_t checkSum;
    //  if (payload = NULL){
    //      return checkSum;
    //  } else {
    //      return checkSum ^ Message_CalculateChecksum (payload +1);
    //  }
}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event) {

}

int Message_Encode(char *message_string, Message message_to_encode) {

}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event) {
    switch (currentDecodeState) {
        case WAITING_FOR_START_DELIMITER:
            // if (start delimiter) {
            //      currentDecodeState = RECORDING_PAYLOAD;  
            break;

        case RECORDING_PAYLOAD:
            // if (checksum delimiter) {
            //      currentDecodeState = RECORDING_SUM;
            //
            // } else if (any other char){
            //      record char
            //
            // } else if (max payload length exceeded) {
            //      currentDecodeState = WAITING_FOR_START_DELIMITER;
            //      return ERROR;
            //
            // } else if (unexpected delimiter) {
            //      currentDecodeState = WAITING_FOR_START_DELIMITER;
            //      return ERROR;
            // }
            break;

        case RECORDING_SUM:
            // if (hex char) {
            //      record character
            // }
            // if (end delimiter) {
            //      parse payload
            //      parse checksum
            //
            //      if (payload is valid && checksum matches payload){
            //          currentDecodeState = WAITING_FOR_START_DELIMITER;
            //          return MESSAGE_RECIEVED;
            //      } else {
            //          currentDecodeState = WAITING_FOR_START_DELIMITER;
            //          return ERROR;
            //      }
            //
            // } else if (incorrect checksum length) {
            //      currentDecodeState = WAITING_FOR_START_DELIMITER;
            //      return ERROR;
            //
            // } else if (any other char) {
            //      currentDecodeState = WAITING_FOR_START_DELIMITER;
            //      return ERROR;
            // }
            break;
    }
}