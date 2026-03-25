from microbit import *
import math

# Configuration
BUFFER_SIZE = 5
x_buffer = [0] * BUFFER_SIZE
z_buffer = [0] * BUFFER_SIZE
buffer_index = 0

def get_smoothed_upright_heading():
    global buffer_index
    
    # 1. Update the buffer with new raw readings
    x_buffer[buffer_index] = compass.get_x()
    z_buffer[buffer_index] = compass.get_z()
    
    # 2. Increment index and wrap around
    buffer_index = (buffer_index + 1) % BUFFER_SIZE
    
    # 3. Calculate the average of the buffers
    avg_x = sum(x_buffer) / BUFFER_SIZE
    avg_z = sum(z_buffer) / BUFFER_SIZE
    
    # 4. Calculate heading from the averaged vectors
    angle_rad = math.atan2(avg_z, avg_x)
    angle_deg = math.degrees(angle_rad)
    
    # 5. Normalize to 0-360 degrees
    heading = (angle_deg + 360) % 360
    
    return heading

# Calibration is required for accurate Z-axis data
compass.calibrate()

while True:
    stable_heading = get_smoothed_upright_heading()
    
    # Displaying as integer to reduce screen scrolling time
    #display.scroll(int(stable_heading), delay=80)
    print(stable_heading)
    sleep(100)