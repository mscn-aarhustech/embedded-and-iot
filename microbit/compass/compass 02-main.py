from microbit import *
import math

BUFFER_SIZE = 5
x_buf = [0] * BUFFER_SIZE
z_buf = [0] * BUFFER_SIZE
buf_i = 0

def get_heading():
    global buf_i
    x_buf[buf_i] = compass.get_x()
    z_buf[buf_i] = compass.get_z()
    buf_i = (buf_i + 1) % BUFFER_SIZE
    avg_x = sum(x_buf) / BUFFER_SIZE
    avg_z = sum(z_buf) / BUFFER_SIZE
    return math.degrees(math.atan2(avg_x, avg_z) + math.pi) % 360

compass.calibrate()
while True:
    print(get_heading())
    sleep(50)