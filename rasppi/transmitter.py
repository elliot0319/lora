import serial
from time import sleep # Time is in seconds not milliseconds

ser = serial.Serial("/dev/ttyso", 9600) # Change the baud rate accordingly
sleep(0.02)
ser.write("AT+RESET\r\n")
sleep(0.02)
ser.write("AT+IPR=9600\r\n") # Change the baud rate accordingly
sleep(0.02)
ser.write("AT+ADDRESS=1\r\n")
sleep(0.02)
ser.write("AT+NETWORKID=5\r\n")
sleep(0.02)
ser.write("AT+MODE=0\r\n")
sleep(0.02)
ser.write("AT+BAND=868500000\r\n")
sleep(0.02)
ser.write("AT+PARAMETER=10,7,1,7\r\n")

while True:
    ser.write("AT+SEND=2,6,Hello!")
    print("Just said Hello!")
    sleep(0.1)
