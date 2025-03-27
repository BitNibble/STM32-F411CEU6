#ifndef I2C_H
#define I2C_H

#include "stm32f4xx.h"  // CMSIS for STM32F4 series

// Function prototypes
void I2C_Init(I2C_TypeDef *I2Cx, uint32_t clockSpeed);
void I2C_Write(I2C_TypeDef *I2Cx, uint8_t deviceAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C_Read(I2C_TypeDef *I2Cx, uint8_t deviceAddr, uint8_t regAddr);

#endif // I2C_H