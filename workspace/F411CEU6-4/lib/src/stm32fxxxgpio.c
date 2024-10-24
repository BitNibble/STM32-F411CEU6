/******************************************************************************
	STM32 XXX GPIO
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19/06/2023
Update: 28/02/2024
Comment:
	File Vars, File Function Header, Library Function Definitions.
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxgpio.h"
#include <math.h>

/****************************************/
#ifndef ZERO
	#define ZERO 0
#endif
#ifndef ONE
	#define ONE 1
#endif
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define N_BITS 32
#define N_LIMBITS 33
#define H_BIT 31
#define L_BIT 0
#ifndef ON
	#define ON 1
#endif
#ifndef OFF
	#define OFF 0
#endif
/****************************************/

/*** File Variables ***/
static STM32FXXX_GPIOA stm32fxxx_gpioa = {0};
static STM32FXXX_GPIOB stm32fxxx_gpiob = {0};
static STM32FXXX_GPIOC stm32fxxx_gpioc = {0};
static STM32FXXX_GPIOD stm32fxxx_gpiod = {0};
static STM32FXXX_GPIOE stm32fxxx_gpioe = {0};
#ifdef STM32F446xx
	static STM32FXXX_GPIOF stm32fxxx_gpiof = {0};
	static STM32FXXX_GPIOG stm32fxxx_gpiog = {0};
	static STM32FXXX_GPIOH stm32fxxx_gpioh = {0};
#endif
/*** GPIO Procedure & Function Definition ***/
/*** GPIOA ***/
void STM32FXXXGpioAclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOAEN_Pos);
    }
}
void STM32FXXXGpioAmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOA->MODER &= ~(MASK << Pos);
		GPIOA->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioAotype(uint8_t pin, uint8_t otype)
{
    if(pin < WORD_BITS && otype < TWO){
    	GPIOA->OTYPER |= ( otype << pin );
    }
}
void STM32FXXXGpioAospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		ospeed &= MASK;
		GPIOA->OSPEEDR &= ~( MASK << Pos );
		GPIOA->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioApupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		pupd &= MASK;
		GPIOA->PUPDR &= ~( MASK << Pos );
		GPIOA->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioAsethpins(uint16_t hpins)
{
	GPIOA->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioAclearhpins(uint16_t hpins)
{
	GPIOA->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioAlck(uint16_t hpins){
	GPIOA->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOA->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOA->LCKR |= 1 << WORD_BITS;
			GPIOA->LCKR &= ~(1 << WORD_BITS);
			GPIOA->LCKR |= 1 << WORD_BITS;
			(void)GPIOA->LCKR;
			status--;
		}
	}

}
void STM32FXXXGpioAaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
    	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

    	af &= MASK;
    	if(index < TWO){
    		GPIOA->AFR[index] &= ~( MASK << Pos );
    		GPIOA->AFR[index] |= ( af << Pos );
    	}
	}
}

/*** GPIOB ***/
void STM32FXXXGpioBclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOBEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOBEN_Pos);
    }
}
void STM32FXXXGpioBmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOB->MODER &= ~(MASK << Pos);
		GPIOB->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioBotype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOB->OTYPER |= ( otype << pin );
	}
}
void STM32FXXXGpioBospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOB->OSPEEDR &= ~( MASK << Pos );
    	GPIOB->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioBpupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOB->PUPDR &= ~( MASK << Pos );
    	GPIOB->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioBsethpins(uint16_t hpins)
{
	GPIOB->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioBclearhpins(uint16_t hpins)
{
	GPIOB->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioBlck(uint16_t hpins){
	GPIOB->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOB->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOB->LCKR |= 1 << WORD_BITS;
			GPIOB->LCKR &= ~(1 << WORD_BITS);
			GPIOB->LCKR |= 1 << WORD_BITS;
			(void)GPIOB->LCKR;
			status--;
		}
	}
}
void STM32FXXXGpioBaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOB->AFR[index] &= ~( MASK << Pos );
	    	GPIOB->AFR[index] |= ( af << Pos );
		}
	}
}

