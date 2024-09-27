/*************************************************************************
	STM32QUERY
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: STM32QUERY
Date: 10/01/2024
Update: 
Comment:
	Tested STM32F446RE || STM32F411CEU6
************************************************************************/
#include "armquery.h"
#include <stdarg.h>

/****************************************/

#define BYTE_BITS 8
#define WORD_BITS 16
#define N_BITS 32
#define N_LIMBITS 33
#define H_BIT 31
#define L_BIT 0

/****************************************/

static uint32_t systick_us;
static uint32_t systick_10us;
static uint32_t systick_100us;
static uint32_t systick_ms;

/****************************************/

static STM32FXXX_Query stm32fxxx_query;
static STM32FXXXSYSTEM_prescaler stm32fxxx_System_prescaler;
static STM32FXXXPLL_prescaler stm32fxxx_Pll_prescaler;

STM32FXXXSYSTEM_prescaler* System_prescaler_inic(void);
STM32FXXXPLL_prescaler* Pll_prescaler_inic(void);

uint16_t gethpre(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 4, 4);
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
	uint32_t value = get_reg_block(RCC->CFGR, 3, 10);
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
	uint32_t value = get_reg_block(RCC->CFGR, 3, 13);
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
	return get_reg_block(RCC->CFGR, 5, 16);
}
uint8_t gethmco1pre(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 3, 24);
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
	uint32_t value = get_reg_block(RCC->CFGR, 3, 27);
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
	return get_reg_block(RCC->PLLCFGR, 6, 0);
}
uint16_t getplln(void)
{
	return get_reg_block(RCC->PLLCFGR, 9, 6);
}
uint8_t getpllp(void)
{
	uint32_t value = get_reg_block(RCC->PLLCFGR, 2, 16);
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
	return get_reg_block(RCC->PLLCFGR, 4, 24);
}
uint8_t getpllr(void)
{
	return get_reg_block(RCC->PLLCFGR, 3, 28);
}
uint32_t getpllsourceclk(void)
{
	uint32_t source;
	if( get_reg_block(RCC->PLLCFGR, 1, 22) ) source = HSE_OSC; else source = HSI_RC;
	return source;
}
uint32_t getpllclk(void)
{
	uint32_t pllclk;
	pllclk = getpllsourceclk() / getpllm();
	pllclk /= getpllp();
	pllclk *= getplln();
	return pllclk;
}
uint32_t getsysclk(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 2, 2);
	switch(value) // SWS[2]: System clock switch status
	{
		case 0:
			value = HSI_RC;
		break;
		case 1: // 01: HSE oscillator used as the system clock
			value = HSE_OSC;
		break;
		case 2: // 10: PLL used as the system clock
			value = getpllsourceclk() / getpllm();
			value /= getpllp();
			value *= getplln();
		break;
		case 3: // 11: PLL_R used as the system clock
			#ifdef STM32F446xx
				value = getpllsourceclk() / getpllm();
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

/*** Tools ***/
inline void set_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg |= hbits;
}
inline void clear_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg &= ~hbits;
}
inline uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk, uint8_t Pos)
{
	if(Pos > H_BIT){ Pos = L_BIT; reg = 0; }
	else{ reg &= Msk; reg = (reg >> Pos); }
	return reg;
}
inline void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data)
{
	uint32_t value = *reg;
	if(Pos > H_BIT){ Pos = L_BIT; }
	else{ data = (data << Pos); data &= Msk; value &= ~(Msk); value |= data; *reg = value; }
}
inline void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data)
{
	if(Pos > H_BIT){ Pos = L_BIT; }
	else{ data = (data << Pos); data &= Msk; *reg &= ~(Msk); *reg |= data; }
}
inline void set_hpins( GPIO_TypeDef* reg, uint16_t hpins )
{
	reg->BSRR = (uint32_t)hpins;
}
inline void clear_hpins( GPIO_TypeDef* reg, uint16_t hpins )
{
	reg->BSRR = (uint32_t)(hpins << WORD_BITS);
}
inline void set_pin( GPIO_TypeDef* reg, uint8_t pin )
{
	reg->BSRR = (1 << pin);
}
inline void clear_pin( GPIO_TypeDef* reg, uint8_t pin )
{
	reg->BSRR = (uint32_t)((1 << pin) << WORD_BITS);
}
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	if(bit_n > H_BIT){ bit_n = L_BIT; reg = 0; }
	else{
		uint32_t mask = (uint32_t)((1 << size_block) - 1);
		reg &= (mask << bit_n);
		reg = (reg >> bit_n);
	}
	return reg;
}
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	if(bit_n > H_BIT){ bit_n = H_BIT; }
	else{
		uint32_t value = *reg;
		uint32_t mask = (uint32_t)((1 << size_block) - 1);
		data &= mask; value &= ~(mask << bit_n);
		data = (data << bit_n);
		value |= data;
		*reg = value;
	}
}
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	if(bit_n > H_BIT){ bit_n = H_BIT; }
	else{
		uint32_t mask = (uint32_t)((1 << size_block) - 1);
		data &= mask;
		*reg &= ~(mask << bit_n);
		*reg |= (data << bit_n);
	}
}
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n)
{
	uint32_t value;
	if(size_block > N_BITS){ size_block = N_BITS; }
	uint32_t n = bit_n / N_BITS; bit_n = bit_n % N_BITS;
	value = *(reg + n );
	uint32_t mask = (uint32_t)((1 << size_block) - 1);
	value &= (mask << bit_n);
	value = (value >> bit_n);
	return value;
}
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	uint32_t n = bit_n / N_BITS; bit_n = bit_n % N_BITS;
	uint32_t mask = (uint32_t)((1 << size_block) - 1);
	data &= mask;
	*(reg + n ) &= ~(mask << bit_n);
	*(reg + n ) |= (data << bit_n);
}
void STM32446SetRegBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > L_BIT && n_bits < N_LIMBITS){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg |= (uint32_t)(1 << va_arg(list, uint32_t));
		}
		va_end(list);
	}
}
void STM32446ResetRegBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > L_BIT && n_bits < N_LIMBITS){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg &= (uint32_t)~((1 << va_arg(list, uint32_t)) << WORD_BITS);
		}
		va_end(list);
	}
}
void STM32446VecSetup( volatile uint32_t vec[], unsigned int size_block, unsigned int block_n, unsigned int data )
{
	const unsigned int n_bits = sizeof(data) * BYTE_BITS;
	if(size_block > n_bits){ size_block = n_bits; }
	const unsigned int mask = (uint32_t) ((1 << size_block) - 1);
	unsigned int index = (block_n * size_block) / n_bits;
	data &= mask;
	vec[index] &= ~( mask << ((block_n * size_block) - (index * n_bits)) );
	vec[index] |= ( data << ((block_n * size_block) - (index * n_bits)) );
}
void delay_Configure(void)
{
    uint32_t DelayCounter_top;

    // Calculate DelayCounter_top once for both STM32 families
    DelayCounter_top = getsysclk() / gethpre(); // Assuming gethpre() returns a valid prescaler

    // Calculate the SysTick values for different delay intervals
    systick_us 		= DelayCounter_top / 1000000 - 1 ; // 1 microsecond
    systick_10us 	= DelayCounter_top / 100000 - 1 ;  // 10 microseconds
    systick_100us 	= DelayCounter_top / 10000 - 1 ;   // 100 microseconds
    systick_ms 		= DelayCounter_top / 1000 - 1 ;    // 1 millisecond
    if(systick_us > 0);else systick_us = 1;
    if(systick_10us > 0);else systick_10us = 1;
    if(systick_100us > 0);else systick_100us = 1;
    if(systick_ms > 0);else systick_ms = 1;
}
inline uint32_t get_systick_us(void)
{
	return systick_us;
}
inline uint32_t get_systick_10us(void)
{
	return systick_10us;
}
inline uint32_t get_systick_ms(void)
{
	return systick_ms;
}
void delayMiliseconds(unsigned int ms) {
    volatile unsigned int count = ms * get_systick_ms( );
    while (count--);
}
void delayMicroseconds(unsigned int us) {
    volatile unsigned int count = us * get_systick_us( );
    while (count--);
}
void delayAsmMicroseconds(unsigned int us) {
    // Adjust the loop count accordingly
    unsigned int count = us * get_systick_us( ); // Rough estimate for timing

    __asm volatile (
        "1: \n"                    // Label 1
        "subs %[count], %[count], #1 \n" // Decrement count
        "bne 1b \n"                // Branch to label 1 if count is not zero
        : [count] "+r" (count)     // Input/output operand
    );
}

