/*************************************************************************
	ARMQUERY
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: STM32QUERY
Date: 10/01/2024
Update: 
Comment:
	Tested STM32F446RE and STM32F411CEU6
************************************************************************/
#ifndef _ARMQUERY_H_
	#define _ARMQUERY_H_

#include "stm32fxxxinstance.h"
#include <stdio.h>

#ifndef HSI_RC
	#define HSI_RC 16000000UL
#endif
#ifndef HSE_OSC
	#define HSE_OSC 25000000UL
#endif

/*******   0 -> HSI    1->HSE   *********/
#define H_Clock_Source 1
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 0
/****************************************/
#ifndef on
	#define on 1
#endif
#ifndef ON
	#define ON 1
#endif
#ifndef off
	#define off 0
#endif
#ifndef OFF
	#define OFF 0
#endif
#ifndef yes
	#define yes 1
#endif
#ifndef YES
	#define YES 1
#endif
#ifndef no
	#define no 0
#endif
#ifndef NO
	#define NO 0
#endif
/****************************************/
typedef struct{
uint16_t (*AHB)(void);
uint8_t (*APB1)(void);
uint8_t (*APB2)(void);
uint8_t (*RTCclk)(void);
uint8_t (*MCO1)(void);
uint8_t (*MCO2)(void);
}STM32FXXXSYSTEM_prescaler;
typedef struct{
uint8_t (*M)(void);
uint16_t (*N)(void);
uint8_t (*P)(void);
uint8_t (*Q)(void);
uint8_t (*R)(void);
}STM32FXXXPLL_prescaler;
typedef struct{
STM32FXXXSYSTEM_prescaler* System_prescaler;
STM32FXXXPLL_prescaler* Pll_prescaler;
uint32_t (*PllClock)(void);
uint32_t (*SystemClock)(void);
uint32_t (*hclk)(void);
uint32_t (*pclk1)(void);
uint32_t (*pclk2)(void);
}STM32FXXX_Query;

void set_reg(volatile uint32_t* reg, uint32_t hbits);
void clear_reg(volatile uint32_t* reg, uint32_t hbits);
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n);
uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk, uint8_t Pos);
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void set_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void reset_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void setpin( GPIO_TypeDef* reg, uint8_t pin );
void resetpin( GPIO_TypeDef* reg, uint8_t pin );

uint32_t getpllclk(void);
uint32_t getsysclk(void);

uint16_t gethpre(void);
uint8_t gethppre1(void);
uint8_t gethppre2(void);
uint8_t getrtcpre(void);
uint8_t gethmco1pre(void);
uint8_t gethmco2pre(void);
uint8_t getpllm(void);
uint16_t getplln(void);
uint8_t getpllp(void);
uint8_t getpllq(void);
uint8_t getpllr(void);

STM32FXXX_Query query_enable(void);
STM32FXXX_Query* query(void);

/****** MISCELLANEOUS ******/
void ADC_TemperatureSetup(void);
uint16_t ADC_ReadTemperature(void);
float CalculateTemperature(uint16_t adc_value);

#endif

/***EOF***/

