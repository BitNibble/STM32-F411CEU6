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
volatile uint32_t DelayCounter;
uint32_t DelayCounter_top;
uint32_t systick_sysclk_calc_xs;
/*** File Function Prototypes ***/
uint32_t systick_sysclk_us(void);
uint32_t systick_sysclk_10us(void);
uint32_t systick_sysclk_ms(void);
/*** File Function Definition ***/
uint32_t systick_sysclk_us(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 1000000 - 1;
}
uint32_t systick_sysclk_10us(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 100000 - 1;
}
uint32_t systick_sysclk_ms(void)
{
	return systick_sysclk_calc_xs = DelayCounter_top / 1000 - 1;
}
/******/
void _delay_us(uint16_t us)
{
	uint32_t trigger = systick_sysclk_us();
	SysTick->LOAD = trigger * us;
	//trigger *= us;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); !DelayCounter; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void _delay_10us(uint16_t dez_us)
{
	uint32_t trigger = systick_sysclk_10us();
	SysTick->LOAD = trigger * dez_us;
	//trigger *= dez_us;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); !DelayCounter; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void _delay_ms(uint16_t ms)
{
	uint32_t trigger = systick_sysclk_ms();
	SysTick->LOAD = trigger;
	trigger *= ms;
	for( DelayCounter = 0, SysTick->CTRL |= (1 << 0); DelayCounter < trigger; );
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void systick_start(void)
{
	#ifdef STM32F411xE
		DelayCounter_top = getsysclk()/(gethpre() * 1);
	#endif
	#ifdef STM32F446xx
		DelayCounter_top = getsysclk()/(gethpre() * 1);
	#endif
	SysTick->LOAD = 0x00FFFFFF;
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