/****** MISCELLANEOUS ******/
void ADC_TemperatureSetup(void){
	uint8_t countdown;
	/********** ADC1 **********/
	//stm()->adc1->clock(on);
	set_reg_Msk(&RCC->APB2ENR, RCC_APB2ENR_ADC1EN_Msk, RCC_APB2ENR_ADC1EN_Pos, ON);
	ADC1->CR1 = 0;
	set_reg_Msk(&ADC1->SQR1, ADC_SQR1_L, ADC_SQR1_L_Pos, 0);
	set_reg_Msk(&ADC1->SQR3, ADC_SQR3_SQ1, ADC_SQR3_SQ1_Pos, 18);
	set_reg_Msk(&ADC1->SMPR1, ADC_SMPR1_SMP18, ADC_SMPR1_SMP18_Pos, 3);
	//set_reg_Msk(&ADC1->CR2, ADC_CR2_CONT, ADC_CR2_CONT_Pos, ON);
	//set_reg_Msk(&ADC->CCR, ADC_CCR_VBATE, ADC_CCR_VBATE_Pos, ON);
	set_reg_Msk(&ADC->CCR, ADC_CCR_TSVREFE, ADC_CCR_TSVREFE_Pos, ON);
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, ON);
	for(countdown = 15; countdown; countdown --); // t_STAB
}
uint16_t ADC_ReadTemperature(void) {
	uint16_t adc_value;
    set_reg_Msk(&ADC1->CR2, ADC_CR2_SWSTART, ADC_CR2_SWSTART_Pos, ON);
    while (!get_reg_Msk(ADC1->SR, ADC_SR_EOC, ADC_SR_EOC_Pos));
    adc_value = ADC1->DR;
    return adc_value;
}
float CalculateTemperature(uint16_t adc_value) {
    const float V_25 = 0.76f;  // Voltage at 25°C (in volts)
    const float Avg_slope = 0.0025f;  // Average slope (in volts/°C)
    const float V_ref = 3.3f;  // Reference voltage, typically 3.0V or 3.3V

    float V_sense = ((float)adc_value / 4096) * V_ref;
    float temperature = ((V_sense - V_25) / Avg_slope) + 25.0f;

    return temperature;
}

