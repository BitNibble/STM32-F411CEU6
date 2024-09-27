/******************************************************************************
	STM32 XXX TIM 6 and 7
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM6AND7_H_
	#define _STM32FXXXTIM6AND7_H_
/*** Library ***/
#include "armquery.h"
/*** TIMER TypeDef***/
// ( 6 and 7 ) TIM 
typedef struct
{

	/*** Bit Mapping ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
}STM32FXXX_TIM6, STM32FXXX_TIM7;
/************************/
/*** INIC TIM 6 AND 7 ***/
/***********************/
STM32FXXX_TIM6* tim6_enable(void);
STM32FXXX_TIM6* tim6(void);
STM32FXXX_TIM7* tim7_enable(void);
STM32FXXX_TIM7* tim7(void);
/****************************************/
/*** TIM6 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim6Clock(uint8_t bool);
void STM32FXXXTim6Nvic(uint8_t bool);
/****************************************/
/*** TIM7 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim7Clock(uint8_t bool);
void STM32FXXXTim7Nvic(uint8_t bool);
/*** INTERRUPT HEADER ***/
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);

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

