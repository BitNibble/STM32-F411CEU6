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
static uint32_t systick_us;
static uint32_t systick_10us;
static uint32_t systick_ms;
static uint32_t systick_xs;
static uint32_t systick_select;

/******/
void _delay_us(uint16_t us)
{
	systick_select = systick_us;
	SysTick->LOAD = systick_select * us;
	for( DelayCounter = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter < systick_select; );
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
}
void _delay_10us(uint16_t dez_us)
{
	systick_select = systick_10us;
	SysTick->LOAD = systick_select * dez_us;
	for( DelayCounter = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter < systick_select; );
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
}
void _delay_ms(uint16_t ms)
{
	systick_select = systick_ms;
	SysTick->LOAD = systick_select * ms;
	for( DelayCounter = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter < systick_select; );
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
}


void systick_start(void)
{
	uint32_t DelayCounter_top;

	#ifdef STM32F411xE
		DelayCounter_top = getsysclk()/(gethpre() * 1);
	#endif
	#ifdef STM32F446xx
		DelayCounter_top = getsysclk()/(gethpre() * 1);
	#endif

	systick_us 		= DelayCounter_top / 1000000 - 1;
	systick_10us 	= DelayCounter_top / 100000 - 1;
	systick_ms 		= DelayCounter_top / 1000 - 1;
	systick_xs 		= DelayCounter_top / 100000 - 1;

	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0UL;
	SysTick->CTRL |= (SYSTICK_TICKINT | SYSTICK_CLKSOURCE);
}

/**** Interrupt Handler ****/
void SysTick_Handler(void)
{
	DelayCounter += systick_select;
	HAL_IncTick();
}
/***************************/

/******
Load does not accept values below 70


******/

/*** EOF ***/

