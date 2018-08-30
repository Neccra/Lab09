/* 
 * File:   Field_Test.c
 * Author: George
 *
 * Created on August 27, 2018, 1:00 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Field.h"
#include "BOARD.h"

Field ownField;
Field oppField;
GuessData guess;
SquareStatus squareStatus;
int row, col;

int main(void) {
    BOARD_Init();
    FieldInit(&ownField, &oppField);
    printf("\nField Test Harness, compiled on %s %s\n", __DATE__, __TIME__);
    FieldPrint_UART(&ownField, &oppField);                              // Testing initialization of board later with lives of enemy boats
    if(FieldGetSquareStatus(&ownField, 0, 0) == FIELD_SQUARE_EMPTY){    // Testing FieldGetSquareStatus Functionality
        printf("SUCCESS\n");
    } else{
        printf("FAILED\n");
    }
    if(FieldGetSquareStatus(&ownField, 0, 11) == FIELD_SQUARE_INVALID){    // Testing FieldGetSquareStatus Functionality
        printf("SUCCESS\n");
    } else{
        printf("FAILED\n");
    }
    if(FieldAddBoat(&ownField, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE) == SUCCESS){ // Testing FieldAddBoat Functionality
        printf("SUCCESS\n");
    } else{
        printf("FAILED\n");
    }
    printf("%d\n", ownField.hugeBoatLives);                 // Ensuring that the boat lives are activiated with the boat placement
    FieldPrint_UART(&ownField, &oppField);    
    for(col = 0; col < 5; col++){
        if(FieldGetSquareStatus(&ownField, 0, 0) == FIELD_SQUARE_HUGE_BOAT){    // Testing FieldGetSquareStatus
            printf("SUCCESS\n");
        } else{
            printf("FAILED\n");
        }
    }
    guess.col = 0;
    guess.row = 0;
    FieldRegisterEnemyAttack(&ownField, &guess);                // Testing FieldRegisterEnemyAttack returning a hit in the result (Form of enum)
    printf("%d, %d, %d\n", guess.row, guess.col, guess.result);
    FieldPrint_UART(&ownField, &oppField);
    if(FieldGetBoatStates(&ownField)== 0x08){                   // Testing FieldGetBoatStates
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
    for(col = 1; col < 7; col++){                               // Destroying the Huge Boat
        guess.col = col;
        FieldRegisterEnemyAttack(&ownField, &guess);
    }
    FieldPrint_UART(&ownField, &oppField);                      
    if(FieldGetBoatStates(&ownField)== 0x00){                   // Ensures the live of the huge boat equals zero
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
    guess.row = 3;                                              
    guess.col = 4;
    guess.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppField, &guess);                    // Testing FieldUpdateKnowledge
    if(FieldGetBoatStates(&oppField)== 0x0F){                   // Testing that the status of all enemy boats are active
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
    FieldPrint_UART(&ownField, &oppField);
    guess.row = 4;
    guess.col = 4;
    guess.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);
    guess.row = 5;
    guess.col = 4;
    guess.result = RESULT_SMALL_BOAT_SUNK;                      // Destroying small boat for testing the state of live boats
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);
    if(FieldGetBoatStates(&oppField)== 0x0E){
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
    // Testing AI functions
    FieldInit(&ownField, &oppField);
    FieldPrint_UART(&ownField, &oppField);
    if(FieldAIPlaceAllBoats(&ownField) == SUCCESS){             // Testing the AI placement of boats
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
    
    //Attempted to Test the original AI Decide function
    FieldPrint_UART(&ownField, &oppField);        
    guess = FieldAIDecideGuess(&oppField);                  
    guess.result = RESULT_MISS;
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);
    guess = FieldAIDecideGuess(&oppField);
    guess.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);
    guess = FieldAIDecideGuess(&oppField);
    guess.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);
    guess = FieldAIDecideGuess(&oppField);
    guess.result = RESULT_SMALL_BOAT_SUNK;
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);
    guess = FieldAIDecideGuess(&oppField);
    guess.result = RESULT_MISS;
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);
    
    FieldInit(&ownField, &oppField);
    // Testing of the AIDecideGuess Function by ensuring that no repeats are called
    for(row = 0; row < FIELD_ROWS; row++){
        for(col = 0; col < FIELD_COLS; col++){
            FieldSetSquareStatus(&oppField, row, col, FIELD_SQUARE_MISS);
        }
    }
    FieldSetSquareStatus(&oppField, 3, 5, FIELD_SQUARE_UNKNOWN);
    FieldPrint_UART(&ownField, &oppField);
    guess = FieldAIDecideGuess(&oppField);
    if(guess.col == 5 && guess.row == 3){
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
    guess.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppField, &guess);
    FieldPrint_UART(&ownField, &oppField);


    
    
    while (1);
}

