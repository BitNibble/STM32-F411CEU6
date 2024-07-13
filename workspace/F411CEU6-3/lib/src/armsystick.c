/******************************************************************************
	STM32 XXX systick
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Update: 16012024
Comment:
	
*******************************************************************************/
#include "armsystick.h"
#include "armquery.h"

/*** File Variables ***/
volatile uint32_t DelayCounter;
uint32_t DelayCounter_top;
uint32_t systick_sysclk_calc_xs;
/*** File Function Prototypes ***/
uint32_t systick_sysclk_us(void);
uint32_t systick_sysclk_5us(void);
uint32_t systick_sysclk_10us(void);
uint32_t systick_sysclk_ms(void);
uint32_t systick_sysclk_xs(void);
/*** File Function Definition ***/
uint32_t systick_sysclk_us(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 1000000 - 1;
}
uint32_t systick_sysclk_5us(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 200000 - 1;
}
uint32_t systick_sysclk_10us(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 100000 - 1;
}
uint32_t systick_sysclk_ms(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 1000 - 1;
}
uint32_t systick_sysclk_xs(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 100000 - 1;
}
/******/
void _delay_us(uint32_t us)
{
	uint32_t trigger = systick_sysclk_us();
	SysTick->LOAD = trigger;
	trigger *= us;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); DelayCounter < trigger; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void _delay_5us(uint32_t cinco_us)
{
	uint32_t trigger = systick_sysclk_5us();
	SysTick->LOAD = trigger;
	trigger *= cinco_us;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); DelayCounter < trigger; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void _delay_10us(uint32_t dez_us)
{
	uint32_t trigger = systick_sysclk_10us();
	SysTick->LOAD = trigger;
	trigger *= dez_us;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); DelayCounter < trigger; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void _delay_ms(uint32_t ms)
{
	uint32_t trigger = systick_sysclk_ms();
	SysTick->LOAD = trigger;
	trigger *= ms;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); DelayCounter < trigger; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void _delay_xs(uint32_t xs)
{
	uint32_t trigger = systick_sysclk_xs();
	SysTick->LOAD = trigger;
	trigger *= xs;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); DelayCounter < trigger; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void systick_start(void)
{
	DelayCounter_top = getsysclk()/gethpre();
	//DelayCounter_top = getsysclk();
	SysTick->LOAD = 0xffffffff;
	SysTick->VAL = 0UL;
	SysTick->CTRL |= ((1 << 1) | (1 << 2));
}

/**** Interrupt Handler ****/
void SysTick_Handler(void)
{
	DelayCounter += systick_sysclk_calc_xs;
}
/***************************/

/*** EOF ***/

