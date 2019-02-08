/*

	Project:	ThermometerHygrometer
	File:		Sensors.h
	Created:	2019-01-26
	Modified:	2019-02-07
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
		static float update_temperature();
		static float update_humidity();
		static float update_heat_index(float*, float*);
		static float get_max_temperature();
		static float get_min_temperature();
		static float get_max_humidity();
		static float get_min_humidity();
		static float convertCtoF(float);
		static float convertFtoC(float);
		static char get_units();
		static bool get_is_fahrenheit();
		static void toggle_units();

	private:
		static DHT dht;
		static const uint8_t DHTTYPE;
		static const uint8_t DHTPIN;
		static bool is_fahrenheit;
		static float max_temperature;
		static float min_temperature;
		static float max_humidity;
		static float min_humidity;

	};
}

#endif
