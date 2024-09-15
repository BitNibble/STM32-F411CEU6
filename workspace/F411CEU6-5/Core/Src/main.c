/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  *
  *		LCD:
  * PB3 - RS
  * PB4 - RW
  * PB5 - E
  * PB6 - D4
  * PB7 - D5
  * PB8 - D6
  * PB9 - D7
  ******************************************************************************
  */
#include "main.h"
#include "stm32fxxxmapping.h"
#include "armlcd.h"
#include "armfunction.h"
#include "explode.h"

EXPLODE PA;

void ADC_setup(void);
void ADC_Init(void);
uint16_t ADC_ReadTemperature(void);
float CalculateTemperature(uint16_t adc_value);

int main(void)
{
	//uint16_t adc1_dr;
	//uint32_t count_0 = 0;
	//uint32_t count_1 = 0;
	STM32FXXX_enable();
	//rtc()->inic(1); // 1 - LSE 0 - LSI (only has to be activated once)
	PA = EXPLODE_enable();

	rtc()->bck_sram_clock(on);
	gpiob()->clock(on); // lcd0
	ARMLCD0_enable((GPIO_TypeDef*)gpiob()->instance);
	gpioc()->clock(on); // gpioc13
	gpioc()->instance->moder.par.pin_13 = 1;
	gpioa()->clock(on); // inputs gpioa0
	gpioa()->instance->moder.par.pin_0 = 0;
	gpioa()->instance->pupdr.par.pin_0 = 1;

	FUNC_enable();
	//HAL_Init();

	PA.update(&PA.par, gpioa()->instance->idr.word.i);

	ADC_setup();
	float temperature = 0;
	uint16_t adc_value = 0;

	while (1)
	{
		/*** preamble ***/
		PA.update(&PA.par, gpioa()->instance->idr.word.i);
		/******/
		lcd0()->gotoxy(0,0);
		lcd0()->string_size("Hello!",10);
		lcd0()->gotoxy(1,0);
		//lcd0()->string_size(func()->ui16toa(adc_value),16);
		lcd0()->string_size(func()->ftoa(temperature,2),16);
		lcd0()->gotoxy(3,0);
		lcd0()->string_size(func()->ui32toa(get_reg_block(ADC1->CR2,1,0)),4);
		lcd0()->gotoxy(3,4);
		lcd0()->string_size(func()->ui32toa(get_reg_block(ADC1->SR,1,5)),4);
		lcd0()->gotoxy(3,8);
		lcd0()->string_size(func()->ui32toa(get_reg_block(ADC1->SR,1,4)),4);
		lcd0()->gotoxy(3,12);
		lcd0()->string_size(func()->ui32toa(get_reg_block(ADC1->SR,1,1)),4);
		_delay_ms(1000);
		// Read temperature sensor value
		adc_value = ADC_ReadTemperature();
		// Convert to actual temperature
		temperature = CalculateTemperature(adc_value);


	}
}

void ADC_setup(void){
	uint8_t countdown;
	/********** ADC1 **********/
	stm()->adc1->clock(on);
	stm()->adc1->instance->cr1.reg = 0;
	stm()->adc1->instance->sqr1.par.l = 0;
	stm()->adc1->instance->sqr3.par.sq1 = 18;
	stm()->adc1->instance->smpr1.par.smp18 = 3;
	//stm()->adc1->instance->cr2.par.eocs = on;
	//stm()->adc1->instance->cr1.par.discen = on;
	stm()->adc1->instance->cr2.par.cont = on;
	//stm()->adc1->instance->cr1.par.scan = on;
	//stm()->adc1->common_instance->ccr.par.vbate = on;
	stm()->adc1->common_instance->ccr.par.tsvrefe = on;
	stm()->adc1->instance->cr2.par.adon = on;
	for(countdown = 15; countdown; countdown --); // t_STAB
}


uint16_t ADC_ReadTemperature(void) {
	uint16_t adc_value;
    // 1. Start ADC conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;

    // 2. Wait until conversion is complete
    while (!(ADC1->SR & ADC_SR_EOC));

    // 3. Read ADC conversion result
    adc_value = ADC1->DR;

    return adc_value;
}

float CalculateTemperature(uint16_t adc_value) {
    // STM32 temperature sensor formula:
    // Temperature (in °C) = ((V_sense - V_25) / Avg_slope) + 25
    // V_sense = ADC_Value * V_ref / 4096
    // V_25 (at 25°C) = 1.43V for STM32F4
    // Avg_slope = 4.3mV/°C (varies by MCU, check datasheet)

    const float V_25 = 0.76f;  // Voltage at 25°C (in volts)
    const float Avg_slope = 0.0025f;  // Average slope (in volts/°C)
    const float V_ref = 3.3f;  // Reference voltage, typically 3.0V or 3.3V


    // Convert ADC value to voltage
    float V_sense = ((float)adc_value / 4096) * V_ref;

    // Calculate temperature
    float temperature = ((V_sense - V_25) / Avg_slope) + 25.0f;

    return temperature;
}

void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}
}

#ifdef  USE_FULL_ASSERT
	void assert_failed(uint8_t *file, uint32_t line)
	{
	}
#endif

