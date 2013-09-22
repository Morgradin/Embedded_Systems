#ifndef ADD_H_GUARD
#define ADD_H_GUARD
#define INT_MAX 1 << 16

int getNextData(FILE *file);
int lowPass(int x[], int y[], int pos);
int highPass (int x[], int y[], int pos);
int movingWindowIntegration(int x[], int y[], int pos);
int derivative(int x[], int y[], int pos);
int squaring(int value);

// remove us before handing in
void testLow();
void testHigh();
void testDerivative();
void testSquaring();
void testMWI();

void searchForPeaks(int dataset[]);
int isPeak(int dataPointOne, int dataPointTwo, int dataPointThree);
#endif
