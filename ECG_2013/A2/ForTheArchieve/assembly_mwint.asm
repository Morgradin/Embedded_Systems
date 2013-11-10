"// Data is supplied by software at two predefined memory locations."
"// One for the latest sensor input and another for the the datapoint being 30 values old."
MOVE R1 R0
MOVE R2 R0					"// container for old value"
MOVE R3 R0                  "// Accumulator"
MOVE R4 R0                  "// data address, first sample"
MOVE R5 R0                  "// temp calculation container"

"// Loading latest data and oldest data (30 steps back)"
LOAD R1 R4      			"//loads value of latest data point"
SUBI R5 R4 30               "If R5 gets to be lower than R4 it means that the procedure hasn't yet run 30 times"
BILT R0 R5 14               "// Branch If Larger Than: If (R4 > R5) goto 14"
MOVE R2 R0                  "// Old value = 0"
BRCH 17
LOAD R2 R5                  "// Load datapoint 30 values old"

"// Updating accumulator"
ADD R3 R3 R1
SUB R3 R3 R2

"// Dividing by 30'ish"
MULI R5 R3 4369
SHRI R5 R4 17
STRE [output] R5
ADDI R4 R4 1
BRCH 8


"// Instruction set"
LOAD    [Reg] [Mem]         
STRE    [Mem] [Reg]         
MOVE    [Reg] [Reg]         :: Implemented

ADD     [Reg] [Reg] [Reg]   :: implemented
SUB     [Reg] [Reg] [Reg]   :: implemented

ADDI    [Reg] [Reg] [Num]   :: implemented
SUBI    [Reg] [Reg] [Num]	:: implemented
SHRI 	[Reg] [Reg] [Num]   :: implemented
MULI 	[Reg] [Reg] [Num]   :: implemented

BILT    [Reg] [Reg] [Num]   // Branch If Larger Than
BRCH    [Num]               // Branch
