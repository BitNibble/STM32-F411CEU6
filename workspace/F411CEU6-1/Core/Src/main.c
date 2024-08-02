/********************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * Author: Sergio Santos
  * <sergio.salazar.santos@gmail.com>
  * License: GNU General Public License
  * Hardware: STM32F4x1 mini_F4x1 Ver. V20 SN: 202005 DevEBox
  * Board Site: mcudev.taobao.com
  * Date: 22022024
  * Comment:
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
********************************************************************************/
/****** Comment
LCD
	PB3 - RS
	PB4 - RW
	PB5 - E
	PB6 - D4
	PB7 - D5
	PB8 - D6
	PB9 - D7
LED Blinking
	PB13 - LED blink
note:
setup stm32f411ceu6 to work with adapted stm32f446re private libraries.
********************************************************************************/
#include "main.h"
#include "stm32fxxxmapping.h"
#include "armlcd.h"
#include "armfunction.h"


int main(void)
{
  STM32FXXX_enable();

  gpiob()->clock(on);

  ARMLCD0_enable((GPIO_TypeDef*)stm()->gpiob->instance);
  FUNC_enable();

  gpiob()->instance->moder.par.pin_13 = 1;

  while (1)
  {
	  lcd0()->gotoxy(0,0);
	  lcd0()->string_size("Welcome",7);
	  lcd0()->gotoxy(1,0);
	  lcd0()->string_size(func()->ftoa((double)33/654,10),20);

	  _delay_ms(1000);
	  set_reg_block(&GPIOB->ODR,1,13,1);
	  _delay_ms(1000);
	  set_reg_block(&GPIOB->ODR,1,13,0);
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
