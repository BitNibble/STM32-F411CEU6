#include "stm32f4_twi.h"

/*** File Variable ***/
static TWI_HandleTypeDef twi_handle;

void TWI_Init(I2C_TypeDef* instance);
void TWI_Start(void);
void TWI_Connect(uint16_t address, uint8_t rw);
void TWI_Master_Write(uint8_t data);
uint8_t TWI_Master_Read(uint8_t ack_nack);
void TWI_Stop(void);
uint8_t TWI_Status(void);

/*** Procedure & Function ***/
TWI_HandleTypeDef TWI_enable(I2C_TypeDef* instance) {
	twi_handle.instance = instance;

	TWI_Init(instance);

	twi_handle.start = TWI_Start;
	twi_handle.connect = TWI_Connect;
	twi_handle.master_write = TWI_Master_Write;
	twi_handle.master_read = TWI_Master_Read;
	twi_handle.stop = TWI_Stop;
	twi_handle.status = TWI_Status;

	return twi_handle;
}

void TWI_Init(I2C_TypeDef* instance) {
	// Initialize I2C peripheral
	instance->CR1 |= I2C_CR1_SWRST;  // Software reset
	instance->CR1 &= ~I2C_CR1_SWRST; // Release reset
	instance->CR2 |= (I2C_SCL_CLOCK / 1000000) & I2C_CR2_FREQ; // Set SCL frequency
	instance->CCR = (100000000 / (2 * TWI_SCL_CLOCK)) & I2C_CCR_CCR; // Set CCR
	instance->TRISE = (I2C_SCL_CLOCK / 1000000) + 1; // Set TRISE
	instance->CR1 |= I2C_CR1_PE; // Enable I2C
}

TWI_HandleTypeDef* TWI(void) {
	return &twi_handle;
}

void TWI_Start(void) {
	twi_handle.instance->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(twi_handle.instance->SR1 & I2C_SR1_SB)); // Wait for start condition
}

void TWI_Connect(uint16_t address, uint8_t rw) {
	if (rw) {
		address |= 1; // Read
		} else {
		address &= ~1; // Write
	}
	twi_handle.instance->DR = address; // Send address
	while (!(twi_handle.instance->SR1 & I2C_SR1_ADDR)); // Wait for address sent
	(void)twi_handle.instance->SR2; // Clear ADDR flag
}

void TWI_Master_Write(uint8_t data) {
	twi_handle.instance->DR = data; // Send data
	while (!(twi_handle.instance->SR1 & I2C_SR1_TXE)); // Wait for transmit data register empty
}

uint8_t TWI_Master_Read(uint8_t ack_nack) {
	if (ack_nack) {
		twi_handle.instance->CR1 |= I2C_CR1_ACK; // Send ACK
		} else {
		twi_handle.instance->CR1 &= ~I2C_CR1_ACK; // Send NACK
	}
	while (!(twi_handle.instance->SR1 & I2C_SR1_RXNE)); // Wait for data received
	return twi_handle.instance->DR; // Return received data
}

void TWI_Stop(void) {
	twi_handle.instance->CR1 |= I2C_CR1_STOP; // Generate stop condition
	while (twi_handle.instance->CR1 & I2C_CR1_STOP); // Wait for stop condition to be generated
}

uint8_t TWI_Status(void) {
	return twi_handle.instance->SR1; // Return status register 1
}
