/******************************************************************************
	STM32 XXX TIM 9 to 14
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim9to14.h"

/*** File Variable ***/
static STM32FXXX_TIM9 stm32fxxx_tim9;
static STM32FXXX_TIM10 stm32fxxx_tim10;
static STM32FXXX_TIM11 stm32fxxx_tim11;
#ifdef __STM32F446xx_H
	static STM32FXXX_TIM12 stm32fxxx_tim12;
	static STM32FXXX_TIM13 stm32fxxx_tim13;
	static STM32FXXX_TIM14 stm32fxxx_tim14;
#endif
/*** TIMER 9 to 14 Procedure & Function Definition ***/
/************/
/*** TIM9 ***/
/************/
void STM32FXXXTim9Clock(uint8_t bool)
{
	if(bool){RCC->APB2ENR |= (1 << 16);}else{RCC->APB2ENR &= ~(1 << 16);}
}
void STM32FXXXTim9Nvic(uint8_t bool)
{ // 24
	if(bool){set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);}
}
/*************/
/*** TIM10 ***/
/*************/
void STM32FXXXTim10Clock(uint8_t bool)
{
	if(bool){RCC->APB2ENR |= (1 << 17);}else{RCC->APB2ENR &= ~(1 << 17);}
}
void STM32FXXXTim10Nvic(uint8_t bool)
{ // 25
	if(bool){set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);}
}
/*************/
/*** TIM11 ***/
/*************/
void STM32FXXXTim11Clock(uint8_t bool)
{
	if(bool){RCC->APB2ENR |= (1 << 18);}else{RCC->APB2ENR &= ~(1 << 18);}
}
void STM32FXXXTim11Nvic(uint8_t bool)
{ // 26
	if(bool){set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);}
}
#ifdef __STM32F446xx_H
/*************/
/*** TIM12 ***/
/*************/
void STM32FXXXTim12Clock(uint8_t bool)
{
	if(bool){RCC->APB1ENR |= (1 << 6);}else{RCC->APB1ENR &= ~(1 << 6);}
}
void STM32FXXXTim12Nvic(uint8_t bool)
{ // 43
	if(bool){set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);}
}
/*************/
/*** TIM13 ***/
/*************/
void STM32FXXXTim13Clock(uint8_t bool)
{
	if(bool){
		RCC->APB1ENR |= (1 << 7); // timer 13 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 7); //timer 13 clock disabled
	}
}
void STM32FXXXTim13Nvic(uint8_t bool)
{ // 44
	if(bool){set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);}
}
/*************/
/*** TIM14 ***/
/*************/
void STM32FXXXTim14Clock(uint8_t bool)
{
	if(bool){RCC->APB1ENR |= (1 << 8);}else{RCC->APB1ENR &= ~(1 << 8);}
}
void STM32FXXXTim14Nvic(uint8_t bool)
{ // 45
	if(bool){set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}
}
#endif
/*** TIM9 Procedure & Function Definition ***/
STM32FXXX_TIM9* tim9_enable(void)
{

	/*** TIM9 Bit Mapping Link ***/
	stm32fxxx_tim9.instance = tim9_instance();
	// CLOCK
	stm32fxxx_tim9.clock = STM32FXXXTim9Clock;
	// NVIC
	stm32fxxx_tim9.nvic = STM32FXXXTim9Nvic;

	return &stm32fxxx_tim9;
}

STM32FXXX_TIM9* tim9(void){ return (STM32FXXX_TIM9*) &stm32fxxx_tim9; }

/*** TIM10 Procedure & Function Definition***/
STM32FXXX_TIM10* tim10_enable(void)
{

	/*** TIM10 Bit Mapping Link ***/
	stm32fxxx_tim10.instance = tim10_instance();
	// CLOCK
	stm32fxxx_tim10.clock = STM32FXXXTim10Clock;
	// NVIC
	stm32fxxx_tim10.nvic = STM32FXXXTim10Nvic;

	return &stm32fxxx_tim10;
}

STM32FXXX_TIM10* tim10(void){ return (STM32FXXX_TIM10*) &stm32fxxx_tim10; }

/*** TIM11 Procedure & Function Definition***/
STM32FXXX_TIM11* tim11_enable(void)
{

	/*** TIM11 Bit Mapping Link ***/
	stm32fxxx_tim11.instance = tim11_instance();
	// CLOCK
	stm32fxxx_tim11.clock = STM32FXXXTim11Clock;
	// NVIC
	stm32fxxx_tim11.nvic = STM32FXXXTim11Nvic;

	return &stm32fxxx_tim11;
}

STM32FXXX_TIM11* tim11(void){ return (STM32FXXX_TIM11*) &stm32fxxx_tim11; }

#ifdef __STM32F446xx_H
/*** TIM12 Procedure & Function Definition***/
STM32FXXX_TIM12* tim12_enable(void)
{

	/*** TIM12 Bit Mapping Link ***/
	stm32fxxx_tim12.instance = tim12_instance();
	// CLOCK
	stm32fxxx_tim12.clock = STM32FXXXTim12Clock;
	// NVIC
	stm32fxxx_tim12.nvic = STM32FXXXTim12Nvic;

	return &stm32fxxx_tim12;
}

STM32FXXX_TIM12* tim12(void){ return (STM32FXXX_TIM12*) &stm32fxxx_tim12; }

/*** TIM13 Procedure & Function Definition***/
STM32FXXX_TIM13* tim13_enable(void)
{

	/*** TIM13 Bit Mapping Link ***/
	stm32fxxx_tim13.instance = tim13_instance();
	// CLOCK
	stm32fxxx_tim13.clock = STM32FXXXTim13Clock;
	// NVIC
	stm32fxxx_tim13.nvic = STM32FXXXTim13Nvic;

	return &stm32fxxx_tim13;
}

STM32FXXX_TIM13* tim13(void){ return (STM32FXXX_TIM13*) &stm32fxxx_tim13; }

/*** TIM14 Procedure & Function Definition ***/
STM32FXXX_TIM14* tim14_enable(void)
{

	/*** TIM14 Bit Mapping Link ***/
	stm32fxxx_tim14.instance = tim14_instance();
	// CLOCK
	stm32fxxx_tim14.clock = STM32FXXXTim14Clock;
	// NVIC
	stm32fxxx_tim14.nvic = STM32FXXXTim14Nvic;

	return &stm32fxxx_tim14;
}

STM32FXXX_TIM14* tim14(void){ return (STM32FXXX_TIM14*) &stm32fxxx_tim14; }

#endif

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

/*** EOF ***/

