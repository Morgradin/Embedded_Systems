#include <stdio.h>
#define BUFFERSIZE 50
#include "buffer.h"

unsigned int counter = 0;
int buffer[BUFFERSIZE] = {0};


// Bufferindex
int pushData(int data)
{
    printf("Buffer::pushData: Adding stuff to the buffer!: %i\n", data);
    buffer[counter] = data;
    incrementCounter();

    return 0;
}


// Getting values based on index offset
// compared to current buffer counter
int readData(int offset)
{
    int index = getIndex(offset);

    //printf("Buffer::readData - offset: %i\n", offset);
    //printf("  Index: %i\n", index);
    //printf("  Value - Buffer[index]: %i\n", buffer[index]);

    return buffer[index];
}


void incrementCounter()
{
    counter = counter+1;
    if (counter >= BUFFERSIZE) {
        printf("Buffer::IncrementCounter - Buffer reached maximum. Looping\n");
        counter = counter-BUFFERSIZE;
    }
}


int getIndex(int offset) {
    int index = counter - offset -1;
    if (index < 0){
        index = index+BUFFERSIZE;
    }

    return index;
}
