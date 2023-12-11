/*

  Arduino IDE
  ATTiny85
  Board: Digispark 16.5MHz (default)

  OR

  Board: ATtiny 25/45/85
  Clock: Internal 1MHz
  Processor: ATTiny85
  Programmer: USBtinyISP
  Sketch -> Upload Using Programmer


  By:     Alexander Bobkov
  Date:   Nov 30, 2023
  Update: Dec 10, 2023

  About:  Basic program written for ATTiny85 that sends data (sensor value) over I2C to a master device.

  Notes:  Use Logic 2 viewer to see data being transmitted over I2C.

*/

//#include "DigiKeyboard.h"
//#include <Wire.h>
//#include <TinyWireM.h>
#include <TinyWireS.h>
//#include <LiquidCrystal_I2C.h>

//#define USB_OUTPUT
//#define SERIAL_OUTPUT

unsigned int sensor_value = 0;
uint8_t sensor_raw = 0;
uint8_t data = 5;
bool inc = true;
unsigned int LED_PIN = 1;
//int SENSOR_PIN = A2; //4;

void setup() {             
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
//  pinMode(SENSOR_PIN, INPUT);
  TinyWireS.begin(5);
}

void loop() {

  //sensor_value = analogRead(SENSOR_PIN);
  //sensor_raw = analogRead(SENSOR_PIN);

  /*#ifdef USB_OUTPUT
  DigiKeyboard.print("ATtiny85. Sensor (");
  DigiKeyboard.print(SENSOR_PIN);
  DigiKeyboard.print("): ");
  DigiKeyboard.println(sensor_value);
  #endif
  #ifdef SERIAL_OUTPUT
  Serial.print("ATtiny85. Sensor (");
  Serial.print(SENSOR_PIN);
  Serial.print("): ");
  Serial.println(11);
  #endif*/

  for (uint8_t k = 0; k < 10; k++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);

    /*for (int n = 0; n < 25; n+=5) {
      analogWrite(LED_PIN, n);
      delay(125); 
    } 
    for (int n = 25; n >= 0; n--) {
      analogWrite(LED_PIN, n);
      delay(125);
    }*/
    TinyWireS.send(k);
  }
}
