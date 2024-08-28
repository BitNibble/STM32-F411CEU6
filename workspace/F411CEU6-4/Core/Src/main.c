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
#include "explode.h"

EXPLODE PA;

int main(void)
{
  STM32FXXX_enable();
  PA = EXPLODE_enable();

  uint8_t Menu = 0;
  uint8_t count_0 = 0;
  uint16_t incr_0 = 0;

  //rtc()->inic(1); // 1 - LSE 0 - LSI
  gpiob()->clock(on); // lcd0
  ARMLCD0_enable((GPIO_TypeDef*)gpiob()->instance);
  gpioc()->clock(on); // gpioc13
  gpioc()->instance->moder.par.pin_13 = 1;
  gpioa()->clock(on); // inputs
  gpioa()->instance->moder.par.pin_0 = 0;
  gpioa()->instance->pupdr.par.pin_0 = 1;


  FUNC_enable();
  //HAL_Init();


  while (1)
  {
	  /*** preamble ***/
	  PA.update(&PA.par, gpioa()->instance->idr.word.i);
	  /******/

	  switch(Menu){
	  case 0:
		  lcd0()->gotoxy(0,0);
		  lcd0()->string_size("Menu 0",7);
		  gpioc()->instance->odr.par.pin_13 = 0;

		  if(PA.par.LH & 1){
			  incr_0++;
		  }
		  if(PA.par.LL & 1){ // Jump menu
			  _delay_ms(500);
			  count_0++;
			  if(count_0 > 5){ Menu = 1; count_0 = 0;}
		  }else{count_0 = 0;}


		  lcd0()->gotoxy(1,0);
		  lcd0()->string_size(func()->ui32toa(incr_0),20);
		  break;
	  case 1:
		  lcd0()->gotoxy(0,0);
		  lcd0()->string_size("Menu 1",7);
		  gpioc()->instance->odr.par.pin_13 = 1;






		  if(PA.par.LL & 1){ // Jump menu
		  	_delay_ms(500);
		  	count_0++;
		  	if(count_0 > 5){ Menu = 0; count_0 = 0;}
		  }else{count_0 = 0;}
		  break;
	  default:
		  break;
	  }





  } /*** While ***/
} /*** Main ***/


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