/*** GPIOC ***/
void STM32FXXXGpioCclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOCEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOCEN_Pos);
    }
}
void STM32FXXXGpioCmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOC->MODER &= ~(MASK << Pos);
		GPIOC->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioCotype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
    	GPIOC->OTYPER |= ( otype << pin );
	}
}
void STM32FXXXGpioCospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOC->OSPEEDR &= ~( MASK << Pos );
    	GPIOC->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioCpupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOC->PUPDR &= ~( MASK << Pos );
    	GPIOC->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioCsethpins(uint16_t hpins)
{
	GPIOC->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioCclearhpins(uint16_t hpins)
{
	GPIOC->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioClck(uint16_t hpins){
	GPIOC->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOC->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOC->LCKR |= 1 << WORD_BITS;
			GPIOC->LCKR &= ~(1 << WORD_BITS);
			GPIOC->LCKR |= 1 << WORD_BITS;
			(void)GPIOC->LCKR;
			status--;
		}
	}

}
void STM32FXXXGpioCaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOC->AFR[index] &= ~( MASK << Pos );
	    	GPIOC->AFR[index] |= ( af << Pos );
		}
	}
}

/*** GPIOD ***/
void STM32FXXXGpioDclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIODEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIODEN_Pos);
    }
}
void STM32FXXXGpioDmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOD->MODER &= ~(MASK << Pos);
		GPIOD->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioDotype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOD->OTYPER |= ( otype << pin );
	}
}
void STM32FXXXGpioDospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		ospeed &= MASK;
		GPIOD->OSPEEDR &= ~( MASK << Pos );
		GPIOD->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioDpupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOD->PUPDR &= ~( MASK << Pos );
    	GPIOD->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioDsethpins(uint16_t hpins)
{
	GPIOD->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioDclearhpins(uint16_t hpins)
{
	GPIOD->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioDlck(uint16_t hpins){
	GPIOD->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOD->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOD->LCKR |= 1 << WORD_BITS;
			GPIOD->LCKR &= ~(1 << WORD_BITS);
			GPIOD->LCKR |= 1 << WORD_BITS;
			(void)GPIOD->LCKR;
			status--;
		}
	}
}
void STM32FXXXGpioDaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOD->AFR[index] &= ~( MASK << Pos );
	    	GPIOD->AFR[index] |= ( af << Pos );
		}
	}
}

/*** GPIOE ***/
void STM32FXXXGpioEclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOEEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOEEN_Pos);
    }
}
void STM32FXXXGpioEmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOE->MODER &= ~(MASK << Pos);
		GPIOE->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioEotype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOE->OTYPER |= ( otype << pin );
	}
}
void STM32FXXXGpioEospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		ospeed &= MASK;
		GPIOE->OSPEEDR &= ~( MASK << Pos );
		GPIOE->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioEpupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		pupd &= MASK;
		GPIOE->PUPDR &= ~( MASK << Pos );
		GPIOE->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioEsethpins(uint16_t hpins)
{
	GPIOE->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioEclearhpins(uint16_t hpins)
{
	GPIOE->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioElck(uint16_t hpins){
	GPIOE->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOE->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOE->LCKR |= 1 << WORD_BITS;
			GPIOE->LCKR &= ~(1 << WORD_BITS);
			GPIOE->LCKR |= 1 << WORD_BITS;
			(void)GPIOE->LCKR;
			status--;
		}
	}

}
void STM32FXXXGpioEaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOE->AFR[index] &= ~( MASK << Pos );
			GPIOE->AFR[index] |= ( af << Pos );
		}
	}
}

