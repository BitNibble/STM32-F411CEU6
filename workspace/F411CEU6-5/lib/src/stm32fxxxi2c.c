/******************************************************************************
	STM32 XXX I2C
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 04102024
Comment:

*******************************************************************************/
#include "stm32fxxxi2c.h"
#include "armquery.h"
/*** File Variable ***/
static STM32FXXX_I2C1 stm32fxxx_i2c1;
static STM32FXXX_I2C2 stm32fxxx_i2c2;
static STM32FXXX_I2C3 stm32fxxx_i2c3;
/*** I2C Procedure & Function Definition ***/
// COMMON
void STM32FXXXI2c_Init(I2C_TypeDef* instance) {
	// Initialize I2C peripheral
	instance->CR1 |= I2C_CR1_SWRST;  // Software reset
	instance->CR1 &= ~I2C_CR1_SWRST; // Release reset
	instance->CR2 |= (I2C_SCL_CLOCK / 1000000) & I2C_CR2_FREQ; // Set SCL frequency
	instance->CCR = (100000000 / (2 * I2C_SCL_CLOCK)) & I2C_CCR_CCR; // Set CCR
	instance->TRISE = (I2C_SCL_CLOCK / 1000000) + 1; // Set TRISE
	instance->CR1 |= I2C_CR1_PE; // Enable I2C
}
// I2C1
void STM32FXXXI2c1Clock( uint8_t state ){
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_I2C1EN_Pos);}
	else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_I2C1EN_Pos);}
}
void STM32FXXXI2c1EvNvic( uint8_t state ){
	if(state){ set_bit_block(NVIC->ISER, 1, I2C1_EV_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, I2C1_EV_IRQn, 1); }
}
void STM32FXXXI2c1ErNvic( uint8_t state ){
	if(state){ set_bit_block(NVIC->ISER, 1, I2C1_ER_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, I2C1_ER_IRQn, 1); }
}
/***/
void STM32FXXXI2c1_Start(void) {
	I2C1->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(I2C1->SR1 & I2C_SR1_SB)); // Wait for start condition
}

void STM32FXXXI2c1_Connect(uint16_t address, uint8_t rw) {
	if (rw) {
		address |= 1; // Read
		} else {
		address &= ~1; // Write
	}
	I2C1->DR = address; // Send address
	while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address sent
	(void)I2C1->SR2; // Clear ADDR flag
}

void STM32FXXXI2c1_Master_Write(uint8_t data) {
	I2C1->DR = data; // Send data
	while (!(I2C1->SR1 & I2C_SR1_TXE)); // Wait for transmit data register empty
}

uint8_t STM32FXXXI2c1_Master_Read(uint8_t ack_nack) {
	if (ack_nack) {
		I2C1->CR1 |= I2C_CR1_ACK; // Send ACK
		} else {
			I2C1->CR1 &= ~I2C_CR1_ACK; // Send NACK
	}
	while (!(I2C1->SR1 & I2C_SR1_RXNE)); // Wait for data received
	return I2C1->DR; // Return received data
}

void STM32FXXXI2c1_Stop(void) {
	I2C1->CR1 |= I2C_CR1_STOP; // Generate stop condition
	while (I2C1->CR1 & I2C_CR1_STOP); // Wait for stop condition to be generated
}

uint8_t STM32FXXXI2c1_Status(void) {
	return I2C1->SR1; // Return status register 1
}
// I2C2
void STM32FXXXI2c2Clock( uint8_t state ){
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_I2C2EN_Pos);}
		else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_I2C2EN_Pos);}
}
void STM32FXXXI2c2EvNvic( uint8_t state ){
	if(state){ set_bit_block(NVIC->ISER, 1, I2C2_EV_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, I2C2_EV_IRQn, 1); }
}
void STM32FXXXI2c2ErNvic( uint8_t state ){
	if(state){ set_bit_block(NVIC->ISER, 1, I2C2_ER_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, I2C2_ER_IRQn, 1); }
}
/***/
void STM32FXXXI2c2_Start(void) {
	I2C2->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(I2C2->SR1 & I2C_SR1_SB)); // Wait for start condition
}

