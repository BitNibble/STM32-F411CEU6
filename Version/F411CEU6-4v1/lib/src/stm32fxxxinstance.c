/*****************************************
	STM32FXXX INSTANCE
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32FXXX
Update: 07/01/2024
Comment:
	
*****************************************/
#include "stm32fxxxinstance.h"
#include <stdarg.h>
#include <math.h>

/****************************************/
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define DWORD_BITS 32
#define QWORD_BITS 64
/****************************************/
/*** Tools ***/
inline void set_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg |= hbits;
}
inline void clear_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg &= ~hbits;
}
inline uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk, uint8_t Pos)
{
	uint32_t filter = ONE << Pos;
	if(Msk & filter){
		reg = (reg & Msk) >> Pos;
	}
	return reg;
}
inline void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data)
{
	uint32_t value = *reg;
	uint32_t filter = ONE << Pos;
	if(Msk & filter){
		data = (data << Pos) & Msk; value &= ~(Msk); value |= data; *reg = value;
	}
}
inline void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data)
{
	uint32_t filter = ONE << Pos;
	if(Msk & filter){
		data = (data << Pos) & Msk; *reg &= ~(Msk); *reg |= data;
	}
}
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n)
{
	if(bit_n < DWORD_BITS &&  size_block != 0 && bit_n + size_block <= DWORD_BITS) {
		uint32_t mask = (uint32_t)((1U << size_block) - 1);
		reg = (reg & (mask << bit_n)) >> bit_n;
	}
	return reg;
}
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	uint32_t value = *reg;
	if(bit_n < DWORD_BITS &&  size_block != 0 && bit_n + size_block <= DWORD_BITS) {
		uint32_t mask = (uint32_t)((1U << size_block) - 1);
		data &= mask; value &= ~(mask << bit_n);
		data = (data << bit_n);
		value |= data;
		*reg = value;
	}
}
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(bit_n < DWORD_BITS &&  size_block != 0 && bit_n + size_block <= DWORD_BITS) {
		uint32_t mask = (uint32_t)((1U << size_block) - 1);
		data &= mask;
		*reg &= ~(mask << bit_n);
		*reg |= (data << bit_n);
	}
}
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n)
{
	uint32_t value;
	uint32_t n = bit_n / DWORD_BITS; bit_n = bit_n % DWORD_BITS;
	value = *(reg + n );
	if(size_block != 0 && bit_n + size_block <= DWORD_BITS){
		uint32_t mask = (uint32_t)((1U << size_block) - 1);
		value = (value & (mask << bit_n)) >> bit_n;
	}
	return value;
}
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	uint32_t n = bit_n / DWORD_BITS; bit_n = bit_n % DWORD_BITS;
	if(size_block != 0 && bit_n + size_block <= DWORD_BITS) {
		uint32_t mask = (uint32_t)((1U << size_block) - 1);
		data &= mask;
		*(reg + n ) &= ~(mask << bit_n);
		*(reg + n ) |= (data << bit_n);
	}
}
/****************************************/
// IO
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
/****************************************/
// UNUSED
void STM32446SetRegBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > ZERO && n_bits <= DWORD_BITS){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg |= (uint32_t)(1 << va_arg(list, int));
		}
		va_end(list);
	}
}
void STM32446ResetRegBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > ZERO && n_bits <= DWORD_BITS){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg &= (uint32_t)~(1 << va_arg(list, int));
		}
		va_end(list);
	}
}
void STM32446VecSetup( volatile uint32_t vec[], unsigned int size_block, unsigned int block_n, unsigned int data )
{
	const unsigned int n_bits = sizeof(data) * BYTE_BITS;
	if(size_block > n_bits){ size_block = n_bits; }
	const unsigned int mask = (uint32_t) ((1U << size_block) - 1);
	unsigned int index = (block_n * size_block) / n_bits;
	data &= mask;
	vec[index] &= ~( mask << ((block_n * size_block) - (index * n_bits)) );
	vec[index] |= ( data << ((block_n * size_block) - (index * n_bits)) );
}

/************ MISCELLANEOUS *************/
/*** Clock ***/
uint16_t gethpre(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 4, RCC_CFGR_HPRE_Pos);
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
	uint32_t value = get_reg_block(RCC->CFGR, 3, RCC_CFGR_PPRE1_Pos);
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
	uint32_t value = get_reg_block(RCC->CFGR, 3, RCC_CFGR_PPRE2_Pos);
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
	return get_reg_block(RCC->CFGR, 5, RCC_CFGR_RTCPRE_Pos);
}
uint8_t gethmco1pre(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 3, RCC_CFGR_MCO1PRE_Pos);
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
	uint32_t value = get_reg_block(RCC->CFGR, 3, RCC_CFGR_MCO2PRE_Pos);
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
	return get_reg_block(RCC->PLLCFGR, 6, RCC_PLLCFGR_PLLM_Pos);
}
uint16_t getplln(void)
{
	return get_reg_block(RCC->PLLCFGR, 9, RCC_PLLCFGR_PLLN_Pos);
}
uint8_t getpllp(void)
{
	uint32_t value = get_reg_block(RCC->PLLCFGR, 2, RCC_PLLCFGR_PLLP_Pos);
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
	return get_reg_block(RCC->PLLCFGR, 4, RCC_PLLCFGR_PLLQ_Pos);
}
#ifdef STM32F446xx
	uint8_t getpllr(void)
	{
		return get_reg_block(RCC->PLLCFGR, 3, RCC_PLLCFGR_PLLR_Pos);
	}
#endif
uint32_t getpllsourceclk(void)
{
	uint32_t source;
	if( get_reg_block(RCC->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos) ) source = HSE_OSC; else source = HSI_RC;
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
	uint32_t value = get_reg_block(RCC->CFGR, 2, RCC_CFGR_SWS_Pos);
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
/****************************************/
/*** NULL Check ***/
int isPtrNull(void* ptr) {
    return (ptr == NULL) ? 1 : 0; // Returns 1 if NULL, 0 otherwise
}
/*** FPU ***/
void fpu_enable(void) {
    // Set the CP10 and CP11 bits to enable access to the FPU
    uint32_t cpacr = SCB->CPACR; // Accessing the CPACR register
    cpacr |= (0xF << 20); // Set bits 20-23 to enable FPU for all modes
    SCB->CPACR = cpacr; // Write back to CPACR
}
/*** ADC ***/
float CalculateTemperature(uint16_t adc_value) {
    const float V_25 = 0.76f;  // Voltage at 25°C (in volts)
    const float Avg_slope = 0.0025f;  // Average slope (in volts/°C)
    const float V_ref = 3.3f;  // Reference voltage, typically 3.0V or 3.3V

    float V_sense = ((float)adc_value / 4096) * V_ref;
    float temperature = ((V_sense - V_25) / Avg_slope) + 25.0f;

    return temperature;
}
/*** General USART Function Definitions ***/
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
/****************************************/
/***
TypeDef -> Instance -> Handler
bit_n = bit_n % DWORD_BITS; is the same as bit_n = bit_n & (DWORD_BITS - 1);, for power of two numbers.
General behavior for filtering inputs, is if does not pass the filter it is to be ignored and not make
any changes, leaving everything as was. Maybe think later to just give a signal warning.
***/

/*** EOF ***/
