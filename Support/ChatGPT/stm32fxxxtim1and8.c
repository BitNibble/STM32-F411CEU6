#include "stm32fxxxtim1and8.h"
#include "stm32fxxxnvic.h"
#include "stm32fxxxrcc.h"

/*** File Variables ***/
static STM32FXXX_TIM1 stm32fxxx_tim1;
static STM32FXXX_TIM8 stm32fxxx_tim8;

/************/
/*** TIM1 ***/
/************/
void STM32FXXXTim1Clock(uint8_t state)
{
	// Use set_reg_Msk or clear_reg functions for RCC handling
	if (state)
	{
		set_reg_Msk(&RCC->APB2ENR, RCC_APB2ENR_TIM1EN_Msk, RCC_APB2ENR_TIM1EN_Pos, 1);
	}
	else
	{
		set_reg_Msk(&RCC->APB2ENR, RCC_APB2ENR_TIM1EN_Msk, RCC_APB2ENR_TIM1EN_Pos, 0);
	}
}

void STM32FXXXTim1Nvic(uint8_t value)
{
	STM32FXXX_NVIC* nvic = nvic_enable();

	switch (value)
	{
		case 0b1000:
		set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);
		break;
		case 0b0100:
		set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);
		break;
		case 0b0010:
		set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
		break;
		case 0b0001:
		set_bit_block(NVIC->ISER, 1, TIM1_CC_IRQn, 1);
		break;
		case 0b11000:
		set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);
		break;
		case 0b10100:
		set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);
		break;
		case 0b10010:
		set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
		break;
		case 0b10001:
		set_bit_block(NVIC->ICER, 1, TIM1_CC_IRQn, 1);
		break;
		default:
		break;
	}
}

#ifdef STM32F446xx
/************/
/*** TIM8 ***/
/************/
void STM32FXXXTim8Clock(uint8_t state)
{
	if (state)
	{
		set_reg(&RCC->APB2ENR, RCC_APB2ENR_TIM8EN_Msk);
	}
	else
	{
		clear_reg(&RCC->APB2ENR, RCC_APB2ENR_TIM8EN_Msk);
	}
}

void STM32FXXXTim8Nvic(uint8_t value)
{
	switch (value)
	{
		case 0b1000:
		set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);
		break;
		case 0b0100:
		set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);
		break;
		case 0b0010:
		set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
		break;
		case 0b0001:
		set_bit_block(NVIC->ISER, 1, TIM8_CC_IRQn, 1);
		break;
		case 0b11000:
		set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);
		break;
		case 0b10100:
		set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);
		break;
		case 0b10010:
		set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
		break;
		case 0b10001:
		set_bit_block(NVIC->ICER, 1, TIM8_CC_IRQn, 1);
		break;
		default:
		break;
	}
}

#endif

/*** TIM1 INIC Procedure & Function Definition ***/
STM32FXXX_TIM1* tim1_enable(void)
{
	/*** TIM1 Bit Field ***/
	stm32fxxx_tim1.instance = TIM1;
	// CLOCK
	stm32fxxx_tim1.clock = STM32FXXXTim1Clock;
	// NVIC
	stm32fxxx_tim1.nvic = STM32FXXXTim1Nvic;

	return &stm32fxxx_tim1;
}

STM32FXXX_TIM1* tim1(void)
{
	return (STM32FXXX_TIM1*)&stm32fxxx_tim1;
}

/*** TIM8 INIC Procedure & Function Definition ***/
STM32FXXX_TIM8* tim8_enable(void)
{
	/*** TIM8 Bit Field ***/
	#ifdef STM32F446xx
	stm32fxxx_tim8.instance = TIM8;
	#else
	stm32fxxx_tim8.instance = NULL;
	#endif
	// CLOCK
	stm32fxxx_tim8.clock = STM32FXXXTim8Clock;
	// NVIC
	stm32fxxx_tim8.nvic = STM32FXXXTim8Nvic;

	return &stm32fxxx_tim8;
}

STM32FXXX_TIM8* tim8(void)
{
	return (STM32FXXX_TIM8*)&stm32fxxx_tim8;
}

/***/ EOF ***/
