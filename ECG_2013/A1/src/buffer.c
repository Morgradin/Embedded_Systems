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
    incrementIndex();

    return 0;
}


// Getting values based on index offset compared to current buffer counter
int read(int offset)
{

}

void incrementIndex()
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
