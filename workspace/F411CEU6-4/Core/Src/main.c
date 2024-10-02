/********************************************************************************
Title: A simple Clock
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
File: main.c 22/09/2024
Software: STM32CubeIDE v1.16.0 Build: 21983_20240628_1741 (UTC)
Hardware: STM32F411CEU6 by DevBox

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
********************************************************************************/
#include "main.h"
#include "stm32fxxxmapping.h"
#include "armlcd.h"
#include "armfunction.h"
#include "explode.h"
#include <stdio.h>

#define JMP_menu 120
#define JMP_menu_repeat 5
#define ADC_DELAY 20
#define ADC_SAMPLE 8

EXPLODE PA;
char ADC_msg[32];
char str[32];

int main(void)
{
    STM32FXXX_enable();
    HAL_Init();
    enable_fpu();
    rtc()->inic(1);
    PA = EXPLODE_enable();

    uint8_t Menu = 7;
    uint8_t count_0 = 0;
    uint8_t count_1 = ADC_DELAY;
    uint8_t n_sample = ADC_SAMPLE;
    uint16_t incr_0 = 0;
    uint8_t skip_0 = 0;
    uint16_t adc_value = 0;
    const char unit = (char)0xDF;

    stm()->rcc->instance->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // lcd0
    ARMLCD0_enable(GPIOB);
    rcc()->instance->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // gpioc13
    set_reg_Msk(&GPIOC->MODER, GPIO_MODER_MODER13, GPIO_MODER_MODER13_Pos, 1);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // inputs gpioa0
    set_reg_Msk(&GPIOA->MODER, GPIO_MODER_MODER0, GPIO_MODER_MODER0_Pos, 0);
    set_reg_Msk(&GPIOA->PUPDR, GPIO_PUPDR_PUPD0, GPIO_PUPDR_PUPD0_Pos, 1);

    FUNC_enable();
    ADC_TemperatureSetup();

    char vecD[8]; // for calendar date
    char vecT[8]; // for calendar time
    PA.update(&PA.par, stm()->gpioa->instance->IDR);

    while (1)  // Infinite loop
    {
        PA.update(&PA.par, gpioa_instance()->IDR);

        switch (Menu) {
        case 0:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Hour", 12);
            gpioc_instance()->BSRR = GPIO_BSRR_BR13;

            if (PA.par.LH & 1) {
                if (skip_0 > 0) {
                    incr_0 = rtc()->get_Hour();
                    incr_0 = (incr_0 > 22) ? 0 : incr_0 + 1;
                    rtc()->Hour(incr_0);
                }
                skip_0++;
            }

            if (PA.par.LL & 1) { // Jump menu
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu = 1; count_0 = 0; skip_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 1:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Minute", 12);
            stm()->gpioc->instance->BSRR = GPIO_BSRR_BS13;

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
                    Menu = 2; count_0 = 0; skip_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 2:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Second", 12);
            GPIOC->BSRR = GPIO_BSRR_BR13;

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
                    Menu = 3; count_0 = 0; skip_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 3:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Year", 12);
            GPIOC->BSRR = GPIO_BSRR_BS13;

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
                    Menu = 4; count_0 = 0; skip_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 4:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Month", 12);
            GPIOC->BSRR = GPIO_BSRR_BR13;

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
                    Menu = 5; count_0 = 0; skip_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 5:
                   lcd0()->gotoxy(0, 0);
                   lcd0()->string_size("Set WeekDay", 12);
                   GPIOC->BSRR = GPIO_BSRR_BS13;

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
                           Menu = 6; count_0 = 0; skip_0 = 0;
                       }
                   } else {
                       count_0 = 0;
                   }
                   break;

        case 6:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Set Day", 12);
            GPIOC->BSRR = GPIO_BSRR_BR13;

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
                    Menu = 7; count_0 = 0; skip_0 = 0;
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
                    adc_value += ADC_ReadTemperature();
                } else {
                    n_sample = ADC_SAMPLE;
                    adc_value /= ADC_SAMPLE;  // Ensure proper averaging
                    //temperature = CalculateTemperature(adc_value);
                    snprintf(str, 8, "%.1f %cC", CalculateTemperature(adc_value), unit);
                    lcd0()->string_size(str, 8);
                    adc_value = 0;  // Reset adc_value after use
                }
            }
            GPIOC->BSRR = GPIO_BSRR_BS13;

            if (PA.par.LH & 1) {
                if (skip_0 < 1) {
                    // Handle button hold logic if necessary
                }
                skip_0++;
            }

            if (PA.par.LL & 1) {
                //_delay_ms(JMP_menu);
                //delayAsmMicroseconds(JMP_menu * 1000);
                delayMicroseconds(JMP_menu * 600);
                count_0++;
                if (count_0 > JMP_menu_repeat) {
                    Menu = 0; count_0 = 0; skip_0 = 0;
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
    }
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

