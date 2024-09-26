/******************************************************************************
	STM32 XXX systick
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Update: 16012024
Comment:
	
*******************************************************************************/
#include "armquery.h"
#include "armsystick.h"

#define SYSTICK_ENABLE (1 << 0)
#define SYSTICK_TICKINT (1 << 1)
#define SYSTICK_CLKSOURCE (1 << 2)

/*** File Variables ***/
volatile uint32_t DelayCounter_0;

/******/
void _delay_us(uint32_t us)
{
	SysTick->LOAD = get_systick_us( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < us; );
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
}
void _delay_10us(uint32_t dez_us)
{
	SysTick->LOAD = get_systick_10us( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < dez_us; );
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
}
void _delay_ms(uint32_t ms)
{
	SysTick->LOAD = get_systick_ms( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < ms; );
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
}


void systick_start(void)
{
	delay_Configure( );

	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0UL;
	SysTick->CTRL |= (SYSTICK_TICKINT | SYSTICK_CLKSOURCE);
}

/**** Interrupt Handler ****/
void SysTick_Handler(void)
{
	DelayCounter_0++;
	HAL_IncTick();
}
/***************************/

/******
Load does not accept values below 70
Note us only work for high frequency clocks.

******/

/*** EOF ***/

