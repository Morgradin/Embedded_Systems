/*
 * Todo:
 *  Restricting speed to 250 requests pr second
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

// returning INT16_MAX will terminate main loop.
int getNextData(FILE *file){

    signed int line = 0;
    if( file == NULL){
        printf("sensor.c::getNextData - couldnt open file. Terminating\n");
        return INT16_MAX;
    }

    fscanf(file,"%i",&line);

    if (feof(file)) {
        //printf("sensor.c::getNextData - Reached EOF. Terminating\n");
        fclose(file);
        return INT16_MAX;
    }
    return line;
}
