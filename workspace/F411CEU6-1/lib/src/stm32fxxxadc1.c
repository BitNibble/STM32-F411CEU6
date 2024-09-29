/******************************************************************************
	STM32 XXX ADC1
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc1.h"

/*** File Variables ***/
// ADC1
static STM32FXXX_ADC1 stm32fxxx_adc1;
/*** File Procedure & Function Header ***/
/*** ADC1 ***/
void STM32FXXXAdc1Clock(uint8_t state)
{
	if(state){ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, RCC_APB2ENR_ADC1EN_Pos, 1); }
	else{ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, RCC_APB2ENR_ADC1EN_Pos, 0); }

}
void STM32FXXXAdc1Nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
/*** ADC1 INIC Procedure & Function Definition ***/
STM32FXXX_ADC1* adc1_enable(void)
{

	/*** ADC1 Bit Mapping Link ***/
	stm32fxxx_adc1.instance = adc1_instance();
	stm32fxxx_adc1.common_instance = adc_common_instance();
	/*** Other ***/
	stm32fxxx_adc1.clock = STM32FXXXAdc1Clock;
	stm32fxxx_adc1.nvic = STM32FXXXAdc1Nvic;
	return &stm32fxxx_adc1;
}

STM32FXXX_ADC1* adc1(void){ return (STM32FXXX_ADC1*) &stm32fxxx_adc1; }

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

