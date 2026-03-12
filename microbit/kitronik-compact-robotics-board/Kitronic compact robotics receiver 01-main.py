from microbit import *
import radio

# Set up radio
radio.on()
radio.config(group=42, channel=42, power=7)

class KitronikRoboticsBoard:
    PRESCALE_REG = 0xFE
    MODE_1_REG = 0x00
    SRV_REG_BASE = 0x08
    MOT_REG_BASE = 0x28
    REG_OFFSET = 4
    SERVO_MULTIPLIER = 226
    SERVO_ZERO_OFFSET = 0x66

    chipAddress = 0x6C
    initialised = False
    stepInit = False
    stepStage = 0
    stepper1Steps = 200
    stepper2Steps = 200

    def __init__(self):
        buf = bytearray(2)
        buf[0] = self.PRESCALE_REG
        buf[1] = 0x7D #50Hz
        i2c.write(self.chipAddress, buf, False)
        
        for blockReg in range(0xFA, 0xFE, 1):
            buf[0] = blockReg
            buf[1] = 0x00
            i2c.write(self.chipAddress, buf, False)

        buf[0] = self.MODE_1_REG
        buf[1] = 0x01
        i2c.write(self.chipAddress, buf, False)

    def motorOn(self, motor, direction, speed):
        buf = bytearray(2)
        motorReg = self.MOT_REG_BASE + (2 * (motor - 1) * self.REG_OFFSET)
        HighByte = False
        OutputVal = speed * 40
        HighOutputVal = 0
        
        if direction == "forward":
            if OutputVal > 0xFF:
                HighByte = True
                HighOutputVal = int(OutputVal / 256)
            
            buf[0] = motorReg
            buf[1] = int(OutputVal)
            i2c.write(self.chipAddress, buf, False)
            buf[0] = motorReg + 1
            
            if HighByte:
                buf[1] = HighOutputVal
            else:
                buf[1] = 0x00
            
            i2c.write(self.chipAddress, buf, False)
            
            for offset in range(4, 6, 1):
                buf[0] = motorReg + offset
                buf[1] = 0x00
                i2c.write(self.chipAddress, buf, False)
            
        elif direction == "reverse":
            if OutputVal > 0xFF:
                HighByte = True
                HighOutputVal = int(OutputVal/256)
            
            buf[0] = motorReg + 4
            buf[1] = int(OutputVal)
            i2c.write(self.chipAddress, buf, False)
            buf[0] = motorReg + 5
            
            if HighByte:
                buf[1] = HighOutputVal
            else:
                buf[1] = 0x00
            
            i2c.write(self.chipAddress, buf, False)
            
            for offset2 in range(0, 2, 1):
                buf[0] = motorReg + offset2
                buf[1] = 0x00
                i2c.write(self.chipAddress, buf, False)

    def motorOff(self, motor):
        buf = bytearray(2)
        motorReg = self.MOT_REG_BASE + (2 * (motor - 1) * self.REG_OFFSET)
        
        for offset3 in range(0, 2, 1):
            buf[0] = motorReg + offset3
            buf[1] = 0x00
            i2c.write(self.chipAddress, buf, False)
        
        for offset4 in range(4, 6, 1):
            buf[0] = motorReg + offset4
            buf[1] = 0x00
            i2c.write(self.chipAddress, buf, False)

    def allOff(self):
        buf = bytearray(2)
        servoOffCount = 0
        servoRegCount = 0
        
        for motors in range(1, 5, 1):
            self.motorOff(motors)

        while servoOffCount < 8:
            for offset5 in range(0, 2, 1):
                buf[0] = self.SRV_REG_BASE + servoRegCount + offset5
                buf[1] = 0x00
                i2c.write(self.chipAddress, buf, False)

            servoRegCount += 4
            servoOffCount += 1

def direction(input):
    if input >= 0:
        return "forward"
    elif input < 0:
        return "reverse"
    

theBoard = KitronikRoboticsBoard()

while True:
    message = radio.receive()
    
    if message:
        try:
            # Deserialize data
            angle_str, a_str, b_str = message.split(",")
            angle = float(angle_str)
            a_pressed = int(a_str)
            b_pressed = int(b_str)

            # Reverse
            if a_pressed and not b_pressed:
                motor1_speed = (-0.5 - angle) * 50
                motor2_speed = (-0.5 + angle) * 50

                theBoard.motorOn(1, direction(motor1_speed), abs(motor1_speed))
                theBoard.motorOn(2, direction(motor2_speed), abs(motor2_speed))

                display.show(Image.ARROW_S)

            # Forward
            elif b_pressed and not a_pressed:
                motor1_speed = (0.5 + angle) * 50
                motor2_speed = (0.5 - angle) * 50

                theBoard.motorOn(1, direction(motor1_speed), abs(motor1_speed))
                theBoard.motorOn(2, direction(motor2_speed), abs(motor2_speed))

                display.show(Image.ARROW_N)

            # Fast forward
            elif a_pressed and b_pressed:
                motor1_speed = 1.0 + angle
                motor2_speed = 1.0 - angle

                theBoard.motorOn(1, direction(motor1_speed), abs(motor1_speed))
                theBoard.motorOn(2, direction(motor2_speed), abs(motor2_speed))

                display.show(Image.SKULL)

            # Stop
            else:
                motor1_speed = 0
                motor2_speed = 0

                theBoard.allOff()

                display.show(Image.ASLEEP)

            #motor_run(MOTOR1_PIN1, MOTOR1_PIN2, motor1_speed)
            #motor_run(MOTOR2_PIN1, MOTOR2_PIN2, motor2_speed)

        except ValueError:
            print("Invalid message:", message)

    sleep(10)

#while True:
#    if button_a.is_pressed():
#        theBoard.motorOn(1, "forward", 20)
#        theBoard.motorOn(2, "forward", 20)
#        #theBoard.motorOn(2, "reverse", 100)
#        
#    
#    if button_b.is_pressed():
#        theBoard.motorOff(1)
#        theBoard.motorOff(2)
#    
#    if button_a.is_pressed() and button_b.is_pressed():
#        theBoard.allOff()
#    
#    sleep(100)