/********************************************************************************
Title:
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

#define JMP_menu 100


EXPLODE PA;

int main(void)
{
    STM32FXXX_enable();
    PA = EXPLODE_enable();

    uint8_t Menu = 6;
    uint8_t count_0 = 0;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // lcd0
    ARMLCD0_enable(GPIOB);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // gpioc13
    set_reg_Msk(&GPIOC->MODER, GPIO_MODER_MODER13, GPIO_MODER_MODER13_Pos, 1);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // inputs gpioa0
    set_reg_Msk(&GPIOA->MODER, GPIO_MODER_MODER0, GPIO_MODER_MODER0_Pos, 0);
    set_reg_Msk(&GPIOA->PUPDR, GPIO_PUPDR_PUPD0, GPIO_PUPDR_PUPD0_Pos, 1);

    FUNC_enable();

    PA.update(&PA.par, GPIOA->IDR);

    while (1)  // Infinite loop
    {
        PA.update(&PA.par, GPIOA->IDR);

        switch (Menu) {
        case 0:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("One", 10);

            if (PA.par.LL & 1) { // Jump menu
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > 5) {
                    Menu = 1; count_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 1:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Two", 10);

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > 5) {
                    Menu = 2; count_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 2:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Three", 10);

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > 5) {
                    Menu = 3; count_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 3:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Four", 10);

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > 5) {
                    Menu = 4; count_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 4:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Five", 10);

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > 5) {
                    Menu = 5; count_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 5:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Six", 10);

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > 5) {
                    Menu = 6; count_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        case 6:
            lcd0()->gotoxy(0, 0);
            lcd0()->string_size("Seven", 12);

            if (PA.par.LL & 1) {
                _delay_ms(JMP_menu);
                count_0++;
                if (count_0 > 5) {
                    Menu = 0; count_0 = 0;
                }
            } else {
                count_0 = 0;
            }
            break;

        default:
            break;
        }/*** switch ***/
        /*** Testing ***/
		//set_bit_block(&test[0],33,20+64,~0);
        Real a = func()->realnumber( 56.567 , 10);
		lcd0()->gotoxy(1, 0);
		//lcd0()->string_size(func()->ftoa(1/0.7,4), 10);
		lcd0()->string_size(func()->ui32toa( a.Quotient ), 10);
		lcd0()->string_size(func()->ui32toa( a.Remainder ), 10);
		lcd0()->gotoxy(2, 0);
		lcd0()->string_size(func()->ftoa( a.Fpart, 10000 ), 8);
		lcd0()->gotoxy(3, 0);
		lcd0()->string_size(func()->i16toa( a.sign ), 3);
		lcd0()->string_size(func()->ui32toa( a.Numerator ), 8);
		lcd0()->string_size(func()->ui32toa( a.Denominator ), 8);
		//lcd0()->string_size(func()->ui32toa(test[2]), 10);
		//lcd0()->gotoxy(1, 0);
		//lcd0()->string_size(func()->ui32toa(HAL_GetTick()), 8);
		//lcd0()->string_size(func()->ui32toa(HAL_GetTickFreq()), 4);
		//lcd0()->string_size(func()->ui32toa(getsysclk()/(gethpre() * 1)), 20);
		/******/
    }/*** while ***/
}/*** main ***/

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

