#include <stdio.h>

int main(void)
{
    printf("Hey, I'm reading a file!\n");

    static const char filename[] = "ECG.txt";
    FILE *file = fopen ( filename, "r");
    int line, rVal;
    int max;

    rVal = fscanf(file, "%i", &line);
    max = line;

    while(rVal != EOF) {

        rVal = fscanf(file, "%i", &line);
        if (max < line) {
            printf("Found a new larger number: %i \n", line);
            max=line;
        }
    }
    printf("Finally, this is the largest numer: %i\n", max);
    return 0;
}

