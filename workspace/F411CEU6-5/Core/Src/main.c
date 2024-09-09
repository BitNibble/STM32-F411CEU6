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

	while (1)
	{
		/*** preamble ***/
		PA.update(&PA.par, gpioa()->instance->idr.word.i);
		/******/
		lcd0()->gotoxy(0,0);
		lcd0()->string_size("Hello!",10);




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

