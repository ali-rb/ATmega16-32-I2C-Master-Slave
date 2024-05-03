/*
 * I2C_Slave_C_File.c
 * Ali Ranjbar
 */ 

#include "I2C_Slave_H_File.h"

void I2C_Slave_Init(uint8_t slave_address)
{
	TWAR = slave_address;						
	TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWINT);	
}

int8_t I2C_Slave_Listen()
{
	while(1)
	{
		uint8_t status;							
		while (!(TWCR & (1<<TWINT)));			
		status = TWSR & 0xF8;					
		if (status == 0x60 || status == 0x68)	
		return 0;								
		if (status == 0xA8 || status == 0xB0)	
		return 1;								
		if (status == 0x70 || status == 0x78)	
		return 2;								
		else
		continue;								
	}
}

int8_t I2C_Slave_Transmit(char data)
{
	uint8_t status;
	TWDR = data;								
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);		
	while (!(TWCR & (1<<TWINT)));				
	status = TWSR & 0xF8;						
	if (status == 0xA0)							
	{
		TWCR |= (1<<TWINT);						
		return -1;
	}
	if (status == 0xB8)							
		return 0;								
	if (status == 0xC0)							
	{
		TWCR |= (1<<TWINT);						
		return -2;
	}
	if (status == 0xC8)							
	return -3;									
	else										
	return -4;
}

char I2C_Slave_Receive()
{
	uint8_t status;								
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);		
	while (!(TWCR & (1<<TWINT)));				
	status = TWSR & 0xF8;						
	if (status == 0x80 || status == 0x90)		
	return TWDR;								
	if (status == 0x88 || status == 0x98)		
	return TWDR;								
	if (status == 0xA0)							
	{
		TWCR |= (1<<TWINT);						
		return -1;
	}
	else
	return -2;									
}
