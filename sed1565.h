/*
	@File 		SED1565_H_
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		16/09/21
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/


#ifndef SED1565_H_
#define SED1565_H_

// Font header size
#define header				5	

// FONTS
#include "Fonts/Arial_10x10.h"
#include "Fonts/Arial_12x12.h"
#include "Fonts/Arial_13x13.h"
#include "Fonts/Arial_16x16.h"

#include "Fonts/Arial_Bold_10x11.h"
#include "Fonts/Arial_Bold_16x17.h"
#include "Fonts/Times_New_Roman_Bold_12x11.h"

#include "Fonts/Calibri_9x10.h"
#include "Fonts/Tahoma_10x11.h"
#include "Fonts/Times_New_Roman_11x12.h"

#include "Fonts/Ms_Serif.h"
#include "Fonts/Verdana_11x11.h"
#include "Fonts/Arial_Italic_11x12.h"

// CONIFGURATION
#define SED1565_CS				PB0
#define SED1565_DC				PB1
#define SED1565_MOSI			PB5
#define SED1565_SCK				PB7

#define SED1565_CS_LOW			PORTB &=~(1<<SED1565_CS)
#define SED1565_CS_HIGH			PORTB |=(1<<SED1565_CS)

#define SED1565_DC_LOW			PORTB &=~(1<<SED1565_DC)
#define SED1565_DC_HIGH			PORTB |= (1<<SED1565_DC)

#define SED1565_SCK_LOW			PORTB &=~(1<<SED1565_SCK)
#define SED1565_SCK_HIGH		PORTB |= (1<<SED1565_SCK)

#define SED1565_MOSI_LOW		PORTB &=~(1<<SED1565_MOSI)
#define SED1565_MOSI_HIGH		PORTB |= (1<<SED1565_MOSI)

class SED1565
{
	public:
	void Char(unsigned char data, const unsigned char Font[]);
	void String(const char * data, unsigned char x, unsigned char y, const unsigned char Font[]);
	void Write_Char(unsigned char data);
	void Write_Command(unsigned char cmd);
	
	void Clear(unsigned char x, unsigned char y, unsigned char width, unsigned char Pages);
	
	void DrawImage(const unsigned char Buffer[],unsigned char x,unsigned char y,unsigned char Width,unsigned char Pages);
	
	void Set_Cursor_8x(unsigned char x, unsigned char y);
	void Set_Cursor(unsigned char x, unsigned char y);
	
	void Serial_Write(unsigned char data);
	void Serial_Init();
	
	void Rotation(unsigned bit);
	
	void Rotation_180();
	
	int X;
	int Y;
};

#endif /* SED1565_H_ */
