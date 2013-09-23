#ifndef ADD_H_GUARD
#define ADD_H_GUARD
#define INT16_MAX 1 << 16

int getNextData(FILE *file);

// remove us before handing in
void testLow();
void testHigh();
void testDerivative();
void testSquaring();
void testMWI();

void searchForPeaks(int dataset[]);
int isPeak(int dataPointOne, int dataPointTwo, int dataPointThree);
#endif
