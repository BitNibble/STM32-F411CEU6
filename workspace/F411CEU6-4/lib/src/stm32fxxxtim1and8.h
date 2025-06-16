/******************************************************************************
	STM32 XXX TIM 1 and 8
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM1AND8_H_
	#define _STM32FXXXTIM1AND8_H_

/*** Library ***/
#include "stm32fxxxinstance.h"
#include "timer_irq.h"
/*************************/
/*** TIMER1and8 TypeDef***/
/*************************/
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t value);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
}STM32FXXX_TIM1, STM32FXXX_TIM8;

void tim1_enable(void); STM32FXXX_TIM1* tim1(void);
void tim8_enable(void); STM32FXXX_TIM8* tim8(void);

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

