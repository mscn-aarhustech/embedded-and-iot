# Ultrasonic distance measurement with HC-SR04
# This version works on Micro:Bit v1 and v2

# Wiring 
# Micro:Bit - HC-SR04+:
# V0/GND - gnd
# 3V - vcc
# Pin0 - trig
# Pin1 - echo

from microbit import *
from machine import time_pulse_us

num_samples = 10
samples = 0
sum = 0

# Setup pins based on wiring
trig = pin0
echo = pin1

# Setup I/O
trig.write_digital(0)
#echo.read_digital()

while True:
    
    # Send an ultrasonic impulse
    trig.write_digital(1)
    trig.write_digital(0)

    # Measure the delay of the echo in microseconds
    # machine.time_pulse_us returns time in us or -1 on timeout
    micros = time_pulse_us(echo, 1, 24000) # 24 ms timeout = 4m limit

    if micros > 0:
        
        # Calculate distance in cm
        # Speed of sound = 0.0343 cm/us
        dist_cm = (micros / 2) * 0.0343

        if samples < num_samples:
            
            sum += dist_cm
            samples = samples + 1

        else:
            
            print("Distance: {:.2f} cm".format(sum/num_samples))
            
            sum = 0
            samples = 0

    else:

        print("Out of range error")

    sleep(10)