#include <Arduino.h>
#include <Wire.h>

#define BUILTIN_LED 2

byte i2c_data, address, err;

void setup() {
  Wire.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("I2C");

  Serial.println("Starting I2C transmission ...");

  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device was found at ");
      Serial.println(address);
      i2c_data = Wire.read();
      Serial.print("Value: ");
      Serial.println(i2c_data);
    }
    else if (Wire.endTransmission() == 4)
      Serial.println("I2C unknown error.");
  }
}

void loop() {

  digitalWrite(BUILTIN_LED, HIGH);
  delay(250);
  digitalWrite(BUILTIN_LED, LOW);
  delay(250);

}