#include "stm32fxxxtim2to5.h"
#include "stm32fxxxnvic.h"
#include "stm32fxxxrcc.h"

/*** File Variables ***/
static STM32FXXX_TIM2 stm32fxxx_tim2;
static STM32FXXX_TIM3 stm32fxxx_tim3;
static STM32FXXX_TIM4 stm32fxxx_tim4;
static STM32FXXX_TIM5 stm32fxxx_tim5;

/************/
/*** TIM2 ***/
/************/
void STM32FXXXTim2Clock(uint8_t state)
{
	// Use set_reg_Msk or clear_reg functions for RCC handling
	if (state)
	{
		set_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
	}
	else
	{
		clear_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
	}
}

void STM32FXXXTim2Nvic(uint8_t value)
{
	if (value)
	{
		set_bit_block(NVIC->ISER, 1, TIM2_IRQn, 1);
	}
	else
	{
		set_bit_block(NVIC->ICER, 1, TIM2_IRQn, 1);
	}
}

/************/
/*** TIM3 ***/
/************/
void STM32FXXXTim3Clock(uint8_t state)
{
	if (state)
	{
		set_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
	}
	else
	{
		clear_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
	}
}

void STM32FXXXTim3Nvic(uint8_t value)
{
	if (value)
	{
		set_bit_block(NVIC->ISER, 1, TIM3_IRQn, 1);
	}
	else
	{
		set_bit_block(NVIC->ICER, 1, TIM3_IRQn, 1);
	}
}

/************/
/*** TIM4 ***/
/************/
void STM32FXXXTim4Clock(uint8_t state)
{
	if (state)
	{
		set_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
	}
	else
	{
		clear_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
	}
}

void STM32FXXXTim4Nvic(uint8_t value)
{
	if (value)
	{
		set_bit_block(NVIC->ISER, 1, TIM4_IRQn, 1);
	}
	else
	{
		set_bit_block(NVIC->ICER, 1, TIM4_IRQn, 1);
	}
}

/************/
/*** TIM5 ***/
/************/
void STM32FXXXTim5Clock(uint8_t state)
{
	if (state)
	{
		set_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
	}
	else
	{
		clear_reg(&RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
	}
}

void STM32FXXXTim5Nvic(uint8_t value)
{
	if (value)
	{
		set_bit_block(NVIC->ISER, 1, TIM5_IRQn, 1);
	}
	else
	{
		set_bit_block(NVIC->ICER, 1, TIM5_IRQn, 1);
	}
}

/*** TIM2 to TIM5 INIC Procedure & Function Definitions ***/
STM32FXXX_TIM2* tim2_enable(void)
{
	stm32fxxx_tim2.instance = TIM2;
	stm32fxxx_tim2.clock = STM32FXXXTim2Clock;
	stm32fxxx_tim2.nvic = STM32FXXXTim2Nvic;

	return &stm32fxxx_tim2;
}

STM32FXXX_TIM2* tim2(void)
{
	return (STM32FXXX_TIM2*)&stm32fxxx_tim2;
}

STM32FXXX_TIM3* tim3_enable(void)
{
	stm32fxxx_tim3.instance = TIM3;
	stm32fxxx_tim3.clock = STM32FXXXTim3Clock;
	stm32fxxx_tim3.nvic = STM32FXXXTim3Nvic;

	return &stm32fxxx_tim3;
}

STM32FXXX_TIM3* tim3(void)
{
	return (STM32FXXX_TIM3*)&stm32fxxx_tim3;
}

STM32FXXX_TIM4* tim4_enable(void)
{
	stm32fxxx_tim4.instance = TIM4;
	stm32fxxx_tim4.clock = STM32FXXXTim4Clock;
	stm32fxxx_tim4.nvic = STM32FXXXTim4Nvic;

	return &stm32fxxx_tim4;
}

STM32FXXX_TIM4* tim4(void)
{
	return (STM32FXXX_TIM4*)&stm32fxxx_tim4;
}

STM32FXXX_TIM5* tim5_enable(void)
{
	stm32fxxx_tim5.instance = TIM5;
	stm32fxxx_tim5.clock = STM32FXXXTim5Clock;
	stm32fxxx_tim5.nvic = STM32FXXXTim5Nvic;

	return &stm32fxxx_tim5;
}

STM32FXXX_TIM5* tim5(void)
{
	return (STM32FXXX_TIM5*)&stm32fxxx_tim5;
}

/***/ EOF ***/
