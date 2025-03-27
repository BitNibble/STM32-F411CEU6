#include "stm32f4xx_hal.h"

I2C_HandleTypeDef hi2c1; // I2C handle

void I2C_Init(void) {
	// Enable I2C clock
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Configure GPIO pins for I2C1 (PB6 -> SCL, PB7 -> SDA)
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; // Open-drain mode
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1; // Alternate function for I2C1
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// Configure I2C1
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000; // 100 kHz
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		// Initialization Error
		while (1); // Handle error
	}
}

uint8_t I2C_Write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	// Write data to a specific register of the I2C device
	if (HAL_I2C_Mem_Write(&hi2c1, dev_addr << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY) != HAL_OK) {
		return 1; // Error
	}
	return 0; // Success
}

uint8_t I2C_Read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	// Read data from a specific register of the I2C device
	if (HAL_I2C_Mem_Read(&hi2c1, dev_addr << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY) != HAL_OK) {
		return 1; // Error
	}
	return 0; // Success
}

uint8_t I2C_WriteByte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
	// Write a single byte to a specific register
	return I2C_Write(dev_addr, reg_addr, &data, 1);
}

uint8_t I2C_ReadByte(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data) {
	// Read a single byte from a specific register
	return I2C_Read(dev_addr, reg_addr, data, 1);
}
