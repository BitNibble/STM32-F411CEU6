/****************************************************************
Title: A simple Clock
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
File: main.c 22/09/2024
Software: STM32CubeIDE v1.16.0 Build: 21983_20240628_1741 (UTC)
Hardware: STM32F411CEU6 by DevBox
	Comment:
	Button K0:
GPIO PA0 - Button
	LED D2:
GPIO PC13 - D2
	LCD 4x20:
GPIO PB3 - RS
GPIO PB4 - RW
GPIO PB5 - EN
GPIO PB6 - D4
GPIO PB7 - D5
GPIO PB8 - D6
GPIO PB9 - D7
****************************************************************/
#include "main.h"
/******/
#include "stm32fxxxrcc.h"
#include "armsystick.h"
#include "stm32fxxxgpio.h"
#include "stm32fxxxrtc.h"
#include "stm32fxxxadc1.h"
#include "stm32fxxxusart1.h"
/******/
#include "BT_Commands.h"
#include "armlcd.h"
#include "armfunction.h"
#include "explode.h"
#include <stdio.h>
#include <string.h>

#define JMP_menu 120
#define JMP_menu_repeat 5
#define ADC_DELAY 20
#define ADC_SAMPLE 8
#define BUFF_SIZE 21

EXPLODE PA;
char ADC_msg[32];
char str[32];

char oneshot[BUFF_SIZE];
char received[BUFF_SIZE];
void setup_usart1(void);

