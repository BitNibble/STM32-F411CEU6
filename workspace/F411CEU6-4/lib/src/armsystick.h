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

void _delay_us(uint32_t us);
void _delay_5us(uint32_t cinco_us);
void _delay_10us(uint32_t dez_us);
void _delay_ms(uint32_t ms);
void _delay_xs(uint32_t xs);
void systick_start(void);

void SysTick_Handler(void);

#endif

/*** EOF ***/

