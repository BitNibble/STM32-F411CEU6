/******************************************************************************
	STM32 XXX SRAM
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXSRAM_H_
	#define _STM32FXXXSRAM_H_
/*** Library ***/
#include "armquery.h"
/*** SRAM TypeDef ***/
typedef struct
{
	/*** Bit Mapping ***/
	/*** Other ***/
	void (*access)(void);
}STM32FXXXSRAMobj;

STM32FXXXSRAMobj* sram_enable(void);
STM32FXXXSRAMobj* sram(void);

/***** SRAM Procedure & Function Header ******/
void STM32FXXXSramAccess(void);
/*** SRAM Bit Mapping Header ***/

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

