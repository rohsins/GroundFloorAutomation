/*
 * GroundFloorAutomation.cpp
 *
 * Created: 11/5/2016 6:18:33 AM
 * Author : rohsins
 */ 


#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <string.h>
//#include "LCDheader(rohsins).h"

volatile uint8_t time = 0;

ISR(TIMER1_OVF_vect) {
	time++;
	if (time >= 204) {
		time = 0;
		WDTCR = (1 << WDE);
		while (1);
	}
}

void OpenDoor(void) {
	PORTC |= (1 << PD0);
	_delay_ms(100);
	PORTC &= ~(1 << PD0);
}

int main(void)
{
	//DDRB = 0xFF;
	DDRA = 0x00;
	DDRC = 0xFF;
	//DDRD |= (1 << 5) | (1 << 3) | (1 << 1);
	
	PORTA = 0xFF;
	PORTC = 0x00;
	
	sei();
	TCCR1B |= (1 << CS12) | (1 << CS10); //prescalar /1024
	TIMSK |= (1 << TOIE1);
	TCNT1 = 0;
	
	//lcd_initialize();
	//lcd(0x01,0);
	//_delay_ms(10);
	//lcd((char *)"Welcome");
	
	int i = 0;
	int data[26];
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
			if (FacilityCode == 188 && CardNumber == 34962) {
				OpenDoor();
			} else if (FacilityCode == 180 && CardNumber == 53992) {
				OpenDoor();
			} else if (FacilityCode == 220 && CardNumber == 53992) {
				OpenDoor();
			} else if (FacilityCode == 70 && CardNumber == 54248) {
				OpenDoor();
			} else if (FacilityCode == 93 && CardNumber == 54248) {
				OpenDoor();
			} else if (FacilityCode == 225 && CardNumber == 53992) {
				OpenDoor();
			} else if (FacilityCode == 147 && CardNumber == 53992) {
				OpenDoor();
			} else if (FacilityCode == 175 && CardNumber == 53736) {
				OpenDoor();
			} else if (FacilityCode == 54 && CardNumber == 54248) {
				OpenDoor();
			} else if (FacilityCode == 207 && CardNumber == 53992) {
				OpenDoor();
			} else {
				//lcd(0x01, 0);
				//lcd(0x80,0);
				//lcd((char *)"FC: ");
				//lcd(FacilityCode);
				//lcd((char *)" ");
				//lcd(0xC0,0);
				//lcd((char *)"CN: ");
				//lcd(CardNumber);
				//lcd((char *)"   ");
			}
			//memset(data, 0, sizeof(data));
			FacilityCode = 0;
			CardNumber = 0;
			i = 0;
		}
	}
}

