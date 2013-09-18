/*
 * Created by Jacob Gjerstrup, s113440 and Bastian Buch, s113432
 */
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

int getNextData(FILE *file){

    // Handling data delivery speed.
    // Throttling down to 250 requests per second.. guess the sensor should be the limiting factor
    /*clock_t start, end;
    double cpu_time_used;
    start = clock();
    end = clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("Time spent on entire program: %f", cpu_time_used);
    */


    int line=0;
	//The if-sentence below checks if the file actually exists.
	//If it doesn't, a print statement is sent.
    if( file == NULL){
		printf("couldnt open file");
        return 0;
	}

	// Scans the next number in the file, then returns it.
    fscanf(file,"%i",&line);
    return line;
}
