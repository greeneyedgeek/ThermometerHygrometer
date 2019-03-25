/*

	Project:	ThermometerHygrometer
	File:		Sensors.h
	Created:	2019-01-26
	Modified:	2019-02-11
	Author:		Gabriel Fontaine-Escobar

*/

#ifndef Sensors_h
#define Sensors_h

#include <stdint.h>
#include <DHT.h>

namespace ns_sensors
{
	class Sensors
	{

	public:
		static void update();
		static float get_current_temperature();
		static float get_max_temperature();
		static float get_min_temperature();
		static float get_current_humidity();
		static float get_max_humidity();
		static float get_min_humidity();
		static float get_heat_index();
		static float convert_c_to_f(float);
		static float convert_f_to_c(float);
		static char get_units();
		static bool get_is_fahrenheit();
		static void toggle_units();

	private:
		static DHT dht;
		static const uint8_t DHTTYPE;
		static const uint8_t DHTPIN;
		static bool is_fahrenheit;
		static float current_temperature;
		static float max_temperature;
		static float min_temperature;
		static float current_humidity;
		static float max_humidity;
		static float min_humidity;
		static float heat_index;

	};
}

#endif
