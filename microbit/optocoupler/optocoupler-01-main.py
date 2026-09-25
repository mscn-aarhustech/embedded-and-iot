from microbit import *

# Motor control pins
MOTOR1_PIN1 = pin12
MOTOR1_PIN2 = pin8
MOTOR2_PIN1 = pin16
MOTOR2_PIN2 = pin0

# Optocoupler outputs
# Connect left-wheel sensor OUT to P1 and right-wheel sensor OUT to P2.
MOTOR1_SENSOR = pin1
MOTOR2_SENSOR = pin2

# Enable pull-ups for optocoupler outputs
MOTOR1_SENSOR.set_pull(MOTOR1_SENSOR.PULL_UP)
MOTOR2_SENSOR.set_pull(MOTOR2_SENSOR.PULL_UP)

# Clear motor pins
MOTOR1_PIN1.write_digital(0)
MOTOR1_PIN2.write_digital(0)
MOTOR2_PIN1.write_digital(0)
MOTOR2_PIN2.write_digital(0)


def motor_run(pin1, pin2, speed):
    """Run one motor at a speed from -1.0 to 1.0."""
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


def sensor_for_motor(pin1, pin2):
    """Return the encoder sensor associated with the motor pins."""
    if pin1 == MOTOR1_PIN1 and pin2 == MOTOR1_PIN2:
        return MOTOR1_SENSOR
    elif pin1 == MOTOR2_PIN1 and pin2 == MOTOR2_PIN2:
        return MOTOR2_SENSOR

    return None


def motor_run_slots(pin1, pin2, speed, slots):
    """
    Run one motor until its encoder has counted `slots` transitions.

    pin1, pin2: motor driver pins
    speed:      -1.0 to 1.0
    slots:      number of encoder slots to count
    """
    sensor = sensor_for_motor(pin1, pin2)

    if sensor is None:
        return

    slots = max(0, slots)

    if speed == 0 or slots == 0:
        motor_run(pin1, pin2, 0)
        return

    count = 0
    previous_value = sensor.read_digital()
    start_time = running_time()

    motor_run(pin1, pin2, speed)

    while count < slots:

        current_value = sensor.read_digital()

        # Count one edge per perforated-disc slot.
        if current_value == 1 and previous_value == 0:
            count += 1

        previous_value = current_value

        # Safety timeout, useful if the wheel stalls or sensor is disconnected.
        if running_time() - start_time > 8000:
            break

        sleep(1)

    motor_run(pin1, pin2, 0)


def run_two_motors_slots(speed1, speed2, slots):
    """
    Run both motors together and stop each one independently once it
    reaches the requested number of encoder slots.
    """
    count1 = 0
    count2 = 0

    previous1 = MOTOR1_SENSOR.read_digital()
    previous2 = MOTOR2_SENSOR.read_digital()

    motor_run(MOTOR1_PIN1, MOTOR1_PIN2, speed1)
    motor_run(MOTOR2_PIN1, MOTOR2_PIN2, speed2)

    start_time = running_time()

    while count1 < slots or count2 < slots:

        current1 = MOTOR1_SENSOR.read_digital()
        current2 = MOTOR2_SENSOR.read_digital()

        if current1 == 1 and previous1 == 0 and count1 < slots:
            count1 += 1

        if current2 == 1 and previous2 == 0 and count2 < slots:
            count2 += 1

        previous1 = current1
        previous2 = current2

        # Stop each wheel as soon as its own target is reached.
        if count1 >= slots:
            motor_run(MOTOR1_PIN1, MOTOR1_PIN2, 0)

        if count2 >= slots:
            motor_run(MOTOR2_PIN1, MOTOR2_PIN2, 0)

        # Safety timeout
        if running_time() - start_time > 8000:
            break

        sleep(1)

    motor_run(MOTOR1_PIN1, MOTOR1_PIN2, 0)
    motor_run(MOTOR2_PIN1, MOTOR2_PIN2, 0)


def drive_slots(speed, slots):
    """Drive straight for a number of encoder slots."""
    run_two_motors_slots(speed, speed, slots)


def rotate_slots(speed, slots):
    """
    Rotate in place for a number of encoder slots.

    Positive speed rotates one way, negative speed the other.
    """
    run_two_motors_slots(speed, -speed, slots)


while True:

    # Step 1: Rotate left at full speed for 25 encoder slots
    display.show("1")
    rotate_slots(1.0, 25)
    sleep(1000)

    # Step 2: Rotate right at half speed for 25 encoder slots
    display.show("2")
    rotate_slots(-0.5, 25)
    sleep(1000)

    # Step 3: Drive forward at full speed for 50 encoder slots
    display.show("3")
    drive_slots(1.0, 50)
    sleep(1000)

    # Step 4: Reverse at half speed for 50 encoder slots
    display.show("4")
    drive_slots(-0.5, 50)
    sleep(1000)

    display.show(Image.ASLEEP) 