import RPi.GPIO as GPIO
import socket
import time


GPIO.setmode(GPIO.BOARD)
TRIG = 7
ECHO = 11


GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)


SERVER_IP = '192.168.1.15'
SERVER_PORT = 5000


def send_data_over_tcp(data):
    try:
        
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            
            s.connect((SERVER_IP, SERVER_PORT))
            
            s.sendall(data)
            print(f"Sent data: {data}")
    except Exception as e:
       print("Error:", e)

try:
    while True:
        
        GPIO.output(TRIG, False)
        time.sleep(0.1)

        GPIO.output(TRIG, True)
        time.sleep(0.00001)
        GPIO.output(TRIG, False)

        
        while GPIO.input(ECHO) == 0:
            pulse_start = time.time()

        while GPIO.input(ECHO) == 1:
            pulse_end = time.time()

        pulse_duration = pulse_end - pulse_start

        
        distance = pulse_duration * 17150

        if distance < 20:  
            
            send_data_over_tcp(b'\x55')

except KeyboardInterrupt:
    GPIO.cleanup()
