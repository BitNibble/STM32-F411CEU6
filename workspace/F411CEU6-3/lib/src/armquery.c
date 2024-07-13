/*************************************************************************
	STM32QUERY
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: STM32QUERY
Date: 10/01/2024
Update: 
Comment:
	Tested STM32F446RE and STM32F411CEU6
************************************************************************/
#include "armquery.h"
#include <stdarg.h>
#include <math.h>

static STM32FXXX_Query stm32fxxx_query;
static STM32FXXXSYSTEM_prescaler stm32fxxx_System_prescaler;
static STM32FXXXPLL_prescaler stm32fxxx_Pll_prescaler;


STM32FXXXSYSTEM_prescaler* System_prescaler_inic(void);
STM32FXXXPLL_prescaler* Pll_prescaler_inic(void);

uint16_t gethpre(void)
{
	uint32_t value = readreg(RCC->CFGR, 4, 4);
	switch(value)
	{
		case 0b1000:
			value = 2;
		break;
		case 0b1001:
			value = 4;
		break;
		case 0b1010:
			value = 8;
		break;
		case 0b1011:
			value = 16;
		break;
		case 0b1100:
			value = 64;
		break;
		case 0b1101:
			value = 128;
		break;
		case 0b1110:
			value = 256;
		break;
		case 0b1111:
			value = 512;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t gethppre1(void)
{
	uint32_t value = readreg(RCC->CFGR, 3, 10);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t gethppre2(void)
{
	uint32_t value = readreg(RCC->CFGR, 3, 13);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t getrtcpre(void)
{
	return readreg(RCC->CFGR, 5, 16);
}
uint8_t gethmco1pre(void)
{
	uint32_t value = readreg(RCC->CFGR, 3, 24);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t gethmco2pre(void)
{
	uint32_t value = readreg(RCC->CFGR, 3, 27);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
		}
	return value;
}
uint8_t getpllm(void)
{
	return readreg(RCC->PLLCFGR, 6, 0);
}
uint16_t getplln(void)
{
	return readreg(RCC->PLLCFGR, 9, 6);
}
uint8_t getpllp(void)
{
	uint32_t value = readreg(RCC->PLLCFGR, 2, 16);
	switch(value)
	{
		case 0b00:
			value = 2;
		break;
		case 0b01:
			value = 4;
		break;
		case 0b10:
			value = 6;
		break;
		case 0b11:
			value = 8;
		break;
		default:
		break;
	}
	return value;
}
uint8_t getpllq(void)
{
	return readreg(RCC->PLLCFGR, 4, 24);
}
uint8_t getpllr(void)
{
	return readreg(RCC->PLLCFGR, 3, 28);
}
uint32_t getpllclk(void)
{
	uint32_t source;
	if( readreg(RCC->PLLCFGR, 1, 22) ) source = HSE_OSC; else source = HSI_RC;
	return source;
}
uint32_t getsysclk(void)
{
	long value = readreg(RCC->CFGR, 2, 2);
	switch(value) // SWS[2]: System clock switch status
	{
		case 0:
			value = HSI_RC;
		break;
		case 1: // 01: HSE oscillator used as the system clock
			value = HSE_OSC;
		break;
		case 2: // 10: PLL used as the system clock
			value = getpllclk() / getpllm();
			value /= getpllp();
			value *= getplln();
		break;
		case 3: // 11: PLL_R used as the system clock
			#ifdef STM32F446xx
				value = getpllclk() / getpllm();
				value /= getpllr();
				value *= getplln();
			#endif
		break;
		default: // 00: HSI oscillator used as the system clock
		break;
	}
	return (uint32_t)value;
}

uint32_t gethclk(void){
	return getsysclk()/gethpre();
}

uint32_t getpclk1(void){
	uint32_t freq = getsysclk()/gethpre();
	return freq/gethppre1();
}

uint32_t getpclk2(void){
	uint32_t freq = getsysclk()/gethpre();
	return freq/gethppre2();
}

STM32FXXXSYSTEM_prescaler* System_prescaler_inic(void)
{
	stm32fxxx_System_prescaler.AHB = gethpre;
	stm32fxxx_System_prescaler.APB1 = gethppre1;
	stm32fxxx_System_prescaler.APB2 = gethppre2;
	stm32fxxx_System_prescaler.RTCclk = getrtcpre;
	stm32fxxx_System_prescaler.MCO1 = gethmco1pre;
	stm32fxxx_System_prescaler.MCO2 = gethmco2pre;
	return &stm32fxxx_System_prescaler;
}
STM32FXXXPLL_prescaler* Pll_prescaler_inic(void)
{
	stm32fxxx_Pll_prescaler.M = getpllm;
	stm32fxxx_Pll_prescaler.N = getplln;
	stm32fxxx_Pll_prescaler.P = getpllp;
	stm32fxxx_Pll_prescaler.Q = getpllq;
	stm32fxxx_Pll_prescaler.R = getpllr;
	return &stm32fxxx_Pll_prescaler;
}
STM32FXXX_Query query_enable(void)
{
	stm32fxxx_query.System_prescaler = System_prescaler_inic();
	stm32fxxx_query.Pll_prescaler = Pll_prescaler_inic();
	stm32fxxx_query.PllClock = getpllclk;
	stm32fxxx_query.SystemClock = getsysclk;
	stm32fxxx_query.hclk = gethclk;
	stm32fxxx_query.pclk1 = getpclk1;
	stm32fxxx_query.pclk2 = getpclk2;
	return stm32fxxx_query;
}

STM32FXXX_Query* query(void){ return (STM32FXXX_Query*) &stm32fxxx_query; }

uint32_t readreg(uint32_t reg, uint8_t size_block, uint8_t bit_n)
{
	if(bit_n > 31){ bit_n = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	reg &= (mask << bit_n);
	reg = (reg >> bit_n);
	return reg;
}
void writereg(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(bit_n > 31){ bit_n = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = *reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	data &= mask; value &= ~(mask << bit_n);
	data = (data << bit_n);
	value |= data;
	*reg = value;
}
void setreg(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(bit_n > 31){ bit_n = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	data &= mask;
	*reg &= ~(mask << bit_n);
	*reg |= (data << bit_n);
}
uint32_t getreg(uint32_t reg, uint8_t size_block, uint8_t bit_n)
{
	if(bit_n > 31){ bit_n = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	reg &= (mask << bit_n);
	reg = (reg >> bit_n);
	return reg;
}
uint32_t getsetbit(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n)
{
	uint32_t n = 0;
	if(bit_n > 31){ n = bit_n/32; bit_n = bit_n - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit_n);
	value = (value >> bit_n);
	return value;
}
void setbit(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	uint32_t n = 0;
	if(bit_n > 31){ n = bit_n/32; bit_n = bit_n - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	data &= mask;
	*(reg + n ) &= ~(mask << bit_n);
	*(reg + n ) |= (data << bit_n);
}
uint32_t getbit(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n)
{
	uint32_t n = 0;
	if(bit_n > 31){ n = bit_n/32; bit_n = bit_n - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit_n);
	value = (value >> bit_n);
	return value;
}

void setregposmsk(volatile uint32_t* reg, uint32_t msk, uint8_t pos, uint32_t data)
{
	pos &= 0x1F;
	data = (data << pos); data &= msk;
	*reg &= ~msk;
	*reg |= data;
}
uint32_t getregposmsk(uint32_t reg, uint32_t msk, uint8_t pos)
{
	pos &= 0x1F;
	reg &= msk; reg = (reg >> pos);
	return reg;
}
void STM32446RegSetBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits < 33){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg |= (uint32_t)(1 << va_arg(list, uint32_t));
		}
		va_end(list);
	}
}
void STM32446RegResetBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits < 33){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg &= (uint32_t)~((1 << va_arg(list, uint32_t)) << 16);
		}
		va_end(list);
	}
}
void STM32446VecSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n )
{
	const unsigned int n_bits = sizeof(data) * 8;
	const unsigned int mask = (unsigned int) (pow(2, size_block) - 1);
	unsigned int index = (block_n * size_block) / n_bits;
	data &= mask;
	vec[index] &= ~( mask << ((block_n * size_block) - (index * n_bits)) );
	vec[index] |= ( data << ((block_n * size_block) - (index * n_bits)) );
}
void sethpins( GPIO_TypeDef* reg, uint16_t hpins )
{
	reg->BSRR = (uint32_t)hpins;
}
void resethpins( GPIO_TypeDef* reg, uint16_t hpins )
{
	reg->BSRR = (uint32_t)(hpins << 16);
}
void setpin( GPIO_TypeDef* reg, uint8_t pin )
{
	reg->BSRR = (1 << pin);
}
void resetpin( GPIO_TypeDef* reg, uint8_t pin )
{
	reg->BSRR = (uint32_t)((1 << pin) << 16);
}

/***EOF***/

