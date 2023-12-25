#include <LCD-I2C.h>
#include <Wire.h>

//LCD_I2C lcd(0x27, 16, 2);

// I2C peripheral address
uint8_t address = 10;
uint8_t i2c_data, device_addr;

// 40 pixels
uint8_t char1 [8] = {
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
uint8_t pixel;

void setup() {
  // put your setup code here, to run once:

  /*lcd.begin();
  lcd.clear();
  lcd.display();
  lcd.backlight();
  lcd.setCursor(0, 0);   // Line 1, column 1
  //lcd.write(0);
  lcd.print(" HAPPY HOLIDAYS ");
  //lcd.displayOff();  
  
  lcd.createChar(0, char1);
  lcd.setCursor(1, 1);
  lcd.write(0);

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
  lcd.write(2);*/

  //Wire.begin(address);
  delay(2500);
  Wire.begin();
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
    size_t buff_size = Wire.readBytes((uint8_t*)&i2c_data, 2);
    Serial.print("Value: ");
    Serial.println(i2c_data, HEX);
    Serial.println();
  }
  // Delay 1 second
  delay(1000);

  /*for (int i = 0; i < 125; i++) {
    //lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("0x");
    delay(500);
  }*/
  // put your main code here, to run repeatedly:
  /*lcd.setCursor(0, 1);              // Line 2
  lcd.print(" ESP32 S2 mini ");
  for (int i = 0; i < 16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(200);
  }*/

  

}
