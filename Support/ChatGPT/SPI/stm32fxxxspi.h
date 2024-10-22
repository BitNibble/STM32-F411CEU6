#ifndef SPI_H
#define SPI_H

#include "stm32f4xx.h"  // Include your STM32 headers

// SPI Mode Definitions
#define SPI_MODE_0    0x00  // CPOL = 0, CPHA = 0
#define SPI_MODE_1    0x01  // CPOL = 0, CPHA = 1
#define SPI_MODE_2    0x02  // CPOL = 1, CPHA = 0
#define SPI_MODE_3    0x03  // CPOL = 1, CPHA = 1

// SPI Data Size Definitions
#define SPI_DATASIZE_8BIT  0x00
#define SPI_DATASIZE_16BIT 0x01

// SPI Handle Structure
typedef struct {
	SPI_TypeDef *Instance;
	uint32_t BaudRatePrescaler;
	uint32_t Mode;         // SPI Mode (0, 1, 2, or 3)
	uint32_t DataSize;     // Data size (8-bit or 16-bit)
} SPI_HandleTypeDef;

// Function Prototypes
void SPI_Init(SPI_HandleTypeDef *hspi, uint32_t baudRate, uint32_t mode, uint32_t dataSize, uint32_t busClock);
void SPI_SetBaudRate(SPI_HandleTypeDef *hspi, uint32_t desiredBaudRate, uint32_t busClock);
uint8_t SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size, uint32_t timeout);
uint8_t SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size, uint32_t timeout);
uint8_t SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *txData, uint8_t *rxData, uint16_t size, uint32_t timeout);

#endif // SPI_H
