/*
 * RPeakDetection.h
 *
 *  Created on: 02/10/2012
 *      Author: Bastian
 */

#ifndef RPEAKDETECTION_H_
#define RPEAKDETECTION_H_

void findPeaks(int (*peaks)[1500][2], int data[]);

/*
int calculateRRAverage(int RRArray[]);
int calculateRRAverage(int RRArray[]);
void Searchback(int *spkf, int *threshold1, int *threshold2, int RR,
		int *RR_low, int *RR_high, int *RR_miss, int *counter1, int (*RRArray1),
		int *RRAverage1, int (*peaks)[][], int *lastPeak);
void calculateRR(int *spkf, int *npkf, int *threshold1, int *threshold2,
		int *RR_low, int *RR_high, int *RR_miss, int *counter1, int *counter2,
		int (*RRArray1)[], int (*RRArray2)[], int *RRAverage1, int *RRAverage2,
		int (*peaks)[][], int *lastPeak, int lastRPeak, int *RRMissCounter,
		int *totalRR, int *irregularHeartbeat);
*/
#endif /* RPEAKDETECTION_H_ */

