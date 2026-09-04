from microbit import *

# Configure pins
buttonPin = pin8

# Set Pin 8 to use an internal pull-up resistor
pin8.set_pull(pin8.PULL_UP)

while True:
    
    # Read button value
    buttonState = buttonPin.read_digital()

    # Cast button value to bool datatype
    buttonBool = bool(buttonState)
        
    # Print data to serial monitor
    print("Button is pressed: {}".format(buttonBool))
    
    sleep(10)

