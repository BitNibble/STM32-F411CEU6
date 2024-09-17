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
#ifdef STM32F446xx
// ADC3
static STM32FXXX_ADC3 stm32fxxx_adc3;
static STM32FXXXADC3single stm32fxxx_adc3_single;
/*** File Procedure & Function Header ***/
STM32FXXXADC3single* stm32fxxx_adc3_single_inic(void);
/*** ADC3 ***/
void STM32FXXXAdc3IClock(uint8_t bool)
{
	if(bool){ rcc_instance()->apb1enr.par.dacen = 1; }else{ rcc_instance()->apb1enr.par.dacen = 0; }
}
void STM32FXXXAdc3Clock(uint8_t bool)
{
	if(bool){ rcc_instance()->apb2enr.par.adc3en = 1; }else{ rcc_instance()->apb2enr.par.adc3en = 0; }
}
void STM32FXXXAdc3Nvic(uint8_t bool)
{
	if(bool){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
void STM32FXXXAdc3Inic(void)
{
	STM32FXXX_ADC3* adc3 = adc3_enable();
	// ADC Clock
	// void STM32FXXXAdc3IClock(1); // DACEN: DAC interface clock enable
	// STM32FXXXAdc3Clock(1) // ADC3EN: ADC3 clock enable
	// ADC CONFIG
	adc3->instance->cr2.par.eocs = 1; // EOCS: End of conversion selection
	adc3->common_instance->ccr.par.adcpre = 3; // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	adc3->instance->smpr1.par.smp15 = 7; // SMPx[2:0]: Channel x sampling time selection
	adc3->instance->cr1.par.discen = 1; // DISCEN: Discontinuous mode on regular channels
	adc3->instance->sqr3.par.sq1 = 15; // SQ1[4:0]: 1st conversion in regular sequence
}
void STM32FXXXAdc3Start()
{
	STM32FXXX_ADC3* adc3 = adc3_enable();
	// turn on select source and start reading
	adc3->instance->cr2.par.adon = 1; // ADON: A/D Converter ON / OFF
	//
	adc3->instance->cr2.par.swstart = 1; // SWSTART: Start conversion of regular channels
}
STM32FXXXADC3single* stm32fxxx_adc3_single_inic(void)
{

	stm32fxxx_adc3_single.inic = STM32FXXXAdc3Inic;
	stm32fxxx_adc3_single.start = STM32FXXXAdc3Start;
	return &stm32fxxx_adc3_single;
}
/*** ADC3 INIC Procedure & Function Definition ***/
STM32FXXX_ADC3* adc3_enable(void)
{

	/*** ADC3 Bit Mapping Link ***/
	stm32fxxx_adc3.instance = adc3_instance();
	stm32fxxx_adc3.common_instance = adc_common_instance();
	// Other
	stm32fxxx_adc3.single = stm32fxxx_adc3_single_inic();
	stm32fxxx_adc3.iclock = STM32FXXXAdc3IClock;
	stm32fxxx_adc3.clock = STM32FXXXAdc3Clock;
	stm32fxxx_adc3.nvic = STM32FXXXAdc3Nvic;
	return &stm32fxxx_adc3;
}

STM32FXXX_ADC3* adc3(void){ return (STM32FXXX_ADC3*) &stm32fxxx_adc3; }

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

