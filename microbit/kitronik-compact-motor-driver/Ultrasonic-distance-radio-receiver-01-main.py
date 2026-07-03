from microbit import *
import radio

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

# Set up radio
radio.on()
radio.config(channel=42, power=7)

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
    motor_run(MOTOR1_PIN1, MOTOR1_PIN2, 0)
    motor_run(MOTOR2_PIN1, MOTOR2_PIN2, 0)

def drive_forward(speed):
    motor_run(MOTOR1_PIN1, MOTOR1_PIN2, speed)
    motor_run(MOTOR2_PIN1, MOTOR2_PIN2, speed)

def rotate_left(speed):
    motor_run(MOTOR1_PIN1, MOTOR1_PIN2, -speed)
    motor_run(MOTOR2_PIN1, MOTOR2_PIN2, speed)

while True:
    message = radio.receive()

    if message:
        try:

            print(message)
            # Deserialize data
            dist = float(message)

            if (dist > 20):
                drive_forward(1.0)
            else:
                rotate_left(1.0)

        except ValueError:
            print("Invalid message:", message)
            motor_stop()

    sleep(10)
