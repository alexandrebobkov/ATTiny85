/*

  Arduino IDE
  Nano 2040 Connect
  
  By:     Alexander Bobkov
  Date:   Dec 3, 2023

  About:  Basic program written for Nano 2040 Connect that reads data (sensor value) over I2C from a slave device.

  Notes:  Use Logic 2 viewer to see data being transmitted over I2C.

*/

#include <Wire.h>

#define SENSOR_ADDRESS 0x5

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(SENSOR_ADDRESS, 1);
  delay(5);

  uint32_t buf;

  while (Wire.available()) {
    size_t actually_read = Wire.readBytes((uint8_t*)&buf, 4);
    Serial.println(buf, BIN);
  }

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);
}