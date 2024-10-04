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
/*** I2C1 INIC Handler ***/
STM32FXXX_I2C1* i2c1_enable(void)
{
	/*** I2C1 Bit Mapping Link ***/
	stm32fxxx_i2c1.instance = I2C1;
	/*** Clock and Interrupt ***/
	stm32fxxx_i2c1.clock = STM32FXXXI2c1Clock;
	stm32fxxx_i2c1.evnvic = STM32FXXXI2c1EvNvic;
	stm32fxxx_i2c1.ernvic = STM32FXXXI2c1ErNvic;
	/*** Other ***/
	return &stm32fxxx_i2c1;
}
STM32FXXX_I2C1*  i2c1(void){ return (STM32FXXX_I2C1*) &stm32fxxx_i2c1; }
/*** I2C2 INIC Handler ***/
STM32FXXX_I2C2* i2c2_enable(void)
{
	/*** I2C1 Bit Mapping Link ***/
	stm32fxxx_i2c2.instance = I2C2;
	/*** Clock and Interrupt ***/
	stm32fxxx_i2c2.clock = STM32FXXXI2c2Clock;
	stm32fxxx_i2c2.evnvic = STM32FXXXI2c2EvNvic;
	stm32fxxx_i2c2.ernvic = STM32FXXXI2c2ErNvic;
	/*** Other ***/
	return &stm32fxxx_i2c2;
}
STM32FXXX_I2C2*  i2c2(void){ return (STM32FXXX_I2C2*) &stm32fxxx_i2c2; }
/*** I2C3 INIC Handler ***/
STM32FXXX_I2C3* i2c3_enable(void)
{
	/*** I2C1 Bit Mapping Link ***/
	stm32fxxx_i2c3.instance = I2C3;
	/*** Clock and Interrupt ***/
	stm32fxxx_i2c3.clock = STM32FXXXI2c3Clock;
	stm32fxxx_i2c3.evnvic = STM32FXXXI2c3EvNvic;
	stm32fxxx_i2c3.ernvic = STM32FXXXI2c3ErNvic;
	/*** Other ***/
	return &stm32fxxx_i2c3;
}
STM32FXXX_I2C3*  i2c3(void){ return (STM32FXXX_I2C3*) &stm32fxxx_i2c3; }

/*** EOF ***/

