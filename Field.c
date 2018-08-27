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
#define BOAT_LIVES 1
#define ZERO_LIVES 0
#define TWO_DIR 2
#define EAST_DIR 1
#define SOUTH_DIR 0
#define OCCUPIED 1
#define EMPTY 0

typedef struct {
    uint8_t row;
    uint8_t col;

};

void FieldPrint_UART(Field *own_field, Field * opp_field) {

}

void FieldInit(Field *own_field, Field * opp_field) {
    int col, row;
    for (row = 0; row < FIELD_ROWS; ++row) {
        for (col = 0; col < FIELD_COLS; ++col) {
            // initialize all grid to 0
            own_field->grid[row][col] = FIELD_SQUARE_EMPTY;
            opp_field->grid[row][col] = FIELD_SQUARE_UNKNOWN;
        }
    }
    // set opponent boat lives
    opp_field->smallBoatLives = BOAT_LIVES;
    opp_field->mediumBoatLives = BOAT_LIVES;
    opp_field->largeBoatLives = BOAT_LIVES;
    opp_field->hugeBoatLives = BOAT_LIVES;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col) {
    if (row > FIELD_ROWS || col > FIELD_COLS) {
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

// update self board

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

// update opponent board

SquareStatus FieldUpdateKnowledge(Field *f, const GuessData * gData) {
    SquareStatus previousValue;
    previousValue = FieldGetSquareStatus(f, gData->row, gData->col);

    if (gData->result == RESULT_MISS) {
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_EMPTY);

    } else if (gData->result == RESULT_HIT) {
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);

    } else if (gData->result == RESULT_SMALL_BOAT_SUNK) {
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        f->smallBoatLives = ZERO_LIVES;

    } else if (gData->result == RESULT_MEDIUM_BOAT_SUNK) {
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        f->mediumBoatLives = ZERO_LIVES;

    } else if (gData->result == RESULT_LARGE_BOAT_SUNK) {
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        f->largeBoatLives = ZERO_LIVES;

    } else if (gData->result == RESULT_HUGE_BOAT_SUNK) {
        FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        f->hugeBoatLives = ZERO_LIVES;

    }
    return previousValue;
}

uint8_t FieldGetBoatStates(const Field * f) {
    uint8_t boatStatesResult = 0x00;
    if (f->smallBoatLives = BOAT_LIVES) {
        boatStatesResult = boatStatesResult & 0x01;
    }
    if (f->mediumBoatLives = BOAT_LIVES) {
        boatStatesResult = boatStatesResult & 0x02;
    }
    if (f->largeBoatLives = BOAT_LIVES) {
        boatStatesResult = boatStatesResult & 0x04;
    }
    if (f->hugeBoatLives = ZERO_LIVES) {
        boatStatesResult = boatStatesResult & 0x80;
    }
    return boatStatesResult;
}

uint8_t FieldAIPlaceAllBoats(Field * f) {
    // variables
    int rowRand, colRand, dirRand, row, col, emptyStatus;
    BoatDirection dirRand;
    BoatType thisType;
    SquareStatus curStatus;

    // empty field check
    while (emptyStatus != EMPTY) { // exit if fully empty
        rowRand = rand() % FIELD_ROWS;
        colRand = rand() % FIELD_COLS;
        dirRand = rand() % TWO_DIR;
        emptyStatus = EmptyFieldCheck(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_HUGE);
    }
    // place boats
    FieldAddBoat(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_HUGE);

    // empty field check
    while (emptyStatus != EMPTY) { // exit if fully empty
        rowRand = rand() % FIELD_ROWS;
        colRand = rand() % FIELD_COLS;
        dirRand = rand() % TWO_DIR;
        emptyStatus = EmptyFieldCheck(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_LARGE);
    }
    // place boats
    FieldAddBoat(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_LARGE);

    // empty field check
    while (emptyStatus != EMPTY) { // exit if fully empty
        rowRand = rand() % FIELD_ROWS;
        colRand = rand() % FIELD_COLS;
        dirRand = rand() % TWO_DIR;
        emptyStatus = EmptyFieldCheck(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_MEDIUM);
    }
    // place boats
    FieldAddBoat(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_MEDIUM);

    // empty field check
    while (emptyStatus != EMPTY) { // exit if fully empty
        rowRand = rand() % FIELD_ROWS;
        colRand = rand() % FIELD_COLS;
        dirRand = rand() % TWO_DIR;
        emptyStatus = EmptyFieldCheck(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_SMALL);
    }
    // place boats
    FieldAddBoat(f, rowRand, colRand, dirRand, FIELD_BOAT_TYPE_SMALL);
}

GuessData FieldAIDecideGuess(const Field * f) {

}

int EmptyFieldCheck(Field *f, uint8_t rowHead, uint8_t colHead,
        int dir, BoatType boatType) {
    int row, col;

    // check direction
    if (dir == EAST_DIR) {

        // check boat_type
        if (boat_type == FIELD_BOAT_TYPE_SMALL) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_SMALL + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_MEDIUM + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_LARGE + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boat_type == FIELD_BOAT_TYPE_HUGE) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_HUGE + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        }

    } else if (dir == SOUTH_DIR) {

        // check boat_type
        if (boat_type == FIELD_BOAT_TYPE_SMALL) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_SMALL + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_MEDIUM + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_LARGE + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boat_type == FIELD_BOAT_TYPE_HUGE) {
            for (row = rowHead; row > (FIELD_BOAT_SIZE_HUGE + rowHead), ++row) {
                curStatus = FieldGetSquareStatus(f, rowRand, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        }
    }
}

