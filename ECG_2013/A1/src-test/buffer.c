#include <stdio.h>
#include "buffer.h"

// Bufferindex
int pushData(BUFFER* buffer, int data)
{
    //printf("Buffer::pushData: Adding stuff to the buffer!: %i\n", data);
    (*buffer).Data[(*buffer).counter] = data;
    incrementCounter(buffer);

    return 0;
}


// Getting values based on index offset
// compared to current buffer counter
int readData(BUFFER* buffer, int offset)
{
    int index = getIndex(buffer, offset);

    //printf("Buffer::readData - offset: %i\n", offset);
    //printf("  Index: %i\n", index);
    //printf("  Value - Buffer[index]: %i\n", buffer[index]);

    return (*buffer).Data[index];
}


void incrementCounter(BUFFER* buffer)
{
    (*buffer).counter++;
    if ((*buffer).counter >= BUFFERSIZE) {
        //printf("Buffer::IncrementCounter - Buffer reached maximum. Looping\n");
        (*buffer).counter -= BUFFERSIZE;
    }
}


int getIndex(BUFFER *buffer, int offset) {
    int index = (*buffer).counter - offset -1;
    if (index < 0){
        index = index+BUFFERSIZE;
    }

    return index;
}








/********** PEAK buffer *************/
int peak_pushData(PEAKBUFFER* buffer, int data)
{
    (*buffer).Data[(*buffer).counter] = data;
    peak_incrementCounter(buffer);

    return 0;
}


int peak_readData(PEAKBUFFER* buffer, int offset)
{
    int index = peak_getIndex(buffer, offset);
    return (*buffer).Data[index];
}


void peak_incrementCounter(PEAKBUFFER* buffer)
{
    (*buffer).counter++;
    if ((*buffer).counter >= PEAKBUFFERSIZE) {
        (*buffer).counter -= PEAKBUFFERSIZE;
    }
}


int peak_getIndex(PEAKBUFFER *buffer, int offset) {
    int index = (*buffer).counter - offset -1;
    if (index < 0){
        index = index+PEAKBUFFERSIZE;
    }

    return index;
}
