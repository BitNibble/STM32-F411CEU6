/******************************************************************************
	STM32 XXX ADC3
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc3.h"

/*** File Variables ***/
// ADC3
static STM32FXXX_ADC3 stm32fxxx_adc3;
/*** File Procedure & Function Header ***/
/*** ADC3 ***/
#ifdef STM32F446xx
void STM32FXXXAdc3Clock(uint8_t bool)
{
	if(bool){ rcc_instance()->apb2enr.par.adc3en = 1; }else{ rcc_instance()->apb2enr.par.adc3en = 0; }
}
void STM32FXXXAdc3Nvic(uint8_t bool)
{
	if(bool){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
#endif
/*** ADC3 INIC Procedure & Function Definition ***/
STM32FXXX_ADC3* adc3_enable(void)
{
	/*** ADC3 Bit Mapping Link ***/
	#ifdef STM32F446xx
		stm32fxxx_adc3.instance = ADC3;
		stm32fxxx_adc3.common_instance = ADC123_COMMON;
	#else
		stm32fxxx_adc3.instance = NULL;
		stm32fxxx_adc3.common_instance = NULL;
	#endif
	// Other
	stm32fxxx_adc3.clock = STM32FXXXAdc3Clock;
	stm32fxxx_adc3.nvic = STM32FXXXAdc3Nvic;
	return &stm32fxxx_adc3;
}

STM32FXXX_ADC3* adc3(void){ return (STM32FXXX_ADC3*) &stm32fxxx_adc3; }

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

/*** EOF ***/
