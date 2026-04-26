from microbit import *
import math
import struct

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
uart.init(baudrate=115200)

while True:
    heading = get_heading()
    #print(heading)
    #uart.write(struct.pack('<f', heading))
    uart.write(str(int(heading)) + '\n')