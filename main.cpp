/*
 * GroundFloorAutomation.cpp
 *
 * Created: 11/5/2016 6:18:33 AM
 * Author : rohsins
 */ 


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "LCDheader(rohsins).h"

int main(void)
{
	DDRB = 0xFF;
	DDRA = 0x00;
	DDRD |= (1 << 5) | (1 << 3) | (1 << 1);
	
	PORTA = 0xFF;
	
	lcd_initialize();
	lcd(0x01,0);
	_delay_ms(10);
	lcd((char *)"Welcome");
	
	int i = 0;
	int data[26];
	//unsigned int FacilityCode = 0;
	//unsigned int CardNumber = 0;
	uint16_t FacilityCode = 0;
	uint16_t CardNumber = 0;
	while (1) {
		if ((PINA & 0x03) == 0x01) {
			data[i] = 0;
			i++;
			while ((PINA & 0x03) == 0x01);
		} 
		if ((PINA & 0x03) == 0x02) {
			data[i] = 1;
			i++;
			while ((PINA & 0x03) == 0x02);
		}
		if (i==26) {
			for (int j = 1; j < 25; j++) { 
				if (j < 9) {
					FacilityCode |= data[j] << (8-j);
				} else {
					CardNumber |= data[j] << (24-j);
				}
			}
			lcd(0x80,0);
			lcd((char *)"FC: ");
			lcd(FacilityCode);
			lcd((char *)" ");
			if (FacilityCode == 188 && CardNumber == 34962) {
				lcd((char *)"rohsins");
			}
			lcd(0xC0,0);
			lcd((char *)"CN: ");
			lcd(CardNumber);
			lcd((char *)"   ");
			memset(data, 0, sizeof(data));
			i = 0;
		}
	}
}

