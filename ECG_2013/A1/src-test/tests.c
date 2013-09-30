#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/sensor.h"
#include "../src/buffer.h"

void test(int choice){

    // Variable initialization
    FILE *inputfile = fopen ( "/Datafiles/ECG.txt", "r" );
    FILE *comparefile = fopen ( "/Datafiles/x_low.txt", "r" );

    BUFFER buff_sensorData = {{0}, 0};
    BUFFER buff_lowPass = {{0}, 0};

    int errorFound = 0;
    int lineNumber = 0;


    // Starts a clock to check how long the lowpass filter takes
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int inputdata = getNextData(inputfile);
    int comparedata = getNextData(comparefile);

    while(inputdata != INT16_MAX && comparedata != INT16_MAX) {
        lineNumber++;
        pushData(&buff_sensorData, inputdata);
        lowPass2(&buff_sensorData, &buff_lowPass);

        int filterVal = readData(&buff_lowPass, 0);
        if (filterVal != comparedata) {
            printf("Value mismatch on line %i. filtered: %i, comparedata: %i\n", lineNumber, filterVal, comparedata);
            errorFound++;
        }

    }


    fclose(inputfile);
    fclose(comparefile);

    end = clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("Time spent on lowpass: %f",
            cpu_time_used);
}

void testHigh(){
    return;

}

void testDerivative(){
    return;

}

void testSquaring(){
    return;

}

void testMWI(){
    return;
}