const char* WeekDay_String(uint8_t weekday_n) {
    // Array of weekday strings, indexed from 0 to 7 for convenience
    const char* weekdays[] = {
        "Domingo", // 0 (unused)
        "Domingo", // 1
        "Segunda", // 2
        "Terca",   // 3
        "Quarta",  // 4
        "Quinta",  // 5
        "Sexta",   // 6
        "Sabado"   // 7
    };

    // Validate the input and return the corresponding weekday
    if (weekday_n >= 1 && weekday_n <= 7) {
        return weekdays[weekday_n];
    } else {
        return weekdays[1]; // Default to "domingo"
    }
}

void Usart_WordLength(USART_TypeDef* usart, uint8_t wordlength) {
    // Clear the M bit to reset word length
    usart->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
        usart->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart_StopBits(USART_TypeDef* usart, double stopbits) {
    // Reset stop bits configuration
    usart->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
        usart->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
        usart->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
        usart->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart_SamplingMode(USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        usart->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
        usart->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    usart->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    usart->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    usart->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}

/******
n = bit_n/32; bit_n = bit_n - (n * 32); -> bit_n = bit_n % 32;
(a+b)/a = a/a + b/a = 1 + b/a
a/b/c/d/e = a/(b*c*d*e)
*******/

/***EOF***/

