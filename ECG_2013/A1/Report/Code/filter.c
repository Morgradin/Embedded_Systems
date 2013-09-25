#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"



int lowPass2(BUFFER* inputBuffer, BUFFER* filtered) {
    /*
     *  GroupDelay: 25 ms
     */

    // Retrieving values
    int x = readData(inputBuffer, 0);
    int x6 = readData(inputBuffer, 6);
    int x12 = readData(inputBuffer, 12);
    int y1 = readData(filtered, 0);
    int y2 = readData(filtered, 1);

    // Filter math
    int y = (2*y1-y2) + ((x - 2*x6 + x12) / 32);

    // pushing data back to buffer object
    pushData(filtered, y);

    return 0;
}


int highPass2(BUFFER* inputBuffer, BUFFER* filtered) {
    /*
     *  GroupDelay: 80 ms
     */

    // Retrieving values
    int x = readData(inputBuffer, 0);
    int x16 = readData(inputBuffer, 16);
    int x17 = readData(inputBuffer, 17);
    int x32 = readData(inputBuffer, 32);
    int y1 = readData(filtered, 0);

    // Filter math
    int y = y1-(x/32)+x16-x17+(x32/32);

    // Pushing data back to buffer object
    pushData(filtered, y);

    return 0;
}


int derivative2(BUFFER* inputBuffer, BUFFER* filtered) {
    /*
     *  GroupDelay: 10 ms
     */

    // Retrieving values
    int x = readData(inputBuffer, 0);
    int x1 = readData(inputBuffer, 1);
    int x3 = readData(inputBuffer, 3);
    int x4 = readData(inputBuffer, 4);

    // Filter math
    int y = (2*x+x1-x3-2*x4) / 8;

    // Pushing data back to buffer object
    pushData(filtered, y);

    return 0;
}


int squaring2(BUFFER* inputBuffer, BUFFER* filtered) {
    /*
     *  GroupDelay: 0 ms
     */

    // Retrieving values
    int x = readData(inputBuffer, 0);

    // Filter math
    int y = x*x;

    // Pushing data back to buffer object
    pushData(filtered, y);

    return 0;
}


int mwInt2(BUFFER* inputBuffer, BUFFER* filtered) {
    /*
     *  GroupDelay: 72.5 ms
     */

    int N = 30;

    // Dynamic Retrieving of values

    int i = 0;
    int sum = 0;

    for (i = N; i >= 0; --i) {
        sum += readData(inputBuffer, i);
    }

    // Filter math
    int y = sum / N;

    // Pushing data back to buffer object
    pushData(filtered, y);

    return 0;
}
