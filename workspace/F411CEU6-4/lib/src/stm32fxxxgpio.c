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

/****************************************/
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOA->MODER &= ~(MASK << Pos);
		GPIOA->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioAafr(uint8_t pin, uint8_t af)
{
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOB->MODER &= ~(MASK << Pos);
		GPIOB->MODER |= (mode << Pos);
	}
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
void STM32FXXXGpioBafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOB->AFR[index] &= ~( MASK << Pos );
	    GPIOB->AFR[index] |= ( data << Pos );
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOC->MODER &= ~(MASK << Pos);
		GPIOC->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioCafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOC->AFR[index] &= ~( MASK << Pos );
	    GPIOC->AFR[index] |= ( data << Pos );
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOD->MODER &= ~(MASK << Pos);
		GPIOD->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioDafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOD->AFR[index] &= ~( MASK << Pos );
	    GPIOD->AFR[index] |= ( data << Pos );
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOE->MODER &= ~(MASK << Pos);
		GPIOE->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioEafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOE->AFR[index] &= ~( MASK << Pos );
	    GPIOE->AFR[index] |= ( data << Pos );
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOF->MODER &= ~(MASK << Pos);
		GPIOF->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioFafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOF->AFR[index] &= ~( MASK << Pos );
	    GPIOF->AFR[index] |= ( data << Pos );
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOG->MODER &= ~(MASK << Pos);
		GPIOG->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioGafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOG->AFR[index] &= ~( MASK << Pos );
	    GPIOG->AFR[index] |= ( data << Pos );
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
	const uint8_t BLOCK_SIZE = TWO;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t Pos = pin * BLOCK_SIZE;

	mode &= MASK;
	if(pin < 16){
		GPIOH->MODER &= ~(MASK << Pos);
		GPIOH->MODER |= (mode << Pos);
	}
}
void STM32FXXXGpioHafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOH->AFR[index] &= ~( MASK << Pos );
	    GPIOH->AFR[index] |= ( data << Pos );
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
    stm32fxxx_gpioa.lck = NULL;
    stm32fxxx_gpioa.afr = STM32FXXXGpioAafr;
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
    stm32fxxx_gpiob.lck = STM32FXXXGpioBlck;
    stm32fxxx_gpiob.afr = STM32FXXXGpioBafr;
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
    stm32fxxx_gpioc.lck = NULL;
    stm32fxxx_gpioc.afr = STM32FXXXGpioCafr;
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
    stm32fxxx_gpiod.lck = NULL;
    stm32fxxx_gpiod.afr = STM32FXXXGpioDafr;
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
    stm32fxxx_gpioe.lck = NULL;
    stm32fxxx_gpioe.afr = STM32FXXXGpioEafr;
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
    stm32fxxx_gpiof.lck = NULL;
    stm32fxxx_gpiof.afr = STM32FXXXGpioFafr;
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
    stm32fxxx_gpiog.lck = NULL;
    stm32fxxx_gpiog.afr = STM32FXXXGpioGafr;
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
    stm32fxxx_gpioh.lck = NULL;
    stm32fxxx_gpioh.afr = STM32FXXXGpioHafr;
    //return &stm32fxxx_gpioh;
}

STM32FXXX_GPIOH* gpioh(void) { return &stm32fxxx_gpioh; }

#endif

/*
 * More Interested in finding the best work flow, then coding itself. Because that will become redundant after
 * achieving the objective.
 *
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

