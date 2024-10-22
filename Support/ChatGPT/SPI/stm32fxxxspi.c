#include "spi.h"

// SPI Configuration Function
void SPI_Init(SPI_HandleTypeDef *hspi, uint32_t baudRate, uint32_t mode, uint32_t dataSize, uint32_t busClock) {
	// Set the SPI mode
	hspi->Mode = mode;
	
	// Set the data size
	hspi->DataSize = dataSize;
	
	// Calculate prescaler based on the desired baud rate
	SPI_SetBaudRate(hspi, baudRate, busClock);
	
	// Configure the SPI peripheral settings
	// Set other configurations like polarity, phase etc.
	// Enable the SPI peripheral
	set_reg(&(hspi->Instance->CR1), SPI_CR1_SPE);
}

// Set SPI Baud Rate Prescaler
void SPI_SetBaudRate(SPI_HandleTypeDef *hspi, uint32_t desiredBaudRate, uint32_t busClock) {
	// Calculate prescaler value based on the desired baud rate and bus clock
	uint32_t prescaler = busClock / desiredBaudRate;

	// Adjust the prescaler to match the hardware settings
	uint32_t prescalerValue = 0;

	// Ensure the prescaler is valid
	if (prescaler < 2) {
		prescalerValue = 0;  // Minimum prescaler
		} else if (prescaler < 4) {
		prescalerValue = 1;  // Prescaler 2
		} else if (prescaler < 8) {
		prescalerValue = 2;  // Prescaler 4
		} else if (prescaler < 16) {
		prescalerValue = 3;  // Prescaler 8
		} else if (prescaler < 32) {
		prescalerValue = 4;  // Prescaler 16
		} else if (prescaler < 64) {
		prescalerValue = 5;  // Prescaler 32
		} else if (prescaler < 128) {
		prescalerValue = 6;  // Prescaler 64
		} else if (prescaler < 256) {
		prescalerValue = 7;  // Prescaler 128
		} else {
		prescalerValue = 7;  // Max prescaler (256)
	}

	hspi->BaudRatePrescaler = prescalerValue;
	set_reg_block(&(hspi->Instance->CR1), 3, SPI_CR1_BR_Pos, prescalerValue);
}

// SPI Polling Transmit Function with Timeout
uint8_t SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size, uint32_t timeout) {
	uint32_t startTime = HAL_GetTick(); // Get the current time

	for (uint16_t i = 0; i < size; i++) {
		// Wait until TX buffer is empty
		while (!(hspi->Instance->SR & SPI_SR_TXE)) {
			if ((HAL_GetTick() - startTime) > timeout) {
				return 0; // Timeout occurred
			}
		}

		// Send data
		hspi->Instance->DR = data[i];
	}

	// Wait until the transmission is complete
	for (uint16_t i = 0; i < size; i++) {
		while (!(hspi->Instance->SR & SPI_SR_RXNE)) {
			if ((HAL_GetTick() - startTime) > timeout) {
				return 0; // Timeout occurred
			}
		}
		volatile uint8_t temp = hspi->Instance->DR; // Read the received data
	}

	return 1; // Successful transmission
}

// SPI Polling Receive Function with Timeout
uint8_t SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size, uint32_t timeout) {
	uint32_t startTime = HAL_GetTick(); // Get the current time

	for (uint16_t i = 0; i < size; i++) {
		// Wait until RX buffer is not empty
		while (!(hspi->Instance->SR & SPI_SR_RXNE)) {
			if ((HAL_GetTick() - startTime) > timeout) {
				return 0; // Timeout occurred
			}
		}
		// Read received data
		data[i] = hspi->Instance->DR;
	}

	return 1; // Successful reception
}

// SPI Polling Transmit and Receive Function with Timeout
uint8_t SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *txData, uint8_t *rxData, uint16_t size, uint32_t timeout) {
	uint32_t startTime = HAL_GetTick(); // Get the current time

	for (uint16_t i = 0; i < size; i++) {
		// Wait until TX buffer is empty
		while (!(hspi->Instance->SR & SPI_SR_TXE)) {
			if ((HAL_GetTick() - startTime) > timeout) {
				return 0; // Timeout occurred
			}
		}

		// Send data
		hspi->Instance->DR = txData[i];

		// Wait until RX buffer is not empty
		while (!(hspi->Instance->SR & SPI_SR_RXNE)) {
			if ((HAL_GetTick() - startTime) > timeout) {
				return 0; // Timeout occurred
			}
		}

		// Read received data
		rxData[i] = hspi->Instance->DR;
	}

	return 1; // Successful transmission and reception
}

// Example Usage
void ExampleUsage(void) {
	SPI_HandleTypeDef hspi;
	hspi.Instance = SPI1; // Assuming SPI1 is used
	SPI_Init(&hspi, 1000000, SPI_MODE_0, SPI_DATASIZE_8BIT, 84000000); // 1MHz baud rate

	uint8_t txData[5] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
	uint8_t rxData[5];

	// Transmit data
	if (!SPI_Transmit(&hspi, txData, 5, 1000)) {
		// Handle timeout error
	}

	// Receive data
	if (!SPI_Receive(&hspi, rxData, 5, 1000)) {
		// Handle timeout error
	}
}
