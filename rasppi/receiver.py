import serial
from time import sleep

ser = serial.Serial("/dev/ttyS0", 9600) # Change the baud rate accordingly
sleep(0.02)
ser.write("AT+RESET\r\n")
sleep(0.02)
ser.write("AT+IPR=9600\r\n") # Change the baud rate accordingly
sleep(0.02)
ser.write("AT+ADDRESS=2\r\n")
sleep(0.02)
ser.write("AT+NETWORKID=5\r\n")
sleep(0.02)
ser.write("AT+MODE=0\r\n")
sleep(0.02)
ser.write("AT+BAND=868500000\r\n")
sleep(0.02)
ser.write("AT+PARAMETER=10,7,1,7\r\n")

while True:
    received_data = ser.read() # Read Serial Port
    sleep(0.03)
    data_left = ser.inWating() # Check for remaining byte
    received_data += ser.read(data_left)
    print(received_data, type(received_data))
    
