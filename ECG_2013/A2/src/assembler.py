#!/usr/bin/python
import sys

bitlength = 32
    
    
  
    
def asmToBin(asmLine):
    
    output = ""
    segs = asmLine.rstrip(" \n").split(" ")
    
    cmd = segs[0]
    
    if cmd=="LOAD":
        # mem location not yet implemented
        checkSegCount(segs, 2)
        
        output += "0001"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)
        output += zPad(19) # Mem location placeholder
        
        
    elif cmd=="STRE":
        # Not implemented. Only placeholders
        checkSegCount(segs, 2)
        
        output += "0010"
        output += zPad(3)
        output += zPad(3)
        output += zPad(3)
        output += zPad(19)
        
    elif cmd=="MOVE":
        checkSegCount(segs, 2)
        
        output += "0011"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += zPad(19)
        
    elif cmd=="ADDI":
        checkSegCount(segs, 3)
        
        output += "1000"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 19)
        
    elif cmd=="SUBI": # SUBI R1 R2 86587 -> R1 = R2 - 86587
        checkSegCount(segs, 3)
        
        output += "1001"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 19)
        
    elif cmd=="MULI":
        checkSegCount(segs, 3)
        
        output += "1010"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 19)
        
    elif cmd=="SHRI":
        checkSegCount(segs, 3)
        
        output += "1011"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 19)
        
    elif cmd=="BRCH":
        checkSegCount(segs, 1)
        output += "0100"
        output += zPad(3) # nothing on the registers
        output += zPad(3)
        output += zPad(3)
        output += numToBin(segs[1], 19)
        
    elif cmd=="BILT":
        checkSegCount(segs, 3)
        
        output += "0101"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 19)
        
    elif cmd=="ADD":
        checkSegCount(segs, 3)
        
        output += "1100"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += getRegBin(segs[3])
        output += zPad(19)
        
    elif cmd=="SUB":
        checkSegCount(segs, 3)
        
        output += "1101"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += getRegBin(segs[3])
        output += zPad(19)

    elif cmd=="NOP":
        # Not implemented. Only placeholders
        checkSegCount(segs, 0)
        
        output += "0000"
        output += zPad(3)
        output += zPad(3)
        output += zPad(3)
        output += zPad(19)
        
    else:
        raise Exception, "Cmd not recognized: " + cmd
        
    return output
        
        
def getRegBin(rString):
    if rString[0] == "R":
        regNum = int(rString[1:])
        binRepr = bin(regNum)[2:].zfill(3)
        return binRepr
    else:
        raise Exception, "Invalid format: string is not a register: " + rString
        
    
def numToBin(num, bitcount):
    return bin(int(num))[2:].zfill(bitcount)
    
def zPad(padding):
    return "".zfill(padding)
    
def checkSegCount(slist, required):
    if len(slist[1:]) != required:
        raise Exception, "Invalid number og arguments provided for this command: " + required + ", " + " ".join(slist)
        
        
def asmToHex_File(fin, fout):
    asm_file = open(fin, "r")
    lines = asm_file.readlines()
    asm_file.close()
    
    i = 0
    printString = ""
    for l in lines:
        binCode = asmToBin(l)
        
        if (len(binCode) > bitlength): # Debugging
            print("code is not correct length. '" + l + "', len = " + str(len(binCode)))
            
        hexCode = hex(int(binCode,2))[2:].strip("L")
        printString += str(i) + " " + hexCode.zfill(8) + "\n"


        #if l.split(" ")[0][0]=="B": # Checking for cmds starting with B for branches
        #    # Adding a NOP after each branch
        #    i += 1
        #    hexCode = hex(int(asmToBin("NOP"),2))[2:].strip("L")
        #    printString += str(i) + " " + hexCode.zfill(8) + "\n"
        
        i += 1

    program_file = open(fout, "w")
    program_file.write(printString)
    program_file.close()
    return 1
    
        
def asmToHex_Line(line):       
    binCode = asmToBin(line)
    hexCode = hex(int(binCode,2))[2:]
    return hexCode

    
if __name__ == "__main__":
    if len(sys.argv) != 3:
        raise Exception, "Wrong number of arguments provided. Should be (input_file, output_file)"
    asmToHex_File(sys.argv[1], sys.argv[2])
