/*
  I2C SLAVE device

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
  Update: Dec 13, 2023

  About:  Basic program written for ATTiny85 that sends data (sensor value) over I2C to a master device.

  Notes:  Use Logic 2 viewer to see data being transmitted over I2C.

*/

//#include "DigiKeyboard.h"
#include <Arduino.h>
//#include <TinyWireM.h>
#include "TinyWireS.h"
//#include <LiquidCrystal_I2C.h>
#include <avr/delay.h>

// I2C address
uint8_t address = 10;

// Peripheral sensor variables
uint8_t sensor_value = 0;
uint8_t sensor_raw = 0;
uint8_t data = 1;

// Built-in LEDs
unsigned int LED_SYS_PIN = 0;
unsigned int LED_PIN = 3;
int SENSOR_PIN = A2; //4;

// Struct for storing sensors values
struct sensors {
  uint8_t t = 0x0;  // temperature
  uint8_t p = 0x0;  // humidity
  uint8_t l = 0x0;  // illuminance
  uint8_t n = 0x0;
};

/*
  I2C Registers
*/
const byte reg_size = 4;
volatile uint16_t i2c_registers[reg_size];
volatile byte reg_position;
boolean update_request = false;

struct sensors sen;


void setup() {       
 
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  // Initialize I2C slave device at given address.
  TinyWireS.begin(address);
  TinyWireS.onRequest(requestEvent);
  TinyWireS.onReceive(receiveEvent);
}

void loop() {

  sensor_value = analogRead(SENSOR_PIN);
  //sensor_raw = analogRead(SENSOR_PIN);

  // LED pulse blink.
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
  // Send value between 0 and 10, depending on a cycle iterration
  if (data < 10)        
    //data++;
    sen.n = sen.n +1;
  else
    //data = 0x0;
    sen.n = 0x0;
  // Delay 0.5 second
  //TinyWireS.send(data);
  //TinyWireS.send(sen.n);
  TinyWireS.send(sensor_value);
  TinyWireS.available();
  delay(500);
}

void requestEvent() {

  // Sends value from current register position
  TinyWireS.send(i2c_registers[reg_position]);

  reg_position++;
  if (reg_position >= reg_size)
    reg_position = 0;
}
void receiveEvent(uint8_t size) {
  if (size < 1)
    return;
  
  reg_position = TinyWireS.receive();
  size--;
  while (size--) {
    i2c_registers[reg_position] = TinyWireS.receive();
    reg_position++;
    if (reg_position >= reg_size)
      reg_position = 0;
  }
  update_request = true;
}
