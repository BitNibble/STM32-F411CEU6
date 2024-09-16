/******************************************************************************
	STM32 XXX MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	-manual um1724, m0390, pm0056, pm0214, and other sources.
	-Virtual Image STM32-XXX, mapping.
	-Still in progress 15062023, increment has go along.
	-Dependent on CMSIS
	-Stable.
*******************************************************************************/
#ifndef _STM32FXXXMAPPING_H_
	#define _STM32FXXXMAPPING_H_
/***** Global Libraries *****/
#include "armquery.h"
#include "armsystick.h"
/****** Define & Macros******/

/*** Module Library ***/
// May comment out modules not being used
#include "stm32fxxxflash.h"
#include "stm32fxxxcrc.h"
#include "stm32fxxxpwr.h"
#include "stm32fxxxrcc.h"
#include "stm32fxxxnvic.h"
#include "stm32fxxxsram.h"
#include "stm32fxxxgpio.h"
#include "stm32fxxxsyscfg.h"
#include "stm32fxxxdma.h"
#include "stm32fxxxadc1.h"
#include "stm32fxxxadc2.h"
#include "stm32fxxxadc3.h"
#include "stm32fxxxrtc.h"
#include "stm32fxxxusart.h"
#include "stm32fxxxtim1and8.h"
#include "stm32fxxxtim2to5.h"
#include "stm32fxxxtim6and7.h"
#include "stm32fxxxtim9to14.h"
/***************** STM32FXXX TypeDef *****************/
typedef struct
{
	// SCB
	SCB_Type* scb_instance;
	// SysTick
	SysTick_Type* systick_instance;
	// NVIC
	NVIC_Type* nvic_instance;
	#if defined(_STM32FXXXNVIC_H_)
		STM32FXXXNVICobj* nvic;
	#endif
	// ADC
	STM32FXXXADC_TypeDef* adc1_instance;
	STM32FXXXADC_COMMON_TypeDef* adc1_common_instance;
	#if defined(_STM32FXXXADC1_H_)
		STM32FXXX_ADC1* adc1;
	#endif
	ADC_TypeDef* adc2_instance;
	ADC_Common_TypeDef* adc2_common_instance;
	#if defined(_STM32FXXXADC2_H_)
		STM32FXXX_ADC2* adc2;
	#endif
	ADC_TypeDef* adc3_instance;
	ADC_Common_TypeDef* adc3_common_instance;
	#if defined(_STM32FXXXADC3_H_)
		STM32FXXX_ADC3* adc3;
	#endif
	// CRC
	CRC_TypeDef* crc_instance;
	#if defined(_STM32FXXXCRC_H_)
		STM32FXXXCRCobj* crc;
	#endif
	// DMA
	#if defined(_STM32FXXXDMA_H_)
		STM32FXXXDMA1obj* dma1;
		STM32FXXXDMA2obj* dma2;
	#endif
	// FLASH
	FLASH_TypeDef* flash_instance;
	#if defined(_STM32FXXXFLASH_H_)
		STM32FXXXFLASHobj* flash;
	#endif
	// GPIO
	#if defined(_STM32FXXXGPIO_H_)
		STM32FXXX_GPIOA* gpioa;
		STM32FXXX_GPIOB* gpiob;
		STM32FXXX_GPIOC* gpioc;
		STM32FXXX_GPIOD* gpiod;
		STM32FXXX_GPIOE* gpioe;
		STM32FXXX_GPIOF* gpiof;
		STM32FXXX_GPIOG* gpiog;
		STM32FXXX_GPIOH* gpioh;
	#endif
	// SYSCFG
	SYSCFG_TypeDef* syscfg_instance;
	#if defined(_STM32FXXXSYSCFG_H_)
		STM32FXXXSYSCFGobj* syscfg;
	#endif
	// PWR
	PWR_TypeDef* pwr_instance;
	#if defined(_STM32FXXXPWR_H_)
		STM32FXXX_PWR* pwr;
	#endif
	// RCC
	STM32FXXXRCC_TypeDef* rcc_instance;
	#if defined(_STM32FXXXRCC_H_)
		STM32FXXX_RCC* rcc;
	#endif
	// RTC
	RTC_TypeDef* rtc_instance;
	#if defined(_STM32FXXXRTC_H_)
		STM32FXXX_RTC* rtc;
	#endif
	// SRAM
	#if defined(_STM32FXXXSRAM_H_)
		STM32FXXXSRAMobj* sram;
	#endif
	// TIM
	#if defined(_STM32FXXXTIM1AND8_H_)
		STM32FXXX_TIM1* tim1;
		STM32FXXX_TIM8* tim8;
	#endif
	#if defined(_STM32FXXXTIM2TO5_H_)
		STM32FXXX_TIM2* tim2;
		STM32FXXX_TIM3* tim3;
		STM32FXXX_TIM4* tim4;
		STM32FXXX_TIM5* tim5;
	#endif
	#if defined(_STM32FXXXTIM6AND7_H_)
		STM32FXXX_TIM6* tim6;
		STM32FXXX_TIM7* tim7;
	#endif
	#if defined(_STM32FXXXTIM9TO14_H_)
		STM32FXXX_TIM9* tim9;
		STM32FXXX_TIM10* tim10;
		STM32FXXX_TIM11* tim11;
		STM32FXXX_TIM12* tim12;
		STM32FXXX_TIM13* tim13;
		STM32FXXX_TIM14* tim14;
	#endif
	// USART
	#if defined(_STM32FXXXUSART_H_)
		STM32FXXX_USART1* usart1;
		STM32FXXX_USART2* usart2;
		STM32FXXX_USART3* usart3;
		STM32FXXX_UART4* uart4;
		STM32FXXX_UART5* uart5;
		STM32FXXX_USART6* usart6;
	#endif

}STM32FXXX;

/*** Global ***/
STM32FXXX* STM32FXXX_enable(void);
STM32FXXX* stm(void);

/*** INTERRUPT HEADER ***/
void Reset_IRQHandler(void);
void NMI_IRQHandler(void);
void HardFault_IRQHandler(void);
void MemManage_IRQHandler(void);
void BusFault_IRQHandler(void);
void UsageFault_IRQHandler(void);
void SVCall_IRQHandler(void);
void PendSV_IRQHandler(void);
void Systick_IRQHandler(void);
void FPU_IRQHandler(void);
void SysTick_Handler(void);

#endif

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting

TypeDef->Instance->Handler
******/

/***EOF***/