#ifdef STM32F446xx
/*** GPIOF ***/
void STM32FXXXGpioFclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOFEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOFEN_Pos);
    }
}
void STM32FXXXGpioFmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOF->MODER &= ~(MASK << Pos);
		GPIOF->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioFotype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOF->OTYPER |= ( otype << Pin );
	}
}
void STM32FXXXGpioFospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOF->OSPEEDR &= ~( MASK << Pos );
    	GPIOF->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioFpupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOF->PUPDR &= ~( MASK << Pos );
    	GPIOF->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioFsethpins(uint16_t hpins)
{
	GPIOF->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioFclearhpins(uint16_t hpins)
{
	GPIOF->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioFlck(uint16_t hpins){
	GPIOF->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOF->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOF->LCKR |= 1 << WORD_BITS;
			GPIOF->LCKR &= ~(1 << WORD_BITS);
			GPIOF->LCKR |= 1 << WORD_BITS;
			(void)GPIOF->LCKR;
			status--;
		}
	}

}
void STM32FXXXGpioFaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOF->AFR[index] &= ~( MASK << Pos );
	    	GPIOF->AFR[index] |= ( af << Pos );
		}
	}
}

/*** GPIOG ***/
void STM32FXXXGpioGclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOGEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOGEN_Pos);
    }
}
void STM32FXXXGpioGmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOG->MODER &= ~(MASK << Pos);
		GPIOG->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioGotype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOG->OTYPER |= ( otype << Pin );
	}
}
void STM32FXXXGpioGospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOG->OSPEEDR &= ~( MASK << Pos );
    	GPIOG->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioGpupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOG->PUPDR &= ~( MASK << Pos );
    	GPIOG->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioGsethpins(uint16_t hpins)
{
	GPIOG->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioGclearhpins(uint16_t hpins)
{
	GPIOG->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioGlck(uint16_t hpins){
	GPIOG->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOG->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOG->LCKR |= 1 << WORD_BITS;
			GPIOG->LCKR &= ~(1 << WORD_BITS);
			GPIOG->LCKR |= 1 << WORD_BITS;
			(void)GPIOG->LCKR;
			status--;
		}
	}

}
void STM32FXXXGpioGaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOG->AFR[index] &= ~( MASK << Pos );
	    	GPIOG->AFR[index] |= ( af << Pos );
		}
	}
}

/*** GPIOH ***/
void STM32FXXXGpioHclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOHEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOHEN_Pos);
    }
}
void STM32FXXXGpioHmoder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOH->MODER &= ~(MASK << Pos);
		GPIOH->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioHotype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOH->OTYPER |= ( otype << Pin );
	}
}
void STM32FXXXGpioHospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOH->OSPEEDR &= ~( MASK << Pos );
    	GPIOH->OSPEEDR |= ( ospeed << Pos );
	}
}
void STM32FXXXGpioHpupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		pupd &= MASK;
    	GPIOH->PUPDR &= ~( MASK << Pos );
    	GPIOH->PUPDR |= ( pupd << Pos );
	}
}
void STM32FXXXGpioHsethpins(uint16_t hpins)
{
	GPIOH->BSRR = (uint32_t)hpins;
}
void STM32FXXXGpioHclearhpins(uint16_t hpins)
{
	GPIOH->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void STM32FXXXGpioHlck(uint16_t hpins){
	GPIOH->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOH->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOH->LCKR |= 1 << WORD_BITS;
			GPIOH->LCKR &= ~(1 << WORD_BITS);
			GPIOH->LCKR |= 1 << WORD_BITS;
			(void)GPIOH->LCKR;
			status--;
		}
	}

}
void STM32FXXXGpioHaf(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOH->AFR[index] &= ~( MASK << Pos );
	    	GPIOH->AFR[index] |= ( af << Pos );
		}
	}
}
#endif
/*** Initialization Procedures & Function Definitions ***/
void gpioa_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioAclock(ON);
    /*** GPIOA TypeDef ***/
	stm32fxxx_gpioa.instance = GPIOA;
    /*** GPIOA RCC Clock Enable ***/
    stm32fxxx_gpioa.clock = STM32FXXXGpioAclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpioa.moder = STM32FXXXGpioAmoder;
    stm32fxxx_gpioa.otype = STM32FXXXGpioAotype;
    stm32fxxx_gpioa.ospeed = STM32FXXXGpioAospeed;
    stm32fxxx_gpioa.pupd = STM32FXXXGpioApupd;
    stm32fxxx_gpioa.set_hpins = STM32FXXXGpioAsethpins;
    stm32fxxx_gpioa.clear_hpins = STM32FXXXGpioAclearhpins;
    stm32fxxx_gpioa.lck = STM32FXXXGpioAlck;
    stm32fxxx_gpioa.af = STM32FXXXGpioAaf;
    //return &stm32fxxx_gpioa;
}

