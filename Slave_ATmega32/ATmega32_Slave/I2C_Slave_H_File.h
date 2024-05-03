/*
 * I2C_Slave_H_File.h
 * Ali Ranjbar
 */ 


#ifndef I2C_SLAVE_H_FILE_H_
#define I2C_SLAVE_H_FILE_H_

#include <avr/io.h>								

void I2C_Slave_Init(uint8_t slave_address);		
int8_t I2C_Slave_Listen();						
int8_t I2C_Slave_Transmit(char data);			
char I2C_Slave_Receive();						

#endif 