/*

	Project:	ThermometerHygrometer
	File:		Display.cpp
	Created:	2019-01-26
	Modified:	2019-02-07
	Author:		Gabriel Fontaine-Escobar

*/

#include "Display.h"
using namespace ns_out;

const uint8_t Display::LCD_LENGHT{16};
const uint8_t Display::LCD_HEIGHT{2};
const uint8_t Display::RS{12};
const uint8_t Display::EN{11};
const uint8_t Display::D4{5};
const uint8_t Display::D5{4};
const uint8_t Display::D6{3};
const uint8_t Display::D7{7};
LiquidCrystal Display::lcd(RS, EN, D4, D5, D6, D7);

void Display::init_output()
{
	lcd.begin(LCD_LENGHT, LCD_HEIGHT);
	lcd << "WEATHER STATION";

	Serial.begin(9600);
}

void Display::lcd_out(float temperature, float humidity, char units)
{

	lcd.setCursor(0, 0);
		lcd
		<< _FLOAT(temperature,2) << (char)223
		<< units << ' '
		<< _FLOAT(humidity, 2) << "%   ";

}

void Display::lcd_clear_bottom()
{

	lcd.setCursor(0, 1);
	lcd << _FILL(' ', LCD_LENGHT);

}

void Display::lcd_heat_index(float heat_index, char units)
{

	lcd.setCursor(0, 1);
	lcd << "Heat Index: " << _FLOAT(heat_index,0) << (char)223
	<< units;

}

void Display::lcd_stats(float max_temperature, float min_temperature, char units,
						   float max_humidity, float min_humidity, float heat_index)
{

	lcd_stats_temp(max_temperature, min_temperature, units);
	delay(2000);
	lcd_stats_hum(max_humidity, min_humidity);
	delay(2000);
	lcd_heat_index(heat_index, units);

}

void Display::lcd_stats_temp(float max_temperature, float min_temperature, char units)
{

	lcd_clear_bottom();
	lcd.setCursor(0, 1);
	lcd
	<< _FLOAT(min_temperature, 2)
	<< " -> " << _FLOAT(max_temperature, 2)
	<< (char)223 << units;


}

void Display::lcd_stats_hum(float max_humidity, float min_humidity)
{

	lcd_clear_bottom();
	lcd.setCursor(0, 1);
	lcd
	<< _FLOAT(min_humidity, 2)
	<< " -> " << _FLOAT(max_humidity, 2)
	<< "%";

}

void Display::serial_out(float temperature, float humidity, float heat_index, char units)
{

	Serial
	<< "Temperature: " << _FLOAT(temperature,2) << units
	<< " Humidity: " << _FLOAT(humidity, 2)
	<< " %, Heat Index: " << _FLOAT(heat_index,2) << units << endl;
	Serial.flush();

}
