#ifndef _STM32FXXXTIM2TO5_H_
#define _STM32FXXXTIM2TO5_H_

/*** Library ***/
#include "stm32fxxxinstance.h"

/*************************/
/*** TIMER2to5 TypeDef ***/
/*************************/
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t value);
} STM32FXXX_TIM2, STM32FXXX_TIM3, STM32FXXX_TIM4, STM32FXXX_TIM5;

/*******************/
/*** INIC 2 to 5 ***/
/*******************/
STM32FXXX_TIM2* tim2_enable(void);
STM32FXXX_TIM2* tim2(void);
STM32FXXX_TIM3* tim3_enable(void);
STM32FXXX_TIM3* tim3(void);
STM32FXXX_TIM4* tim4_enable(void);
STM32FXXX_TIM4* tim4(void);
STM32FXXX_TIM5* tim5_enable(void);
STM32FXXX_TIM5* tim5(void);

/****************************************/
/*** TIM2 to TIM5 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim2Clock(uint8_t state);
void STM32FXXXTim2Nvic(uint8_t value);
void STM32FXXXTim3Clock(uint8_t state);
void STM32FXXXTim3Nvic(uint8_t value);
void STM32FXXXTim4Clock(uint8_t state);
void STM32FXXXTim4Nvic(uint8_t value);
void STM32FXXXTim5Clock(uint8_t state);
void STM32FXXXTim5Nvic(uint8_t value);

/****************************************/

#endif
