/*
 * RPeakDetection.c
 *
 *  Created on: 26/09/2012
 *      Author: Bastian
 */

#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

void findPeaks(int (*peaks)[1500][2], int data[]) {

	int peakPos = 0, i=0;

	for (i = 0; i < 2999; i++) {
		if (data[i-1] > data[(i - 2)] && data[i-1] > data[i]) {
			(*peaks)[peakPos][0] = data[i-1];
			(*peaks)[peakPos][1] = i-1;
			if(data[i-1] > 4000) printf("%d at %d with pos %d\n"
					, data[i-1], peakPos, i);
			peakPos++;
		}
	}
}


int calculateRRAverage(int (*RRArray)[8], int *pos) {
	if (*pos>8){
		return (((*RRArray)[0] + (*RRArray)[1] + (*RRArray)[2]
		        + (*RRArray)[3] + (*RRArray)[4] + (*RRArray)[5]
		        + (*RRArray)[6] + (*RRArray)[7]) / 8);
	}
	else{
		return (((*RRArray)[0] + (*RRArray)[1] + (*RRArray)[2] +
				(*RRArray)[3] + (*RRArray)[4] + (*RRArray)[5]
				+ (*RRArray)[6] + (*RRArray)[7]) / *pos);
	}


}

void Searchback(int *spkf, int *npkf, int *threshold1,
		int *threshold2, int RR, int *RR_low, int *RR_high,
		int *RR_miss, int *counter1, int (*RRArray1)[8],
		int *RRAverage1, int (*peaks)[1500][2], int *lastPeak,
		int *totalPeakCounter) {
	int i = 0;
	for (i = *totalPeakCounter; i >= 0; i--) {
		if ((*peaks)[i][0] > *threshold2) {
			(*RRArray1)[(*counter1 % 8)] = RR;
			*counter1 = *counter1 + 1;
			*RRAverage1 = calculateRRAverage(RRArray1,counter1);
			*lastPeak = (*peaks)[i][0];
			*RR_low = (0.92 * *RRAverage1);
			*RR_high = (1.16 * *RRAverage1);
			*RR_miss = (1.66 * *RRAverage1);
			*spkf = ((*peaks)[i][0]/4) + ((*spkf * 3)/4);
			*threshold1 = *npkf + ((*spkf - *npkf) / 4);
			*threshold2 = (*threshold1 / 2);
<<<<<<< .mine			printf("Peak = %d / Peaktime = %d / RRlow = %d / "
					"RRhigh = %d / RR = %d\n",(*peaks)[i][0],
					(*peaks)[(i)][1]+1, *RR_low, *RR_high, RR);
=======			printf("Peak = %d / Peaktime = %d / RRlow = %d / RRhigh = %d / RR = %d / Threshold1 = %d\n",(*peaks)[i][0],(*peaks)[i][1]+1, *RR_low, *RR_high, RR, *threshold1);
			*lastPeak = (*peaks)[i][1];
>>>>>>> .theirs			break;
			}
		}
	}

void calculateRR(int *spkf, int *npkf, int *threshold1,
		int *threshold2, int *RR_low, int *RR_high,
		int *RR_miss, int *counter1, int *counter2,
		int (*RRArray1)[8], int (*RRArray2)[8], int *RRAverage1,
		int *RRAverage2, int (*peaks)[1500][2], int *lastPeak,
		int *lastRPeak, int *RRMissCounter,int *totalRR,
		int *irregularHeartbeat, int *totalPeakCounter) {
	(*peaks)[20][0] = 5000;
	int i = 0;
	for (i = 0; i < 1500; i++) {
<<<<<<< .mine		if((*peaks)[i][0] > 4000) printf("Peak at %d with "
			"value %d to SPKF %d\n",i,(*peaks)[i][0]), *spkf;
=======>>>>>>> .theirs		if (*RRMissCounter >= 5) {
			(*irregularHeartbeat) = 1;
		}
		*totalPeakCounter = *totalPeakCounter + 1;
		// peak = treshold is not specified in assignment;
		// assuming not Rpeak due to danger of false negative
		if ((*peaks)[i][0] > *threshold1) {
			// to convert RR to seconds divide with 250, as
			//this is the sample rate per second
			int RR = (((*peaks)[i][1]-*lastPeak)*1000/250);
			//1000 to convert 1s to ms and 250 because that's
			//how many calculations per minute we do.
			if (RR > *RR_low && RR < *RR_high) {
				(*RRArray1)[*counter1 % 8] = RR;
				*counter1 = *counter1 + 1;
				*RRAverage1 = calculateRRAverage(RRArray1,
						counter1);
				// since RR misses have to be consecutive,
				//the counter is reset
				*RRMissCounter = 0;
				(*RRArray2)[((*counter2) % 8)] = RR;
				*counter2 = *counter2 + 1;
				*RRAverage2 = calculateRRAverage(RRArray2,
						counter2);
				*lastRPeak = (*peaks)[i][0];
				*RR_low = (0.92 * *RRAverage2);
				*RR_high = (1.16 * *RRAverage2);
				*RR_miss = (1.66 * *RRAverage2);
<<<<<<< .mine				*spkf = (((*peaks)[i][0] * 0.125) +
						(spkf * 0.875));
=======				*spkf = (((*peaks)[i][0]/8) + ((*spkf * 7)/8));
>>>>>>> .theirs				*threshold1 = (*npkf + ((*spkf - *npkf) / 4));
				*threshold2 = ((*threshold1) / 2);
				*totalRR = *totalRR + RR;
				printf("Peak = %d / Peaktime = %d / RRlow = %d / "
						"RRhigh = %d / RR = %d / Threshold1 = "
						"%d\n",(*peaks)[i][0],(*peaks)[i][1]+1,
						*RR_low, *RR_high, RR, *threshold1);
				*lastPeak = (*peaks)[i][1];
			} else if (RR <= *RR_miss) {
				*RRMissCounter = *RRMissCounter + 1;
			} else if (RR > *RR_miss) {
				*RRMissCounter = *RRMissCounter + 1;
				Searchback(spkf, npkf, threshold1, threshold2,
						RR, RR_low, RR_high, RR_miss, counter1,
						RRArray1, RRAverage1, peaks, lastPeak,
						totalPeakCounter);
			}
		} else {
			*npkf = (((*peaks)[i][0] + 7 * *npkf) / 8);
			*threshold1 = *npkf + ((*spkf - *npkf) / 4);
			*threshold2 = ((*threshold1) / 2);
		}
	}
}
