# Ultrasonic distance measurement with HC-SR04
# This version only works on Micro:Bit v2

# Wiring 
# Micro:Bit - HC-SR04+:
# V0/GND - gnd
# 3V - vcc
# Pin0 - trig
# Pin1 - echo

from microbit import *
import utime
import machine

# Setup pins
trig = pin0
echo = pin1

# Ensure trig is low initially
trig.write_digital(0)

def get_distance():
    # 1. Send a 10 microsecond pulse
    trig.write_digital(1)
    utime.sleep_us(10)
    trig.write_digital(0)
    
    # 2. Measure the duration of the Echo pulse in microseconds
    # machine.time_pulse_us returns the time in us, or -1/-2 on timeout
    duration = machine.time_pulse_us(echo, 1, 30000) # 30ms timeout
    
    if duration > 0:
        # 3. Calculate distance in cm
        # Speed of sound: 0.0343 cm/us
        distance = (duration * 0.0343) / 2
        return distance
    else:
        return None

while True:
    dist = get_distance()
    if dist is not None:
        print("Distance: {:.2f} cm".format(dist))
    else:
        print("Out of range")
    
    sleep(100)