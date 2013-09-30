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
    return (*buffer).Data[index];
}


void incrementCounter(BUFFER* buffer)
{
    (*buffer).counter++;
    if ((*buffer).counter >= BUFFERSIZE) {
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



