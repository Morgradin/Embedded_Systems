#include <stdio.h>
#include "buffer.h"

// Bufferindex
int pushData(Buffer* buffer, int data)
{
    printf("Buffer::pushData: Adding stuff to the buffer!: %i\n", data);
    (*buffer).Data[(*buffer).counter] = data;
    incrementCounter(buffer);

    return 0;
}


// Getting values based on index offset
// compared to current buffer counter
int readData(Buffer* buffer, int offset)
{
    int index = getIndex(buffer, offset);

    //printf("Buffer::readData - offset: %i\n", offset);
    //printf("  Index: %i\n", index);
    //printf("  Value - Buffer[index]: %i\n", buffer[index]);

    return (*buffer).Data[index];
}


void incrementCounter(Buffer* buffer)
{
    (*buffer).counter++;
    if ((*buffer).counter >= BUFFERSIZE) {
        printf("Buffer::IncrementCounter - Buffer reached maximum. Looping\n");
        (*buffer).counter -= BUFFERSIZE;
    }
}


int getIndex(Buffer *buffer, int offset) {
    int index = (*buffer).counter - offset -1;
    if (index < 0){
        index = index+BUFFERSIZE;
    }

    return index;
}
