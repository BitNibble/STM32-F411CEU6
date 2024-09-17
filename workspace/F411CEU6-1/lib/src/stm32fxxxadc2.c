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
#ifdef STM32F446xx
// ADC2
static STM32FXXX_ADC2 stm32fxxx_adc2;
static STM32FXXXADC2single stm32fxxx_adc2_single;
/*** File Procedure & Function Header ***/
STM32FXXXADC2single* stm32fxxx_adc2_single_inic(void);
/*** ADC2 ***/
void STM32FXXXAdc2IClock(uint8_t bool)
{
	if(bool){ rcc_instance()->apb1enr.par.dacen = 1; }else{ rcc_instance()->apb1enr.par.dacen = 0; }
}
void STM32FXXXAdc2Clock(uint8_t bool)
{
	if(bool){ rcc_instance()->apb2enr.par.adc2en = 1; }else{ rcc_instance()->apb2enr.par.adc2en = 0; }
}
void STM32FXXXAdc2Nvic(uint8_t bool)
{
	if(bool){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
void STM32FXXXAdc2Inic(void)
{
	STM32FXXX_ADC2* adc2 = adc2_enable();
	// ADC Clock
	// void STM32FXXXAdc2IClock(1); // DACEN: DAC interface clock enable
	// STM32FXXXAdc2Clock(1) // ADC2EN: ADC2 clock enable
	// ADC CONFIG
	adc2->instance->cr2.par.eocs = 1; // EOCS: End of conversion selection
	adc2->common_instance->ccr.par.adcpre = 3; // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	adc2->instance->smpr1.par.smp15 = 7; // SMPx[2:0]: Channel x sampling time selection
	adc2->instance->cr1.par.discen = 1; // DISCEN: Discontinuous mode on regular channels
	adc2->instance->sqr3.par.sq1 = 10; // SQ1[4:0]: 1st conversion in regular sequence
}
void STM32FXXXAdc2Start()
{
	STM32FXXX_ADC2* adc2 = adc2_enable();
	// turn on select source and start reading
	adc2->instance->cr2.par.adon = 1; // ADON: A/D Converter ON / OFF
	//
	adc2->instance->cr2.par.swstart = 1; // SWSTART: Start conversion of regular channels


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

