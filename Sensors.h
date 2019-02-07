/*

	Project:	ThermometerHygrometer
	File:		Sensors.h
	Created:	2019-01-26
	Modified:	2019-02-06
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
		float get_temperature(bool);
		float get_humidity();
		float get_heat_index(float, float, bool);
		float convertCtoF(float);
		float convertFtoC(float);

	private:
		static const uint8_t DHTTYPE;
		static const uint8_t DHTPIN;
		static DHT dht;
		static bool isFahrenheit;

	};
}

#endif
