/*
 * I2C_Master_C_file.c
 *Ali Ranjbar
 */ 


#include "I2C_Master_H_file.h"								

void I2C_Init()												
{
	TWBR = BITRATE(TWSR = 0x00);							
}	


uint8_t I2C_Start(char write_address)						
{
	uint8_t status;											
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status != 0x08)										
	return 0;												
	TWDR = write_address;									
	TWCR = (1<<TWEN)|(1<<TWINT);							
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status == 0x18)										
	return 1;												
	if (status == 0x20)										
	return 2;												
	else
	return 3;												
}

uint8_t I2C_Repeated_Start(char read_address)				
{
	uint8_t status;											
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status != 0x10)										
	return 0;												
	TWDR = read_address;									
	TWCR = (1<<TWEN)|(1<<TWINT);							
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status == 0x40)										
	return 1;												
	if (status == 0x20)										
	return 2;												
	else
	return 3;												
}

void I2C_Stop()												
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					
	while(TWCR & (1<<TWSTO));								
}

void I2C_Start_Wait(char write_address)						
{
	uint8_t status;											
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				
		while (!(TWCR & (1<<TWINT)));						
		status = TWSR & 0xF8;								
		if (status != 0x08)									
		continue;											
		TWDR = write_address;								
		TWCR = (1<<TWEN)|(1<<TWINT);						
		while (!(TWCR & (1<<TWINT)));						
		status = TWSR & 0xF8;								
		if (status != 0x18 )								
		{
			I2C_Stop();										
			continue;										
		}
		break;												
	}
}

uint8_t I2C_Write(char data)								
{
	uint8_t status;											
	TWDR = data;											
	TWCR = (1<<TWEN)|(1<<TWINT);							
	while (!(TWCR & (1<<TWINT)));							
	status = TWSR & 0xF8;									
	if (status == 0x28)										
	return 0;												
	if (status == 0x30)										
	return 1;												
	else
	return 2;												
}

char I2C_Read_Ack()											
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					
	while (!(TWCR & (1<<TWINT)));							
	return TWDR;											
}	

char I2C_Read_Nack()										
{
	TWCR=(1<<TWEN)|(1<<TWINT);								
	while (!(TWCR & (1<<TWINT)));							
	return TWDR;											
}	