STM32FXXX_GPIOA* gpioa(void) { return &stm32fxxx_gpioa; }

void gpiob_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioBclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpiob.instance = GPIOB;
    /*** GPIOB RCC Clock Enable ***/
    stm32fxxx_gpiob.clock = STM32FXXXGpioBclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiob.moder = STM32FXXXGpioBmoder;
    stm32fxxx_gpiob.otype = STM32FXXXGpioBotype;
    stm32fxxx_gpiob.ospeed = STM32FXXXGpioBospeed;
    stm32fxxx_gpiob.pupd = STM32FXXXGpioBpupd;
    stm32fxxx_gpiob.set_hpins = STM32FXXXGpioBsethpins;
    stm32fxxx_gpiob.clear_hpins = STM32FXXXGpioBclearhpins;
    stm32fxxx_gpiob.lck = STM32FXXXGpioBlck;
    stm32fxxx_gpiob.af = STM32FXXXGpioBaf;
    //return &stm32fxxx_gpiob;
}

STM32FXXX_GPIOB* gpiob(void) { return &stm32fxxx_gpiob; }

void gpioc_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioCclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpioc.instance = GPIOC;
    /*** GPIOC RCC Clock Enable ***/
    stm32fxxx_gpioc.clock = STM32FXXXGpioCclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpioc.moder = STM32FXXXGpioCmoder;
    stm32fxxx_gpioc.otype = STM32FXXXGpioCotype;
    stm32fxxx_gpioc.ospeed = STM32FXXXGpioCospeed;
    stm32fxxx_gpioc.pupd = STM32FXXXGpioCpupd;
    stm32fxxx_gpioc.set_hpins = STM32FXXXGpioCsethpins;
    stm32fxxx_gpioc.clear_hpins = STM32FXXXGpioCclearhpins;
    stm32fxxx_gpioc.lck = STM32FXXXGpioClck;
    stm32fxxx_gpioc.af = STM32FXXXGpioCaf;
    //return &stm32fxxx_gpioc;
}

STM32FXXX_GPIOC* gpioc(void) { return &stm32fxxx_gpioc; }

void gpiod_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioDclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpiod.instance = GPIOD;
    /*** GPIOD RCC Clock Enable ***/
    stm32fxxx_gpiod.clock = STM32FXXXGpioDclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiod.moder = STM32FXXXGpioDmoder;
    stm32fxxx_gpiod.otype = STM32FXXXGpioDotype;
    stm32fxxx_gpiod.ospeed = STM32FXXXGpioDospeed;
    stm32fxxx_gpiod.pupd = STM32FXXXGpioDpupd;
    stm32fxxx_gpiod.set_hpins = STM32FXXXGpioDsethpins;
    stm32fxxx_gpiod.clear_hpins = STM32FXXXGpioDclearhpins;
    stm32fxxx_gpiod.lck = STM32FXXXGpioDlck;
    stm32fxxx_gpiod.af = STM32FXXXGpioDaf;
    //return &stm32fxxx_gpiod;
}

STM32FXXX_GPIOD* gpiod(void) { return &stm32fxxx_gpiod; }

void gpioe_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioEclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpioe.instance = GPIOE;
    /*** GPIOE RCC Clock Enable ***/
    stm32fxxx_gpioe.clock = STM32FXXXGpioEclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpioe.moder = STM32FXXXGpioEmoder;
    stm32fxxx_gpioe.otype = STM32FXXXGpioEotype;
    stm32fxxx_gpioe.ospeed = STM32FXXXGpioEospeed;
    stm32fxxx_gpioe.pupd = STM32FXXXGpioEpupd;
    stm32fxxx_gpioe.set_hpins = STM32FXXXGpioEsethpins;
    stm32fxxx_gpioe.clear_hpins = STM32FXXXGpioEclearhpins;
    stm32fxxx_gpioe.lck = STM32FXXXGpioElck;
    stm32fxxx_gpioe.af = STM32FXXXGpioEaf;
    //return &stm32fxxx_gpioe;
}

