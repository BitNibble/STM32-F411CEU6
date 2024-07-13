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
#ifndef _STM32FXXXNVIC_H_
	#define _STM32FXXXNVIC_H_
/*** Library ***/
#include "armquery.h"
/*** NVIC TypeDef ***/
typedef struct
{

	/*** Bit Mapping ***/
	void (*set_enable)( uint8_t IRQn );
	void (*clear_enable)( uint8_t IRQn );
	void (*set_pending)( uint8_t IRQn );
	void (*clear_pending)( uint8_t IRQn );
	uint8_t (*active)( uint8_t IRQn );
	void (*priority)(uint32_t IRQn, uint32_t priority);
	void (*trigger)(uint32_t IRQn);
	/*** Other ***/
}STM32FXXXNVICobj;

STM32FXXXNVICobj* nvic_enable(void);
STM32FXXXNVICobj* nvic(void);

/*** NVIC Bit Mapping Header ***/
// NVIC
void STM32FXXXNVIC_set_enable( uint8_t IRQn );
void STM32FXXXNVIC_clear_enable( uint8_t IRQn );
void STM32FXXXNVIC_set_pending( uint8_t IRQn );
void STM32FXXXNVIC_clear_pending( uint8_t IRQn );
uint8_t STM32FXXXNVIC_active( uint8_t IRQn );
void STM32FXXXNVIC_priority(uint32_t IRQn, uint32_t priority);
void STM32FXXXNVIC_trigger(uint32_t IRQn);

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

