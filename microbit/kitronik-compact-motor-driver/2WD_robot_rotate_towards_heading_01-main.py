from microbit import *
import math

target_heading = 180
target_buffer = 20

# Define motor control pins
MOTOR1_PIN1 = pin12
MOTOR1_PIN2 = pin8
MOTOR2_PIN1 = pin16
MOTOR2_PIN2 = pin0

# Clear pins
MOTOR1_PIN1.write_digital(0)
MOTOR1_PIN2.write_digital(0)
MOTOR2_PIN1.write_digital(0)
MOTOR2_PIN2.write_digital(0)

# Motor controller
def motor_run(pin1, pin2, speed):
    speed = max(-1, min(1, speed))
    
    if speed > 0:
        pin1.write_analog(int(speed * 1023))
        pin2.write_digital(0)  
    elif speed < 0:
        pin1.write_digital(0) 
        pin2.write_analog(int(-speed * 1023))
    else:
        pin1.write_digital(0)
        pin2.write_digital(0)

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

def rotate_towards_heading(heading, speed):
    if(heading - target_buffer > get_heading()):
        print("heading too big")
        motor_run(MOTOR1_PIN1, MOTOR1_PIN2, -speed)
        motor_run(MOTOR2_PIN1, MOTOR2_PIN2,  speed)

    elif(heading + target_buffer < get_heading()):
        print("heading too small")
        motor_run(MOTOR1_PIN1, MOTOR1_PIN2,  speed)
        motor_run(MOTOR2_PIN1, MOTOR2_PIN2, -speed)

    else:
        print("heading reached")
        motor_run(MOTOR1_PIN1, MOTOR1_PIN2, 0.0)
        motor_run(MOTOR2_PIN1, MOTOR2_PIN2, 0.0)

compass.calibrate()

while True:
    print(get_heading())

    rotate_towards_heading(target_heading, 0.5)
        
    sleep(10)