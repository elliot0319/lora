#define ledPin 2

unsigned long lastTransmission;
const int interval = 1000;
String incomingString;

void setup() {
	// Change the baud rate according to the manual
	Serial.begin(9600);
	delay(20);
	Serial.print("AT+RESET\r\n");
	delay(20);
	Serial.print("AT+IPR=9600\r\n");
	delay(20);
	Serial.print("AT+ADDRESS=1\r\n");
	delay(20);
	Serial.print("AT+NETWORKID=5\r\n");
	delay(20);
	// AES128 Password (Should be the same as the one set on the receiver side)
	// Serial.print("AT+CPIN");
	// delau(20);
	Serial.print("AT+MODE=1\r\n");
	delay(20);
	Serial.print("AT+BAND=868500000\r\n");
	delay(20);
	Serial.print("AT+PARAMETER=10,7,1,7\r\n");
	pinMode(ledPin, OUTPUT);
}

void loop() {
	if (millis() > lastTransmission + interval) {
		Serial.println("AT\r\n");
    delay(200);
    if (Serial.available()) {
      incomingString = Serial.read();
      Serial.print(incomingString);
      if (incomingString.indexOf("+OK") > 0) {
        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
        }
	    }
		lastTransmission = millis();
	}
}
