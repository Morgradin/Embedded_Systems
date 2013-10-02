#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int main (void){
	static const char filename[] = "ECG.txt";
	FILE *file = NULL;
	file = fopen ( filename, "r" );
	int Data[50]={0}, FilteredData[50]={0}, i=0;

	for (i=0;i<3;i++){
		Data[i] = getNextData(file);
	}

	//Closes the file, as we no longer need to read from it, then prints the highest value and stops the program.
	fclose(file);
	return 0;
}