int main(void)
{
	rcc_start();
	systick_start();
	fpu_enable();

    HAL_Init();

    rtc_enable();
    adc1_enable();
    gpioa_enable(); // button k0 gpioa0
    gpiob_enable(); // lcd0
    gpioc_enable(); // gpioc13

    setup_usart1();

    rtc()->inic(1);
    PA = EXPLODE_enable();

    _UN8var Menu;
    Menu.un8.b = 7;
    _UN16var adc_value;
    adc_value.un16.w = 0;
    uint8_t count_0 = 0;
    uint8_t count_1 = ADC_DELAY;
    uint8_t n_sample = ADC_SAMPLE;
    uint16_t incr_0 = 0;
    uint8_t skip_0 = 0;
    uint8_t AT_counter = 0;

    const char unit = (char)0xDF;

    ARMLCD0_enable(gpiob()->instance);

    gpioc()->moder(13,1);
    gpioa()->moder(0,0);
    gpioa()->pupd(0,1);

    FUNC_enable();
    adc1()->temperaturesetup();

    char vecD[8]; // for calendar date
    char vecT[8]; // for calendar time
    PA.update(&PA.par, gpioa()->instance->IDR);

    gpioc()->instance->BSRR = GPIO_BSRR_BS13;

    while (ONE)  // Infinite loop
    {
        PA.update(&PA.par, gpioa()->instance->IDR);

        lcd0()->gotoxy(1, 0);
        usart1()->receive_string(oneshot, received, BUFF_SIZE, "\r\n");
        lcd0()->string_size(received, 20);

        switch (Menu.nibble.n0) {
        case 0:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Hour", 12);

            if (PA.par.LH & 1) {
                if (skip_0 > 0) {
                    incr_0 = rtc()->get_Hour();
                    incr_0 = (incr_0 > 22) ? 0 : incr_0 + 1;
                    rtc()->Hour(incr_0);
                }
                skip_0++;
            }



            usart1()->transmit_string(BT_AT_Run(AT_counter));
            _delay_ms(2000);
            AT_counter++;
            if(AT_counter > 11){ AT_counter = 0; }


            if (PA.par.LL & 1) { // Jump menu
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu.un8.b = 1; count_0 = 0; skip_0 = 0;
                    usart1()->transmit_string(BT_AT_GetName());
                }
            } else {
                count_0 = 0;
            }
            break;

        case 1:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Minute", 12);

            if (PA.par.LH & 1) {
                if (skip_0 > 0) {
                    incr_0 = rtc()->get_Minute();
                    incr_0 = (incr_0 > 58) ? 0 : incr_0 + 1;
                    rtc()->Minute(incr_0);
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu.un8.b = 2; count_0 = 0; skip_0 = 0;
                    usart1()->transmit_string(BT_AT_GetVersion());
                }
            } else {
                count_0 = 0;
            }
            break;

        case 2:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Second", 12);

            if (PA.par.LH & 1) {
                if (skip_0 > 0) {
                    incr_0 = rtc()->get_Second();
                    incr_0 = (incr_0 > 58) ? 0 : incr_0 + 1;
                    rtc()->Second(incr_0);
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu.un8.b = 3; count_0 = 0; skip_0 = 0;
                    usart1()->transmit_string(BT_AT_GetPin());
                }
            } else {
                count_0 = 0;
            }
            break;

        case 3:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Year", 12);

            if (PA.par.LH & 1) {
                if (skip_0 > 0) {
                    incr_0 = rtc()->get_Year();
                    incr_0 = (incr_0 > 98) ? 0 : incr_0 + 1;
                    rtc()->Year(incr_0);
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu.un8.b = 4; count_0 = 0; skip_0 = 0;
                    usart1()->transmit_string(BT_AT_GetRole());
                }
            } else {
                count_0 = 0;
            }
            break;

        case 4:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Month", 12);

            if (PA.par.LH & 1) {
                if (skip_0 > 0) {
                    incr_0 = rtc()->get_Month();
                    incr_0 = (incr_0 > 11) ? 1 : incr_0 + 1;
                    rtc()->Month(incr_0);
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu.un8.b = 5; count_0 = 0; skip_0 = 0;
                    usart1()->transmit_string(BT_AT_Run(0));
                }
            } else {
                count_0 = 0;
            }
            break;

        case 5:
        	lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set WeekDay", 12);

            if (PA.par.LH & 1) {
            	if (skip_0 > 0) {
            		incr_0 = rtc()->get_WeekDay();
                    incr_0 = (incr_0 > 6) ? 1 : incr_0 + 1;
                    rtc()->WeekDay(incr_0);
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
            	_delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                	Menu.un8.b = 6; count_0 = 0; skip_0 = 0;
                    usart1()->transmit_string(BT_AT_Test());
                }
            } else {
            	count_0 = 0;
            }
            break;

        case 6:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Day", 12);

            if (PA.par.LH & 1) {
                if (skip_0 > 0) {
                    incr_0 = rtc()->get_Day();
                    incr_0 = (incr_0 > 30) ? 1 : incr_0 + 1;
                    rtc()->Day(incr_0);
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu.un8.b = 7; count_0 = 0; skip_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 7:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Clock", 12);
            count_1--;
            if (!count_1) {
                count_1 = ADC_DELAY;
                if (n_sample) {
                    n_sample--;
                    adc_value.un16.w += adc1()->readtemperature();
                } else {
                    n_sample = ADC_SAMPLE;
                    adc_value.un16.w /= ADC_SAMPLE;  // Ensure proper averaging
                    //temperature = CalculateTemperature(adc_value);
                    snprintf(str, 8, "%.1f %cC", CalculateTemperature(adc_value.un16.w), unit);
                    lcd0()->string_size(str, 8);
                    adc_value.un16.w = 0;  // Reset adc_value after use
                }
            }

            if (PA.par.LH & 1) {
                if (skip_0 < 1) {
                    // Handle button hold logic if necessary
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
                HAL_Delay(1000);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu.un8.b = 0; count_0 = 0; skip_0 = 0;
                    //usart1()->transmit_string(BT_AT_Test());
                }
            } else {
                count_0 = 0;
            }
            break;
        }

        rtc()->dr2vec(vecD);
        rtc()->tr2vec(vecT);

        lcd0()->gotoxy(2, 0);
        func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
        lcd0()->string_size(str, 10);

        lcd0()->gotoxy(2, 11);
        lcd0()->string_size((char*)WeekDay_String(vecD[2]), 7);

        lcd0()->gotoxy(3, 11);
        func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
        lcd0()->string_size(str, 8);

        if(!strcmp(oneshot,"s01.")){
        	gpioc()->set_hpins(1 << 13);
        }
         if(!strcmp(oneshot,"s00.")){
         	gpioc()->clear_hpins(1 << 13);
        }
    }
}

void setup_usart1(void){
	usart1_enable();
	// Enable GPIOA and USART1 clocks
	//gpioa()->clock(ON);
	usart1()->clock(ON); // Enable USART1 clock

	// Set PA9 and PA10 to alternate function mode
	gpioa()->moder(9,MODE_AF); gpioa()->moder(10,MODE_AF);

	// Set alternate function type to AF7 (USART1) for PA9 and PA10
	gpioa()->af(9,7); gpioa()->af(10,7); // Set AF7 for PA9 and PA10

	// Set PA9 as push-pull output, high speed
	gpioa()->ospeed(9,3); gpioa()->ospeed(10,3); // High speed for PA9, PA10
	gpioa()->otype(9,0); gpioa()->otype(10,0);  // Set to push-pull
	gpioa()->pupd(9,0); gpioa()->pupd(10,0); // No pull-up, no pull-down

	// Set USART1 baud rate
	usart1()->samplingmode(0,38400);

	// Interrupt handler setup
	usart1()->instance->CR1 |= USART_CR1_TXEIE;
	usart1()->instance->CR1 |= USART_CR1_RXNEIE;
	usart1()->nvic(ON);

	// Enable USART1, TX, RX
	usart1()->tx_enable(); usart1()->rx_enable(); // Enable transmitter and receiver
	usart1()->start(); // Enable USART1
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif

