/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  *
  ******************************************************************************
  */
#include "main.h"
#include "stm32fxxxmapping.h"
#include "armlcd.h"
#include "armfunction.h"

int main(void)
{
  STM32FXXX_enable();
  //rtc()->inic(1); // 1 - LSE 0 - LSI
  //gpiob()->clock(on); // lcd0
  gpioc()->clock(on); // gpio13
  ARMLCD0_enable((GPIO_TypeDef*)gpiob()->instance);
  FUNC_enable();
  //HAL_Init();


  while (1)
  {
	  lcd0()->gotoxy(0,0);
	  lcd0()->string_size("Welcome",7);
	  _delay_ms(1000);
	  lcd0()->gotoxy(0,0);
	  lcd0()->string_size("Sergio",7);
	  _delay_ms(2000);

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


