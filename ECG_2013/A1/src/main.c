#include <stdio.h>
#include "buffer.h"
#include "sensor.h"

int main(void)
{
    static const char filename[] = "DataFiles/ECG.txt";
    FILE *file = fopen ( filename, "r");

    int data = getNextData(file);

    while(data != EOF) {

        printf("Data read from file: %i\n", data);
        data = getNextData(file);
    }

    return 0;
}

