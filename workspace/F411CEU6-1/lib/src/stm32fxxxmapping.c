/******************************************************************************
	STM32 XXX MAPPING
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28/02/2024
Comment:
	-manual um1724, m0390, pm0056, pm0214, and other sources.
	-Virtual Image STM32-XXX, mapping.
	-Still in progress 15062023, increment has go along.
	-Dependent on CMSIS
	-Stable.
*******************************************************************************/
/*** File Library ***/
#include <stm32fxxxmapping.h>

/*** File Variables ***/
static STM32FXXX stm32fxxx;

/******* STM32F446RE Procedure & Function Definition *******/
STM32FXXX* STM32FXXX_enable(void){
	/************* CORE ************/
	// SCB
	stm32fxxx.scb_instance = SCB;
	// SysTick
	stm32fxxx.systick_instance = SysTick;
	// NVIC
	stm32fxxx.nvic_instance = NVIC;
	#if defined(_STM32FXXXNVIC_H_)
		stm32fxxx.nvic = nvic_enable();
	#endif
	/************ MCU ************/
	// ADC
	#if defined(_STM32FXXXADC1_H_)
		stm32fxxx.adc1 = adc1_enable();
	#endif
	#if defined(_STM32FXXXADC2_H_)
		#ifdef __STM32F446xx_H
			stm32fxxx.adc2 = adc2_enable();
		#endif
	#endif
	#if defined(_STM32FXXXADC3_H_)
		#ifdef __STM32F446xx_H
			stm32fxxx.adc3 = adc3_enable();
		#endif
	#endif
	// CRC
	stm32fxxx.crc_instance = CRC;
	#if defined(_STM32FXXXCRC_H_)
		stm32fxxx.crc = crc_enable();
	#endif
	// DMA
	#if defined(_STM32FXXXDMA_H_)
		stm32fxxx.dma1 = dma1_enable();
		stm32fxxx.dma2 = dma2_enable();
	#endif
	// FLASH
	stm32fxxx.flash_instance = flash_instance();
	#if defined(_STM32FXXXFLASH_H_)
		stm32fxxx.flash = flash_enable();
	#endif
	// GPIO
	#if defined(_STM32FXXXGPIO_H_)
		stm32fxxx.gpioa = gpioa_enable();
		stm32fxxx.gpiob = gpiob_enable();
		stm32fxxx.gpioc = gpioc_enable();
		stm32fxxx.gpiod = gpiod_enable();
		stm32fxxx.gpioe = gpioe_enable();
		stm32fxxx.gpioh = gpioh_enable();
	#endif
	// SYSCFG
	stm32fxxx.syscfg_instance = SYSCFG;
	#if defined(_STM32FXXXSYSCFG_H_)
		stm32fxxx.syscfg = syscfg_enable();
	#endif
	// PWR
	stm32fxxx.pwr_instance = PWR;
	#if defined(_STM32FXXXPWR_H_)
		stm32fxxx.pwr = pwr_enable();
	#endif
	// RCC
	stm32fxxx.rcc_instance = rcc_instance();
	#if defined(_STM32FXXXRCC_H_)
		stm32fxxx.rcc = rcc_enable();
	#endif
	// RTC
	stm32fxxx.rtc_instance = RTC;
	#if defined(_STM32FXXXRTC_H_)
		stm32fxxx.rtc = rtc_enable();
	#endif
	// SRAM
	#if defined(_STM32FXXXSRAM_H_)
		stm32fxxx.sram = sram_enable();
	#endif
	// TIM
	#if defined(_STM32FXXXTIM1AND8_H_)
		stm32fxxx.tim1 = tim1_enable();
		#ifdef __STM32F446xx_H
			stm32fxxx.tim8 = tim8_enable();
		#endif
	#endif
	#if defined(_STM32FXXXTIM2TO5_H_)
		stm32fxxx.tim2 = tim2_enable();
		stm32fxxx.tim3 = tim3_enable();
		stm32fxxx.tim4 = tim4_enable();
		stm32fxxx.tim5 = tim5_enable();
	#endif
	#if defined(_STM32FXXXTIM6AND7_H_)
		#ifdef __STM32F446xx_H
			stm32fxxx.tim6 = tim6_enable();
			stm32fxxx.tim7 = tim7_enable();
		#endif
	#endif
	#if defined(_STM32FXXXTIM9TO14_H_)
		stm32fxxx.tim9 = tim9_enable();
		stm32fxxx.tim10 = tim10_enable();
		stm32fxxx.tim11 = tim11_enable();
		#ifdef __STM32F446xx_H
			stm32fxxx.tim12 = tim12_enable();
			stm32fxxx.tim13 = tim13_enable();
			stm32fxxx.tim14 = tim14_enable();
		#endif
	#endif
	// USART
	#if defined(_STM32FXXXUSART_H_)
		stm32fxxx.usart1 = usart1_enable();
		stm32fxxx.usart2 = usart2_enable();
		#ifdef __STM32F446xx_H
			stm32fxxx.usart3 = usart3_enable();
			stm32fxxx.uart4 = uart4_enable();
			stm32fxxx.uart5 = uart5_enable();
		#endif
		stm32fxxx.usart6 = usart6_enable();
	#endif

	/*** System ***/
	rcc_start();
	query_enable();
	systick_start();

	return &stm32fxxx;
}

STM32FXXX* stm(void){return (STM32FXXX*) &stm32fxxx;}

/***EOF***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

