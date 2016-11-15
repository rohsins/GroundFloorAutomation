#ifndef _LCDheader_H_
#define _LCDheader_H_

#include <util/delay.h>
#include <stdlib.h>

#define dataPort PORTB
#define metaDataPort PORTD
#define RS PD1
#define RW PD3
#define EN PD5

void lcd(unsigned char command,unsigned char what)
{
	dataPort = command;
	metaDataPort |= 0<<RS | 0<<RW | 1<<EN;
	_delay_us(45);
	metaDataPort |= 0<<RS | 0<<RW | 0<<EN;
	_delay_us(45);
}

void lcd(unsigned char data)
{	
	dataPort = data;
	metaDataPort = 1<<RS | 0<<RW | 1<<EN;
	_delay_us(45);
	metaDataPort = 1<<RS | 0<<RW | 0<<EN;
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
	itoa(data,temp,10);
	lcd(temp);	
}

void lcd_initialize()
{
	//DDRB = 0xFF;
	//DDRD |= (1 << 5) | (1 << 3) | (1 << 1);
	
	lcd(0x38,0);
	lcd(0x0C,0);	
}

#endif