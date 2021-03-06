/*
 * Created by Jacob Gjerstrup, s113440
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sensor.h"

	/***********************************************************
	 * Initiate is what starts the entire program. It starts out
	 * with opening our initial data file, then it proceeds to
	 * create the arrays necessary for data treatment from raw
	 * data to filtered data.
	 *
	 * After the treatment of each data point, it checks if the
	 * loop has run for 49 times. If it has, it enters the while
	 * loop, in which all data points are moved one step
	 * backwards - thus ensuring that the last data point in the
	 * arrays are a duplication of the second-to-last, and thus
	 * free to be overwritten.
	 **********************************************************/
void initiate(){
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	static const char filename[] = "ECG.txt";
	FILE *file = NULL;
	int temp=0;
	file = fopen ( filename, "r" );
	int data[50]={0}, filt_Low[50]={0}, filt_High[50]={0},
			filt_Derivative[50]={0}, filt_Squaring[50]={0},
			filt_MWI[50]={0}, i=0, q=0;;

	while(!feof(file)){
		int j=0;
		data[i] = getNextData(file);

		filt_Low[i] = lowPass(data, filt_Low, i);
		filt_High[i] = highPass(filt_Low,
				filt_High, i);
		filt_Derivative[i] = derivative(filt_High,
				filt_Derivative, i);
		filt_Squaring[i] = squaring(
				filt_Derivative[i]);
		filt_MWI[i] = movingWindowIntegration(
				filt_Squaring, filt_MWI, i);
		if (i==49){
			for (j=0;j<50;++j){
				data[j]=data[j+1];
				filt_Low[j]=filt_Low[j+1];
				filt_High[j]=filt_High[j+1];
				filt_Derivative[j]=filt_Derivative[j+1];
				filt_Squaring[j]=filt_Squaring[j+1];
				filt_MWI[j]=filt_MWI[j+1];
			}
		}
		// Moves i one backwards in preparation for the
		// next run of the while loop
		if (i==49){
			i=48;
		}
		i++;
	}

	//Closes the file, as we no longer need to read from it
	fclose(file);

	end = clock();
	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("Time spent on entire program: %f",
			cpu_time_used);
}

int main (void){
	initiate();
	return 0;
}
