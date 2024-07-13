/******************************************************************************
	STM32 XXX ADC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc.h"

/*** ADC Common Header ***/
static STM32FXXXADC_COMMON stm32fxxx_adc_common;

/*** COMMON ***/
// CDR
uint32_t STM32FXXXADC_cdr(void)
{
	return readreg(ADC->CDR, 32, 0);
}
/*** Auxiliary ***/
STM32FXXXADC_COMMON* stm32fxxx_adc_common_inic(void)
{

	// CSR
	stm32fxxx_adc_common.csr = (STM32FXXXADC_CSR_TypeDef*) &ADC->CSR;
	// CCR
	stm32fxxx_adc_common.ccr = (STM32FXXXADC_CCR_TypeDef*) &ADC->CCR;
	// CDR
	stm32fxxx_adc_common.cdr = STM32FXXXADC_cdr;
	return &stm32fxxx_adc_common;
}

/*** EOF ***/

