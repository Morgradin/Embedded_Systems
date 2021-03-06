/*
 * RPeakTest.c
 *
 *  Created on: 03/10/2012
 *      Author: Bastian
 */

#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "RPeakDetection.h"


void findPeakTest(int (*peaks)[1500][2]) {

	static const char filename[] = "x_mwi.txt";
	FILE *file = NULL;
	file = fopen(filename, "r");
	int data[3000] = { 0 }, i = 0;

	for (i = 0; i < 3000; i++) {
		data[i] = getNextData(file);
	}

	findPeaks(peaks, data);
}

int main (void){
	int peaks[1500][2] = {0,0};
	int (*peaks_pointer)[1500][2] = &peaks;
	int spkf = 0;
	int npkf = 0;
	int threshold1 = 0;
	int threshold2 = 0;
	int RR_low = 0;
	int RR_high = 999999;
	int RR_miss = 0;
	int counter1 = 0;
	int counter2 = 0;
	int RRArray1[8] = { 0 };
	int RRArray2[8] = { 0 };
	int RRAverage1 = 0;
	int RRAverage2 = 0;
	int lastPeak = 0;
	int lastRPeak = 0;
	int RRMissCounter = 0;
	int totalRR = 0;
	int irregularHeartbeat = 0;
	int *spkf_pointer = &spkf;
	int *npkf_pointer = &npkf;
	int *threshold1_pointer = &threshold1;
	int *threshold2_pointer = &threshold2;
	int *RR_low_pointer = &RR_low;
	int *RR_high_pointer = &RR_high;
	int *RR_miss_pointer = &RR_miss;
	int *counter1_pointer = &counter1;
	int *counter2_pointer = &counter2;
	int (*RRArray1_pointer)[8] = &RRArray1;
	int (*RRArray2_pointer)[8] = &RRArray2;
	int *RRAverage1_pointer = &RRAverage1;
	int *RRAverage2_pointer = &RRAverage2;
	int *lastPeak_pointer = &lastPeak;
	int *lastRPeak_pointer = &lastRPeak;
	int *RRMissCounter_pointer = &RRMissCounter;
	int *totalRR_pointer = &totalRR;
	int *irregularHeartbeat_pointer = &irregularHeartbeat;
	int totalPeakCounter = 0;
	int *totalPeakCounter_pointer = &totalPeakCounter;

	int input=1;
	findPeakTest(peaks_pointer);
	calculateRR( spkf_pointer, npkf_pointer, threshold1_pointer, threshold2_pointer, RR_low_pointer, RR_high_pointer, RR_miss_pointer,
			counter1_pointer, counter2_pointer, RRArray1_pointer, RRArray2_pointer, RRAverage1_pointer, RRAverage2_pointer, peaks_pointer,
			lastPeak_pointer, lastRPeak_pointer, RRMissCounter_pointer, totalRR_pointer, irregularHeartbeat_pointer, totalPeakCounter_pointer);
	printf("rraverage=%d",*RRAverage1_pointer);
	/*
	printf("Latest R-peak: %d. Latest R-peak at: %d seconds.\nHeartbeats per minute: %d. Warnings:/n", lastRpeak, totalRR/250, totalPeaks);
	if (lastRPeak <= 2000) printf("Weak heartbeat./n");
	if (RRMissCounter >= 5) printf("Irregular heartbeat./n");
	if (RRMissCounter < 5 && lastRPeak > 2000) printf("No warnings.");
	printf("/n/nPress 0 to exit.");
	scanf("%d", &input);*/

	return 0;
}
