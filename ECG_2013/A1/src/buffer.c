#include <stdio.h>
#define BUFFERSIZE 50
#include "buffer.h"

unsigned int counter = 0;
int buffer[BUFFERSIZE] = {0};


// Bufferindex
int push(int data)
{
    printf("Adding stuff to the buffer!\n");
    buffer[counter] = data;
    incrementCounter();

    return 0;
}


// Getting values based on index offset
// compared to current buffer counter
int read(int offset)
{
    int index = getIndex(offset);

    printf("buffer::read - offset: %i\n", offset);
    printf("Index: %i\n", index);
    printf("Buffer[index]: %i\n", buffer[index]);

    return buffer[index];
}


void incrementCounter()
{
    counter = counter+1;
    if (counter >= BUFFERSIZE) {
        counter = counter-BUFFERSIZE;
    }
}


int getIndex(int offset) {
    int index = counter + offset;
    if (index >= BUFFERSIZE){
        index = index-BUFFERSIZE;
    }
    else if (index < 0) {
        index = index + BUFFERSIZE;
    }

    return index;
}
