#include "i2c_driver.h"

// Private function prototypes
static void I2C_WaitUntilIdle(I2C_TypeDef *I2C);
static uint8_t I2C_CheckEvent(I2C_TypeDef *I2C, uint32_t event);

// I2C Initialization function
void I2C_Init(I2C_Config_t *config) {
	// Enable the peripheral clock for the I2C
	if (config->I2C == I2C1) {
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		} else if (config->I2C == I2C2) {
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	}

	// Disable I2C before configuring
	config->I2C->CR1 &= ~I2C_CR1_PE;

	// Set the I2C clock speed
	config->I2C->CCR = SystemCoreClock / (2 * config->ClockSpeed);

	// Set the addressing mode (7-bit or 10-bit)
	config->I2C->OAR1 &= ~I2C_OAR1_ADDMODE;
	config->I2C->OAR1 |= config->AddressingMode << 15;

	// Set own address
	config->I2C->OAR1 &= ~I2C_OAR1_ADD0;
	config->I2C->OAR1 |= (config->OwnAddress & 0x3FF) << 1;

	// Enable Dual Address Mode (if needed)
	if (config->DualAddressMode) {
		config->I2C->OAR1 |= I2C_OAR1_DUALF;
	}

	// Enable General Call Mode (if needed)
	if (config->GeneralCallMode) {
		config->I2C->CR1 |= I2C_CR1_ENGC;
	}

	// Enable clock stretching (if needed)
	if (!config->NoStretchMode) {
		config->I2C->CR1 &= ~I2C_CR1_NOSTRETCH;
		} else {
		config->I2C->CR1 |= I2C_CR1_NOSTRETCH;
	}

	// Enable the I2C peripheral
	config->I2C->CR1 |= I2C_CR1_PE;
}

// Wait until the I2C is no longer busy
static void I2C_WaitUntilIdle(I2C_TypeDef *I2C) {
	while (I2C->SR2 & I2C_SR2_BUSY);
}

// I2C Write Function
uint8_t I2C_Write(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t *data, uint16_t size) {
	I2C_WaitUntilIdle(I2C);

	// Generate Start Condition
	I2C->CR1 |= I2C_CR1_START;

	// Wait for the Start condition to be generated
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Send the Slave Address with Write bit (0)
	I2C->DR = slaveAddr & 0xFE;

	// Wait for the address to be sent
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Send the data
	for (uint16_t i = 0; i < size; i++) {
		I2C->DR = data[i];
		if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
			return I2C_ERROR_TIMEOUT;
		}
	}

	// Generate Stop Condition
	I2C->CR1 |= I2C_CR1_STOP;

	return I2C_OK;
}

// I2C Read Function
uint8_t I2C_Read(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t *data, uint16_t size) {
	I2C_WaitUntilIdle(I2C);

	// Generate Start Condition
	I2C->CR1 |= I2C_CR1_START;

	// Wait for the Start condition to be generated
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Send the Slave Address with Read bit (1)
	I2C->DR = slaveAddr | 0x01;

	// Wait for the address to be sent
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Receive the data
	for (uint16_t i = 0; i < size; i++) {
		if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
			return I2C_ERROR_TIMEOUT;
		}
		data[i] = I2C->DR;
	}

	// Generate Stop Condition
	I2C->CR1 |= I2C_CR1_STOP;

	return I2C_OK;
}

// Write to a specific register on the I2C slave device
uint8_t I2C_WriteRegister(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint16_t size) {
	I2C_WaitUntilIdle(I2C);

	// Generate Start Condition
	I2C->CR1 |= I2C_CR1_START;

	// Wait for Start condition
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Send Slave Address and register address
	I2C->DR = slaveAddr & 0xFE;

	// Wait for the address to be sent
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Send the register address
	I2C->DR = regAddr;

	// Wait for the register address to be transmitted
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Write data to the register
	for (uint16_t i = 0; i < size; i++) {
		I2C->DR = data[i];
		if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
			return I2C_ERROR_TIMEOUT;
		}
	}

	// Generate Stop Condition
	I2C->CR1 |= I2C_CR1_STOP;

	return I2C_OK;
}

// Read from a specific register on the I2C slave device
uint8_t I2C_ReadRegister(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint16_t size) {
	I2C_WaitUntilIdle(I2C);

	// Generate Start Condition
	I2C->CR1 |= I2C_CR1_START;

	// Wait for Start condition
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Send Slave Address (write) and register address
	I2C->DR = slaveAddr & 0xFE;

	// Wait for the address to be sent
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Send the register address
	I2C->DR = regAddr;

	// Wait for the register address to be transmitted
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Generate Start Condition again for reading
	I2C->CR1 |= I2C_CR1_START;

	// Send the slave address (read)
	I2C->DR = slaveAddr | 0x01;

	// Wait for the address to be sent
	if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
		return I2C_ERROR_TIMEOUT;
	}

	// Read the data
	for (uint16_t i = 0; i < size; i++) {
		if (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
			return I2C_ERROR_TIMEOUT;
		}
		data[i] = I2C->DR;
	}

	// Generate Stop Condition
	I2C->CR1 |= I2C_CR1_STOP;

	return I2C_OK;
}

// Helper function to check I2C event
static uint8_t I2C_CheckEvent(I2C_TypeDef *I2C, uint32_t event) {
	return (I2C->SR1 & event) == event;
}
