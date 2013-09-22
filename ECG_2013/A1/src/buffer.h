#define BUFFERSIZE 50

typedef struct {
    int Data[BUFFERSIZE];
    unsigned int counter;
} Buffer;

int pushData(Buffer* buffer, int data);
void incrementCounter(Buffer* buffer);
int getIndex(Buffer* buffer, int offset);
int readData(Buffer* buffer, int offset);

