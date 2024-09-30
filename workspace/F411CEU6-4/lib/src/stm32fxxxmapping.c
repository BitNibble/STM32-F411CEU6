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
/*** File Function Identity ***/
static void initialize_nvic(void);
static void initialize_adc(void);
static void initialize_crc(void);
static void initialize_dma(void);
static void initialize_flash(void);
static void initialize_gpio(void);
static void initialize_syscfg(void);
static void initialize_pwr(void);
static void initialize_rcc(void);
static void initialize_rtc(void);
static void initialize_sram(void);
static void initialize_tim(void);
static void initialize_usart(void);
/******* STM32F446RE Procedure & Function Definition *******/
STM32FXXX* STM32FXXX_enable(void){
	/************* CORE ************/
	initialize_nvic();
	/************ MCU ************/
	initialize_adc();
	initialize_crc();
	initialize_dma();
	initialize_flash();
	initialize_gpio();
	initialize_syscfg();
	initialize_pwr();
	initialize_rcc();
	initialize_rtc();
	initialize_sram();
	initialize_tim();
	initialize_usart();
	/*** System ***/
	rcc_start();
	query_enable();
	systick_start();
	return &stm32fxxx;
}
STM32FXXX* stm(void){return (STM32FXXX*) &stm32fxxx;}
// NVIC
static void initialize_nvic(void) {
	#if defined(_STM32FXXXNVIC_H_)
		stm32fxxx.nvic = nvic_enable();
	#endif
}
// ADC
static void initialize_adc(void) {
    #if defined(_STM32FXXXADC1_H_)
        stm32fxxx.adc1 = adc1_enable();
    #endif
	#if defined(_STM32FXXXADC2_H_)
		#ifdef STM32F446xx
			stm32fxxx.adc2 = adc2_enable();
		#endif
	#endif
	#if defined(_STM32FXXXADC3_H_)
		#ifdef STM32F446xx
			stm32fxxx.adc3 = adc3_enable();
		#endif
	#endif
}
// CRC
static void initialize_crc(void) {
	#if defined(_STM32FXXXCRC_H_)
		stm32fxxx.crc = crc_enable();
	#endif
}
// DMA
static void initialize_dma(void) {
	#if defined(_STM32FXXXDMA_H_)
		stm32fxxx.dma1 = dma1_enable();
		stm32fxxx.dma2 = dma2_enable();
	#endif
}
// FLASH
static void initialize_flash(void) {
	#if defined(_STM32FXXXFLASH_H_)
		stm32fxxx.flash = flash_enable();
	#endif
}
// GPIO
static void initialize_gpio(void) {
    #if defined(_STM32FXXXGPIO_H_)
        stm32fxxx.gpioa = gpioa_enable();
        stm32fxxx.gpiob = gpiob_enable();
        stm32fxxx.gpioc = gpioc_enable();
        stm32fxxx.gpiod = gpiod_enable();
        stm32fxxx.gpioe = gpioe_enable();
		#ifdef STM32F446xx
        	stm32fxxx.gpiof = gpiof_enable();
        	stm32fxxx.gpiog = gpiog_enable();
		#else
        	stm32fxxx.gpiof = NULL;
        	stm32fxxx.gpiog = NULL;
		#endif
        stm32fxxx.gpioh = gpioh_enable();
    #endif
}
// SYSCFG
static void initialize_syscfg(void) {
	#if defined(_STM32FXXXSYSCFG_H_)
		stm32fxxx.syscfg = syscfg_enable();
	#endif
}
// PWR
static void initialize_pwr(void) {
	#if defined(_STM32FXXXPWR_H_)
		stm32fxxx.pwr = pwr_enable();
	#endif
}
// RCC
static void initialize_rcc(void) {
	#if defined(_STM32FXXXRCC_H_)
		stm32fxxx.rcc = rcc_enable();
	#endif
}
// RTC
static void initialize_rtc(void) {
	#if defined(_STM32FXXXRTC_H_)
		stm32fxxx.rtc = rtc_enable();
	#endif
}
// SRAM
static void initialize_sram(void) {
	#if defined(_STM32FXXXSRAM_H_)
		stm32fxxx.sram = sram_enable();
	#endif
}
// TIM
static void initialize_tim(void) {
	#if defined(_STM32FXXXTIM1AND8_H_)
		stm32fxxx.tim1 = tim1_enable();
		#ifdef STM32F446xx
			stm32fxxx.tim8 = tim8_enable();
		#else
			stm32fxxx.tim8 = NULL;
		#endif
	#endif
	#if defined(_STM32FXXXTIM2TO5_H_)
		stm32fxxx.tim2 = tim2_enable();
		stm32fxxx.tim3 = tim3_enable();
		stm32fxxx.tim4 = tim4_enable();
		stm32fxxx.tim5 = tim5_enable();
	#endif
	#if defined(_STM32FXXXTIM6AND7_H_)
		#ifdef STM32F446xx
			stm32fxxx.tim6 = tim6_enable();
			stm32fxxx.tim7 = tim7_enable();
		#else
			stm32fxxx.tim6 = NULL;
			stm32fxxx.tim7 = NULL;
		#endif
	#endif
	#if defined(_STM32FXXXTIM9TO14_H_)
		stm32fxxx.tim9 = tim9_enable();
		stm32fxxx.tim10 = tim10_enable();
		stm32fxxx.tim11 = tim11_enable();
		#ifdef STM32F446xx
			stm32fxxx.tim12 = tim12_enable();
			stm32fxxx.tim13 = tim13_enable();
			stm32fxxx.tim14 = tim14_enable();
		#else
			stm32fxxx.tim12 = NULL;
			stm32fxxx.tim13 = NULL;
			stm32fxxx.tim14 = NULL;
		#endif
	#endif
}
// USART
static void initialize_usart(void) {
	#if defined(_STM32FXXXUSART_H_)
		stm32fxxx.usart1 = usart1_enable();
		stm32fxxx.usart2 = usart2_enable();
		#ifdef STM32F446xx
			stm32fxxx.usart3 = usart3_enable();
			stm32fxxx.uart4 = uart4_enable();
			stm32fxxx.uart5 = uart5_enable();
		#else
			stm32fxxx.usart3 = NULL;
			stm32fxxx.uart4 = NULL;
			stm32fxxx.uart5 = NULL;
		#endif
		stm32fxxx.usart6 = usart6_enable();
	#endif
}
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

