#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
 
SoftwareSerial lora(2,3);
 
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
 
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  lora.begin(115200);
  if (!bme.begin(0x76)) 
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}
 
void loop()
{
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.readHumidity();
 
  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.println(F("*C"));
 
  Serial.print(F("Pressure = "));
  Serial.print(pressure);
  Serial.println(F("hPa"));
 
  Serial.print(F("Approx. Altitude = "));
  Serial.print(altitude);
  Serial.println(F("m"));
 
  Serial.print(F("Humidity = "));
  Serial.print(humidity);
  Serial.println(F("%"));
 
  String temp = String(temperature);
  String pres = String(pressure);
  String alt = String(altitude);
  String hum = String(humidity);
 
  String values = String(temp)+","+ String(pres)+","+ String(alt)+","+ String(hum);
  String cmd = "AT+SEND=0,"+String(values.length())+","+values;
  lora.println(cmd);
 
  while(lora.available())
  {
    Serial.write(lora.read());
  }
  Serial.println();
  Serial.println(cmd);
  delay(5000);
}
