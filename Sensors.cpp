/*

	Project:	ThermometerHygrometer
	File:		Sensors.cpp
	Created:	2019-01-26
	Modified:	2019-02-11
	Author:		Gabriel Fontaine-Escobar

*/

#include "Sensors.h"
using namespace ns_sensors;

// Maximum and minimum values
const float MAX{9999};
const float MIN{-9999};

const uint8_t Sensors::DHTTYPE{22}; //DHT22
const uint8_t Sensors::DHTPIN{6};

bool Sensors::is_fahrenheit{false};
DHT Sensors::dht(DHTPIN, DHTTYPE);

float Sensors::current_temperature;
float Sensors::current_humidity;
float Sensors::heat_index;
float Sensors::max_temperature{MIN};
float Sensors::min_temperature{MAX};
float Sensors::max_humidity{MIN};
float Sensors::min_humidity{MAX};

void Sensors::update()
{
	current_temperature = dht.readTemperature(is_fahrenheit);
	max_temperature = current_temperature > max_temperature ? current_temperature : max_temperature;
	min_temperature = current_temperature < min_temperature ? current_temperature : min_temperature;

	current_humidity = dht.readHumidity();
	max_humidity = current_humidity > max_humidity ? current_humidity : max_humidity;
	min_humidity = current_humidity < min_humidity ? current_humidity : min_humidity;

	heat_index = dht.computeHeatIndex(current_temperature, current_humidity, is_fahrenheit);
}

float Sensors::get_current_temperature()
{
	return current_temperature;
}

float Sensors::get_max_temperature()
{
	return max_temperature;
}

float Sensors::get_min_temperature()
{
	return min_temperature;
}

float Sensors::get_current_humidity()
{
	return current_humidity;
}

float Sensors::get_max_humidity()
{
	return max_humidity;
}

float Sensors::get_min_humidity()
{
	return min_humidity;
}

float Sensors::get_heat_index()
{
	return heat_index;
}

float Sensors::convert_f_to_c(float temperature)
{
	return dht.convertFtoC(temperature);
}

float Sensors::convert_c_to_f(float temperature)
{
	return dht.convertCtoF(temperature);
}

char Sensors::get_units()
{
	return is_fahrenheit ? 'F' : 'C';
}

bool Sensors::get_is_fahrenheit()
{
	return is_fahrenheit;
}

void Sensors::toggle_units()
{
	// Toggle between Celsius and Fahrenheit
	if (is_fahrenheit)
	{
		max_temperature = convert_f_to_c(max_temperature);
		min_temperature = convert_f_to_c(min_temperature);

	} else
	{
		max_temperature = convert_c_to_f(max_temperature);
		min_temperature = convert_c_to_f(min_temperature);
	}

	// Change the bool value
	is_fahrenheit = !is_fahrenheit;

}
