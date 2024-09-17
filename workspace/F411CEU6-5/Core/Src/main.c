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

int main(void)
{
	//uint16_t adc1_dr;
	//uint32_t count_0 = 0;
	//uint32_t count_1 = 0;
	STM32FXXX_enable();
	//rtc()->inic(1); // 1 - LSE 0 - LSI (only has to be activated once)
	PA = EXPLODE_enable();

	gpiob()->clock(on); // lcd0
	ARMLCD0_enable((GPIO_TypeDef*)gpiob()->instance);
	gpioc()->clock(on); // gpioc13
	gpioc()->instance->MODER.par.MODER13 = 1;
	gpioa()->clock(on); // inputs gpioa0
	gpioa()->instance->MODER.par.MODER0 = 0;
	gpioa()->instance->PUPDR.par.PUPDR0 = 1;

	FUNC_enable();
	//HAL_Init();

	gpioc()->instance->BSRR.par.BS13 = 1;
	PA.update(&PA.par, gpioa()->instance->IDR.reg);

	ADC_TemperatureSetup();
	float temperature = 0;
	uint16_t adc_value = 0;

	while (1)
	{
		/*** preamble ***/
		PA.update(&PA.par, gpioa()->instance->IDR.reg);
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

