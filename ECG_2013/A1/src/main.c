#include <stdio.h>
#include "buffer.h"
#include "sensor.h"

Buffer sensorData = {{0}, 0};
Buffer filteredData = {{0}, 0};

int main()
{
    static const char filename[] = "DataFiles/ECG.txt";
    FILE *file = fopen ( filename, "r");

    int data = getNextData(file);

    while(data != INT_MAX) {

        //printf("Data read from file: %d\n", data);
        pushData(&sensorData, data);
        pushData(&filteredData, data+200);


        // Reading data from sensor buffer
        int currentSensor = readData(&sensorData, 0);
        int previousSensor = readData(&sensorData, 3);
        printf("Current sensor %i\nPrevious sensor %i\n", currentSensor, previousSensor);

        // Reading data from filtered buffer
        int currentFilter = readData(&filteredData, 0);
        int previousFilter = readData(&filteredData, 3);
        printf("Current filter %i\nPrevious filter %i\n", currentFilter, previousFilter);

        data = getNextData(file);
    }
    printf("last data value: %d\n", data);

    return 0;
}

