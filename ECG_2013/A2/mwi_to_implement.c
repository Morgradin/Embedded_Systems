int mwInt2(BUFFER* inputBuffer, BUFFER* filtered) {
    /*
     *  GroupDelay: 72.5 ms
     */

    int N = 30;

    // Dynamic Retrieving of values
    int i = 0;
    int sum = 0;

    for (i = 0; i < N; i++) {
        sum += readData(inputBuffer, i);
    }

    // Filter math
    int y = sum / N;

    // Pushing data back to buffer object
    pushData(filtered, y);

    return 0;
}