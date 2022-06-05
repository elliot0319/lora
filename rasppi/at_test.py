import serial
from time import sleep

ser = serial.Serial(port = '/dev/ttyS0', baudrate = 115200, parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1) # Change the baud rate accordingly/ /dev/serial0
ser.reset_input_buffer()

reset_cmd = "AT+RESET\r\n"
baud_cmd = "AT+IPR=115200\r\n"
addr_cmd = "AT+ADDRESS=2\r\n"
network_cmd = "AT+NETWORKID=5\r\n"
mode_cmd = "AT+MODE=0\r\n"
band_cmd = "AT+BAND=868500000\r\n"
parameter_cmd = "AT+PARAMETER=10,7,1,7\r\n"

sleep(0.02)
ser.write(reset_cmd.encode('utf-8'))
sleep(0.02)
ser.write(baud_cmd.encode('utf-8')) # Change the baud rate accordingly
sleep(0.02)
ser.write(addr_cmd.encode('utf-8'))
sleep(0.02)
ser.write(network_cmd.encode('utf-8'))
sleep(0.02)
ser.write(mode_cmd.encode('utf-8'))
sleep(0.02)
ser.write(band_cmd.encode('utf-8'))
sleep(0.02)
ser.write(parameter_cmd.encode('utf-8'))

try:
    while True:
        received_data = ser.readline()
        sleep(0.03)
        data_left = ser.inWaiting() # Check for remaining byte
        received_data += ser.read(data_left)
        print(received_data, type(received_data))
except KeyboardInterrupt:
    ser.close()
