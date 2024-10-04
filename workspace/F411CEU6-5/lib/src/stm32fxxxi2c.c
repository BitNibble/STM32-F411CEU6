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
void STM32FXXXI2c1Clock( uint8_t state ){}
void STM32FXXXI2c1Nvic( uint8_t state ){}
// I2C2
void STM32FXXXI2c2Clock( uint8_t state ){}
void STM32FXXXI2c2Nvic( uint8_t state ){}
// I2C3
void STM32FXXXI2c3Clock( uint8_t state ){}
void STM32FXXXI2c3Nvic( uint8_t state ){}
/*** I2C1 INIC Handler ***/
STM32FXXX_I2C1* i2c1_enable(void)
{
	/*** I2C1 Bit Mapping Link ***/
	stm32fxxx_i2c1.instance = I2C1;
	// Other
	stm32fxxx_i2c1.clock = STM32FXXXI2c1Clock;
	stm32fxxx_i2c1.nvic = STM32FXXXI2c1Nvic;
	return &stm32fxxx_i2c1;
}
STM32FXXX_I2C1*  i2c1(void){ return (STM32FXXX_I2C1*) &stm32fxxx_i2c1; }
/*** I2C2 INIC Handler ***/
STM32FXXX_I2C2* i2c2_enable(void)
{
	/*** I2C1 Bit Mapping Link ***/
	stm32fxxx_i2c2.instance = I2C2;
	// Other
	stm32fxxx_i2c2.clock = STM32FXXXI2c2Clock;
	stm32fxxx_i2c2.nvic = STM32FXXXI2c2Nvic;
	return &stm32fxxx_i2c2;
}
STM32FXXX_I2C2*  i2c2(void){ return (STM32FXXX_I2C2*) &stm32fxxx_i2c2; }
/*** I2C3 INIC Handler ***/
STM32FXXX_I2C3* i2c3_enable(void)
{
	/*** I2C1 Bit Mapping Link ***/
	stm32fxxx_i2c3.instance = I2C3;
	// Other
	stm32fxxx_i2c3.clock = STM32FXXXI2c3Clock;
	stm32fxxx_i2c3.nvic = STM32FXXXI2c3Nvic;
	return &stm32fxxx_i2c3;
}
STM32FXXX_I2C3*  i2c3(void){ return (STM32FXXX_I2C3*) &stm32fxxx_i2c3; }

/*** EOF ***/

