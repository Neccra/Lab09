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

//typedef struct {
//    uint8_t row;
//    uint8_t col;
//
//};

int EmptyFieldCheck(Field *f, uint8_t rowRand, uint8_t colRand,
        int dir, BoatType boatType);

void FieldPrint_UART(Field *own_field, Field * opp_field) {
    int col, row;
    printf("Friendly Field:\n");
    // <editor-fold defaultstate="collapsed" desc="print friendly field">
    for (row = 0; row < FIELD_ROWS; ++row) {
        for (col = 0; col < FIELD_COLS; ++col) {
            if (own_field->grid[row][col] == FIELD_SQUARE_EMPTY) {
                printf("~");
            } else if (own_field->grid[row][col] == FIELD_SQUARE_UNKNOWN) {
                printf("?");
            } else if (own_field->grid[row][col] == FIELD_SQUARE_SMALL_BOAT) {
                printf("s");
            } else if (own_field->grid[row][col] == FIELD_SQUARE_MEDIUM_BOAT) {
                printf("m");
            } else if (own_field->grid[row][col] == FIELD_SQUARE_LARGE_BOAT) {
                printf("l");
            } else if (own_field->grid[row][col] == FIELD_SQUARE_HUGE_BOAT) {
                printf("h");
            } else if (own_field->grid[row][col] == FIELD_SQUARE_HIT) {
                printf("X");
            } else if (own_field->grid[row][col] == FIELD_SQUARE_MISS) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    // </editor-fold>
    printf("Opponent Field:\n");
    // <editor-fold defaultstate="collapsed" desc="print opponent field">
    for (row = 0; row < FIELD_ROWS; ++row) {
        for (col = 0; col < FIELD_COLS; ++col) {
            if (own_field->grid[row][col] == FIELD_SQUARE_EMPTY) {
                printf("~");
            } else if (opp_field->grid[row][col] == FIELD_SQUARE_UNKNOWN) {
                printf("?");
            } else if (opp_field->grid[row][col] == FIELD_SQUARE_SMALL_BOAT) {
                printf("s");
            } else if (opp_field->grid[row][col] == FIELD_SQUARE_MEDIUM_BOAT) {
                printf("m");
            } else if (opp_field->grid[row][col] == FIELD_SQUARE_LARGE_BOAT) {
                printf("l");
            } else if (opp_field->grid[row][col] == FIELD_SQUARE_HUGE_BOAT) {
                printf("h");
            } else if (opp_field->grid[row][col] == FIELD_SQUARE_HIT) {
                printf("X");
            } else if (opp_field->grid[row][col] == FIELD_SQUARE_MISS) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    // </editor-fold>
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
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
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
        gData->result = RESULT_MISS;

    } else if (FIELD_SQUARE_SMALL_BOAT == previousStatus) {
        // minus boat health, if 0 
        f->smallBoatLives -= 1;
        if (f->smallBoatLives == ZERO_LIVES) {
            gData->result = RESULT_SMALL_BOAT_SUNK;
        } else {
            FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        }
        
    } else if (FIELD_SQUARE_MEDIUM_BOAT == previousStatus) {
        // minus boat health, if 0 
        f->smallBoatLives -= 1;
        if (f->smallBoatLives == ZERO_LIVES) {
            gData->result = RESULT_MEDIUM_BOAT_SUNK;
        } else {
            FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        }
               
    } else if (FIELD_SQUARE_LARGE_BOAT == previousStatus) {
        // minus boat health, if 0 
        f->smallBoatLives -= 1;
        if (f->smallBoatLives == ZERO_LIVES) {
            gData->result = RESULT_LARGE_BOAT_SUNK;
        } else {
            FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        }
        
    } else if (FIELD_SQUARE_HUGE_BOAT == previousStatus) {
        // minus boat health, if 0 
        f->smallBoatLives -= 1;
        if (f->smallBoatLives == ZERO_LIVES) {
            gData->result = RESULT_HUGE_BOAT_SUNK;
        } else {
            FieldSetSquareStatus(f, gData->row, gData->col, FIELD_SQUARE_HIT);
        }
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
    if (f->smallBoatLives == BOAT_LIVES) {
        boatStatesResult = boatStatesResult & FIELD_BOAT_STATUS_SMALL;
    }
    if (f->mediumBoatLives == BOAT_LIVES) {
        boatStatesResult = boatStatesResult & FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->largeBoatLives == BOAT_LIVES) {
        boatStatesResult = boatStatesResult & FIELD_BOAT_STATUS_LARGE;
    }
    if (f->hugeBoatLives == ZERO_LIVES) {
        boatStatesResult = boatStatesResult & FIELD_BOAT_STATUS_HUGE;
    }
    return boatStatesResult;
}

uint8_t FieldAIPlaceAllBoats(Field * f) {
    // variables
    int rowRand, colRand;
    int emptyStatus;
    BoatDirection dirRand;


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

int EmptyFieldCheck(Field *f, uint8_t rowRand, uint8_t colRand,
        int dir, BoatType boatType) {
    int row, col;
    SquareStatus curStatus;
    // check direction
    if (dir == SOUTH_DIR) {

        // check boat_type
        if (boatType == FIELD_BOAT_TYPE_SMALL) {
            for (row = rowRand; row > (FIELD_BOAT_SIZE_SMALL + rowRand); ++row) {
                curStatus = FieldGetSquareStatus(f, row, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boatType == FIELD_BOAT_TYPE_MEDIUM) {
            for (row = rowRand; row > (FIELD_BOAT_SIZE_MEDIUM + rowRand); ++row) {
                curStatus = FieldGetSquareStatus(f, row, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boatType == FIELD_BOAT_TYPE_LARGE) {
            for (row = rowRand; row > (FIELD_BOAT_SIZE_LARGE + rowRand); ++row) {
                curStatus = FieldGetSquareStatus(f, row, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boatType == FIELD_BOAT_TYPE_HUGE) {
            for (row = rowRand; row > (FIELD_BOAT_SIZE_HUGE + rowRand); ++row) {
                curStatus = FieldGetSquareStatus(f, row, colRand);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        }

    } else if (dir == EAST_DIR) {

        // check boat_type
        if (boatType == FIELD_BOAT_TYPE_SMALL) {
            for (col = colRand; col > (FIELD_BOAT_SIZE_SMALL + colRand); ++col) {
                curStatus = FieldGetSquareStatus(f, rowRand, col);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boatType == FIELD_BOAT_TYPE_MEDIUM) {
            for (col = colRand; col > (FIELD_BOAT_SIZE_MEDIUM + colRand); ++col) {
                curStatus = FieldGetSquareStatus(f, rowRand, col);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boatType == FIELD_BOAT_TYPE_LARGE) {
            for (col = colRand; col > (FIELD_BOAT_SIZE_LARGE + colRand); ++col) {
                curStatus = FieldGetSquareStatus(f, rowRand, col);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        } else if (boatType == FIELD_BOAT_TYPE_HUGE) {
            for (col = colRand; col > (FIELD_BOAT_SIZE_HUGE + colRand); ++col) {
                curStatus = FieldGetSquareStatus(f, rowRand, col);
                if (curStatus != FIELD_SQUARE_EMPTY) {
                    return OCCUPIED;
                } else {
                    return EMPTY;
                }
            }
        }
    }
}

