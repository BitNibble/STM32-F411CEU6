#include "i2c.h"

// Initialize the I2C peripheral
void I2C_Init(I2C_TypeDef *I2Cx, uint32_t clockSpeed) {
	// Enable the clock for the I2C peripheral
	if (I2Cx == I2C1) {
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		} else if (I2Cx == I2C2) {
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		} else if (I2Cx == I2C3) {
		RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
	}

	// Reset the I2C peripheral
	I2Cx->CR1 |= I2C_CR1_SWRST;
	I2Cx->CR1 &= ~I2C_CR1_SWRST;

	// Configure the clock control register
	uint32_t pclk1 = SystemCoreClock / 2;  // APB1 clock frequency
	uint32_t freqRange = pclk1 / 1000000;  // MHz
	I2Cx->CR2 = (freqRange & I2C_CR2_FREQ);

	// Configure the rise time register
	I2Cx->TRISE = freqRange + 1;

	// Configure the clock control register for standard mode (100 kHz)
	I2Cx->CCR = (pclk1 / (2 * clockSpeed)) & I2C_CCR_CCR;

	// Enable the I2C peripheral
	I2Cx->CR1 |= I2C_CR1_PE;
}

// Write data to an I2C device
void I2C_Write(I2C_TypeDef *I2Cx, uint8_t deviceAddr, uint8_t regAddr, uint8_t data) {
	// Wait until the bus is not busy
	while (I2Cx->SR2 & I2C_SR2_BUSY);

	// Generate start condition
	I2Cx->CR1 |= I2C_CR1_START;

	// Wait for the start condition to be generated
	while (!(I2Cx->SR1 & I2C_SR1_SB));

	// Send the device address with write bit
	I2Cx->DR = (deviceAddr << 1) & ~0x01;

	// Wait for address to be acknowledged
	while (!(I2Cx->SR1 & I2C_SR1_ADDR));

	// Clear ADDR flag by reading SR1 and SR2
	(void)I2Cx->SR1;
	(void)I2Cx->SR2;

	// Send the register address
	I2Cx->DR = regAddr;

	// Wait for the byte to be transmitted
	while (!(I2Cx->SR1 & I2C_SR1_TXE));

	// Send the data
	I2Cx->DR = data;

	// Wait for the byte to be transmitted
	while (!(I2Cx->SR1 & I2C_SR1_TXE));

	// Generate stop condition
	I2Cx->CR1 |= I2C_CR1_STOP;
}

// Read data from an I2C device
uint8_t I2C_Read(I2C_TypeDef *I2Cx, uint8_t deviceAddr, uint8_t regAddr) {
	uint8_t data = 0;

	// Wait until the bus is not busy
	while (I2Cx->SR2 & I2C_SR2_BUSY);

	// Generate start condition
	I2Cx->CR1 |= I2C_CR1_START;

	// Wait for the start condition to be generated
	while (!(I2Cx->SR1 & I2C_SR1_SB));

	// Send the device address with write bit
	I2Cx->DR = (deviceAddr << 1) & ~0x01;

	// Wait for address to be acknowledged
	while (!(I2Cx->SR1 & I2C_SR1_ADDR));

	// Clear ADDR flag by reading SR1 and SR2
	(void)I2Cx->SR1;
	(void)I2Cx->SR2;

	// Send the register address
	I2Cx->DR = regAddr;

	// Wait for the byte to be transmitted
	while (!(I2Cx->SR1 & I2C_SR1_TXE));

	// Generate repeated start condition
	I2Cx->CR1 |= I2C_CR1_START;

	// Wait for the start condition to be generated
	while (!(I2Cx->SR1 & I2C_SR1_SB));

	// Send the device address with read bit
	I2Cx->DR = (deviceAddr << 1) | 0x01;

	// Wait for address to be acknowledged
	while (!(I2Cx->SR1 & I2C_SR1_ADDR));

	// Clear ADDR flag by reading SR1 and SR2
	(void)I2Cx->SR1;
	(void)I2Cx->SR2;

	// Wait for data to be received
	while (!(I2Cx->SR1 & I2C_SR1_RXNE));

	// Read the data
	data = I2Cx->DR;

	// Generate stop condition
	I2Cx->CR1 |= I2C_CR1_STOP;

	return data;
}