/******************************************************************************
	STM32 XXX ADC2
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc2.h"

/*** File Variables ***/
#ifdef __STM32F446xx_H
// ADC2
static STM32FXXX_ADC2 stm32fxxx_adc2;
static STM32FXXXADC2single stm32fxxx_adc2_single;
/*** File Procedure & Function Header ***/
STM32FXXXADC2single* stm32fxxx_adc2_single_inic(void);
/*** ADC2 ***/
void STM32FXXXAdc2IClock(uint8_t bool)
{
	if(bool){ RCC->APB1ENR |= (1 << 29); }else{ RCC->APB1ENR &= ~(1 << 29); }
}
void STM32FXXXAdc2Clock(uint8_t bool)
{
	if(bool){ RCC->APB2ENR |= (1 << 9); }else{ RCC->APB2ENR &= ~(1 << 9); }
}
void STM32FXXXAdc2Nvic(uint8_t bool)
{
	if(bool){ setbit(NVIC->ISER, 1, ADC_IRQn, 1); } else{ setbit(NVIC->ICER, 1, ADC_IRQn, 1); }
}
void STM32FXXXAdc2Inic(void)
{
	STM32FXXX_ADC2* adc2_config = adc2_enable();
	// ADC Clock
	// void STM32FXXXAdc2IClock(1); // DACEN: DAC interface clock enable
	// STM32FXXXAdc2Clock(1) // ADC2EN: ADC2 clock enable
	// ADC CONFIG
	STM32FXXXADC2_cr2_eocs(1); // EOCS: End of conversion selection
	adc2_config->common->ccr->par.adcpre = 3; // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	STM32FXXXADC2_smpr1_smp10(7); // SMPx[2:0]: Channel x sampling time selection
	STM32FXXXADC2_cr1_discen(1); // DISCEN: Discontinuous mode on regular channels
	STM32FXXXADC2_sqr3_sq1(10); // SQ1[4:0]: 1st conversion in regular sequence
}
void STM32FXXXAdc2Start()
{
	// turn on select source and start reading
	STM32FXXXADC2_cr2_adon(1); // ADON: A/D Converter ON / OFF
	//
	STM32FXXXADC2_cr2_swstart(1); // SWSTART: Start conversion of regular channels
}
STM32FXXXADC2single* stm32fxxx_adc2_single_inic(void)
{

	stm32fxxx_adc2_single.inic = STM32FXXXAdc2Inic;
	stm32fxxx_adc2_single.start = STM32FXXXAdc2Start;
	return &stm32fxxx_adc2_single;
}
/*** ADC2 INIC Procedure & Function Definition ***/
STM32FXXX_ADC2* adc2_enable(void)
{

	/*** ADC2 Bit Mapping Link ***/
	stm32fxxx_adc2.instance = adc2_instance();
	stm32fxxx_adc2.common_instance = adc_common_instance();
	// Other
	stm32fxxx_adc2.single = stm32fxxx_adc2_single_inic();
	stm32fxxx_adc2.iclock = STM32FXXXAdc2IClock;
	stm32fxxx_adc2.clock = STM32FXXXAdc2Clock;
	stm32fxxx_adc2.nvic = STM32FXXXAdc2Nvic;
	return &stm32fxxx_adc2;
}

STM32FXXX_ADC2* adc2(void){ return (STM32FXXX_ADC2*) &stm32fxxx_adc2; }

#endif

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

