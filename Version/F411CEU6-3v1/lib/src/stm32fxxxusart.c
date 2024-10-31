/******************************************************************************
	STM32 XXX USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 24022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart.h"
#include <string.h>
#include <math.h>

/*** Define and Macro ***/
//#define UART_NULL
#ifndef ZERO
	#define ZERO 0
#endif
#ifndef ONE
	#define ONE 1
#endif
/*** File Variable ***/
#ifdef STM32F446xx
	static STM32FXXX_USART3 stm32fxxx_usart3 = {ZERO};
	static STM32FXXX_UART4 stm32fxxx_uart4 = {ZERO};
	static STM32FXXX_UART5 stm32fxxx_uart5 = {ZERO};
#endif
/******/
#define RX_BUFFER_LIM (RX_BUFFER_SIZE + ONE)
#define TX_BUFFER_LIM (TX_BUFFER_SIZE + ONE)
// Buffer for received and transmit data
uint8_t rx_buffer[RX_BUFFER_LIM];
volatile uint16_t rx_index = ZERO;
uint8_t tx_buffer[TX_BUFFER_LIM];
volatile uint16_t tx_index = ZERO;
/*** USART Procedure & Function Definition ***/
#ifdef STM32F446xx
/*** USART3 ***/
void STM32FXXXUsart3Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_USART3EN_Pos); }else{ RCC->APB1ENR &= ~(1 << RCC_APB1ENR_USART3EN_Pos); }
}
void STM32FXXXUsart3Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART3_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART3_IRQn, 1); }
}
void Usart3_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART3->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART3->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart3_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART3->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART3->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART3->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART3->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}

void Usart3_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART3->CR1 |= (1 << USART_CR1_OVER8_Pos); // Set OVER8 for 8 times oversampling
    } else {
    	USART3->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART3->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART3->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART3->BRR |= ((uint32_t) intpart << USART_BRR_DIV_Mantissa_Pos); // Set DIV_Mantissa[11:0]
}
void USART3_start(void) { USART3->CR1 |= USART_CR1_UE; }
void USART3_stop(void) { USART3->CR1 &= ~USART_CR1_UE; }
/*** UART4 ***/
void STM32FXXXUart4Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_UART4EN_Pos); }else{ RCC->APB1ENR &= ~(1 << RCC_APB1ENR_UART4EN_Pos); }

}
void STM32FXXXUart4Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, UART4_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, UART4_IRQn, 1); }
}
void Usart4_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART4->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART4->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart4_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART4->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART4->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART4->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART4->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}

void Usart4_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART4->CR1 |= (1 << USART_CR1_OVER8_Pos); // Set OVER8 for 8 times oversampling
    } else {
    	USART4->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART4->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART4->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART4->BRR |= ((uint32_t) intpart << USART_BRR_DIV_Mantissa_Pos); // Set DIV_Mantissa[11:0]
}
void UART4_start(void) { USART4->CR1 |= USART_CR1_UE; }
void UART4_stop(void) { USART4->CR1 &= ~USART_CR1_UE; }
/*** UART5 ***/
void STM32FXXXUart5Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_UART5EN_Pos); } // UART5EN: USART5 clock enable
	else{ RCC->APB1ENR &= ~(1 << RCC_APB1ENR_UART5EN_Pos); } // UART5EN: USART5 clock disable
}
void STM32FXXXUart5Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, UART5_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, UART5_IRQn, 1); }
}
void Usart5_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART5->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART5->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart5_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART5->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART5->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART5->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART5->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}

void Usart5_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART5->CR1 |= (1 << USART_CR1_OVER8_Pos); // Set OVER8 for 8 times oversampling
    } else {
    	USART5->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART5->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART5->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART5->BRR |= ((uint32_t) intpart << USART_BRR_DIV_Mantissa_Pos); // Set DIV_Mantissa[11:0]
}
void UART5_start(void) { USART5->CR1 |= USART_CR1_UE; }
void UART5_stop(void) { USART5->CR1 &= ~USART_CR1_UE; }
#endif

