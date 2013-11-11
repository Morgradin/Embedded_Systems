"// Assembly code //"
"Initiating registers"
 0 MOVE R1 R0		
 1 MOVE R2 R0
 2 MOVE R3 R0
 3 MOVE R4 R0
 4 MOVE R5 R0
"Loading datapoint from R4"
 5 LOAD R1 R4
"If R4 is larger than 30 load old value at R4-30"
"else use 0 as old sample value"
 6 SUBI R5 R4 30	
 7 BILT R5 R0 10
 8 MOVE R2 R0
 9 BRCH 11
10 LOAD R2 R5
"Accumulate values. Add latest sample, subtrack oldest"
11 ADD R3 R3 R1
12 SUB R3 R3 R2
"Divide by 30. Approximate by (x*4369)>>17"
13 MULI R5 R3 4369
14 SHRI R5 R5 17
"Store value"
15 STRE R5
"Increment sample address and repeat from line 5"
16 ADDI R4 R4 1
17 BRCH 5


"// Instruction set"
LOAD    [Reg] [Mem]         
STRE    [Mem] [Reg]         
MOVE    [Reg] [Reg]         

ADD     [Reg] [Reg] [Reg]   
SUB     [Reg] [Reg] [Reg]   

ADDI    [Reg] [Reg] [Num]   
SUBI    [Reg] [Reg] [Num]	
SHRI 	[Reg] [Reg] [Num]   
MULI 	[Reg] [Reg] [Num]   

BILT    [Reg] [Reg] [Num]   
BRCH    [Num]               
