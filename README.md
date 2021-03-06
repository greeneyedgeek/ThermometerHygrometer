# Thermometer Hygrometer

<p>The intent of this project is to build a small weather station that measures temperature and air humidity. </p>

<h2>Hardware Required</h2>

<ul>
  <li>Arduino Nano Board</li>
  <li>LCD Screen (compatible with Hitachi <span class="wikiword">HD44780</span> driver)</li>
  <li>DHT22 Sensor</li>
  <li>Pin headers to solder to the LCD display pins</li>
  <li>10k ohm potentiometer</li>
  <li>220 ohm resistor</li>
  <li>Jumper wires</li>
  <li>Breadboard</li>
  <li>ABS Plastic Enclosure 100*60*40mm</li>
  <li>Power source</li>
  <li>2 switches</li>
</ul>

<h2>Circuit</h2>

<img src="https://github.com/greeneyedgeek/ThermometerHygrometer/blob/master/breadboard.png" alt="">
  
LCD Screen &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; | Arduino Nano
------------------|------------
RS                | 12 
EN                | 11
D4                | 5
D5                | 4
D6                | 3
D7                | 7
RW                | GND
VSS               | Gnd
VCC               | 5V
V0                | 10K Resistor (ends 5V/GND)

Switches &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;| Arduino Nano &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
------------------|------------
Switch A          | 2 
Switch B          | 8

DHT22 Sensor &nbsp; &nbsp; | Arduino Nano &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
------------------|------------
DATA              | 6
VCC               | 3.3V 
GND               | GND

<!--
<h2>Schematic</h2>
<h2>Code</h2>
-->
<h2>See Also</h2>
<ul>
  <li><a class="urllink" href="https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay" rel="nofollow" target="_blank">Arduino LCD       Tutorial</a></li>
  <li><a class="urllink" href="http://www.fritzing.org" rel="nofollow" target="_blank">Fritzing</a></li>
  <li><a class="urllink" href="http://arduiniana.org/libraries/streaming/" rel="nofollow" target="_blank">Streaming library</a></li>
  <li><a class="urllink" href="http://eclipse.baeyens.it/" rel="nofollow" target="_blank">Sloeber IDE for Arduino</a></li>
  <li><a class="urllink" href="https://www.eclipse.org/downloads/packages/release/2018-12/r/eclipse-ide-cc-developers" rel="nofollow" target="_blank">Eclipse IDE for C/C++ Developers</a></li>
</ul>
