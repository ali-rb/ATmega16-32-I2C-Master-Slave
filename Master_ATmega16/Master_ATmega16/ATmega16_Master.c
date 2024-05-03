/*
 * ATmega16_Master.c
 * Ali Ranjbar
 */ 

#define F_CPU 8000000UL						
#include <avr/io.h>							
#include <util/delay.h>						
#include <stdio.h>							
#include <string.h>							
#include "I2C_Master_H_file.h"				
#include "LCD_16x2_H_file.h"				

#define Slave_Write_Address		0x20
#define Slave_Read_Address		0x21
#define	count					10

int main()
{
	char buffer[10];
	
	LCD_Init();								
	I2C_Init();								
	
	LCD_String_xy(1, 0, "Master Device");
	
	while (1)
	{
		LCD_String_xy(2, 0, "Sending :       ");
		I2C_Start_Wait(Slave_Write_Address);
		_delay_ms(5);
		for (uint8_t i = 0; i < count ; i++)
		{
			sprintf(buffer, "%d    ",i);
			LCD_String_xy(2, 13, buffer);
			I2C_Write(i);					
			_delay_ms(500);
		}
		LCD_String_xy(2, 0, "Receiving :       ");
		I2C_Repeated_Start(Slave_Read_Address);	
		_delay_ms(5);
		for (uint8_t i = 0; i < count; i++)
		{
			if(i < count - 1)
				sprintf(buffer, "%d    ", I2C_Read_Ack());
			else
				sprintf(buffer, "%d    ", I2C_Read_Nack());
			LCD_String_xy(2, 13, buffer);
			_delay_ms(500);
		}
		I2C_Stop();				
	}
}