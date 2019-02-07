/*

	Project:	ThermometerHygrometer
	File:		Sensors.cpp
	Created:	2019-01-26
	Modified:	2019-02-06
	Author:		Gabriel Fontaine-Escobar

*/

#include "Sensors.h"
using namespace ns_sensors;

const uint8_t Sensors::DHTTYPE{22}; //DHT22
const uint8_t Sensors::DHTPIN{6};
bool Sensors::isFahrenheit{false};
DHT Sensors::dht(DHTPIN, DHTTYPE);

float Sensors::get_temperature(bool isFarenheit)
{

	return dht.readTemperature(isFarenheit);

}

float Sensors::get_humidity()
{

	return dht.readHumidity();

}

float Sensors::get_heat_index(float temperature, float humidity, bool isFahrenheit)
{

	return dht.computeHeatIndex(temperature, humidity, isFahrenheit);

}

float Sensors::convertFtoC(float temperature)
{

	return dht.convertFtoC(temperature);

}

float Sensors::convertCtoF(float temperature)
{

	return dht.convertCtoF(temperature);

}