#ifdef STM32F446xx
/*** USART3 INIC Procedure & Function Definition ***/
void usart3_enable(void)
{
	STM32FXXXUsart3Clock( ON );
	/*** USART3 Bit Mapping Link ***/
	#ifdef STM32F446xx
		stm32fxxx_usart3.instance = USART3;
	#else
		stm32fxxx_usart3.instance = NULL;
	#endif
	// Other
	stm32fxxx_usart3.clock = STM32FXXXUsart3Clock;
	stm32fxxx_usart3.nvic = STM32FXXXUsart3Nvic;
	stm32fxxx_usart3.wordlength = Usart3_WordLength;
	stm32fxxx_usart3.stopbits = Usart3_StopBits;
	stm32fxxx_usart3.samplingmode = Usart3_SamplingMode;
	stm32fxxx_usart3.tx_enable = NULL;
	stm32fxxx_usart3.tx_disable = NULL;
	stm32fxxx_usart3.rx_enable = NULL;
	stm32fxxx_usart3.transmit_disable = NULL;
	stm32fxxx_usart3.send_char = NULL;
	stm32fxxx_usart3.receive_char = NULL;
	stm32fxxx_usart3.start = USART3_start;
	stm32fxxx_usart3.stop = USART3_stop;
	//return &stm32fxxx_usart3;
}

STM32FXXX_USART3*  usart3(void){ return (STM32FXXX_USART3*) &stm32fxxx_usart3; }

/*** UART4 INIC Procedure & Function Definition ***/
void uart4_enable(void)
{
	STM32FXXXUsart4Clock( ON );
	/*** UART4 Bit Mapping Link ***/
	#ifdef STM32F446xx
		stm32fxxx_uart4.instance = UART4;
	#else
		stm32fxxx_uart4.instance = NULL;
	#endif
	// Other
	stm32fxxx_uart4.clock = STM32FXXXUart4Clock;
	stm32fxxx_uart4.nvic = STM32FXXXUart4Nvic;
	stm32fxxx_uart4.wordlength = Usart4_WordLength;
	stm32fxxx_uart4.stopbits = Usart4_StopBits;
	stm32fxxx_uart4.samplingmode = Usart4_SamplingMode;
	stm32fxxx_uart4.tx_enable = NULL;
	stm32fxxx_uart4.tx_disable = NULL;
	stm32fxxx_uart4.rx_enable = NULL;
	stm32fxxx_uart4.rx_disable = NULL;
	stm32fxxx_uart4.transmit_char = NULL;
	stm32fxxx_uart4.receive_char = NULL;
	stm32fxxx_uart4.start = USART4_start;
	stm32fxxx_uart4.stop = USART4_stop;

	//return &stm32fxxx_uart4;
}

STM32FXXX_UART4*  uart4(void){ return (STM32FXXX_UART4*) &stm32fxxx_uart4; }

/*** UART5 INIC Procedure & Function Definition ***/
void uart5_enable(void)
{
	STM32FXXXUsart5Clock( ON );
	/*** UART5 Bit Mapping Link ***/
	#ifdef STM32F446xx
		stm32fxxx_uart5.instance = UART5;
	#else
		stm32fxxx_uart5.instance = NULL;
	#endif
	// Other
	stm32fxxx_uart5.clock = STM32FXXXUart5Clock;
	stm32fxxx_uart5.nvic = STM32FXXXUart5Nvic;
	stm32fxxx_uart5.wordlength = Usart5_WordLength;
	stm32fxxx_uart5.stopbits = Usart5_StopBits;
	stm32fxxx_uart5.samplingmode = Usart5_SamplingMode;
	stm32fxxx_uart5.tx_enable = NULL;
	stm32fxxx_uart5.tx_disable = NULL;
	stm32fxxx_uart5.rx_enable = NULL;
	stm32fxxx_uart5.rx_disable = NULL;
	stm32fxxx_uart5.transmit_char = NULL;
	stm32fxxx_uart5.receive_char = NULL;
	stm32fxxx_uart5.start = USART5_start;
	stm32fxxx_uart5.stop = USART5_stop;
	//return &stm32fxxx_uart5;
}

STM32FXXX_UART5*  uart5(void){ return (STM32FXXX_UART5*) &stm32fxxx_uart5; }

#endif

/*** EOF ***/

