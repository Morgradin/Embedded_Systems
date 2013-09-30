#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

void chooseTest(int input){
    if (input==1){
        testLow();
    }
    else if (input == 2){
        testHigh();
    }
    else if (input == 3){
        testDerivative();
    }
    else if (input == 4){
        testSquaring();
    }
    else if (input == 5){
        testMWI();
    }
    else if (input == 0){
        printf("You've chosen to exit. Goodbye!");
        exit(EXIT_FAILURE);
    }

    printf("Please enter your choice of test.\n "
        "Press 1 for Low test, 2 for hightest, 3 for Deri"
        ", 4 for Square, 5 for MWI and 0 for exit.\n");
    scanf("%d", &input);
    chooseTest(input);
}

int mainTest (void){
    int input=0;
    printf("Please enter your choice of test.\n "
        "Press 1 for Low test, 2 for hightest, 3 for Deri"
        ", 4 for Square, 5 for MWI and 0 for exit.\n");
    scanf("%d", &input);

    chooseTest(input);
    return 0;
}
