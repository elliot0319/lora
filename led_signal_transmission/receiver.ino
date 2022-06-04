#include <SoftwareSerial.h>

SoftwareSerial ReyaxLoRa(5, 4); //--> RX, TX

String myString; 
char data; 

#define LED 2 //--> LED Pin

//========================================================================VOID SETUP
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
  ReyaxLoRa.begin(9600);
  
  pinMode(LED, OUTPUT);

  delay(100);
  
  ReyaxLoRa.print("AT\r\n");
  Serial.print("AT\r\n");
  ReyaxLoRa.print("AT+IPR=9600\r\n");
  delay(20);
  ReyaxLoRa.print("AT+ADDRESS=2\r\n");
  delay(20);
  ReyaxLoRa.print("AT+NETWORKID=5\r\n");
  delay(20);
  ReyaxLoRa.print("AT+MODE=0\r\n");
  delay(20);
  ReyaxLoRa.print("AT+BAND=868500000\r\n");
  delay(20);
  ReyaxLoRa.print("AT+PARAMETER=10,7,1,7\r\n");
  delay(20);
}
//========================================================================

//========================================================================VOID LOOP
void loop() {
  // put your main code here, to run repeatedly:

  if (ReyaxLoRa.available() > 0 ) {
    myString = ReyaxLoRa.readString(); 
    Serial.print("Receive Data : ");
    Serial.print(myString); 
   
    Serial.println("Data Processing");
   
    String addr = getValue(myString, ',', 0);   //--> address
    String dtl = getValue(myString, ',', 1);    //--> data length
    String dt = getValue(myString, ',', 2);     //--> data
    String rssi = getValue(myString, ',', 3);   //--> RSSI
    String snr = getValue(myString, ',', 4);    //--> SNR
     
    Serial.print("Address : "); 
    Serial.println(addr); 
     
    Serial.print("Data length : "); 
    Serial.println(dtl);
     
    Serial.print("Data : "); 
    Serial.println(dt);
     
    Serial.print("RSSI : "); 
    Serial.println(rssi);
     
    Serial.print("SNR : "); 
    Serial.println(snr); 

    //----------------------------------------Conditions to turn on or turn off the LED
    if (dt == "1") digitalWrite(LED, HIGH);
    if (dt == "0") digitalWrite(LED, LOW);
    //----------------------------------------
  }
}
//========================================================================

//========================================================================String function to process the data received
// I got this from : https://www.electroniclinic.com/reyax-lora-based-multiple-sensors-monitoring-using-arduino/
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