void STM32FXXXI2c2_Connect(uint16_t address, uint8_t rw) {
	if (rw) {
		address |= 1; // Read
		} else {
		address &= ~1; // Write
	}
	I2C2->DR = address; // Send address
	while (!(I2C2->SR1 & I2C_SR1_ADDR)); // Wait for address sent
	(void)I2C2->SR2; // Clear ADDR flag
}

void STM32FXXXI2c2_Master_Write(uint8_t data) {
	I2C2->DR = data; // Send data
	while (!(I2C2->SR1 & I2C_SR1_TXE)); // Wait for transmit data register empty
}

uint8_t STM32FXXXI2c2_Master_Read(uint8_t ack_nack) {
	if (ack_nack) {
		I2C2->CR1 |= I2C_CR1_ACK; // Send ACK
		} else {
			I2C2->CR1 &= ~I2C_CR1_ACK; // Send NACK
	}
	while (!(I2C2->SR1 & I2C_SR1_RXNE)); // Wait for data received
	return I2C2->DR; // Return received data
}

void STM32FXXXI2c2_Stop(void) {
	I2C2->CR1 |= I2C_CR1_STOP; // Generate stop condition
	while (I2C2->CR1 & I2C_CR1_STOP); // Wait for stop condition to be generated
}

uint8_t STM32FXXXI2c2_Status(void) {
	return I2C2->SR1; // Return status register 1
}
// I2C3
void STM32FXXXI2c3Clock( uint8_t state ){
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_I2C3EN_Pos);}
	else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_I2C3EN_Pos);}
}
void STM32FXXXI2c3EvNvic( uint8_t state ){
	if(state){ set_bit_block(NVIC->ISER, 1, I2C3_EV_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, I2C3_EV_IRQn, 1); }
}
void STM32FXXXI2c3ErNvic( uint8_t state ){
	if(state){ set_bit_block(NVIC->ISER, 1, I2C3_ER_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, I2C3_ER_IRQn, 1); }
}
/***/
void STM32FXXXI2c3_Start(void) {
	I2C3->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(I2C3->SR1 & I2C_SR1_SB)); // Wait for start condition
}

void STM32FXXXI2c3_Connect(uint16_t address, uint8_t rw) {
	if (rw) {
		address |= 1; // Read
		} else {
		address &= ~1; // Write
	}
	I2C3->DR = address; // Send address
	while (!(I2C3->SR1 & I2C_SR1_ADDR)); // Wait for address sent
	(void)I2C3->SR2; // Clear ADDR flag
}

void STM32FXXXI2c3_Master_Write(uint8_t data) {
	I2C3->DR = data; // Send data
	while (!(I2C3->SR1 & I2C_SR1_TXE)); // Wait for transmit data register empty
}

uint8_t STM32FXXXI2c3_Master_Read(uint8_t ack_nack) {
	if (ack_nack) {
		I2C3->CR1 |= I2C_CR1_ACK; // Send ACK
		} else {
			I2C3->CR1 &= ~I2C_CR1_ACK; // Send NACK
	}
	while (!(I2C3->SR1 & I2C_SR1_RXNE)); // Wait for data received
	return I2C3->DR; // Return received data
}

void STM32FXXXI2c3_Stop(void) {
	I2C3->CR1 |= I2C_CR1_STOP; // Generate stop condition
	while (I2C3->CR1 & I2C_CR1_STOP); // Wait for stop condition to be generated
}

uint8_t STM32FXXXI2c3_Status(void) {
	return I2C3->SR1; // Return status register 1
}

