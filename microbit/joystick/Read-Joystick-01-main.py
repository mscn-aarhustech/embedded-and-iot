from microbit import *

# Configure pins
x_pin = pin0
y_pin = pin1
b_pin = pin8

# Set Pin 8 to use an internal pull-up resistor
pin8.set_pull(pin8.PULL_UP)

while True:
    
    # Read values
    x_val = x_pin.read_analog()
    y_val = y_pin.read_analog()
    b_val = not b_pin.read_digital()
    
    # Serialize data and print message
    print("{},{},{}".format(x_val, y_val, b_val))
    
    sleep(10)