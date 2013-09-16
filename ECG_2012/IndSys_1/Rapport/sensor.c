/*
 * Created by Jacob Gjerstrup, s113440 and Bastian Buch, s113432
 */
#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(FILE *file){
	int i1=0;
	//The if-sentence below checks if the file actually exists.
	//If it doesn't, a print statement is sent.
	if( file== NULL){
		printf("couldnt open file");
		return 0;
	}

	// Scans the next number in the file, then returns it.
	fscanf(file,"%i",&i1);
	return i1;
}
