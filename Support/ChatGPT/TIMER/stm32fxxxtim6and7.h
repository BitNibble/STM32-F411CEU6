#ifndef _STM32FXXXTIM6AND7_H_
#define _STM32FXXXTIM6AND7_H_

/*** Library ***/
#include "stm32fxxxinstance.h"

/*** TIMER TypeDef***/
// ( 6 and 7 ) TIM
typedef struct
{
	/*** Bit Mapping ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
} STM32FXXX_TIM6, STM32FXXX_TIM7;

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
void STM32FXXXTim6Clock(uint8_t state);
void STM32FXXXTim6Nvic(uint8_t state);

/****************************************/
/*** TIM7 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim7Clock(uint8_t state);
void STM32FXXXTim7Nvic(uint8_t state);

/*** INTERRUPT HEADER ***/
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);

#endif
