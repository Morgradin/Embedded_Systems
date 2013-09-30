#include <stdio.h>
#include <stdlib.h>
#include "../src/sensor.h"

void chooseTest(int input){
    if (input != 0) test(input);
    else {
        printf("You've chosen to exit. Goodbye!");
        exit(EXIT_FAILURE);
    }

    printf("Please enter your choice of test.\n "
        "Press 1 for Low test, 2 for hightest, 3 for Deri"
        ", 4 for Square, 5 for MWI and 0 for exit.\n");
    scanf("%d", &input);
    chooseTest(input);
}

int main (void){
    int input=0;
    printf("Please enter your choice of test.\n "
        "Press 1 for Low test, 2 for hightest, 3 for Deri"
        ", 4 for Square, 5 for MWI and 0 for exit.\n");
    scanf("%d", &input);

    chooseTest(input);
    return 0;
}
