/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  *
  * A simple Clock
  *
  *   LCD:
  * PB3 - RS
  * PB4 - RW
  * PB5 - E
  * PB6 - D4
  * PB7 - D5
  * PB8 - D6
  * PB9 - D7
  *
  ******************************************************************************
  **/
#include "main.h"
#include "stm32fxxxmapping.h"
#include "armlcd.h"
#include "armfunction.h"
#include "explode.h"

#define JMP_menu 100

EXPLODE PA;

char message[32];

int main(void)
{
	STM32FXXX_enable();
	//rtc()->inic(1); // 1 - LSE 0 - LSI (only has to be activated once)
	PA = EXPLODE_enable();

	uint8_t Menu = 6;
	uint8_t count_0 = 0;
	uint8_t count_1 = ~0;
	uint16_t incr_0 = 0;
	uint8_t skip_0 = 0;
	uint16_t adc_value = 0;

	gpiob()->clock(on); // lcd0
	ARMLCD0_enable((GPIO_TypeDef*)gpiob()->instance);
	gpioc()->clock(on); // gpioc13
	gpioc()->instance->moder.par.pin_13 = 1;
	gpioa()->clock(on); // inputs gpioa0
	gpioa()->instance->moder.par.pin_0 = 0;
	gpioa()->instance->pupdr.par.pin_0 = 1;

	FUNC_enable();
	//HAL_Init();
	ADC_TemperatureSetup();

	char vecD[8]; // for calendar date
	char vecT[8]; // for calendar time
	PA.update(&PA.par, gpioa()->instance->idr.word.i);

	while (on)
	{
		/*** preamble ***/
		PA.update(&PA.par, gpioa()->instance->idr.word.i);
		/******/

		switch(Menu){
		case 0:
			lcd0()->gotoxy(0,0);
			lcd0()->string_size("Set Hour",10);
			gpioc()->instance->odr.par.pin_13 = 0;

			if(PA.par.LH & 1){
				if(skip_0 > 0){
					incr_0 = rtc()->get_Hour();
					if(incr_0 > 22){ incr_0 = 0;}else{incr_0++;}
					rtc()->Hour(incr_0);
				}
				skip_0++;
			}

			if(PA.par.LL & 1){ // Jump menu
				_delay_ms(JMP_menu);
				count_0++;
				if(count_0 > 5){ Menu = 1; count_0 = 0; skip_0 = 0;}
			}else{count_0 = 0;}

			break;
		case 1:
			lcd0()->gotoxy(0,0);
			lcd0()->string_size("Set Minute",10);
			gpioc()->instance->odr.par.pin_13 = 1;

			if(PA.par.LH & 1){
				if(skip_0 > 0){
					incr_0 = rtc()->get_Minute();
					if(incr_0 > 58){ incr_0 = 0;}else{incr_0++;}
					rtc()->Minute(incr_0);
				}
				skip_0++;
			}

			if(PA.par.LL & 1){ // Jump menu
				_delay_ms(JMP_menu);
				count_0++;
				if(count_0 > 5){ Menu = 2; count_0 = 0; skip_0 = 0;}
			}else{count_0 = 0;}

			break;
		case 2:
			lcd0()->gotoxy(0,0);
			lcd0()->string_size("Set Second",10);
			gpioc()->instance->odr.par.pin_13 = 0;

			if(PA.par.LH & 1){
				if(skip_0 > 0){
					incr_0 = rtc()->get_Second();
					if(incr_0 > 58){ incr_0 = 0;}else{incr_0++;}
					rtc()->Second(incr_0);
				}
				skip_0++;
			}

			if(PA.par.LL & 1){ // Jump menu
				_delay_ms(JMP_menu);
				count_0++;
				if(count_0 > 5){ Menu = 3; count_0 = 0; skip_0 = 0;}
			}else{count_0 = 0;}

			break;
		case 3:
					lcd0()->gotoxy(0,0);
					lcd0()->string_size("Set Year",10);
					gpioc()->instance->odr.par.pin_13 = 0;

					if(PA.par.LH & 1){
						if(skip_0 > 0){
							incr_0 = rtc()->get_Year();
							if(incr_0 > 98){ incr_0 = 0;}else{incr_0++;}
							rtc()->Year(incr_0);
						}
						skip_0++;
					}

					if(PA.par.LL & 1){ // Jump menu
						_delay_ms(JMP_menu);
						count_0++;
						if(count_0 > 5){ Menu = 4; count_0 = 0; skip_0 = 0;}
					}else{count_0 = 0;}

					break;
		case 4:
					lcd0()->gotoxy(0,0);
					lcd0()->string_size("Set Month",10);
					gpioc()->instance->odr.par.pin_13 = 1;

					if(PA.par.LH & 1){
						if(skip_0 > 0){
							incr_0 = rtc()->get_Month();
							if(incr_0 > 11){ incr_0 = 0;}else{incr_0++;}
							rtc()->Month(incr_0);
						}
						skip_0++;
					}

					if(PA.par.LL & 1){ // Jump menu
						_delay_ms(JMP_menu);
						count_0++;
						if(count_0 > 5){ Menu = 5; count_0 = 0; skip_0 = 0;}
					}else{count_0 = 0;}

					break;
		case 5:
					lcd0()->gotoxy(0,0);
					lcd0()->string_size("Set Day",10);
					gpioc()->instance->odr.par.pin_13 = 0;

					if(PA.par.LH & 1){
						if(skip_0 > 0){
							incr_0 = rtc()->get_Day();
							if(incr_0 > 30){ incr_0 = 0;}else{incr_0++;}
							rtc()->Day(incr_0);
						}
						skip_0++;
					}

					if(PA.par.LL & 1){ // Jump menu
						_delay_ms(JMP_menu);
						count_0++;
						if(count_0 > 5){ Menu = 6; count_0 = 0; skip_0 = 0;}
					}else{count_0 = 0;}

					break;
		case 6:
			lcd0()->gotoxy(0,0);
			lcd0()->string_size("Clock",12);
			count_1--;
			if(!count_1){
				adc_value = ADC_ReadTemperature();
				lcd0()->string_size( func()->print_v1(message, 10, "%d %cC", (int32_t)CalculateTemperature(adc_value), (char) 0xDF ), 8);
			}
			gpioc()->instance->odr.par.pin_13 = 1;

			if(PA.par.LH & 1){
				if(skip_0 < 1){
				}
				skip_0++;
			}

			if(PA.par.LL & 1){ // Jump menu
				_delay_ms(JMP_menu);
				count_0++;
				if(count_0 > 5){ Menu = 0; count_0 = 0; skip_0 = 0;}
			}else{count_0 = 0;}

			break;
		default:
			break;
		}

		lcd0()->gotoxy(2,0);
		rtc()->dr2vec(vecD);
		lcd0()->string_size(func()->print_v2("data: %d%d-%d%d-20%d%d", vecD[5],vecD[6],vecD[3],vecD[4],vecD[0],vecD[1]),16);

		lcd0()->gotoxy(3,0);
		rtc()->tr2vec(vecT);
		lcd0()->string_size(func()->print_v2("hora: %d%d:%d%d:%d%d", vecT[0],vecT[1],vecT[2],vecT[3],vecT[4],vecT[5]),14);

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


