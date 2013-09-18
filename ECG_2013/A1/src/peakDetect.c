#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sensor.h"


int isPeak(int dataPointOne, int dataPointTwo, int dataPointThree){
    if (dataPointOne < dataPointTwo && dataPointTwo > dataPointThree){
        return 1;
	}
    return 0;
}

void searchForPeaks(int dataset[]){
    int i=0, j=0, datasetLength=0;
	int data[10000]={0}; //replace with actual data structure for peak storing
	datasetLength = sizeof(dataset)/sizeof(int);
	for (i=1; i<datasetLength; i++){
		if(isPeak(dataset[i-1], dataset[i], dataset[i+1])){
			data[j]=dataset[i];
			j++;
		}
	}
}
