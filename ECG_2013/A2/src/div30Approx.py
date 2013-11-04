import math
maxSensor = 8000

bestDiffs = 1.0
bestVal = 1.0
exponent = 1.0
for i in range(2, 30):

    val = math.pow(2,i)
    if val*maxSensor > 2**32:
        print "Number reached overflow limit. Breaking\n"
        break
    val = val / 30.0
    floored = math.floor(val)
    diff = val - floored
    
    if abs(diff) < bestDiffs:
        bestDiffs = abs(diff)
        bestVal = val
        exponent = i
    
    
print "Accuracy: ", (math.floor(bestVal) / 2**exponent)
print "Exponent: ", exponent
print "Multiplier: ", math.floor(bestVal)
print 'Best approximated equation: "x *', math.floor(bestVal), ">>", exponent, '"'