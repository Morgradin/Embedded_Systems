#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "buffer.h"

void testing(int choice, char inputpath[], char comparepath[]){

    FILE *inputfile = fopen ( inputpath, "r");
    FILE *comparefile = fopen ( comparepath, "r");

    BUFFER buff_source = {{0}, 0};
    BUFFER buff_filtered = {{0}, 0};

    int errorFound = 0;
    int lineNumber = 0;
    int ran = 0;


    int inputdata = getNextData(inputfile);
    int comparedata = getNextData(comparefile);



    while(inputdata != INT16_MAX && comparedata != INT16_MAX) {
        lineNumber++;
        pushData(&buff_source, inputdata);
        switch (choice) {
            case 1: lowPass2(&buff_source, &buff_filtered); break;
            case 2: highPass2(&buff_source, &buff_filtered); break;
            case 3: derivative2(&buff_source, &buff_filtered); break;
            case 4: squaring2(&buff_source, &buff_filtered); break;
            case 5: mwInt2(&buff_source, &buff_filtered); break;
        }


        int filterVal = readData(&buff_filtered, 0);
        if (filterVal != comparedata) {
            printf("Value mismatch on line %i. filtered: %i, comparedata: %i\n", lineNumber, filterVal, comparedata);
            errorFound++;
        }
        inputdata = getNextData(inputfile);
        comparedata = getNextData(comparefile);
        ran = 1;

    }

    if (!errorFound && ran) printf("No errors found. You're clear for takeoff\nComparing input: %s with file: %s\n\n", inputpath, comparepath);
    else if (!ran) printf("Didn't run. No conclusion\n\n");
    else printf("ERROR: %i value-mismatch found\nComparing input: %s with file: %s\n\n", errorFound, inputpath, comparepath);

    return;
}




int main(){

    testing(1, "Datafiles/ECG.txt","Datafiles/x_low.txt");
    testing(2, "Datafiles/x_low.txt","Datafiles/x_high.txt");
    testing(3, "Datafiles/x_high.txt","Datafiles/x_der.txt");
    testing(4, "Datafiles/x_der.txt","Datafiles/x_sqr.txt");
    testing(5, "Datafiles/x_sqr.txt","Datafiles/x_mwi_div_after.txt");

    return 0;
}



