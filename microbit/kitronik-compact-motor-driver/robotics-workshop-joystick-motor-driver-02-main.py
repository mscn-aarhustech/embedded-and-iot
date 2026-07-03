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
radio.config(group=42, channel=42, power=7)

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

while True:
    message = radio.receive()

    if message:
        try:
            # Deserialize data
            #angle_str, speed_str, button_str = message.split(",")
            angle_str, speed_str = message.split(",")
            angle = float(angle_str)
            speed = float(speed_str)
            #b_val = bool(button_str)

            # Limit motor speed to range [-1, 1]
            motor1_speed = max(-1, min(1, speed + angle))
            motor2_speed = max(-1, min(1, speed - angle))

            # Set motor speed
            motor_run(MOTOR1_PIN1, MOTOR1_PIN2, motor1_speed)
            motor_run(MOTOR2_PIN1, MOTOR2_PIN2, motor2_speed)

        except ValueError:
            print("Invalid message:", message)

    sleep(10)
