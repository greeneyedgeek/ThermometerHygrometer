/*

	Project:	ThermometerHygrometer
	File:		Display.h
	Created:	2019-01-26
	Modified:	2019-02-06
	Author:		Gabriel Fontaine-Escobar

*/

#ifndef Display_h
#define Display_h

#include <Streaming.h>
#include <stdint.h>
#include <LiquidCrystal.h>

namespace ns_out
{
	class Display
	{

	public:
		void init_output();
		void lcd_out(float*, float*, bool*);
		void lcd_clear_bottom();
		void lcd_stats_temp(float*, float*, bool*);
		void lcd_stats_hum(float*, float*);
		void lcd_heat_index(float*, bool*);
		void serial_out(float*, float*, float*);

	private:
		static const uint8_t LCD_LENGHT, LCD_HEIGHT, RS, EN, D4, D5, D6, D7;
		static LiquidCrystal lcd;

	};
}

#endif
