#include <stdio.h>
#include "buffer.h"
#include "sensor.h"
#include "RRHandling.h"

// Initiating buffers
BUFFER buff_sensorData = {{0}, 0};
BUFFER buff_lowPass = {{0}, 0};
BUFFER buff_highPass = {{0}, 0};
BUFFER buff_derivPass = {{0}, 0};
BUFFER buff_sqrPass = {{0}, 0};
BUFFER buff_mwiPass = {{0}, 0};

PEAKBUFFER pbuff_peaks = {{0}, 0};


int main()
{
    static const char filename[] = "DataFiles/ECG.txt";
    FILE *file = fopen ( filename, "r");

    int data = getNextData(file);
    int clock = 0;

    while(data != INT16_MAX) {

        //printf("Data read from file: %d\n", data);
        pushData(&buff_sensorData, data);


        // Reading data from sensor buffer
        //int currentSensor = readData(&sensorData, 0);
        //int previousSensor = readData(&sensorData, 3);
        //printf("Current sensor %i\nPrevious sensor %i\n", currentSensor, previousSensor);

        // Do filtering;
        // all filters tages an input buffer and output buffer and updates output in-place
        lowPass2(&buff_sensorData, &buff_lowPass);
        highPass2(&buff_lowPass, &buff_highPass);
        derivative2(&buff_highPass, &buff_derivPass);
        squaring2(&buff_derivPass, &buff_sqrPass);
        mwInt2(&buff_sqrPass, &buff_mwiPass);

        // Peak detection
        if (clock > 3) {
            int x2 = readData(&buff_mwiPass, 2);
            int x1 = readData(&buff_mwiPass, 1);
            int x0 = readData(&buff_mwiPass, 0);
            RRcalculate(x0, x1, x2, clock);
        }

        // Reading data from filtered buffer
        //int currentFilter = readData(&buff_mwiPass, 0);
        //printf("Current filter %i at time %i\n", currentFilter, clock);

        data = getNextData(file);
        clock++;
    }
    printf("main::Received termination value: %i\n", data);
    printf("main::Ran %i times\n", clock);

    //print_list();

    return 0;
}

