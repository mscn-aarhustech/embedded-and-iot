from microbit import *
import radio

# Configure radio
radio.on()
radio.config(group=42, channel=42, power=7)

# Joystick deadzone
deadzone_value = 0.1

# Configure pins
x_pin = pin0
y_pin = pin1
b_pin = pin8

# Set Pin 8 to use an internal pull-up resistor
pin8.set_pull(pin8.PULL_UP)

while True:

    # Read input
    #a_pressed = bool(button_a.is_pressed())
    #b_pressed = bool(button_b.is_pressed())
    
    # Read values
    x_val = x_pin.read_analog()
    y_val = y_pin.read_analog()
    #b_val = not b_pin.read_digital()

    # Calculate angle and speed
    angle = round((y_val / 1024) * 2 - 1, 2)
    speed = round((x_val / 1024) * 2 - 1, 2)

    # Limit angle and speed to range [-1, 1]
    angle = 0 if abs(angle) < deadzone_value else angle
    speed = 0 if abs(speed) < deadzone_value else speed
    
    # Serialize data
    #message = "{},{},{},{},{}".format(angle, speed, b_val, a_pressed, b_pressed)
    message = "{},{}".format(angle, speed)
    
    radio.send(message)
    #print(message)
    
    sleep(10)