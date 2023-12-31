<h2>ATTiny85 Inside</h2>

<div><p><i>A customizable I2C peripheral slave device powered by ATTiny85 controller. Build your own I2C device.</i></p></div>

<div><p>An eco-system of ESP32 and ATTiny85 microcontrollers. ESP32 serves a function of I2C master device, primarily for demonstration purposes. ATTiny85 serves a function of I2C slave device, i.e. peripheral.</p></div>

<img src="https://github.com/alexandrebobkov/ATTiny85/blob/main/assets/attiny85-chip.jpg" style="width:200px;" alt="ATTiny85">
<h3>Pins Reservations</h3>
<p>
 <li>PB3 - Status LED</li>
 <li>PB4 - Sensor</li>
 <li>PB0 - I2C SDA</li>
 <li>PB2 - I2C SCL</li>
</p>
<h3>Operations Codes</h3>
<li>0x10: LED high pulse</li>
<li>0x11: LED low pulse</li>
<li>0x12: LED steady</li>

<img src="https://github.com/alexandrebobkov/ATTiny85/blob/main/assets/attiny85-pinout-1.jpg" style="width:40%;" alt="ATTiny85 Pinout">
