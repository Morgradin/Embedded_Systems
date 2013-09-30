#define BUFFERSIZE 50
#define PEAKBUFFERSIZE 500

typedef struct {
    int Data[BUFFERSIZE];
    unsigned int counter;
} BUFFER;

typedef struct {
    int Data[PEAKBUFFERSIZE];
    unsigned int counter;
} PEAKBUFFER;


int pushData(BUFFER* buffer, int data);
void incrementCounter(BUFFER* buffer);
int getIndex(BUFFER* buffer, int offset);
int readData(BUFFER* buffer, int offset);


int peak_pushData(PEAKBUFFER* buffer, int data);
void peak_incrementCounter(PEAKBUFFER* buffer);
int peak_getIndex(PEAKBUFFER* buffer, int offset);
int peak_readData(PEAKBUFFER* buffer, int offset);




int lowPass2(BUFFER* inputBuffer, BUFFER* filtered);
int highPass2(BUFFER* inputBuffer, BUFFER* filtered);
int derivative2(BUFFER* inputBuffer, BUFFER* filtered);
int squaring2(BUFFER* inputBuffer, BUFFER* filtered);
int mwInt2(BUFFER* inputBuffer, BUFFER* filtered);
