#define BUFFERSIZE 50
#define PEAKBUFFERSIZE 500

typedef struct {
    int Data[BUFFERSIZE];
    unsigned int counter;
} BUFFER;

int pushData(BUFFER* buffer, int data);
void incrementCounter(BUFFER* buffer);
int getIndex(BUFFER* buffer, int offset);
int readData(BUFFER* buffer, int offset);

int lowPass2(BUFFER* inputBuffer, BUFFER* filtered);
int highPass2(BUFFER* inputBuffer, BUFFER* filtered);
int derivative2(BUFFER* inputBuffer, BUFFER* filtered);
int squaring2(BUFFER* inputBuffer, BUFFER* filtered);
int mwInt2(BUFFER* inputBuffer, BUFFER* filtered);
