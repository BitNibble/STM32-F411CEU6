#include "stm32fxxxtim9to14.h"

/*** File Variable ***/
static STM32FXXX_TIM9 stm32fxxx_tim9;
static STM32FXXX_TIM10 stm32fxxx_tim10;
static STM32FXXX_TIM11 stm32fxxx_tim11;
static STM32FXXX_TIM12 stm32fxxx_tim12;
static STM32FXXX_TIM13 stm32fxxx_tim13;
static STM32FXXX_TIM14 stm32fxxx_tim14;
/*** TIMER 9 to 14 Procedure & Function Definition ***/
/************/
/*** TIM9 ***/
/************/
void STM32FXXXTim9Clock(uint8_t state)
{
	if(state)
	set_reg(RCC->APB2ENR, 1 << 16); // Enable TIM9 clock
	else
	clear_reg(RCC->APB2ENR, 1 << 16); // Disable TIM9 clock
}

void STM32FXXXTim9Nvic(uint8_t state)
{
	if(state)
	set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);
	else
	set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);
}
/*************/
/*** TIM10 ***/
/*************/
void STM32FXXXTim10Clock(uint8_t state)
{
	if(state)
	set_reg(RCC->APB2ENR, 1 << 17); // Enable TIM10 clock
	else
	clear_reg(RCC->APB2ENR, 1 << 17); // Disable TIM10 clock
}

void STM32FXXXTim10Nvic(uint8_t state)
{
	if(state)
	set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);
	else
	set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);
}
/*************/
/*** TIM11 ***/
/*************/
void STM32FXXXTim11Clock(uint8_t state)
{
	if(state)
	set_reg(RCC->APB2ENR, 1 << 18); // Enable TIM11 clock
	else
	clear_reg(RCC->APB2ENR, 1 << 18); // Disable TIM11 clock
}

void STM32FXXXTim11Nvic(uint8_t state)
{
	if(state)
	set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
	else
	set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
}
#ifdef STM32F446xx
/*************/
/*** TIM12 ***/
/*************/
void STM32FXXXTim12Clock(uint8_t state)
{
	if(state)
	set_reg(RCC->APB1ENR, 1 << 6); // Enable TIM12 clock
	else
	clear_reg(RCC->APB1ENR, 1 << 6); // Disable TIM12 clock
}

void STM32FXXXTim12Nvic(uint8_t state)
{
	if(state)
	set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);
	else
	set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);
}
/*************/
/*** TIM13 ***/
/*************/
void STM32FXXXTim13Clock(uint8_t state)
{
	if(state)
	set_reg(RCC->APB1ENR, 1 << 7); // Enable TIM13 clock
	else
	clear_reg(RCC->APB1ENR, 1 << 7); // Disable TIM13 clock
}

void STM32FXXXTim13Nvic(uint8_t state)
{
	if(state)
	set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);
	else
	set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);
}
/*************/
/*** TIM14 ***/
/*************/
void STM32FXXXTim14Clock(uint8_t state)
{
	if(state)
	set_reg(RCC->APB1ENR, 1 << 8); // Enable TIM14 clock
	else
	clear_reg(RCC->APB1ENR, 1 << 8); // Disable TIM14 clock
}

void STM32FXXXTim14Nvic(uint8_t state)
{
	if(state)
	set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
	else
	set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
}
#endif
/*** TIM9 Procedure & Function Definition ***/
STM32FXXX_TIM9* tim9_enable(void)
{
	/*** TIM9 Bit Mapping Link ***/
	stm32fxxx_tim9.instance = TIM9;
	// CLOCK
	stm32fxxx_tim9.clock = STM32FXXXTim9Clock;
	// NVIC
	stm32fxxx_tim9.nvic = STM32FXXXTim9Nvic;

	return &stm32fxxx_tim9;
}

STM32FXXX_TIM9* tim9(void) { return &stm32fxxx_tim9; }

/*** TIM10 Procedure & Function Definition***/
STM32FXXX_TIM10* tim10_enable(void)
{
	/*** TIM10 Bit Mapping Link ***/
	stm32fxxx_tim10.instance = TIM10;
	// CLOCK
	stm32fxxx_tim10.clock = STM32FXXXTim10Clock;
	// NVIC
	stm32fxxx_tim10.nvic = STM32FXXXTim10Nvic;

	return &stm32fxxx_tim10;
}

STM32FXXX_TIM10* tim10(void) { return &stm32fxxx_tim10; }

/*** TIM11 Procedure & Function Definition ***/
STM32FXXX_TIM11* tim11_enable(void)
{
	/*** TIM11 Bit Mapping Link ***/
	stm32fxxx_tim11.instance = TIM11;
	// CLOCK
	stm32fxxx_tim11.clock = STM32FXXXTim11Clock;
	// NVIC
	stm32fxxx_tim11.nvic = STM32FXXXTim11Nvic;

	return &stm32fxxx_tim11;
}

STM32FXXX_TIM11* tim11(void) { return &stm32fxxx_tim11; }

/*** TIM12 Procedure & Function Definition ***/
STM32FXXX_TIM12* tim12_enable(void)
{
	/*** TIM12 Bit Mapping Link ***/
	stm32fxxx_tim12.instance = TIM12;
	// CLOCK
	stm32fxxx_tim12.clock = STM32FXXXTim12Clock;
	// NVIC
	stm32fxxx_tim12.nvic = STM32FXXXTim12Nvic;

	return &stm32fxxx_tim12;
}

STM32FXXX_TIM12* tim12(void) { return &stm32fxxx_tim12; }

/*** TIM13 Procedure & Function Definition ***/
STM32FXXX_TIM13* tim13_enable(void)
{
	/*** TIM13 Bit Mapping Link ***/
	stm32fxxx_tim13.instance = TIM13;
	// CLOCK
	stm32fxxx_tim13.clock = STM32FXXXTim13Clock;
	// NVIC
	stm32fxxx_tim13.nvic = STM32FXXXTim13Nvic;

	return &stm32fxxx_tim13;
}

STM32FXXX_TIM13* tim13(void) { return &stm32fxxx_tim13; }

/*** TIM14 Procedure & Function Definition ***/
STM32FXXX_TIM14* tim14_enable(void)
{
	/*** TIM14 Bit Mapping Link ***/
	stm32fxxx_tim14.instance = TIM14;
	// CLOCK
	stm32fxxx_tim14.clock = STM32FXXXTim14Clock;
	// NVIC
	stm32fxxx_tim14.nvic = STM32FXXXTim14Nvic;

	return &stm32fxxx_tim14;
}

STM32FXXX_TIM14* tim14(void) { return &stm32fxxx_tim14; }

/*** Interrupt Handlers ***/
void TIM1_BRK_TIM9_IRQHandler(void) {
	// Handle TIM9 interrupt
}

void TIM1_UP_TIM10_IRQHandler(void) {
	// Handle TIM10 interrupt
}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
	// Handle TIM11 interrupt
}

void TIM8_BRK_TIM12_IRQHandler(void) {
	// Handle TIM12 interrupt
}

void TIM8_UP_TIM13_IRQHandler(void) {
	// Handle TIM13 interrupt
}

void TIM8_TRG_COM_TIM14_IRQHandler(void) {
	// Handle TIM14 interrupt
}
