/*

  I2C MASTER device ESP32 (DevKit v.1)

  By: Alexander Bobkov

  December 4, 2023
  Updated: December 13, 2023

  Scans I2C bus for devices and requests variable value from available ATTiny85 device(s).

  Known issue: ATTiny85 stalls/stops sending values after 1-2 minutes.
    Cause: happens when master I2C device is offline; I2C slave device power is dependant on ESP32 master I2C device

  ESP32:
    SDA -> GPIO 21 (green)
    SCL -> GPIO 22 (yellow)
    
*/

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

//#define ESP32-S2-Mini
#define ESP32-DevKit

//#define BUILTIN_LED 17

byte i2c_data, address, err, device_addr;

void setup() {
  delay(100);
  // I2C setup for ESP32 S2 mini board
  Wire.begin(33,35); // SDA -> GPIO33; SCL -> GPIO35
  Wire.setClock(1000);
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);

//ifdef ESP32-DevKit
  // Scan I2C bus
  Serial.println("I2C");
  int dev_num = 0;  //Save number of devices connected to I2C bus
  Serial.println("I2C scan ...");
  for (address = 1; address < 127; address++)
  {
    Serial.print("Address: ");
    Serial.println(address, HEX);
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device was found at address: ");
      dev_num++;                                          // +1 if I2C device is connected to a bus
      Serial.println(address, HEX);
      Wire.requestFrom(address, 2);
      size_t buff_size = Wire.readBytes((uint8_t*)&i2c_data, 2);
      Serial.print("Value: ");
      Serial.println(i2c_data, HEX);
      // Note address of available device.
      device_addr = address;
    }
    else if (Wire.endTransmission() == 4)
      Serial.println("I2C unknown error.");
    delay(150); //500
  }
  device_addr = 0xA;
  Serial.println("\n");
  Serial.print(dev_num);
  Serial.println(" devices on I2C bus\n\n");
  delay(2500);
//  #endif
}

void loop() {

  // LED pulse blink.
  digitalWrite(BUILTIN_LED, HIGH);
  delay(250);
  digitalWrite(BUILTIN_LED, LOW);
  delay(250);

  // Reset value
  i2c_data = 0;
  // Request value from available device
  Serial.print("Listening to I2C device at address: ");
  Serial.println(device_addr, HEX);
  Wire.beginTransmission(device_addr);
  // Display value if request succeeded
  if (Wire.endTransmission() == 0) {
    Wire.requestFrom(device_addr, 2);
    size_t buff_size = Wire.readBytes((uint8_t*)&i2c_data, 2);
    Serial.print("Value: ");
    Serial.println(i2c_data, HEX);
    Serial.println();
  }
  // Delay 1 second
  delay(1000);
}