/*

Arduino IDE
Board: Digispark 16.5MHz (default)

Alexander Bobkov
Nov 30, 2023

*/

#include "DigiKeyboard.h"
//#include <Wire.h>
#include <TinyWireM.h>

//#define USB_OUTPUT
//#define SERIAL_OUTPUT

unsigned int sensor_value = 0;
uint8_t sensor_raw = 0;
unsigned int LED_PIN = 1;
int SENSOR_PIN = A2; //4;

void setup() {             
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  //Wire.begin();
  TinyWireM.begin();
  #ifdef SERIAL_OUTPUT
  Serial.begin(9600);
  Serial.println("ATTinu 85");
  #endif
}

void loop() {

  sensor_value = analogRead(SENSOR_PIN);
  sensor_raw = analogRead(SENSOR_PIN);
  //readInput();

  #ifdef USB_OUTPUT
  DigiKeyboard.print("ATtiny85. Sensor (");
  DigiKeyboard.print(SENSOR_PIN);
  DigiKeyboard.print("): ");
  DigiKeyboard.println(sensor_value);
  #endif
  #ifdef SERIAL_OUTPUT
  Serial.print("ATtiny85. Sensor (");
  Serial.print(SENSOR_PIN);
  Serial.print("): ");
  Serial.println(sensor_value);
  #endif

  for (int n = 5; n < 25; n+=5)
  {
    analogWrite(LED_PIN, n);
    delay(125);
  } 
  for (int n = 25; n >= 5; n--)
  {
    analogWrite(LED_PIN, n);
    delay(125);
  }           

  /*Wire.beginTransmission(10);
  Wire.write(sensor_raw);*/
  TinyWireM.beginTransmission(10);
  TinyWireM.send(sensor_raw);
  TinyWireM.endTransmission();
  //Wire.endTransmission();
}

/*void readInput()
{
  sensor_value = analogRead(SENSOR_PIN);
  sensor_raw = analogRead(SENSOR_PIN);
}

void sendInput()
{
  Wire.write(sensor_raw);
}*/
