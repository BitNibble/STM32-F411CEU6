/******************************************************************************
	STM32 XXX systick
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Update: 16012024
Comment:
	
*******************************************************************************/
#ifndef _ARMSYSTICK_H_
	#define _ARMSYSTICK_H_

#include <inttypes.h>

void _delay_us(uint16_t us);
void _delay_10us(uint16_t dez_us);
void _delay_ms(uint16_t ms);
void systick_start(void);

void SysTick_Handler(void);

#endif

/*** EOF ***/

