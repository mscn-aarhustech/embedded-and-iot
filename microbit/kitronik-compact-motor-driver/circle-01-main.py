from microbit import *

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

def motor_stop():
    motor_run(MOTOR1_PIN1, MOTOR1_PIN2, 0.0)
    motor_run(MOTOR2_PIN1, MOTOR2_PIN2, 0.0)

def circle():
    motor_run(MOTOR1_PIN1, MOTOR1_PIN2, 1.0)
    motor_run(MOTOR2_PIN1, MOTOR2_PIN2, 0.5)  

#
circle() 
