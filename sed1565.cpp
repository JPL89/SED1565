/*
	@File 		sed1565.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		16/09/21
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "sed1565.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

void SED1565::Serial_Write(unsigned char data)
{
	int i = 0;
	
	for (i=7; i>=0; i--)
	{
		SED1565_SCK_LOW;
		
		if(data & (1 << i))
			SED1565_MOSI_HIGH;	
		else
			SED1565_MOSI_LOW;
		
		SED1565_SCK_HIGH;
	}
}

void SED1565::Char(unsigned char data, const unsigned char Font[])
{
	unsigned char wd				= pgm_read_byte( &Font[0] );	// font width
	unsigned char pg				= pgm_read_byte( &Font[2] );	// font pages
	unsigned char st				= pgm_read_byte( &Font[3] );	// font start
	unsigned char ch				= 0;							// character
	unsigned char fh				= 5;							// font header size
	unsigned char cl				= 0;							// col
	unsigned int i					= 0;							// width * width ...
	unsigned int rw					= 0;							// rows
	
	int id = ( ( ( data - st) * ( (wd+1) * 2) + fh ) );
	
	unsigned char character_width = pgm_read_byte( &Font[ id ] );
	
	Set_Cursor(X, Y);
	
	for (cl=0; cl<pg; cl++)
	{
		Set_Cursor(X, Y + cl);
		
		for (; rw < (wd + i); rw++)
		{
			ch = pgm_read_byte( &Font[ (id + rw) + 2 ] );
			
			Write_Char( ch );
		}
		
		i += wd;
	}
	
	X += character_width + 1;
}

void SED1565::String(const char * data, unsigned char x, unsigned char y, const unsigned char Font[])
{
	SED1565::X = x;
	SED1565::Y = y;
	
	while(*data)
	{
		SED1565::Char(*data++, Font);
	}
}

void SED1565::Write_Char(unsigned char data)
{
	SED1565_DC_HIGH;
	SED1565_CS_LOW;
	
	Serial_Write( data );
	
	SED1565_CS_HIGH;
}

void SED1565::Write_Command(unsigned char cmd)
{
	SED1565_DC_LOW;
	SED1565_CS_LOW;
	
	Serial_Write( cmd );
	
	SED1565_CS_HIGH;
}

void SED1565::Set_Cursor_8x(unsigned char x, unsigned char y)
{
	// Column Address Set
	x <<= 3; // x*8
	Write_Command(0x10 | (x>>4));
	Write_Command(x & 0x0f);
	
	// Page Address Set
	Write_Command(0xB0 | y); 
}

void SED1565::Set_Cursor(unsigned char x, unsigned char y)
{
	// Column Address Set
	Write_Command(0x10 | (x>>4));
	Write_Command(x & 0x0f);
	
	// Page Address Set
	Write_Command(0xB0 | y); 
}

void SED1565::Rotation(unsigned bit)
{
	SED1565::Write_Command(0xC0 | (bit << 3));
}

void SED1565::Clear(unsigned char x, unsigned char y, unsigned char width, unsigned char Pages)
{
	SED1565::X = x;
	SED1565::Y = y;
	
	for (unsigned char i=0; i<Pages; i++)
	{
		SED1565::Write_Command(0xB0 |  ( SED1565::Y + i));
		
		SED1565::Write_Command(0x10 | SED1565::X >> 4);
		SED1565::Write_Command(0x0F & SED1565::X);
		
		for (unsigned char k=0; k<width; k++)
		{
			SED1565::Write_Char( 0 );
		}
	}
}

// DrawImage Max 128x64 = 896
// Ex: DrawImage(0, 0, 128, 8, Image_Area);
// Ex: Draw a Pic from 0 to 128 7x
void SED1565::DrawImage(
const unsigned char Buffer[],
unsigned char x,
unsigned char y,
unsigned char Width,
unsigned char Pages)
{
	unsigned int j = 0;
	
	unsigned int i = 0;
	
	for (unsigned char k=0; k<Pages; k++)
	{
		SED1565::Write_Command(0xB0 | (y + k));
		
		SED1565::Write_Command(0x10 | (x >> 4));
		SED1565::Write_Command(0x0F & x);
		
		for (; i<(Width + j); i++)
		{
			SED1565::Write_Char( pgm_read_byte( &Buffer[ i ] ) );
		}
		
		j += Width;
	}
}

void SED1565::Serial_Init()
{
	DDRB |= (1<<SED1565_MOSI);
	DDRB |= (1<<SED1565_SCK);
	DDRB |= (1<<SED1565_CS);
	DDRB |= (1<<SED1565_DC);
	
	SED1565_CS_HIGH;

	Write_Command(0xAE); // DISPLAY OFF
	
	Write_Command(0xA0); // ADC NORMAL
	
	Write_Command(0x22); // VOLTAGE REGULATOR ON

	Write_Command(0xA6); // 0xA6, 0xA7
	
	Write_Command(0xC8); // output mode 1
	
	Write_Command(0x40); // start line 0

	Write_Command( 0xAF ); // DISPLAY ON
}
