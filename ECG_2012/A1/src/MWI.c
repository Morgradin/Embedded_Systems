#include <stdio.h>
#include <stdlib.h>

int getNextData(FILE *file){
	int i1=0;
	//The if-sentence below checks if the file actually exists.
	//If it doesn't, a print statement is sent.
	if( file== NULL){
		printf("couldnt open file");
		return 0;
	}

	// Scans the next number in the file, then returns it.
	fscanf(file,"%i",&i1);
	return i1;
}

int movingWindowIntegration(int x[], int y[], int pos){
	int i=0;
	for (i=30;i>=1;i--){
		y[pos]+=((x[pos-(30-i)])/30);
	}

	return y[pos];
}

void testMWI(){
	static const char filename[] = "x_sqr.txt";
	FILE *file = NULL;
	file = fopen ( filename, "r" );
	static const char filename2[] = "x_mwi.txt";
	FILE *file2 = NULL;
	file2 = fopen ( filename2, "r" );
	int Data[3000]={0}, FilteredData[3000]={0},
			checkData[3000]={0}, i=0;

	for (i=0;i<3000;i++){
		Data[i] = getNextData(file);
		checkData[i]=getNextData(file2);
		FilteredData[i] = movingWindowIntegration(
				Data, FilteredData, i);
	}

	for (i=0;i<3000;i++){
		if (checkData[i]!=FilteredData[i]){
			printf("Error in line %d.\n"
				"Value was supposed to be %d, but was %d"
				"\n", i, checkData[i], FilteredData[i]);
		}
	}
	printf("\nIf no errors were found, everything's good.\n\n");
	/*
	 * Closes the file, as we no longer need to read from it,
	 * then prints the highest value and stops the program.
	 */
	fclose(file);
}

int main(void){
	testMWI();
}