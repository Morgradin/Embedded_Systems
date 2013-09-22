#include <stdio.h>
#include "buffer.h"
#include "sensor.h"



int main()
{
    static const char filename[] = "DataFiles/ECG.txt";
    FILE *file = fopen ( filename, "r");

    int data = getNextData(file);

    while(data != INT_MAX) {

        //printf("Data read from file: %d\n", data);
        pushData(data);

        int current = readData(0);
        int previous = readData(3);
        printf("Current %i\nPrevious 3 back %i\n", current, previous);



        data = getNextData(file);
    }
    printf("last data value: %d\n", data);

    return 0;
}

