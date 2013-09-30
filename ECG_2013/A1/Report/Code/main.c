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


int main()
{
    static const char filename[] = "DataFiles/ECG.txt";
    FILE *file = fopen ( filename, "r");

    int data = getNextData(file);
    int clock = 0;

    while(data != INT16_MAX) {

		pushData(&buff_sensorData, data);

        /******* Do filtering; ******/
        //  all filters tages an input buffer and output buffer and updates output in-place
        lowPass2(&buff_sensorData, &buff_lowPass);
        highPass2(&buff_lowPass, &buff_highPass);
        derivative2(&buff_highPass, &buff_derivPass);
        squaring2(&buff_derivPass, &buff_sqrPass);
        mwInt2(&buff_sqrPass, &buff_mwiPass);

        /******* Peak detection ******/
        if (clock > 7) {

            int samples[7] = {readData(&buff_mwiPass, 0),
                              readData(&buff_mwiPass, 1),
                              readData(&buff_mwiPass, 2),
                              readData(&buff_mwiPass, 3),
                              readData(&buff_mwiPass, 4),
                              readData(&buff_mwiPass, 5),
                              readData(&buff_mwiPass, 6)};
            RRcalculate(samples[3], samples, clock);
        }
        data = getNextData(file);
        clock++;
    }
    printf("main::Received termination value: %i\n", data);
    printf("main::Ran %i times\n", clock);

    return 0;
}

