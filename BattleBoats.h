#ifndef BATTLEBOATS_H
#define BATTLEBOATS_H

#include <stdint.h>

/**
    This file contains standard structures that are used 
 */

typedef enum {
    BB_EVENT_NO_EVENT,
    BB_EVENT_START_BUTTON,
    BB_EVENT_RESET_BUTTON,
    BB_EVENT_CHA_RECEIVED,
    BB_EVENT_ACC_RECEIVED,
    BB_EVENT_REV_RECEIVED,
    BB_EVENT_SHO_RECEIVED,
    BB_EVENT_RES_RECEIVED,
    BB_EVENT_MESSAGE_SENT,
    BB_EVENT_ERROR,
} BB_EventType;

/**
All BB events use this struct:
 */
typedef struct {
    BB_EventType type;
    uint16_t param0; //defined in Message.h
    uint16_t param1;
    uint16_t param2;
} BB_Event;


/**
 * Used to signal different types of errors as the param0
 * of a BattleBoat Error event.  You are not required to utilize these,
 * but they can make error checking much more effective.
 * 
 */
typedef enum {
    BB_SUCCESS = 0,                     //0
    BB_ERROR_BAD_CHECKSUM,              //1
    BB_ERROR_PAYLOAD_LEN_EXCEEDED,      //2
    BB_ERROR_CHECKSUM_LEN_EXCEEDED,     //3
    BB_ERROR_INVALID_MESSAGE_TYPE,      //4
} BB_Error;



#endif // BATTLEBOATS_H