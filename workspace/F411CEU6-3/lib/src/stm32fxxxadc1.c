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

#define ADC_STAB_DELAY 15 // 15
#define END_OF_CONVERSION_TIME_OUT 100
#ifndef ZERO
	#define ZERO 0
#endif
#ifndef ONE
	#define ONE 1
#endif
/*** File Variables ***/
// ADC1
static STM32FXXX_ADC1 stm32fxxx_adc1 = {0};
/*** File Procedure & Function Header ***/
/*** ADC1 ***/
void ADC1_Clock(uint8_t state)
{
	if(state){ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, RCC_APB2ENR_ADC1EN_Pos, ON); }
	else{ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, RCC_APB2ENR_ADC1EN_Pos, OFF); }

}
void ADC1_Nvic(uint8_t state) {
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
void ADC1_StartConversion(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_SWSTART, ADC_CR2_SWSTART_Pos, ON);
}
void ADC1_WaitEndOfConversion(void) {
	for (uint32_t time_out = END_OF_CONVERSION_TIME_OUT; !get_reg_Msk(ADC1->SR, ADC_SR_EOC, ADC_SR_EOC_Pos) && time_out; time_out-- );
}
void ADC1_Start(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, ON);
	for(uint8_t countdown = ADC_STAB_DELAY; countdown; countdown--); // Stabilization delay
}
void ADC1_Stop(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, OFF);
}
void ADC1_TemperatureSetup(void) {
    // Enable ADC1 clock
    ADC1_Clock(ON);

    // Configure ADC1 parameters
    ADC1->CR1 = 0; // Clear control register
    set_reg_Msk(&ADC1->SQR1, ADC_SQR1_L, ADC_SQR1_L_Pos, 0);
    set_reg_Msk(&ADC1->SQR3, ADC_SQR3_SQ1, ADC_SQR3_SQ1_Pos, 18);
    set_reg_Msk(&ADC1->SMPR1, ADC_SMPR1_SMP18, ADC_SMPR1_SMP18_Pos, 3);

    // Enable temperature sensor
    set_reg_Msk(&ADC->CCR, ADC_CCR_TSVREFE, ADC_CCR_TSVREFE_Pos, ON);
    ADC1_Start();
}
uint16_t ADC1_ReadTemperature(void) {
	uint16_t adc_value;
	ADC1_StartConversion();
	ADC1_WaitEndOfConversion();
    adc_value = ADC1->DR;
    return adc_value;
}

/*** ADC1 INIC Procedure & Function Definition ***/
void adc1_enable(void)
{
	/*** ADC1 Clock ***/
	ADC1_Clock(ON);
	/*** ADC1 TypeDef ***/
	stm32fxxx_adc1.instance = ADC1;
	stm32fxxx_adc1.common_instance = ADC1_COMMON;
	/*** Clock and Nvic ***/
	stm32fxxx_adc1.clock = ADC1_Clock;
	stm32fxxx_adc1.nvic = ADC1_Nvic;
	/*** Procedures ***/
	stm32fxxx_adc1.startconversion = ADC1_StartConversion;
	stm32fxxx_adc1.waitendofconversion = ADC1_WaitEndOfConversion;
	/*** Other ***/
	stm32fxxx_adc1.start = ADC1_Start;
	stm32fxxx_adc1.stop = ADC1_Stop;
	stm32fxxx_adc1.temperaturesetup = ADC1_TemperatureSetup;
	stm32fxxx_adc1.readtemperature = ADC1_ReadTemperature;

	//return &stm32fxxx_adc1;
}

STM32FXXX_ADC1* adc1(void){ return (STM32FXXX_ADC1*) &stm32fxxx_adc1; }

/****** MISCELLANEOUS ******/

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

