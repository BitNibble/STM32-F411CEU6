/******************************************************************************
	STM32 XXX CRC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXCRC_H_
	#define _STM32FXXXCRC_H_

/*** Library ***/
#include "stm32fxxxinstance.h"
/*** CRC TypeDef ***/
typedef struct
{
	CRC_TypeDef* instance;
	/*** Bit Mapping ***/
	void (*dr)(uint32_t value);
	uint32_t (*get_dr)(void);
	void (*idr)(uint8_t value);
	uint8_t (*get_idr)(void);
	void (*reset)(void);
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
}STM32FXXX_CRC;

void crc_enable(void); STM32FXXX_CRC* crc(void);

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

