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
void _delay_xs(uint32_t xs);
void systick_start(void);

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif

/*** EOF ***/

