/*
 * ATmega32_Slave.c
 * Ali Ranjbar
 */ 


#define F_CPU 8000000UL							
#include <avr/io.h>								
#include <util/delay.h>							
#include <stdio.h>								
#include <string.h>								
#include "LCD_16x2_H_file.h"					
#include "I2C_Slave_H_File.h"					

#define Slave_Address			0x20

int main(void)
{
	char buffer[10];
	int8_t count = 0;
	
	LCD_Init();
	I2C_Slave_Init(Slave_Address);
	
	LCD_String_xy(1, 0, "Slave Device");
	
	while (1)
	{
		switch(I2C_Slave_Listen())				
		{
			case 0:
			{
				LCD_String_xy(2, 0, "Receiving :       ");
				do
				{
					sprintf(buffer, "%d    ", count);
					LCD_String_xy(2, 13, buffer);
					count = I2C_Slave_Receive();
				} while (count != -1);			
				count = 0;
				break;
			}
			case 1:
			{
				int8_t Ack_status;
				LCD_String_xy(2, 0, "Sending :       ");
				do
				{
					Ack_status = I2C_Slave_Transmit(count);	
					sprintf(buffer, "%d    ",count);
					LCD_String_xy(2, 13, buffer);
					count++;
				} while (Ack_status == 0);		
				break;
			}
			default:
				break;
		}
	}
}

