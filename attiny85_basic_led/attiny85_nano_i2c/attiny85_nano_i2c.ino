#include <Wire.h>

#define SENSOR_ADDRESS 0x11

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

  delay(500);
}