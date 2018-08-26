/*
 * File:   Field.c
 * Author: Jake
 *
 * Created on August 26, 2018, 12:20 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "xc.h"
#include "Field.h"
#define BOAT_COUNT 1

void FieldPrint_UART(Field *own_field, Field * opp_field) {

}

void FieldInit(Field *own_field, Field * opp_field) {
    int col, row;
    for (row = 0; row < FIELD_ROWS; ++row) {
        for (col = 0; col < FIELD_COLS; ++col) {
            // initialize all grid to 0
            own_field->grid[row][col] = FIELD_SQUARE_EMPTY;
            opp_field->grid[row][col] = FIELD_SQUARE_EMPTY;
        }
    }
    // set opponent boat lives
    opp_field->smallBoatLives = BOAT_COUNT;
    opp_field->mediumBoatLives = BOAT_COUNT;
    opp_field->largeBoatLives = BOAT_COUNT;
    opp_field->hugeBoatLives = BOAT_COUNT;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col) {
    if (row < FIELD_ROWS || row > FIELD_ROWS || col < FIELD_COLS || col > FIELD_COLS) {
        return FIELD_SQUARE_INVALID;
    } else {
        return f->grid[row][col];
    }
}

SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p) {
    uint8_t buff;
    buff = f->grid[row][col];
    f->grid[row][col] = p;
    return buff;
}

uint8_t FieldAddBoat(Field *f, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type) {
    int colCount, rowCount, boatSize;
    SquareStatus boatType;
    // check if field is pre-occupied
    if (FIELD_SQUARE_EMPTY != FieldGetSquareStatus(f, row, col)) {
        return STANDARD_ERROR;
    }
    // determine boat size
    if (boat_type == FIELD_BOAT_TYPE_SMALL) {
        boatSize = FIELD_BOAT_SIZE_SMALL;
        boatType = FIELD_SQUARE_SMALL_BOAT;

    } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
        boatSize = FIELD_BOAT_SIZE_MEDIUM;
        boatType = FIELD_SQUARE_MEDIUM_BOAT;

    } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
        boatSize = FIELD_BOAT_SIZE_LARGE;
        boatType = FIELD_SQUARE_LARGE_BOAT;

    } else if (boat_type == FIELD_BOAT_TYPE_HUGE) {
        boatSize = FIELD_BOAT_SIZE_HUGE;
        boatType = FIELD_SQUARE_HUGE_BOAT;

    } else {
        return STANDARD_ERROR;
    }
    // check direction
    if (dir == FIELD_DIR_EAST) {
        for (colCount = 0; colCount < boatSize; ++colCount) {
            f->grid[row][col] = boatType;

        }
        return SUCCESS;

    } else if (dir == FIELD_DIR_SOUTH) {
        for (rowCount = 0; rowCount < boatSize; ++rowCount) {
            f->grid[row][col] = boatType;
        }
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

SquareStatus FieldRegisterEnemyAttack(Field *f, GuessData *gData) {
    SquareStatus previousStatus;
    previousStatus = FieldGetSquareStatus(f, gData->row, gData->col);
    
    if (FIELD_SQUARE_EMPTY == previousStatus) {
        // if square is empty, set as miss
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_MISS);

    } else if (FIELD_SQUARE_SMALL_BOAT == previousStatus ||
            FIELD_SQUARE_MEDIUM_BOAT == previousStatus ||
            FIELD_SQUARE_LARGE_BOAT == previousStatus ||
            FIELD_SQUARE_HUGE_BOAT == previousStatus) {
        // if square contains a boat
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
    }
    return previousStatus;
}

SquareStatus FieldUpdateKnowledge(Field *f, const GuessData * gData) {

}

uint8_t FieldGetBoatStates(const Field * f) {

}

uint8_t FieldAIPlaceAllBoats(Field * f) {

}

GuessData FieldAIDecideGuess(const Field * f) {

}
