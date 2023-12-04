/*

  Arduino IDE
  ATTiny85
  Board: Digispark 16.5MHz (default)

  By:     Alexander Bobkov
  Date:   Nov 30, 2023

  About:  Basic program written for ATTiny85 that sends data (sensor value) over I2C to a master device.

  Notes:  Use Logic 2 viewer to see data being transmitted over I2C.

*/

#include <TinyWireS.h>

//#define USB_OUTPUT
//#define SERIAL_OUTPUT

unsigned int sensor_value = 0;
uint8_t sensor_raw = 0;
uint8_t data = 0;
unsigned int LED_PIN = 1;
int SENSOR_PIN = A2; //4;

void setup() {             
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
  //pinMode(SENSOR_PIN, INPUT);
  TinyWireS.begin(5);
  #ifdef SERIAL_OUTPUT;
  Serial.begin(9600);
  Serial.println("ATTinu 85");
  #endif
}

void loop() {

  //sensor_value = analogRead(SENSOR_PIN);
  //sensor_raw = analogRead(SENSOR_PIN);

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
  Serial.println(11);
  #endif

  for (int n = 0; n < 25; n+=5) {
    analogWrite(LED_PIN, n);
    delay(125); } 
  for (int n = 25; n >= 0; n--) {
    analogWrite(LED_PIN, n);
    delay(125); }           

  TinyWireS.send(data);
  data++;
}