STM32FXXX_GPIOE* gpioe(void) { return &stm32fxxx_gpioe; }

#ifdef STM32F446xx
void gpiof_enable(void)
{
	STM32FXXXGpioFclock(ON);
    stm32fxxx_gpiof.instance = GPIOF;
    /*** GPIOF RCC Clock Enable ***/
    stm32fxxx_gpiof.clock = STM32FXXXGpioFclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiof.moder = STM32FXXXGpioFmoder;
    stm32fxxx_gpiof.otype = STM32FXXXGpioFotype;
    stm32fxxx_gpiof.ospeed = STM32FXXXGpioFospeed;
    stm32fxxx_gpiof.pupd = STM32FXXXGpioFpupd;
    stm32fxxx_gpiof.set_hpins = STM32FXXXGpioFsethpins;
    stm32fxxx_gpiof.clear_hpins = STM32FXXXGpioFclearhpins;
    stm32fxxx_gpiof.lck = STM32FXXXGpioFlck;
    stm32fxxx_gpiof.af = STM32FXXXGpioFaf;
    //return &stm32fxxx_gpiof;
}

STM32FXXX_GPIOF* gpiof(void) { return &stm32fxxx_gpiof; }

void gpiog_enable(void)
{
	STM32FXXXGpioGclock(ON);
    stm32fxxx_gpiog.instance = GPIOG;
    /*** GPIOG RCC Clock Enable ***/
    stm32fxxx_gpiog.clock = STM32FXXXGpioGclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiog.moder = STM32FXXXGpioGmoder;
    stm32fxxx_gpiog.otype = STM32FXXXGpioGotype;
    stm32fxxx_gpiog.ospeed = STM32FXXXGpioGospeed;
    stm32fxxx_gpiog.pupd = STM32FXXXGpioGpupd;
    stm32fxxx_gpiog.set_hpins = STM32FXXXGpioGsethpins;
    stm32fxxx_gpiog.clear_hpins = STM32FXXXGpioGclearhpins;
    stm32fxxx_gpiog.lck = STM32FXXXGpioGlck;
    stm32fxxx_gpiog.af = STM32FXXXGpioGaf;
    //return &stm32fxxx_gpiog;
}

STM32FXXX_GPIOG* gpiog(void) { return &stm32fxxx_gpiog; }

void gpioh_enable(void)
{
	STM32FXXXGpioHclock(ON);
    stm32fxxx_gpioh.instance = GPIOH;
    /*** GPIOH RCC Clock Enable ***/
    stm32fxxx_gpioh.clock = STM32FXXXGpioHclock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpioh.moder = STM32FXXXGpioHmoder;
    stm32fxxx_gpioh.otype = STM32FXXXGpioHotype;
    stm32fxxx_gpioh.ospeed = STM32FXXXGpioHospeed;
    stm32fxxx_gpioh.pupd = STM32FXXXGpioHpupd;
    stm32fxxx_gpioh.set_hpins = STM32FXXXGpioHsethpins;
    stm32fxxx_gpioh.clear_hpins = STM32FXXXGpioHclearhpins;
    stm32fxxx_gpioh.lck = STM32FXXXGpioHlck;
    stm32fxxx_gpioh.af = STM32FXXXGpioHaf;
    //return &stm32fxxx_gpioh;
}

STM32FXXX_GPIOH* gpioh(void) { return &stm32fxxx_gpioh; }

#endif

/*
 * More Interested in finding the best work flow, then coding itself. Because that will become redundant after
 * achieving the objective.
 * bit_n = bit_n % DWORD_BITS; is the same as bit_n = bit_n & (DWORD_BITS - 1);, for power of two numbers.
 * **/

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

/**** EOF ****/

