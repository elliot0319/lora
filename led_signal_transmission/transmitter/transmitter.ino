#include <SoftwareSerial.h>
#define ledPin 2

SoftwareSerial ReyaxLoRa(5, 4); //--> RX, TX

int data_length; 
String data;

int Stat_LED = HIGH;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
  ReyaxLoRa.begin(9600);
  delay(100); 
  ReyaxLoRa.print("AT\r\n");
  Serial.print("AT\r\n");
  ReyaxLoRa.print("AT+IPR=9600\r\n");
  delay(20);
  ReyaxLoRa.print("AT+ADDRESS=1\r\n");
  delay(20);
  ReyaxLoRa.print("AT+NETWORKID=5\r\n");
  delay(20);
  ReyaxLoRa.print("AT+MODE=0\r\n");
  delay(20);
  ReyaxLoRa.print("AT+BAND=868500000\r\n");
  delay(20);
  ReyaxLoRa.print("AT+PARAMETER=10,7,1,7\r\n");
  delay(20);
  pinMode(ledPin, OUTPUT)
}

void loop() {
  // put your main code here, to run repeatedly:
  Stat_LED = !Stat_LED;
  data = String(Stat_LED);
  data_length = data.length();
  String mymessage;
  digitalWrite(ledPin, HIGH);
  mymessage = mymessage + "AT+SEND=2" + "," + data_length + "," + data + "\r\n";
  ReyaxLoRa.print(mymessage); //--> Send Data
  Serial.print("Send Data : "); 
  Serial.print(mymessage);
  digitalWrite(ledPin, LOW);
  delay(2000);
}
