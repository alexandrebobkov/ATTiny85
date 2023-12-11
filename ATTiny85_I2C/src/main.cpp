/*
  By: Alexander Bobkov

  December 4, 2023

  Scans I2C bus and requests variable value from ATTiny85 device.
  
*/
#include <Arduino.h>
#include <Wire.h>

#define BUILTIN_LED 2

byte i2c_data, address, err, device_addr;

void setup() {
  Wire.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("I2C");

  Serial.println("I2C scan ...");

  for (address = 1; address < 127; address++)
  {
    Serial.print("Address: ");
    Serial.println(address, HEX);
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device was found at address: ");
      Serial.println(address, HEX);
      Wire.requestFrom(address, 2);
      size_t buff_size = Wire.readBytes((uint8_t*)&i2c_data, 2);
      Serial.print("Value: ");
      Serial.println(i2c_data, HEX);
    }
    else if (Wire.endTransmission() == 4)
      Serial.println("I2C unknown error.");
  }
  Wire.end();
}

void loop() {

  digitalWrite(BUILTIN_LED, HIGH);
  delay(250);
  digitalWrite(BUILTIN_LED, LOW);
  delay(250);

  /*i2c_data = 0;
  Serial.print("I2C device at address: ");
  Serial.println(device_addr, HEX);
  Wire.beginTransmission(device_addr);
  Wire.requestFrom(device_addr, 1);
  size_t buff_size = Wire.readBytes((uint8_t*)&i2c_data, 1);
  Serial.print("Value: ");
  Serial.println(i2c_data, HEX);
  Serial.println();

  /*address = 5;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 1);
  if (Wire.endTransmission() == 0) {
    Wire.requestFrom(address, 1);
    size_t buff_size = Wire.readBytes((uint8_t*)&i2c_data, 1);
    Serial.print("Value: ");
    Serial.println(i2c_data, HEX);
  }
  else if (Wire.endTransmission() == 4)
    Serial.println("I2C unknown error.");*/

}