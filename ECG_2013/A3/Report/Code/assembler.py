#!/usr/bin/python
import sys

bitlength = 32
    
    
  
    
def asmToBin(asmLine):
    
    output = ""
    segs = asmLine.rstrip(" \n").split(" ")
    
    cmd = segs[0]
    
    if cmd=="LOAD":
        checkSegCount(segs, 2)
        
        output += "00001"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)
        output += zPad(18)
        
        
    elif cmd=="STRE":
        checkSegCount(segs, 1)
        
        output += "00010"
        output += getRegBin(segs[1])
        output += zPad(3)
        output += zPad(3)
        output += zPad(18)
        
    elif cmd=="MOVE":
        checkSegCount(segs, 2)
        
        output += "00011"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += zPad(18)
        
    elif cmd=="ADDI":
        checkSegCount(segs, 3)
        
        output += "01000"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 18)
        
    elif cmd=="SUBI": 
        checkSegCount(segs, 3)
        
        output += "01001"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 18)
        
    elif cmd=="MULI":
        checkSegCount(segs, 3)
        
        output += "01010"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 18)
        
    elif cmd=="SHRI":
        checkSegCount(segs, 3)
        
        output += "01011"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 18)
        
    elif cmd=="BRCH":
        checkSegCount(segs, 1)
        output += "00100"
        output += zPad(3) # nothing on the registers
        output += zPad(3)
        output += zPad(3)
        output += numToBin(segs[1], 18)
        
    elif cmd=="BILT":
        checkSegCount(segs, 3)
        
        output += "00101"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += zPad(3)    # No third register
        output += numToBin(segs[3], 18)
        
    elif cmd=="ADD":
        checkSegCount(segs, 3)
        
        output += "01100"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += getRegBin(segs[3])
        output += zPad(18)
        
    elif cmd=="SUB":
        checkSegCount(segs, 3)
        
        output += "01101"
        output += getRegBin(segs[1])
        output += getRegBin(segs[2])
        output += getRegBin(segs[3])
        output += zPad(18)

    elif cmd=="NOP":
        # Not implemented. Only placeholders
        checkSegCount(segs, 0)
        
        output += "00000"
        output += zPad(3)
        output += zPad(3)
        output += zPad(3)
        output += zPad(18)

    elif cmd=="SCMD":
        if segs[1] == "mwi_run":
            checkSegCount(segs, 4)

            output += "10001"
            output += getRegBin(segs[2])
            output += getRegBin(segs[3])
            output += getRegBin(segs[4])
            output += zPad(18)

        elif segs[1] == "mwi_reset":
            checkSegCount(segs, 1)

            output += "10010"
            output += zPad(27)
        else:
            output += "10000"
            output += zPad(27)

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
        raise Exception, "Invalid number og arguments provided for this command: " + `required` + ", " + " ".join(slist)
        
        
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
        printString += str(hex(i)[2:]) + " " + hexCode.zfill(8) + "\n"
     
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
        print("""
            Assembler Help: J2-ECG architecture
Converts J2-ECG assembly instructions to hexadecimal, 
which can be run by the GEZEL hardware implementation.

Use:
Cmdline
    :python assembler.py input_file_assembler output_file_hexadecimal
Python:
    >>import assembler
    >>assembler.asmToHex_File( input_file_assembler, output_file_hexadecimal)

""")
    else:
        asmToHex_File(sys.argv[1], sys.argv[2])
