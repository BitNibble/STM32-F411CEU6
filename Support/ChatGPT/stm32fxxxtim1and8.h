#ifndef _STM32FXXXTIM1AND8_H_
#define _STM32FXXXTIM1AND8_H_

/*** Library ***/
#include "stm32fxxxinstance.h"

/*************************/
/*** TIMER1and8 TypeDef ***/
/*************************/
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t value);
} STM32FXXX_TIM1, STM32FXXX_TIM8;

/*******************/
/*** INIC 1 and 8 ***/
/*******************/
STM32FXXX_TIM1* tim1_enable(void);
STM32FXXX_TIM1* tim1(void);
STM32FXXX_TIM8* tim8_enable(void);
STM32FXXX_TIM8* tim8(void);

/****************************************/
/*** TIM1 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim1Clock(uint8_t state);
void STM32FXXXTim1Nvic(uint8_t value);

/****************************************/
/*** TIM8 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim8Clock(uint8_t state);
void STM32FXXXTim8Nvic(uint8_t value);

/****************************************/

#endif