/**************************************************************************************************/
/*** I2C1 INIC Handler ***/
STM32FXXX_I2C1* i2c1_enable(void)
{
	/*** I2C1 Bit Mapping Link ***/
	stm32fxxx_i2c1.instance = I2C1;
	/*** I2C1 Init ***/
	STM32FXXXI2c_Init(I2C1);
	/*** Clock and Interrupt ***/
	stm32fxxx_i2c1.clock = STM32FXXXI2c1Clock;
	stm32fxxx_i2c1.evnvic = STM32FXXXI2c1EvNvic;
	stm32fxxx_i2c1.ernvic = STM32FXXXI2c1ErNvic;
	/*** Other ***/
	stm32fxxx_i2c1.start = STM32FXXXI2c1_Start;
	stm32fxxx_i2c1.connect = STM32FXXXI2c1_Connect;
	stm32fxxx_i2c1.master_write = STM32FXXXI2c1_Master_Write;
	stm32fxxx_i2c1.master_read = STM32FXXXI2c1_Master_Read;
	stm32fxxx_i2c1.stop = STM32FXXXI2c1_Stop;
	stm32fxxx_i2c1.status = STM32FXXXI2c1_Status;
	return &stm32fxxx_i2c1;
}
STM32FXXX_I2C1*  i2c1(void){ return (STM32FXXX_I2C1*) &stm32fxxx_i2c1; }
/*** I2C2 INIC Handler ***/
STM32FXXX_I2C2* i2c2_enable(void)
{
	/*** I2C2 Bit Mapping Link ***/
	stm32fxxx_i2c2.instance = I2C2;
	/*** I2C2 Init ***/
	STM32FXXXI2c_Init(I2C2);
	/*** Clock and Interrupt ***/
	stm32fxxx_i2c2.clock = STM32FXXXI2c2Clock;
	stm32fxxx_i2c2.evnvic = STM32FXXXI2c2EvNvic;
	stm32fxxx_i2c2.ernvic = STM32FXXXI2c2ErNvic;
	/*** Other ***/
	stm32fxxx_i2c2.start = STM32FXXXI2c2_Start;
	stm32fxxx_i2c2.connect = STM32FXXXI2c2_Connect;
	stm32fxxx_i2c2.master_write = STM32FXXXI2c2_Master_Write;
	stm32fxxx_i2c2.master_read = STM32FXXXI2c2_Master_Read;
	stm32fxxx_i2c2.stop = STM32FXXXI2c2_Stop;
	stm32fxxx_i2c2.status = STM32FXXXI2c2_Status;
	return &stm32fxxx_i2c2;
}
STM32FXXX_I2C2*  i2c2(void){ return (STM32FXXX_I2C2*) &stm32fxxx_i2c2; }
/*** I2C3 INIC Handler ***/
STM32FXXX_I2C3* i2c3_enable(void)
{
	/*** I2C3 Bit Mapping Link ***/
	stm32fxxx_i2c3.instance = I2C3;
	/*** I2C3 Init ***/
	STM32FXXXI2c_Init(I2C3);
	/*** Clock and Interrupt ***/
	stm32fxxx_i2c3.clock = STM32FXXXI2c3Clock;
	stm32fxxx_i2c3.evnvic = STM32FXXXI2c3EvNvic;
	stm32fxxx_i2c3.ernvic = STM32FXXXI2c3ErNvic;
	/*** Other ***/
	stm32fxxx_i2c3.start = STM32FXXXI2c3_Start;
	stm32fxxx_i2c3.connect = STM32FXXXI2c3_Connect;
	stm32fxxx_i2c3.master_write = STM32FXXXI2c3_Master_Write;
	stm32fxxx_i2c3.master_read = STM32FXXXI2c3_Master_Read;
	stm32fxxx_i2c3.stop = STM32FXXXI2c3_Stop;
	stm32fxxx_i2c3.status = STM32FXXXI2c3_Status;
	return &stm32fxxx_i2c3;
}
STM32FXXX_I2C3*  i2c3(void){ return (STM32FXXX_I2C3*) &stm32fxxx_i2c3; }

/*** EOF ***/

