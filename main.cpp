/*
	@File 		main.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		20/06/21
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#define F_CPU 16000000UL

#include <avr/io.h>

#include "sed1565.h"

SED1565 sed1565;

int main(void)
{
	sed1565.Serial_Init();
	
	sed1565.Rotation( 0 );
	
	sed1565.String("Sed1565", 0, 0, Font_Arial_10x10);
	
	while(1);
}
