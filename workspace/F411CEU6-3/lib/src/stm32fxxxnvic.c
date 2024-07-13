/******************************************************************************
	STM32FXXX NVIC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19062023
Comment:
	Interrupt Vector
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxnvic.h"

/*** File Variable ***/
static STM32FXXXNVICobj stm32fxxx_nvic;

/*** NVIC Procedure & Function Definition ***/
void STM32FXXXNVIC_set_enable( uint8_t IRQn )
{
	setbit(NVIC->ISER, 1, IRQn, 1);
}
void STM32FXXXNVIC_clear_enable( uint8_t IRQn )
{
	setbit(NVIC->ICER, 1, IRQn, 1);
}
void STM32FXXXNVIC_set_pending( uint8_t IRQn )
{
	setbit(NVIC->ISPR, 1, IRQn, 1);
}
void STM32FXXXNVIC_clear_pending( uint8_t IRQn )
{
	setbit(NVIC->ICPR, 1, IRQn, 1);
}
uint8_t STM32FXXXNVIC_active( uint8_t IRQn ) // Query
{
	volatile uint32_t* reg = NVIC->IABR;
	uint8_t bool; uint32_t n = 0;
	if(IRQn > 31){ n = IRQn/32; IRQn = IRQn - (n * 32); }
	if( *(reg + n ) & (1 << IRQn) ) bool = 1; else bool = 0 ;
	//return nvic_getsetbit(NVIC->ICPR, 1, IRQn);
	return bool;
}
void STM32FXXXNVIC_priority(uint32_t IRQn, uint32_t priority)
{
	volatile uint8_t* reg = (uint8_t*) NVIC->IP;
	*(reg + IRQn ) = priority;
}
void STM32FXXXNVIC_trigger(uint32_t IRQn)
{
	writereg(&NVIC->STIR, 9, 0, IRQn);
}
/*** INIC Procedure & Function Definition ***/
STM32FXXXNVICobj* nvic_enable(void)
{

	/*** NVIC Bit Mapping Link ***/
	stm32fxxx_nvic.set_enable = STM32FXXXNVIC_set_enable;
	stm32fxxx_nvic.clear_enable = STM32FXXXNVIC_clear_enable;
	stm32fxxx_nvic.set_pending = STM32FXXXNVIC_set_pending;
	stm32fxxx_nvic.clear_pending = STM32FXXXNVIC_clear_pending;
	stm32fxxx_nvic.active = STM32FXXXNVIC_active;
	stm32fxxx_nvic.priority = STM32FXXXNVIC_priority;
	stm32fxxx_nvic.trigger = STM32FXXXNVIC_trigger;
	return &stm32fxxx_nvic;
}

STM32FXXXNVICobj* nvic(void){ return (STM32FXXXNVICobj*) &stm32fxxx_nvic; }

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

