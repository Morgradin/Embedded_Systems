int mwInt2(int* accum, int* latest, int* old, BUFFER* filtered) {
    /*
     *  GroupDelay: 72.5 ms
     */


    // Dynamic Retrieving of values
    &accu += &latest;
    &accu -= &old;

    // Filter math
    int y = &accu / 30;

    // Pushing data back to buffer object
    pushData(filtered, y);

    return 0;
}