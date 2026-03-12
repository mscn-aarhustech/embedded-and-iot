from microbit import *
from math import atan2, pi
import radio

# Configure radio
radio.on()
radio.config(group=42, channel=42, power=7)

while True:

    # Read input
    a_pressed = int(button_a.is_pressed())
    b_pressed = int(button_b.is_pressed())
    
    x, y = accelerometer.get_x(), accelerometer.get_y()

    angle = atan2(y, x) - 0.5 * pi

    # Keep angle in range [-pi, pi]
    if angle < -pi:
        angle += 2 * pi
    elif angle > pi:
        angle -= 2 * pi

    angle = round(angle / (0.5 * pi), 2)

    # Serialize data
    message = "{},{},{}".format(angle, a_pressed, b_pressed)

    radio.send(message)
    #print(message)

    # Print icon to screen
    if a_pressed and not b_pressed: # Reverse
        display.show(Image.ARROW_S)

    elif b_pressed and not a_pressed: # Forward
        display.show(Image.ARROW_N)

    elif a_pressed and b_pressed: # Fast forward
        display.show(Image.SKULL)

    else: # Stop
        display.show(Image.ASLEEP)

    sleep(10)
