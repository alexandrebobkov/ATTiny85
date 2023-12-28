#include <Arduino.h>
#include <LCD-I2C.h>
#include <Wire.h>

LCD_I2C lcd(0x27, 16, 2);

// I2C peripheral address
uint8_t address = 0;
uint8_t i2c_data, device_addr;

unsigned int sw = 5;  //  D5

// 40 pixels
uint8_t char1 [8] = {
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100
};
uint8_t char2 [8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111
};
uint8_t pixel;
uint8_t cmd = 0x00;
size_t buff_size;

void setup() {
  
  pinMode(sw, INPUT_PULLDOWN);

  Serial.begin(9600);
  Serial.println("LCD");

  lcd.begin();
  lcd.clear();
  lcd.display();
  lcd.backlight();
  lcd.setCursor(0, 0);   // Line 1, column 1
  //lcd.write(0);
  //lcd.print(" HAPPY HOLIDAYS ");
  lcd.print(" I2C Bus Scanner ");
  //lcd.displayOff();  
  
  lcd.createChar(0, char1);
  lcd.createChar(0, char2);
  lcd.setCursor(1, 1);
  lcd.write(0);
  lcd.setCursor(2, 1);
  lcd.write(1);

  delay(500);
  pixel = char1[0];
  pixel << 1;
  char1[1] = pixel;
  lcd.createChar(1, char1);
  lcd.setCursor(2, 1);
  lcd.write(1);
  delay(500);

  pixel = char1[0];
  pixel << 4;
  char1[3] = pixel;
  lcd.createChar(2, char1);
  lcd.setCursor(3, 1);
  lcd.write(2);

  //Wire.begin(address);
  lcd.setCursor(0, 2);
  lcd.print("Addr: ");
  delay(2500);
  Wire.begin();
  Serial.println("I2C");
  int dev_num = 0;  //Save number of devices connected to I2C bus
  Serial.println("I2C scan ...");
  for (address = 1; address < 127; address++)
  {
    //Serial.print("Address: ");
    //Serial.println(address, HEX);
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
      //lcd.setCursor(uint8_t column, uint8_t row);
      lcd.setCursor(7, 2);
      //lcd.print("0A");
      lcd.print("   ");
      lcd.setCursor(7, 2);
      lcd.print(address);
    }
    else if (Wire.endTransmission() == 4)
      Serial.println("I2C unknown error.");
    delay(150); //500
  }

  device_addr = 0xA;
  lcd.setCursor(7, 2);
  lcd.print("   ");
  lcd.setCursor(7, 2);
  lcd.print(device_addr);
}

void loop() {

  delay(1000);

  device_addr = 0xA;
  Serial.print("Listening to I2C device at address: ");
  Serial.println(device_addr, HEX);
  Wire.beginTransmission(device_addr);
  // Display value if request succeeded
  if (Wire.endTransmission() == 0) {
    Wire.requestFrom(device_addr, 2);
    buff_size = Wire.readBytes((uint8_t*)&i2c_data, 2);
    delay(500);
    Serial.print("Value: 0x");
    Serial.print(i2c_data, HEX);
    Serial.print(" (");
    Serial.print(i2c_data, DEC);
    Serial.println(")");
    Serial.println();
  }
  lcd.setCursor(13, 2);
  lcd.print(i2c_data);
  Wire.endTransmission();
  // Delay 1 second
  delay(500);

  // Change the state of an output on ATtiny85 device at address 17
  if (!digitalRead(sw))
    cmd = 0x10; // if switch is not pressed -> send LED off command
  if (digitalRead(sw))
    cmd = 0x12; // if switch is pressed -> send LED on command
  //cmd = 0x11;                   // Command 0x11 corresponds to LED ON
  Serial.print("Device at addr 17. Sent command: 0x");
  Serial.println(cmd, HEX);
  Wire.beginTransmission(17);   // Begin transmission to device at address 17
  Wire.write(cmd);              // Write command to a device at address 17
  Wire.endTransmission();       // End transmission with device at address 17
  Wire.beginTransmission(17);   // Begin transmission to device at address 17
  Wire.requestFrom(17, 2);      // Request 2 bytes from a device at address 17
  buff_size = Wire.readBytes((uint8_t*)&i2c_data, 4);
  Wire.endTransmission();       // End transmission with device at address 17
  Serial.print("Confirmed command: 0x");
  Serial.println(i2c_data, HEX);

  // if Switch is pressed
  Serial.println(digitalRead(sw));

    

}
