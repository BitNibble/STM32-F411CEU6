/******************************************************************************
	STM32 XXX I2C
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 04102024
Comment:

*******************************************************************************/
#ifndef _STM32FXXXI2C_H_
	#define _STM32FXXXI2C_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*** I2C 1..3 Handler TypeDef ***/
// I2C -> I2C1,2,3
typedef struct
{
	/*** Bit Mapping ***/
	I2C_TypeDef* instance;
	/*** Clock and Interrupt ***/
	void (*clock)(uint8_t state);
	void (*evnvic)(uint8_t state);
	void (*ernvic)(uint8_t state);
	/*** Other ***/
}STM32FXXX_I2C1, STM32FXXX_I2C2, STM32FXXX_I2C3;
/*** I2C Procedure and Function Declarations ***/
STM32FXXX_I2C1* i2c1_enable(void);
STM32FXXX_I2C1* i2c1(void);
STM32FXXX_I2C2* i2c2_enable(void);
STM32FXXX_I2C2* i2c2(void);
STM32FXXX_I2C3* i2c3_enable(void);
STM32FXXX_I2C3* i2c3(void);
/*** I2C ***/
// I2C1
void STM32FXXXI2c1Clock( uint8_t state );
void STM32FXXXI2c1EvNvic( uint8_t state );
void STM32FXXXI2c1ErNvic( uint8_t state );
// I2C2
void STM32FXXXI2c2Clock( uint8_t state );
void STM32FXXXI2c2EvNvic( uint8_t state );
void STM32FXXXI2c2ErNvic( uint8_t state );
// I2C3
void STM32FXXXI2c3Clock( uint8_t state );
void STM32FXXXI2c3EvNvic( uint8_t state );
void STM32FXXXI2c3ErNvic( uint8_t state );

#endif

/*** EOF ***/

