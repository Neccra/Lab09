/*
 * File:   Message.c
 * Author: Jake
 *
 * Created on August 23, 2018, 9:28 PM
 */
#include <stdlib.h>
#include "BOARD.h"
#include "Message.h"
#include "BattleBoats.h"

typedef enum {
    WAITING_FOR_START_DELIMITER,
    RECORDING_PAYLOAD,
    RECORDING_SUM
} DecodeStates;

DecodeStates currentDecodeState;
char incomingPayload[MESSAGE_MAX_PAYLOAD_LEN];
char incomingChecksum[MESSAGE_MAX_PAYLOAD_LEN];
int payloadLength;
int checksumLength;
int parseMessageResult;
BB_Event currentBBEvent;

uint8_t Message_CalculateChecksum(const char* payload) {

    int payloadValue, increment, strLength;
    strLength = strlen(payload);
    payloadValue = (int) *(payload);
    for (increment = 1; increment < strLength; ++increment) {
        payloadValue = payloadValue ^ (int) *(payload + increment);
        //printf("%x\n", payloadValue);
    }

    return payloadValue;
}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event) {
    uint8_t derivedChecksum, givenChecksumValue;
    // check for errors

    if (strlen(checksum_string) > MESSAGE_CHECKSUM_LEN) {
        message_event->type = BB_EVENT_ERROR;

        return STANDARD_ERROR;
    }
    if (*payload == 'C'){
        message_event->type = BB_EVENT_CHA_RECEIVED;

    } else if (*payload == 'A'){
        message_event->type = BB_EVENT_ACC_RECEIVED;

    } else if (*payload == 'C'){
        message_event->type = BB_EVENT_REV_RECEIVED;

    } else if (*payload == 'S'){
        message_event->type = BB_EVENT_SHO_RECEIVED;

    } else if (*payload == 'R'){
        message_event->type = BB_EVENT_RES_RECEIVED;

    }

    // check if checksums equal
    derivedChecksum = Message_CalculateChecksum(payload);
    givenChecksumValue = (int) checksum_string + (int) (*(&checksum_string + 1));
    if (derivedChecksum == givenChecksumValue) {
        return SUCCESS;
    } else {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }
}


int Message_Encode(char *message_string, Message message_to_encode) {
    // message_string is output

    // <editor-fold defaultstate="collapsed" desc="identify message type">
    char outgoingPayload[MESSAGE_MAX_PAYLOAD_LEN];
    int outgoingMessageLength;
    // identify message type
    if (message_to_encode.type == MESSAGE_CHA) {
        sprintf(outgoingPayload, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);

    } else if (message_to_encode.type == MESSAGE_ACC) {
        sprintf(outgoingPayload, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);

    } else if (message_to_encode.type == MESSAGE_REV) {
        sprintf(outgoingPayload, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);

    } else if (message_to_encode.type == MESSAGE_SHO) {
        sprintf(outgoingPayload, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0,
                message_to_encode.param1);

    } else if (message_to_encode.type == MESSAGE_RES) {
        sprintf(outgoingPayload, PAYLOAD_TEMPLATE_RES, message_to_encode.param0,
                message_to_encode.param1, message_to_encode.param2);
    } else if (message_to_encode.type == MESSAGE_NONE) {
        return STANDARD_ERROR;
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="message wrap">
    // wrap payload
    int encodingChecksum;
    // get checksum
    encodingChecksum = (int) Message_CalculateChecksum(outgoingPayload);
    // wrap payload
    outgoingMessageLength = sprintf(message_string, MESSAGE_TEMPLATE, outgoingPayload,
            encodingChecksum);
    // return message length
    return outgoingMessageLength;
    // </editor-fold>
}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event) {

    switch (currentDecodeState) {

        case WAITING_FOR_START_DELIMITER:
            // <editor-fold defaultstate="collapsed" desc="WAITING_FOR_START_DELIMITER">
            if (char_in == '$') {
                // delimiter detected, change state to RECORDING_PAYLOAD
                decoded_message_event = BB_EVENT_NO_EVENT;
                currentDecodeState = RECORDING_PAYLOAD;
                return SUCCESS;
            } else {
                decoded_message_event = BB_EVENT_NO_EVENT;
                return SUCCESS;
            }

            break;
            // </editor-fold>

        case RECORDING_PAYLOAD:
            // <editor-fold defaultstate="collapsed" desc="RECORDING_PAYLOAD">
            if (char_in == '$' || char_in == '\n') {
                // unexpected delimiter detected, return state to WAITING_FOR_START_DELIMITER
                currentDecodeState = WAITING_FOR_START_DELIMITER;
                decoded_message_event = BB_EVENT_NO_EVENT;
                return STANDARD_ERROR;
            }

            if (payloadLength > MESSAGE_MAX_PAYLOAD_LEN) {
                // payload exceed max, return state to WAITING_FOR_START_DELIMITER
                currentDecodeState = WAITING_FOR_START_DELIMITER;
                decoded_message_event = BB_EVENT_NO_EVENT;
                return STANDARD_ERROR;

            }

            if (char_in == '*') {
                // checksum delimiter detected, change state to RECORDING_SUM
                currentDecodeState = RECORDING_SUM;
                decoded_message_event = BB_EVENT_NO_EVENT;
                return SUCCESS;

            } else {
                // for any other char, record and stay in current state
                char payloadBuffer = (char) char_in;
                payloadLength = sprintf(incomingPayload, "%s%c", incomingPayload, payloadBuffer);
                decoded_message_event = BB_EVENT_NO_EVENT;
                return SUCCESS;
            }

            break;
            // </editor-fold>

        case RECORDING_SUM:
            // <editor-fold defaultstate="collapsed" desc="RECORDING_SUM">
            // hex char, record character, stay in state
            if (char_in == '0' || char_in == '1' || char_in == '2' || char_in == '3'
                    || char_in == '4' || char_in == '5' || char_in == '6' || char_in == '7'
                    || char_in == '8' || char_in == '9' || char_in == 'a' || char_in == 'b'
                    || char_in == 'c' || char_in == 'd' || char_in == 'e' || char_in == 'f') {
                char checksumBuffer = (char) char_in;
                checksumLength = sprintf(incomingChecksum, "%s%c", incomingChecksum, checksumBuffer);
                decoded_message_event = BB_EVENT_NO_EVENT;
                return SUCCESS;
            }
            if (char_in == '\n') {
                // end of packet detected

                parseMessageResult = Message_ParseMessage(incomingPayload, incomingChecksum, &currentBBEvent);

                if (SUCCESS == parseMessageResult) {
                    // checksum is correct, no cheating detected
                    currentDecodeState = WAITING_FOR_START_DELIMITER;
                    decoded_message_event->type = currentBBEvent.type;
                    return SUCCESS;
                } else {
                    // checksum is incorrect, ignoring message
                    currentDecodeState = WAITING_FOR_START_DELIMITER;
                    return STANDARD_ERROR;
                }

            } else if (checksumLength > MESSAGE_CHECKSUM_LEN) {
                // checksum exceed max, return state to WAITING_FOR_START_DELIMITER
                currentDecodeState = WAITING_FOR_START_DELIMITER;
                return STANDARD_ERROR;

            } else {
                // anything else, return state to WAITING_FOR_START_DELIMITER
                currentDecodeState = WAITING_FOR_START_DELIMITER;
                return STANDARD_ERROR;
            }
            
            break;
            // </editor-fold>
    }
    return SUCCESS;
}