/*

	Project:	ThermometerHygrometer
	File:		ThermometerHygrometer.cpp
	Created:	2019-01-26
	Modified:	2019-02-06
	Author:		Gabriel Fontaine-Escobar

	LCD Hello World example code was used as a starting point.
	http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

	This code is in the public domain.
	https://github.com/greeneyedgeek/ThermometerHygrometer

	The circuit:
	* LCD RS pin to digital pin 12
	* LCD Enable pin to digital pin 11
	* LCD D4 pin to digital pin 5
	* LCD D5 pin to digital pin 4
	* LCD D6 pin to digital pin 3
	* LCD D7 pin to digital pin 7
	* LCD R/W pin to ground
	* LCD VSS pin to ground
	* LCD VCC pin to 5V
	* 10K resistor:
	* ends to +5V and ground
	* wiper to LCD VO pin (pin 3)
	* DHT pin to digital pin 6
	* DHT VCC pin to 3.3V
	* DHT GND pin to ground
	* Switch to pin 2
	* Switch to pin 8

*/

// Includes used in this sketch
#include <Arduino.h>
#include "Display.h"
#include "Sensors.h"

// Function prototypes
void update();
void display_stats();
void toggle_units();
void interrupt();

// These are the pins the switches are plugged to
const uint8_t PIN_INTERRUPT{2};
const uint8_t PIN_UNITS{8};

// A constant for our timer
const uint16_t base_delay{1000};

// Maximum and minimum values
const float MAX{9999};
const float MIN{-9999};

// A variable to store the millis() value
uint32_t timer;

// To call our sensors functions
ns_sensors::Sensors sensors;

// To call our display functions
ns_out::Display display;

// To toggle between Celsius and Fahrenheit
bool is_fahrenheit{false};

// To know if need to display the stats
bool is_display_stats{false};

// To store our current data
float current_temperature;
float current_humidity;
float heat_index;

// To keep track of the temperature and humidity
float max_temperature{MIN}, min_temperature{MAX};
float max_humidity{MIN},  min_humidity{MAX};

// Updates the temperature and humidity data to the LCD and Serial
void update()
{
	// Fetch new data
	current_temperature = sensors.get_temperature(is_fahrenheit);
	current_humidity = sensors.get_humidity();
	heat_index = sensors.get_heat_index(current_temperature, current_humidity, is_fahrenheit);

	// Check if we need to update max and min values
	max_temperature = current_temperature > max_temperature ? current_temperature : max_temperature;
	min_temperature = current_temperature < min_temperature ? current_temperature : min_temperature;
	max_humidity = current_humidity > max_humidity ? current_humidity : max_humidity;
	min_humidity = current_humidity < min_humidity ? current_humidity : min_humidity;

	// Output data
	display.lcd_out(&current_temperature, &current_humidity, &is_fahrenheit);
	display.lcd_heat_index(&heat_index, &is_fahrenheit);
	display.serial_out(&current_temperature, &current_humidity, &heat_index);

	// Reset the timer
	timer = millis();
}

// Displays the temperature and humidity stats
void display_stats()
{
	// Update the ensure we have the latest data
	update();

	// Display the stats on the LCD screen
	display.lcd_stats_temp(&max_temperature, &min_temperature, &is_fahrenheit);
	delay(2*base_delay);
	display.lcd_stats_hum(&max_humidity, &min_humidity);
	delay(2*base_delay);

	// Reset the bool value
	is_display_stats = !is_display_stats;

	// Update the display to get back to the main display
	update();
}

// Changes the units then updates the display
void toggle_units()
{
	// To ensure the function is only called once when the switch is activated
	delay(base_delay);

	// Toggle between Celsius and Fahrenheit
	if (is_fahrenheit)
	{
		max_temperature = sensors.convertFtoC(max_temperature);
		min_temperature = sensors.convertFtoC(min_temperature);

	} else
	{
		max_temperature = sensors.convertCtoF(max_temperature);
		min_temperature = sensors.convertCtoF(min_temperature);
	}

	// Change the bool value
	is_fahrenheit = !is_fahrenheit;

	// Update the display to see the change
	update();
}

// This function is called when the PIN_INTERRUPT is toggled
void interrupt()
{
	// Change the bool value so that the display_stats() function will be called
	is_display_stats = !is_display_stats;
}

void setup()
{
	// These are the pins our switches are attached to
	pinMode(PIN_UNITS, INPUT_PULLUP);
	pinMode(PIN_INTERRUPT, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), &interrupt, FALLING);

	// A loading screen to let the sensor output its first data
	display.init_output();
	delay(3*base_delay);
	update();

	// Set timer value
	timer = millis();
}

void loop()
{
	// Update data every minute
	if (millis() - timer > 60*base_delay) { update(); }

	// Display min and max values if is_display_stats is true
	if (is_display_stats) { display_stats(); }

	// Change the units of the temperature variables if PIN_UNITS is low
	if (digitalRead(PIN_UNITS) == LOW) { toggle_units(); }
}

