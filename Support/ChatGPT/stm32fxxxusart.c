#include "stm32fxxxuart.h"

/*** File Variable ***/
static STM32FXXX_USART1 stm32fxxx_usart1;
static STM32FXXX_USART2 stm32fxxx_usart2;
static STM32FXXX_USART6 stm32fxxx_usart6;

/*** USART Procedure & Function Definition ***/
/*************/
/*** USART1 ***/
/*************/
void STM32FXXXUsart1Clock(uint8_t state)
{
	if(state) { RCC->APB2ENR |= (1 << 14); } // Enable USART1 clock
	else { RCC->APB2ENR &= ~(1 << 14); } // Disable USART1 clock
}

void STM32FXXXUsart1Nvic(uint8_t state)
{
	if(state) { set_bit_block(NVIC->ISER, 1, USART1_IRQn, 1); }
	else { set_bit_block(NVIC->ICER, 1, USART1_IRQn, 1); }
}

/*************/
/*** USART2 ***/
/*************/
void STM32FXXXUsart2Clock(uint8_t state)
{
	if(state) { RCC->APB1ENR |= (1 << 17); } // Enable USART2 clock
	else { RCC->APB1ENR &= ~(1 << 17); } // Disable USART2 clock
}

void STM32FXXXUsart2Nvic(uint8_t state)
{
	if(state) { set_bit_block(NVIC->ISER, 1, USART2_IRQn, 1); }
	else { set_bit_block(NVIC->ICER, 1, USART2_IRQn, 1); }
}

/*************/
/*** USART6 ***/
/*************/
void STM32FXXXUsart6Clock(uint8_t state)
{
	if(state) { RCC->APB2ENR |= (1 << 5); } // Enable USART6 clock
	else { RCC->APB2ENR &= ~(1 << 5); } // Disable USART6 clock
}

void STM32FXXXUsart6Nvic(uint8_t state)
{
	if(state) { set_bit_block(NVIC->ISER, 1, USART6_IRQn, 1); }
	else { set_bit_block(NVIC->ICER, 1, USART6_IRQn, 1); }
}

/*** USART Configuration Functions ***/
void STM32FXXXUsartSetBaudrate(USART_TypeDef* instance, uint32_t baudrate)
{
	uint32_t clock = 16000000; // Assuming 16 MHz clock for example
	instance->BRR = (clock + (baudrate / 2)) / baudrate; // Baud rate calculation
}

void Usart_WordLength(USART_TypeDef* usart, uint8_t wordlength)
{
	// Clear the M bit to reset word length
	usart->CR1 &= ~(1 << 12);

	if (wordlength == 9) {
		usart->CR1 |= (1 << 12); // Set M bit for 9-bit word length
	}
	// If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart_StopBits(USART_TypeDef* usart, double stopbits)
{
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

/*** USART1 Procedure & Function Definition ***/
STM32FXXX_USART1* usart1_enable(void)
{
	/*** USART1 Bit Mapping Link ***/
	stm32fxxx_usart1.instance = USART1;
	// CLOCK
	stm32fxxx_usart1.clock = STM32FXXXUsart1Clock;
	// NVIC
	stm32fxxx_usart1.nvic = STM32FXXXUsart1Nvic;
	// Configuration functions
	stm32fxxx_usart1.set_baudrate = STM32FXXXUsartSetBaudrate;
	stm32fxxx_usart1.set_word_length = Usart_WordLength;
	stm32fxxx_usart1.set_sampling_mode = Usart_SamplingMode;
	stm32fxxx_usart1.set_stop_bits = Usart_StopBits;

	return &stm32fxxx_usart1;
}

STM32FXXX_USART1* usart1(void) { return (STM32FXXX_USART1*)&stm32fxxx_usart1; }

/*** USART2 Procedure & Function Definition ***/
STM32FXXX_USART2* usart2_enable(void)
{
	/*** USART2 Bit Mapping Link ***/
	stm32fxxx_usart2.instance = USART2;
	// CLOCK
	stm32fxxx_usart2.clock = STM32FXXXUsart2Clock;
	// NVIC
	stm32fxxx_usart2.nvic = STM32FXXXUsart2Nvic;
	// Configuration functions
	stm32fxxx_usart2.set_baudrate = STM32FXXXUsartSetBaudrate;
	stm32fxxx_usart2.set_word_length = Usart_WordLength;
	stm32fxxx_usart2.set_sampling_mode = Usart_SamplingMode;
	stm32fxxx_usart2.set_stop_bits = Usart_StopBits;

	return &stm32fxxx_usart2;
}

STM32FXXX_USART2* usart2(void) { return (STM32FXXX_USART2*)&stm32fxxx_usart2; }

/*** USART6 Procedure & Function Definition ***/
STM32FXXX_USART6* usart6_enable(void)
{
	/*** USART6 Bit Mapping Link ***/
	stm32fxxx_usart6.instance = USART6;
	// CLOCK
	stm32fxxx_usart6.clock = STM32FXXXUsart6Clock;
	// NVIC
	stm32fxxx_usart6.nvic = STM32FXXXUsart6Nvic;
	// Configuration functions
	stm32fxxx_usart6.set_baudrate = STM32FXXXUsartSetBaudrate;
	stm32fxxx_usart6.set_word_length = Usart_WordLength;
	stm32fxxx_usart6.set_sampling_mode = Usart_SamplingMode;
	stm32fxxx_usart6.set_stop_bits = Usart_StopBits;

	return &stm32fxxx_usart6;
}

STM32FXXX_USART6* usart6(void) { return (STM32FXXX_USART6*)&stm32fxxx_usart6; }

/*** Interrupt Handlers ***/
void USART1_IRQHandler(void)
{
	// USART1 interrupt handling code
}

void USART2_IRQHandler(void)
{
	// USART2 interrupt handling code
}

void USART6_IRQHandler(void)
{
	// USART6 interrupt handling code
}
