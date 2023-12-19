/*
  ATTiny85 Blink
  Basic scetch to test functionality of ATTiny85 development board.

  Cycles LED on and off for a quarter of second.
  Dims on and off external LED.

  December 10, 2023
  by: Alexander Bobkov

  On-board LED.
  Different pin is used on different boards.
  DigiSpark PIN # is 1
  ATTiny Programmer PIN # is 0
  
  Board: ATtiny 25/45/85
  Clock: Internal 1MHz
  Processor: ATTiny85
  Programmer: USBtinyISP
  Sketch -> Upload Using Programmer

*/
#define HW-280  // ATtiny85 PCB micro-USB Development board (Arduino Digispark compatible)
//#define TinyAVR // USB tiny ISP programmer board

#ifdef HW-280
  unsigned int LED_SYS_PIN = 0;
  unsigned int LED_PIN = 1;
#endif

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs.
  pinMode(LED_SYS_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  blink_status(1);
  for (int n = 0; n < 255; n+=5) {
    analogWrite(LED_PIN, n);
    delay(125); 
  } 
  for (int n = 255; n >= 0; n--) {
    analogWrite(LED_PIN, n);
    delay(125);
  } 
}

void blink_status(int status) {
  if (status == 1) {  // status O.K.
    digitalWrite(LED_SYS_PIN, HIGH);
    delay(250);
    digitalWrite(LED_SYS_PIN, LOW);
    delay(250);
    digitalWrite(LED_SYS_PIN, HIGH);
    delay(250);
    digitalWrite(LED_SYS_PIN, LOW);
  }
}
