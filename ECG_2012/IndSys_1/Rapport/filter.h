#ifndef ADD_H_GUARD
#define ADD_H_GUARD
int lowPass(int x[], int y[], int pos);
int highPass (int x[], int y[], int pos);
int movingWindowIntegration(int x[], int y[], int pos);
int derivative(int x[], int y[], int pos);
int squaring(int value);
#endif
