// input enten array of counter eller 30 separate vaerdier
LOAD R0 31 					// loading Counter value: 30
LOAD R1 32 					// Loading Subtractor value: -1
LOAD R4 memAddress			// Mem Address of first datapoint (array pointer)
LOAD R2 R4					// getting first value of datapoints
LOAD R3 33 					// Initialising Sum: 0


// loop through 30 elements and add them together
ADD R3 R3 R2 				// Doing the sum
ADD R0 R0 R1 				// subtracting from counter (adding -1)
BZERO 21 					// Breaking out. Pointing to division by 30
ADD R4 1
LOAD R2 R4
LOAD R2 nextValue 			// Loading next value from buffer
BRANCH 8



// divide by 30: multiply by 4369 and bitshift >> 17. Close enough
LOAD R0 34 					// Overwriting counter - Now multiplier: 4369
LOAD R1 35 					// Overwriting subtractor - Now bitshift value: 17
MUL R3 R3 R0 				// multiply by 4369
SHRW R1 R3 					// bitshift R3 >> 17... should be signed
STORE R3 outputAddress
HALT




30
-1
0
4369
17



// Instruction set
LOAD
ADD
STORE
BRANCH
BZERO
SHRW 	// bitshift right
MUL 	// Multiply