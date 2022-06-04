//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Reyax RYLR896 890 LoRa Controlling LEDs with Button
#include <SoftwareSerial.h>

SoftwareSerial ReyaxLoRa(5, 4); //--> RX, TX

#define LED 2 //--> LED Pin

int Button = 2; //--> Button Pin

int data_length; 
String data_send;

int Stat_LED = LOW;

bool Waiting_to_send_the_next_data = false; //--> Variable for the next data delivery indicator

unsigned long buttonPushedMillis; //--> when button was released
unsigned long turnOnDelay = 2000; //--> wait to turn on delay millis

String myString; 

//========================================================================VOID SETUP
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
  ReyaxLoRa.begin(9600);
  
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);

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

  unsigned long currentMillis = millis();

  //----------------------------------------Sending Data with a button
  if (Waiting_to_send_the_next_data == false) {
    if (digitalRead(Button) == LOW) {
      buttonPushedMillis = currentMillis;
      Waiting_to_send_the_next_data = true;
      Stat_LED = !Stat_LED;
      data_send = String(Stat_LED);
      data_length = data_send.length();
      String mymessage;
      mymessage = mymessage + "AT+SEND=0" + "," + data_length + "," + data_send + "\r\n"; // Adderss must be changed and matched accordingly 0 means all addresses
      ReyaxLoRa.print(mymessage);
      Serial.print("Send Data : "); 
      Serial.print(mymessage);
    }
  }
  //----------------------------------------

  //----------------------------------------After pressing the button, it will wait 2 seconds for further data transmission
  if (Waiting_to_send_the_next_data) {
    if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
      Waiting_to_send_the_next_data = false;
    }
  }
  //----------------------------------------

  if ( ReyaxLoRa.available() > 0 ) {
    myString = ReyaxLoRa.readString(); 
    Serial.print("Receive Data : ");
    Serial.print(myString); 

//    Serial.println("Data Processing");
//   
//    String addr = getValue(myString, ',', 0);   //--> address
//    String dtl = getValue(myString, ',', 1);    //--> data length
    String dt = getValue(myString, ',', 2);     //--> data
//    String rssi = getValue(myString, ',', 3);   //--> RSSI
//    String snr = getValue(myString, ',', 4);    //--> SNR
//     
//    Serial.print("Address : "); 
//    Serial.println(addr); 
//     
//    Serial.print("Data length : "); 
//    Serial.println(dtl);
//     
//    Serial.print("Data : "); 
//    Serial.println(dt);
//     
//    Serial.print("RSSI : "); 
//    Serial.println(rssi);
//     
//    Serial.print("SNR : "); 
//    Serial.println(snr); 

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
//========================================================================
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
