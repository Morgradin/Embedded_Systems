#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sensor.h"

void testLow(){

	// Starts a clock to check how long the lowpass filter takes
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	// Variable initialization
	FILE *file = fopen ( "/Datafiles/ECG.txt", "r" );
	FILE *file = fopen ( "/Datafiles/x_low.txt", "r" );
	int errorFound = 0;
	int Data[10000]={0}, FilteredData[10000]={0},
			checkData[10000]={0}, i=0;

	/*
	 *  The next two loops runs through the two files, stores the data, filters
	 *  it and compares it, showing errors if such are found
	 */
	for (i=0;i<10000;i++){
		Data[i] = getNextData(file);
		checkData[i]=getNextData(file2);
		FilteredData[i] = lowPass(Data, FilteredData, i);
	}

	for (i=0;i<10000;i++){
		if (checkData[i]!=FilteredData[i]){
			printf("Error in line %d.\n"
				"Value was supposed to be %d, but was %d"
				"\n", 1+i, checkData[i], FilteredData[i]);
			errorFound = 1;
		}
	}
	if (errorFound == 1){
		printf("\nIf no errors were found, everything's good.\n\n");
	}


	/*
	 * Closes the file, as we no longer need to read from it,
	 * then prints the highest value and stops the program.
	 */
	fclose(file);
	end = clock();
	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("Time spent on lowpass: %f",
			cpu_time_used);
}

void testHigh(){
	// Starts a clock to check how long the highpass filter takes
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	// Variable initialization
	FILE *file = fopen ( "/Datafiles/x_low.txt", "r" );
	FILE *file = fopen ( "/Datafiles/x_high.txt", "r" );
	int errorFound = 0;
	int Data[10000]={0}, FilteredData[10000]={0},
			checkData[10000]={0}, i=0;

	/*
	 *  The next two loops runs through the two files, stores the data, filters
	 *  it and compares it, showing errors if such are found
	 */
	for (i=0;i<1000;i++){
		Data[i] = getNextData(file);
		checkData[i]=getNextData(file2);
		FilteredData[i] = highPass(Data, FilteredData, i);
	}

	for (i=0;i<100;i++){
		if (checkData[i]!=FilteredData[i]){
			printf("Error in line %d.\n"
				"Value was supposed to be %d, but was %d"
				"\n", i, checkData[i], FilteredData[i]);
			errorFound = 1;
		}
	}
	if (errorFound == 1){
			printf("\nIf no errors were found, everything's good.\n\n");
		}
	/*
	 * Closes the file, as we no longer need to read from it,
	 * then prints the highest value and stops the program.
	 */
	fclose(file);
	end = clock();
	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("Time spent on highpass: %f",
			cpu_time_used);
}

void testDerivative(){
	// Starts a clock to check how long the derivative filter takes
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	// Variable initialization
	FILE *file = fopen ( "/Datafiles/x_high.txt", "r" );
	FILE *file = fopen ( "/Datafiles/x_der.txt", "r" );
	int errorFound = 0;
	int Data[10000]={0}, FilteredData[10000]={0},
			checkData[10000]={0}, i=0;

	/*
	 *  The next two loops runs through the two files, stores the data, filters
	 *  it and compares it, showing errors if such are found
	 */
	for (i=0;i<10000;i++){
		Data[i] = getNextData(file);
		checkData[i]=getNextData(file2);
		FilteredData[i] = derivative(Data, FilteredData, i);
	}

	for (i=0;i<10000;i++){
		if (checkData[i]!=FilteredData[i]){
			printf("Error in line %d.\n"
				"Value was supposed to be %d, but was %d"
				"\n", i, checkData[i], FilteredData[i]);
			errorFound = 1;
		}
	}
	if (errorFound == 1){
			printf("\nIf no errors were found, everything's good.\n\n");
	}
	/*
	 * Closes the file, as we no longer need to read from it,
	 * then prints the highest value and stops the program.
	 */
	fclose(file);
	end = clock();
	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("Time spent on derivative: %f",
			cpu_time_used);
}

void testSquaring(){
	// Starts a clock to check how long the squaring filter takes
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	// Variable initialization
	FILE *file = fopen ( "/Datafiles/x_der.txt", "r" );
	FILE *file = fopen ( "/Datafiles/x_sqr.txt", "r" );
	int errorFound = 0;
	int Data[10000]={0}, FilteredData[10000]={0},
			checkData[10000]={0}, i=0;

	/*
	 *  The next two loops runs through the two files, stores the data, filters
	 *  it and compares it, showing errors if such are found
	 */
	for (i=0;i<10000;i++){
		Data[i] = getNextData(file);
		checkData[i]=getNextData(file2);
		FilteredData[i] = squaring(Data[i]);
	}

	for (i=0;i<10000;i++){
		if (checkData[i]!=FilteredData[i]){
			printf("Error in line %d.\n"
				"Value was supposed to be %d, but was %d"
				"\n", i, checkData[i], FilteredData[i]);
			errorFound = 1;
		}
	}
	if (errorFound == 1){
			printf("\nIf no errors were found, everything's good.\n\n");
	}
	/*
	 * Closes the file, as we no longer need to read from it,
	 * then prints the highest value and stops the program.
	 */
	fclose(file);
	end = clock();
	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("Time spent on squaring: %f",
			cpu_time_used);
}

void testMWI(){
	// Starts a clock to check how long the MWI filter takes
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	// Variable initialization
	FILE *file = fopen ( "/Datafiles/x_sqr.txt", "r" );
	FILE *file = fopen ( "/Datafiles/x_mwi_div_after.txt", "r" );
	int errorFound = 0;
	int Data[10000]={0}, FilteredData[10000]={0},
			checkData[10000]={0}, i=0;

	/*
	 *  The next two loops runs through the two files, stores the data, filters
	 *  it and compares it, showing errors if such are found
	 */
	for (i=0;i<10000;i++){
		Data[i] = getNextData(file);
		checkData[i]=getNextData(file2);
		FilteredData[i] = movingWindowIntegration(
				Data, FilteredData, i);
	}

	for (i=0;i<10000;i++){
		if (checkData[i]!=FilteredData[i]){
			printf("Error in line %d.\n"
				"Value was supposed to be %d, but was %d"
				"\n", i, checkData[i], FilteredData[i]);
			errorFound = 1;
		}
	}
	if (errorFound == 1){
			printf("\nIf no errors were found, everything's good.\n\n");
	}
	/*
	 * Closes the file, as we no longer need to read from it,
	 * then prints the highest value and stops the program.
	 */
	fclose(file);
	end = clock();
	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("Time spent on MWI: %f",
			cpu_time_used);
}
