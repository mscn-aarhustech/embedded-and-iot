from microbit import *

# Configure pins
xAxisPin = pin1

while True:
    
    # Read values
    xAxisValue = xAxisPin.read_analog()
    
    # Serialize data and print message
    print("xAxisValue: {}".format(xAxisValue))
    
    sleep(10)


