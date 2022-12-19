import RPi.GPIO as GPIO
import time
import mmap

#pwmPin=19
#dirPin=26
motorA1=19
motorA2=26
motorB1=9
motorB2=10


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(motorA1,GPIO.OUT)
GPIO.setup(motorA2,GPIO.OUT)
GPIO.setup(motorB1,GPIO.OUT)
GPIO.setup(motorB2,GPIO.OUT)

#GPIO.output(motorA1,0)
#GPIO.output(motorA2,0)
#GPIO.output(motorB2,0)
#GPIO.output(motorB1,0)

A1=GPIO.PWM(motorA1,100)
A1.start(0)
B1=GPIO.PWM(motorB1,100)
B1.start(0)

with open("shared_memory", "r+b") as f:
    shmem = mmap.mmap(f.fileno(), 0)

#n=10
while True:
	n = shmem[7]
	if n == 1000:
		GPIO.cleanup()
		break
	GPIO.output(motorA2,False)
	GPIO.output(motorB2,False)
	A1.ChangeDutyCycle(n)
	B1.ChangeDutyCycle(n)
	time.sleep(0.1)


