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
static STM32FXXX_TIM9 stm32fxxx_tim9 = {0};
static STM32FXXX_TIM10 stm32fxxx_tim10 = {0};
static STM32FXXX_TIM11 stm32fxxx_tim11 = {0};
static STM32FXXX_TIM12 stm32fxxx_tim12 = {0};
static STM32FXXX_TIM13 stm32fxxx_tim13 = {0};
static STM32FXXX_TIM14 stm32fxxx_tim14 = {0};
/*** TIMER 9 to 14 Procedure & Function Definition ***/
/************/
/*** TIM9 ***/
/************/
void STM32FXXXTim9Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM9EN_Pos);}else{RCC->APB2ENR &= ~(1 << RCC_APB2ENR_TIM9EN_Pos);}
}
void STM32FXXXTim9Nvic(uint8_t state)
{ // 24
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);}
}
void STM32FXXXTim9start(void){ set_reg_Msk(&TIM9->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void STM32FXXXTim9stop(void){ set_reg_Msk(&TIM9->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
/*************/
/*** TIM10 ***/
/*************/
void STM32FXXXTim10Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM10EN_Pos);}else{RCC->APB2ENR &= ~(1 << RCC_APB2ENR_TIM10EN_Pos);}
}
void STM32FXXXTim10Nvic(uint8_t state)
{ // 25
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);}
}
void STM32FXXXTim10start(void){ set_reg_Msk(&TIM10->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void STM32FXXXTim10stop(void){ set_reg_Msk(&TIM10->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
/*************/
/*** TIM11 ***/
/*************/
void STM32FXXXTim11Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM11EN_Pos);}else{RCC->APB2ENR &= ~(1 << RCC_APB2ENR_TIM11EN_Pos);}
}
void STM32FXXXTim11Nvic(uint8_t state)
{ // 26
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);}
}
void STM32FXXXTim11start(void){ set_reg_Msk(&TIM11->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void STM32FXXXTim11stop(void){ set_reg_Msk(&TIM11->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
#ifdef STM32F446xx
/*************/
/*** TIM12 ***/
/*************/
void STM32FXXXTim12Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM12EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM12EN_Pos);}
}
void STM32FXXXTim12Nvic(uint8_t state)
{ // 43
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);}
}
void STM32FXXXTim12start(void){ set_reg_Msk(&TIM12->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void STM32FXXXTim12stop(void){ set_reg_Msk(&TIM12->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
/*************/
/*** TIM13 ***/
/*************/
void STM32FXXXTim13Clock(uint8_t state)
{
	if(state){
		RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM13EN_Pos); // timer 13 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM13EN_Pos); //timer 13 clock disabled
	}
}
void STM32FXXXTim13Nvic(uint8_t state)
{ // 44
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);}
}
void STM32FXXXTim13start(void){ set_reg_Msk(&TIM13->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void STM32FXXXTim13stop(void){ set_reg_Msk(&TIM13->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
/*************/
/*** TIM14 ***/
/*************/
void STM32FXXXTim14Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM14EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM14EN_Pos);}
}
void STM32FXXXTim14Nvic(uint8_t state)
{ // 45
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}
}
void STM32FXXXTim14start(void){ set_reg_Msk(&TIM14->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void STM32FXXXTim14stop(void){ set_reg_Msk(&TIM14->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
#endif
/*** TIM9 Procedure & Function Definition ***/
void tim9_enable(void)
{
	STM32FXXXTim9Clock(ON);
	/*** TIM9 Bit Mapping Link ***/
	stm32fxxx_tim9.instance = TIM9;
	// CLOCK
	stm32fxxx_tim9.clock = STM32FXXXTim9Clock;
	// NVIC
	stm32fxxx_tim9.nvic = STM32FXXXTim9Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim9.start = STM32FXXXTim9start;
	stm32fxxx_tim9.stop = STM32FXXXTim9stop;
	//return &stm32fxxx_tim9;
}

STM32FXXX_TIM9* tim9(void){ return (STM32FXXX_TIM9*) &stm32fxxx_tim9; }

/*** TIM10 Procedure & Function Definition***/
void tim10_enable(void)
{
	STM32FXXXTim10Clock(ON);
	/*** TIM10 Bit Mapping Link ***/
	stm32fxxx_tim10.instance = TIM10;
	// CLOCK
	stm32fxxx_tim10.clock = STM32FXXXTim10Clock;
	// NVIC
	stm32fxxx_tim10.nvic = STM32FXXXTim10Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim10.start = STM32FXXXTim10start;
	stm32fxxx_tim10.stop = STM32FXXXTim10stop;
	//return &stm32fxxx_tim10;
}

STM32FXXX_TIM10* tim10(void){ return (STM32FXXX_TIM10*) &stm32fxxx_tim10; }

/*** TIM11 Procedure & Function Definition***/
void tim11_enable(void)
{
	STM32FXXXTim11Clock(ON);
	/*** TIM11 Bit Mapping Link ***/
	stm32fxxx_tim11.instance = TIM11;
	// CLOCK
	stm32fxxx_tim11.clock = STM32FXXXTim11Clock;
	// NVIC
	stm32fxxx_tim11.nvic = STM32FXXXTim11Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim11.start = STM32FXXXTim11start;
	stm32fxxx_tim11.stop = STM32FXXXTim11stop;
	//return &stm32fxxx_tim11;
}

STM32FXXX_TIM11* tim11(void){ return (STM32FXXX_TIM11*) &stm32fxxx_tim11; }

/*** TIM12 Procedure & Function Definition***/
void tim12_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXTim12Clock(ON);
		stm32fxxx_tim12.instance = TIM12;
	// CLOCK
	stm32fxxx_tim12.clock = STM32FXXXTim12Clock;
	// NVIC
	stm32fxxx_tim12.nvic = STM32FXXXTim12Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim12.start = STM32FXXXTim12start;
	stm32fxxx_tim12.stop = STM32FXXXTim12stop;
	#endif
	//return &stm32fxxx_tim12;
}

STM32FXXX_TIM12* tim12(void){ return (STM32FXXX_TIM12*) &stm32fxxx_tim12; }

/*** TIM13 Procedure & Function Definition***/
void tim13_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXTim13Clock(ON);
		stm32fxxx_tim13.instance = TIM13;
	// CLOCK
	stm32fxxx_tim13.clock = STM32FXXXTim13Clock;
	// NVIC
	stm32fxxx_tim13.nvic = STM32FXXXTim13Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim13.start = STM32FXXXTim13start;
	stm32fxxx_tim13.stop = STM32FXXXTim13stop;
	#endif
	//return &stm32fxxx_tim13;
}

STM32FXXX_TIM13* tim13(void){ return (STM32FXXX_TIM13*) &stm32fxxx_tim13; }

/*** TIM14 Procedure & Function Definition ***/
void tim14_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXTim14Clock(ON);
		stm32fxxx_tim14.instance = TIM14;
	// CLOCK
	stm32fxxx_tim14.clock = STM32FXXXTim14Clock;
	// NVIC
	stm32fxxx_tim14.nvic = STM32FXXXTim14Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim14.start = STM32FXXXTim14start;
	stm32fxxx_tim14.stop = STM32FXXXTim14stop;
	#endif
	//return &stm32fxxx_tim14;
}

STM32FXXX_TIM14* tim14(void){ return (STM32FXXX_TIM14*) &stm32fxxx_tim14; }

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

