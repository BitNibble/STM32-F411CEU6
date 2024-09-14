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

int main(void)
{
	uint8_t tmp;
	uint16_t adc1_dr;
	uint32_t time_out;
	uint32_t count_0 = 0;
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

	while (1)
	{
		/*** preamble ***/
		PA.update(&PA.par, gpioa()->instance->idr.word.i);
		/******/
		adc1_dr = stm()->adc1->instance->dr.reg;
		stm()->adc1->instance->cr2.par.swstart = on;
		for(time_out = 2000000, tmp = 1; tmp && time_out; tmp = stm()->adc1->instance->cr2.par.swstart, time_out-- );

		lcd0()->gotoxy(0,0);
		lcd0()->string_size("Hello!",10);
		lcd0()->gotoxy(1,0);
		lcd0()->string_size(func()->ui16toa(adc1_dr),10);
		lcd0()->gotoxy(2,0);
		lcd0()->string_size(func()->ui32toa(count_0++),10);
	}
}

void ADC_setup(void){
	/********** ADC1 **********/
	stm()->adc1->iclock(on);
	stm()->adc1->clock(on);
	stm()->adc1->common_instance->ccr.par.adcpre = 3;
	stm()->adc1->instance->smpr1.par.smp18 = 7;
	stm()->adc1->instance->sqr1.par.l = 0;
	stm()->adc1->instance->sqr3.par.sq1 = 18;
	stm()->adc1->common_instance->ccr.par.tsvrefe = on;
	//stm()->adc1->common_instance->ccr.par.vbate = on;
	stm()->adc1->instance->cr2.par.eocs = on;
	stm()->adc1->instance->cr2.par.dds = on;
	stm()->adc1->instance->cr2.par.adon = on;
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

