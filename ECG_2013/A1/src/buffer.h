#define BUFFERSIZE 50

typedef struct {
    int Data[BUFFERSIZE];
    unsigned int counter;
} Buffer;


int pushData(Buffer* buffer, int data);
void incrementCounter(Buffer* buffer);
int getIndex(Buffer* buffer, int offset);
int readData(Buffer* buffer, int offset);

int lowPass2(Buffer* inputBuffer, Buffer* filtered);
int highPass2(Buffer* inputBuffer, Buffer* filtered);
int derivative2(Buffer* inputBuffer, Buffer* filtered);
int squaring2(Buffer* inputBuffer, Buffer* filtered);
int mwInt2(Buffer* inputBuffer, Buffer* filtered);
