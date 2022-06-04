#include <SoftwareSerial.h>

SoftwareSerial ReyaxLoRa(3, 2); //--> RX, TX

void setup() {
  // put your setup code here, to run once:
  
  // set the data rate for the HardwareSerial port
  Serial.begin(9600);
  
  // set the data rate for the SoftwareSerial port
  //ReyaxLoRa.begin(9600);
  ReyaxLoRa.begin(115200); //--> 115200 is the Reyax RYLR896 890 LoRa default baud rate

  delay(100);

  ReyaxLoRa.print("AT\r\n");
  delay(200);
  ReyaxLoRa.print("AT+ADDRESS?\r\n");
  Serial.print("AT\r\n");
}

void loop() { 
  // put your main code here, to run repeatedly:
  if (ReyaxLoRa.available()) Serial.println(ReyaxLoRa.readString());
  if (Serial.available()) ReyaxLoRa.print(Serial.readString());
}
