/****************************************************************************
Title:
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
*****************************************************************************/
#include "main.h"

#include "stm32fxxxrcc.h"
#include "armsystick.h"
#include "stm32fxxxgpio.h"

#include "armlcd.h"
#include "armfunction.h"
#include "explode.h"

#define JMP_menu 100

EXPLODE PA;
//uint32_t test[8] = {~0,~0,~0,~0,~0,~0,~0,~0};

int main(void)
{
	rcc_start();
	systick_start();
	gpioa_enable(); // inputs k0 gpioa0
	gpiob_enable(); // lcd0
	gpioc_enable(); // gpioc13

    PA = EXPLODE_enable();

    uint8_t Menu = 6;
    uint8_t count_0 = 0;
    uint32_t number[4];
    number[0] = 0;
    number[1] = 0;
    number[2] = 0;
    number[3] = 0;

    ARMLCD0_enable(GPIOB);
    set_reg_Msk(&GPIOC->MODER, GPIO_MODER_MODER13, GPIO_MODER_MODER13_Pos, 1);
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
        number[0] = 11;
		//set_bit_block(&test[0],33,20+64,~0);
        RealNum_TypeDef a = func()->realnumber( -67.010101, number[0]);
        //RealNum_TypeDef a = func()->divide( 83333 , 65536);
		lcd0()->gotoxy(1, 0);
		//lcd0()->string_size(func()->ftoa(1/0.7,4), 10);
		lcd0()->string_size(func()->ui32toa( a.Quotient ), 4);lcd0()->hspace(1);
		lcd0()->string_size(func()->i32toa( a.Denominator ), 15);
		//lcd0()->string_size(func()->ui32toa( pow(10,2) ), 4);
		lcd0()->gotoxy(2, 0);
		lcd0()->string_size(func()->ftoa( a.Number, number[0] ), 11);lcd0()->hspace(1);
		lcd0()->string_size(func()->ftoa( a.Fpart, number[0] ), 8);
		lcd0()->gotoxy(3, 0);
		//lcd0()->string_size(func()->i16toa( a.sign ), 3);
		//lcd0()->string_size(func()->ui32toa( a.Numerator ), 8);lcd0()->hspace(1);
		//lcd0()->string_size(func()->ui32toa( a.Remainder ), 11);
		//lcd0()->string_size(func()->ui32toa( a.Denominator ), 8);
		//set_bit_block(number,1,32,1);
		set_reg_block(number,1,0,1);
		//lcd0()->string_size(func()->ui32toa(number[0]), 20);
		lcd0()->string_size(func()->ui32toa(get_reg_block(number[0],33,0)), 20);
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

