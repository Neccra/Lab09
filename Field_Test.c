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

int main(void) {
    BOARD_Init();
    FieldInit(&ownField, &oppField);
    printf("\nField Test Harness, compiled on %s %s\n", __DATE__, __TIME__);
    FieldPrint_UART(&ownField, &oppField);


    
    
    while (1);
}

