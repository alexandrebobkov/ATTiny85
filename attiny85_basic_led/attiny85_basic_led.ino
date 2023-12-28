/*
  ATTiny85 I2C SLAVE device

  Arduino IDE
  ATTiny85
  Board: Digispark 16.5MHz (default)

  OR

  Controller: ATTiny 25/45/85
  Clock: Internal 1MHz
  Processor: ATTiny85
  Programmer: USBtinyISP
  Sketch -> Upload Using Programmer

  By:     Alexander Bobkov
  Date:   Nov 30, 2023
  Update: Dec 23, 2023

  About:  Basic program written for ATTiny85 that exchanges data (sensor value) over I2C between master and slave device.

  Notes:  Use Logic 2 viewer to see data being transmitted over I2C.

*/

//#include "DigiKeyboard.h"
#include <Arduino.h>
//#include <TinyWireM.h>
#include "TinyWireS.h"
//#include <LiquidCrystal_I2C.h>
#include <avr/delay.h>

// I2C address
//uint8_t address = 10;
volatile uint8_t address = 17;

// Peripheral sensor variables
uint8_t sensor_value = 0;
uint8_t sensor_raw = 0;
uint8_t data = 1;

// Built-in LEDs
unsigned int LED_SYS_PIN = 0;
unsigned int LED_PIN = 3;
int SENSOR_PIN = A2; //4;
int t_delay = 15;

// Struct for storing sensors values
struct sensors {
  uint8_t t = 0x0;  // temperature
  uint8_t p = 0x0;  // humidity
  uint8_t l = 0x0;  // illuminance
  uint8_t n = 0x0;
};

// Commands codes
typedef uint8_t command;
command cmd = 0x00;
command led_on = 0x11;
command led_off = 0x10;

enum operations {
  LED_ON, LED_OFF
};
struct registers {
  enum operations operationCode;
  union {} addresses;
};

// Serial to Parallel register
struct LM {
  unsigned int D:4; // Bitfield for storing I/O 4 bits
};

//typedef uint8_t opcode;
typedef operations opcode;

/*
  I2C Registers
*/
const byte reg_size = 4;
volatile uint16_t i2c_registers[reg_size];
volatile byte reg_position;
boolean update_request = false;

namespace COMMANDS {
  enum {
    set_output_1 = 0xB1,
    set_output_2 = 0xB2,
    read_sensor_1 = 0xC1
  };
  bool do_command(uint8_t cmd, uint16_t cmd_data) {
    switch (cmd) {
      case COMMANDS::set_output_1:
        return true;
        break;
      case COMMANDS::set_output_2:
        return true;
        break;
      case COMMANDS::read_sensor_1:
        return true;
        break;
    }
  }
}

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
  delay(t_delay*10);
  digitalWrite(LED_PIN, LOW);
  delay(t_delay*10);
  digitalWrite(LED_PIN, HIGH);
  delay(t_delay*10);
  digitalWrite(LED_PIN, LOW);
  delay(t_delay*10);
  // Send value between 0 and 10, depending on a cycle iterration
  /*if (data < 10)        
    //data++;
    sen.n = sen.n +1;
  else
    //data = 0x0;
    sen.n = 0x0;
  // Delay 0.5 second
  //TinyWireS.send(data);
  //TinyWireS.send(sen.n);
  TinyWireS.send(sensor_value);
  TinyWireS.available();*/
  delay(500);
}

void requestEvent() {

  //TinyWireS.send(t_delay);
  TinyWireS.send(cmd);
  //t_delay = 150;

  // Sends value from current register position
  /*TinyWireS.send(i2c_registers[reg_position]);

  reg_position++;
  if (reg_position >= reg_size)
    reg_position = 0;*/
}
void receiveEvent(uint8_t size) {

  cmd = TinyWireS.receive();

  if (cmd == 0x10)
    t_delay = 75;
  else if (cmd == 0x11)
    t_delay = 25;
  /*if (size < 1)
    return;
  
  reg_position = TinyWireS.receive();
  size--;
  while (size--) {
    i2c_registers[reg_position] = TinyWireS.receive();
    reg_position++;
    if (reg_position >= reg_size)
      reg_position = 0;
  }
  update_request = true;*/
}
