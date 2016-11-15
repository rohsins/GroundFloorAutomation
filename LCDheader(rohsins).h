#ifndef _LCDheader_H_
#define _LCDheader_H_
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

void lcd(unsigned char command,unsigned char what)
{
	PORTB = command;
	PORTD = 0<<PD1 | 0<<PD3 | 1<<PD5;
	_delay_us(45);
	PORTD = 0<<PD1 | 0<<PD3 | 0<<PD5;
	_delay_us(45);
}

void lcd(unsigned char data)
{	
	PORTB = data;
	PORTD = 1<<PD1 | 0<<PD3 | 1<<PD5;
	_delay_us(45);
	PORTD = 1<<PD1 | 0<<PD3 | 0<<PD5;
	_delay_us(45);
}

void lcd(char *string)
{
	unsigned int c=0;
	while(string[c]!='\0')
		{
		lcd(string[c]);
		c++;
		}
}

void lcd(int data)
{
	char temp[40];
	//itoa(data,temp,10);
	sprintf(temp, "%d", data);
	lcd(temp);	
}

void lcd(uint16_t data)
{
	char temp[40];
	//itoa(data,temp,10);
	sprintf(temp, "%u", data);
	lcd(temp);
}

void lcd_initialize()
{
	lcd(0x38,0);
	lcd(0x0C,0);	
}

#endif