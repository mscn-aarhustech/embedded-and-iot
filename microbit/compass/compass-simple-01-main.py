from microbit import *
import math

compass.calibrate()

while True:
    x = compass.get_x()
    z = compass.get_z()

    heading = (math.degrees(math.atan2(-x, -z)) + 360) % 360

    print(int(heading))
    sleep(100)