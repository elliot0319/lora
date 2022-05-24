#define ledPin 2

String incomingString;

void setup() {
	 // Change the baud rate according to the manual
        Serial.begin(9600);
        delay(20);
        Serial.print("AT+RESET\r\n");
        delay(20);
        Serial.print("AT+IPR=9600\r\n");
        delay(20);
	Serial.print("AT+ADDRESS=2\r\n");
	delay(20);
        Serial.print("AT+NETWORKID=5\r\n");
        delay(20);
        Serial.print("AT+MODE=1\r\n");
        delay(20);
        Serial.print("AT+BAND=868500000\r\n");
        delay(20);
        Serial.print("AT+PARAMETER=10,7,1,7\r\n");
	pinMode(ledPin, OUTPUT);
}

void loop() {
	if (Serial.available) {
		incomingString = Serial.readString();
		if (incomingString.indexOf("Hello!") > 0) {
			digitalWrite(ledPin, HIGH);
			delay(100);
			digitalWrite(ledPing, Low);
		}
	}
}
