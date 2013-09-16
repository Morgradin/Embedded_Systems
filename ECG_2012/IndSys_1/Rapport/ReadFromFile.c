/*
 * Created by Jacob Gjerstrup, s113440 and Bastian Buch, s113432
 */
#include <stdio.h>

int main (void){

	/*
	 * Creates an array with the filename. Then, it initiates the
	 * file to Null, and then opens the file. Also initiates
	 * other variables used for the calculations
	 */
	int i1=0, temp=0;
	static const char filename[] = "ECG.txt";
	FILE *file = NULL;
	file = fopen ( filename, "r" );

	/*
	 * The if-sentence below checks if the file actually exists.
	 * If it doesn't, a print is made.
	 */
	if( file== NULL){
		printf("Couldn't open the file - name is incorrect");
		return 0;
	}

	/*
	 * Scans the initial number, and then a while loop proceeds
	 * to scan and check the rest of the numbers.
	 */
	fscanf(file,"%i",&i1);
	while (fscanf(file,"%i",&temp)>0){
		fscanf(file,"%i",&temp);

		if (temp>i1){
			i1=temp;
		}
	}

	/*
	 * Closes the file, as we no longer need to read from it,
	 * then prints the highest value and stops the program.
	 */

	fclose(file);
	printf("The highest number is: %d",i1);
	return 0;
}
