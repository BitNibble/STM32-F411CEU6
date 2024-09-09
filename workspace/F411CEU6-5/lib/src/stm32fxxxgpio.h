/******************************************************************************
	STM32 XXX GPIO
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19/06/2023
Update: 28/02/2024
Comment:
	TypeDef Pointer Structures, Library Function Headers.
*******************************************************************************/
#ifndef _STM32FXXXGPIO_H_
	#define _STM32FXXXGPIO_H_

/*** File Library ***/
#include "armquery.h"

/*** GPIO -> GPIO ***/
typedef struct
{

	/*** BitField Mapping ***/
	STM32FXXXGPIOX_TypeDef* instance;
	/*** Other ***/
	void (*clock)( uint8_t bool );

}STM32FXXX_GPIOA, STM32FXXX_GPIOB, STM32FXXX_GPIOC, \
 STM32FXXX_GPIOD, STM32FXXX_GPIOE, STM32FXXX_GPIOF, \
 STM32FXXX_GPIOG, STM32FXXX_GPIOH;
// INIC
STM32FXXX_GPIOA* gpioa_enable(void);
STM32FXXX_GPIOA* gpioa(void);

STM32FXXX_GPIOB* gpiob_enable(void);
STM32FXXX_GPIOB* gpiob(void);

STM32FXXX_GPIOC* gpioc_enable(void);
STM32FXXX_GPIOC* gpioc(void);

STM32FXXX_GPIOD* gpiod_enable(void);
STM32FXXX_GPIOD* gpiod(void);

STM32FXXX_GPIOE* gpioe_enable(void);
STM32FXXX_GPIOE* gpioe(void);

STM32FXXX_GPIOF* gpiof_enable(void);
STM32FXXX_GPIOF* gpiof(void);

STM32FXXX_GPIOG* gpiog_enable(void);
STM32FXXX_GPIOG* gpiog(void);

STM32FXXX_GPIOH* gpioh_enable(void);
STM32FXXX_GPIOH* gpioh(void);

/***** GPIO Procedure & Funtion Header ******/
void STM32FXXXGpioAclock( uint8_t bool );
void STM32FXXXGpioAafr( uint8_t pin, uint8_t data );
void STM32FXXXGpioBclock( uint8_t bool );
void STM32FXXXGpioBafr( uint8_t pin, uint8_t data );
void STM32FXXXGpioCclock( uint8_t bool );
void STM32FXXXGpioCafr( uint8_t pin, uint8_t data );
void STM32FXXXGpioDclock( uint8_t bool );
void STM32FXXXGpioDafr( uint8_t pin, uint8_t data );
void STM32FXXXGpioEclock( uint8_t bool );
void STM32FXXXGpioEafr( uint8_t pin, uint8_t data );
void STM32FXXXGpioFclock( uint8_t bool );
void STM32FXXXGpioFafr( uint8_t pin, uint8_t data );
void STM32FXXXGpioGclock( uint8_t bool );
void STM32FXXXGpioGafr( uint8_t pin, uint8_t data );
void STM32FXXXGpioHclock( uint8_t bool );
void STM32FXXXGpioHafr( uint8_t pin, uint8_t data );

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

