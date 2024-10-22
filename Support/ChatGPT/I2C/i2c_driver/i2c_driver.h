#ifndef __I2C_DRIVER_H__
#define __I2C_DRIVER_H__

#include "stm32f4xx.h"

// I2C Error Codes
#define I2C_OK                0x00
#define I2C_ERROR_TIMEOUT      0x01
#define I2C_ERROR_BUSY         0x02
#define I2C_ERROR_NACK         0x04

// I2C Configuration structure
typedef struct {
	I2C_TypeDef *I2C;         // I2C peripheral instance (I2C1, I2C2, etc.)
	uint32_t ClockSpeed;      // Clock speed for I2C (in Hz)
	uint32_t AddressingMode;  // Addressing mode (7-bit or 10-bit)
	uint32_t OwnAddress;      // Own address (7-bit or 10-bit)
	uint32_t DualAddressMode; // Enable/Disable dual address mode
	uint32_t GeneralCallMode; // Enable/Disable general call mode
	uint32_t NoStretchMode;   // Enable/Disable clock stretching
} I2C_Config_t;

// Function Prototypes
void I2C_Init(I2C_Config_t *config);
uint8_t I2C_Write(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t *data, uint16_t size);
uint8_t I2C_Read(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t *data, uint16_t size);
uint8_t I2C_WriteRegister(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint16_t size);
uint8_t I2C_ReadRegister(I2C_TypeDef *I2C, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint16_t size);

#endif /* __I2C_DRIVER_H__ */

