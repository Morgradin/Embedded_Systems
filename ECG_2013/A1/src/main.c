#include <stdio.h>
#include "buffer.h"
#include "sensor.h"

// Initiating buffers
Buffer sensorData = {{0}, 0};
Buffer filt_lowPass = {{0}, 0};
Buffer filt_highPass = {{0}, 0};
Buffer filt_derivPass = {{0}, 0};
Buffer filt_sqrPass = {{0}, 0};
Buffer filt_mwiPass = {{0}, 0};


int main()
{
    static const char filename[] = "DataFiles/ECG.txt";
    FILE *file = fopen ( filename, "r");

    int data = getNextData(file);
    int i = 0;

    /*
    // Reading 12 samples ahead
    int i = 0;
    while (i<12) {
        pushData(&sensorData, data);
        data = getNextData(file);
        i++;
    }
    */


    while(data != INT16_MAX) {

        //printf("Data read from file: %d\n", data);
        pushData(&sensorData, data);


        // Reading data from sensor buffer
        //int currentSensor = readData(&sensorData, 0);
        //int previousSensor = readData(&sensorData, 3);
        //printf("Current sensor %i\nPrevious sensor %i\n", currentSensor, previousSensor);

        // Do filtering, add to filterData
        lowPass2(&sensorData, &filt_lowPass);
        highPass2(&filt_lowPass, &filt_highPass);
        derivative2(&filt_highPass, &filt_derivPass);
        squaring2(&filt_derivPass, &filt_sqrPass);
        mwInt2(&filt_sqrPass, &filt_mwiPass);


        // Reading data from filtered buffer
        int currentFilter = readData(&filt_mwiPass, 0);
        printf("Current filter %i\n", currentFilter);

        data = getNextData(file);
        i++;
    }
    printf("main::Received termination value: %i\n", data);
    printf("main::Ran %i times\n", i);

    return 0;
}

