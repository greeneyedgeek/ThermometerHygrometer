/*

	Project:	ThermometerHygrometer
	File:		ThermometerHygrometer.ino
	Created:	2019-01-26
	Modified:	2019-02-11
	Author:		Gabriel Fontaine-Escobar

	The following code was used as a starting point:
	https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/main.cpp
	https://github.com/arduino-libraries/LiquidCrystal/blob/master/examples/HelloWorld/HelloWorld.ino

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

// Include the contents of a these files
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
const uint16_t BASE_DELAY{1000};

// A variable to store the millis() value
uint32_t timer;

// To call our sensors functions
ns_sensors::Sensors sensors;

// To call our display functions
ns_out::Display display;

// To know if we need to display the stats
bool is_display_stats{false};

// Updates the temperature and humidity data to the LCD and Serial
void update()
{
	sensors.update();

	// Output data
	display.lcd_out(sensors.get_current_temperature(), sensors.get_current_humidity(), sensors.get_units());
	display.lcd_heat_index(sensors.get_heat_index(), sensors.get_units());
	display.serial_out(sensors.get_current_temperature(), sensors.get_current_humidity(),
					   sensors.get_heat_index(), sensors.get_units());

	// Reset the timer
	timer = millis();
}

// Displays the temperature and humidity stats
void display_stats()
{
	// Update the ensure we have the latest data
	update();

	// Display the stats on the LCD screen
	display.lcd_stats(sensors.get_max_temperature(), sensors.get_min_temperature(), sensors.get_units(),
					  sensors.get_max_humidity(), sensors.get_min_humidity(), sensors.get_heat_index());

	// Reset the bool value
	is_display_stats = !is_display_stats;

}

// Changes the units then updates the display
void toggle_units()
{
	delay(BASE_DELAY);
	sensors.toggle_units();
	update();
}

// This function is called when the PIN_INTERRUPT is toggled
void interrupt()
{
	// Change the bool value so that the display_stats() function will be called
	is_display_stats = !is_display_stats;
}

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

int main(void)
{
	init();

	initVariant();

#if defined(USBCON)
	USBDevice.attach();
#endif

	// Setup pins
	pinMode(PIN_UNITS, INPUT_PULLUP);
	pinMode(PIN_INTERRUPT, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), &interrupt, FALLING);

	// Setup display
	display.init_output();
	delay(3*BASE_DELAY);
	update();

	// Start the timer
	timer = millis();

	// This is the main loop
	for (;;)
	{
		// Update data every minute
		if (millis() - timer > 60*BASE_DELAY) { update(); }

		// Display min and max values if is_display_stats is true
		if (is_display_stats) { display_stats(); }

		// Change the units of the temperature variables if PIN_UNITS is low
		if (digitalRead(PIN_UNITS) == LOW) { toggle_units(); }

		if (serialEventRun) serialEventRun();
	}

	return 0;
}
