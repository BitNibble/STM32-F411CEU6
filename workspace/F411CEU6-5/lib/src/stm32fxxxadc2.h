/******************************************************************************
	STM32 XXX ADC2
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC2_H_
	#define _STM32FXXXADC2_H_

/*** Library ***/
#include "stm32fxxxadc.h"

/*** ADC TypeDef ***/
// ADC -> ADC2
typedef struct
{
	/*** BitField Mapping ***/
	ADC_TypeDef* instance;
	ADC_Common_TypeDef* common_instance;
	/*** Other ***/
	STM32FXXXADC2single* single;
	void (*iclock)(uint8_t bool);
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
}STM32FXXX_ADC2;

// INIC
STM32FXXX_ADC2* adc2_enable(void);
STM32FXXX_ADC2* adc2(void);

/***** ADC2 Procedure & Function Header ******/
void STM32FXXXAdc2IClock(uint8_t bool);
void STM32FXXXAdc2Clock(uint8_t bool);
void STM32FXXXAdc2Nvic(uint8_t bool);
void STM32FXXXAdc2Inic(void);
void STM32FXXXAdc2Start(void);

#endif

/*** EOF ***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

