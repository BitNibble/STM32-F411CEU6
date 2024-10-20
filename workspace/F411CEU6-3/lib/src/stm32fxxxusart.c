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
/*** File Variable ***/
static STM32FXXX_USART1 stm32fxxx_usart1 = {0};
static STM32FXXX_USART2 stm32fxxx_usart2 = {0};
#ifdef STM32F446xx
	static STM32FXXX_USART3 stm32fxxx_usart3 = {0};
	static STM32FXXX_UART4 stm32fxxx_uart4 = {0};
	static STM32FXXX_UART5 stm32fxxx_uart5 = {0};
#endif
static STM32FXXX_USART6 stm32fxxx_usart6 = {0};
/******/
#define RX_BUFFER_LIM (RX_BUFFER_SIZE + 1)
#define TX_BUFFER_LIM (TX_BUFFER_SIZE + 1)
// Buffer for received and transmit data
uint8_t rx_buffer[RX_BUFFER_LIM];
volatile uint16_t rx_index = 0;
uint8_t tx_buffer[TX_BUFFER_LIM];
volatile uint16_t tx_index = 0;
/*** USART Procedure & Function Definition ***/
void Usart3_WordLength(uint8_t wordlength);
void Usart3_StopBits(double stopbits);
void Usart3_SamplingMode(uint8_t samplingmode, uint32_t baudrate);
void Usart4_WordLength(uint8_t wordlength);
void Usart4_StopBits(double stopbits);
void Usart4_SamplingMode(uint8_t samplingmode, uint32_t baudrate);
void Usart5_WordLength(uint8_t wordlength);
void Usart5_StopBits(double stopbits);
void Usart5_SamplingMode(uint8_t samplingmode, uint32_t baudrate);
/*** USART1 ***/
void STM32FXXXUsart1Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos); }else{ RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART1EN_Pos); }
}
void STM32FXXXUsart1Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART1_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART1_IRQn, 1); }
}
void Usart1_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART1->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART1->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}
void Usart1_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART1->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART1->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART1->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART1->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}
void Usart1_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART1->CR1 |= (1 << USART_CR1_OVER8_Pos); // Set OVER8 for 8 times oversampling
    } else {
    	USART1->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART1->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART1->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART1->BRR |= ((uint32_t) intpart << USART_BRR_DIV_Mantissa_Pos); // Set DIV_Mantissa[11:0]
}
void USART1_TxEnable(void) { USART1->CR1 |= USART_CR1_TE; }
void USART1_TxDisable(void) { USART1->CR1 &= ~USART_CR1_TE; }
void USART1_RxEnable(void) { USART1->CR1 |= USART_CR1_RE; }
void USART1_RxDisable(void) { USART1->CR1 &= ~USART_CR1_RE; }
void USART1_SendChar(char c) {
	USART1->CR1 &= ~USART_CR1_TXEIE;
    while (!(USART1->SR & USART_SR_TXE)); // Wait until TX is empty
    USART1->DR = c;                       // Send the character
}
char USART1_ReceiveChar(void) {
	USART1->CR1 &= ~USART_CR1_RXNEIE;
    while (!(USART1->SR & USART_SR_RXNE)); // Wait until RX is ready
    return (char)USART1->DR;               // Return the received character
}
void USART1_SendString(const char *str) {
    // Copy the string into the transmit buffer
    strcpy((char *)tx_buffer, str); // Ensure tx_buffer is big enough
    // Enable the TXE interrupt to start sending data
    USART1->CR1 |= USART_CR1_TXEIE;
}
void USART1_start(void) { USART1->CR1 |= USART_CR1_UE; }
void USART1_stop(void) { USART1->CR1 &= ~USART_CR1_UE; }
/*** USART2 ***/
void STM32FXXXUsart2Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_USART2EN_Pos); }else{ RCC->APB1ENR &= ~(1 << RCC_APB1ENR_USART2EN_Pos); }
}
void STM32FXXXUsart2Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART2_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART2_IRQn, 1); }
}
void Usart2_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART2->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART2->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart2_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART2->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART2->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART2->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART2->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}

void Usart2_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART2->CR1 |= (1 << USART_CR1_OVER8_Pos); // Set OVER8 for 8 times oversampling
    } else {
    	USART2->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART2->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART2->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART2->BRR |= ((uint32_t) intpart << USART_BRR_DIV_Mantissa_Pos); // Set DIV_Mantissa[11:0]
}
void USART2_start(void) { USART2->CR1 |= USART_CR1_UE; }
void USART2_stop(void) { USART2->CR1 &= ~USART_CR1_UE; }
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
/*** USART6 ***/
void STM32FXXXUsart6Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << RCC_APB2ENR_USART6EN_Pos); }else{ RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART6EN_Pos); }
}
void STM32FXXXUsart6Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART6_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART6_IRQn, 1); }
}
void Usart6_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART6->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART6->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}
void Usart6_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART6->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART6->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART6->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART6->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}
void Usart6_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART6->CR1 |= (1 << USART_CR1_OVER8_Pos); // Set OVER8 for 8 times oversampling
    } else {
    	USART6->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART6->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART6->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART6->BRR |= ((uint32_t) intpart << USART_BRR_DIV_Mantissa_Pos); // Set DIV_Mantissa[11:0]
}
void USART6_start(void) { USART6->CR1 |= USART_CR1_UE; }
void USART6_stop(void) { USART6->CR1 &= ~USART_CR1_UE; }
/*** USART1 INIC Procedure & Function Definition ***/
void usart1_enable(void)
{
	STM32FXXXUsart1Clock( ON );
	/*** USART1 Bit Mapping Link ***/
	stm32fxxx_usart1.instance = USART1;
	// Other
	stm32fxxx_usart1.clock = STM32FXXXUsart1Clock;
	stm32fxxx_usart1.nvic = STM32FXXXUsart1Nvic;
	stm32fxxx_usart1.wordlength = Usart1_WordLength;
	stm32fxxx_usart1.stopbits = Usart1_StopBits;
	stm32fxxx_usart1.samplingmode = Usart1_SamplingMode;
	stm32fxxx_usart1.tx_enable = USART1_TxEnable;
	stm32fxxx_usart1.tx_disable = USART1_TxDisable;
	stm32fxxx_usart1.rx_enable = USART1_RxEnable;
	stm32fxxx_usart1.rx_disable = USART1_RxDisable;
	stm32fxxx_usart1.send_char = USART1_SendChar;
	stm32fxxx_usart1.receive_char = USART1_ReceiveChar;
	stm32fxxx_usart1.tx_buff = (char*)tx_buffer;
	stm32fxxx_usart1.rx_buff = (char*)rx_buffer;
	stm32fxxx_usart1.send_string = USART1_SendString;
	stm32fxxx_usart1.start = USART1_start;
	stm32fxxx_usart1.stop = USART1_stop;
	// Inic
	tx_buffer[TX_BUFFER_LIM] = ZERO;
	rx_buffer[RX_BUFFER_LIM] = ZERO;
	//return &stm32fxxx_usart1;
}

STM32FXXX_USART1*  usart1(void){ return (STM32FXXX_USART1*) &stm32fxxx_usart1; }

/*** USART2 INIC Procedure & Function Definition ***/
void usart2_enable(void)
{
	STM32FXXXUsart2Clock( ON );
	/*** USART2 Bit Mapping Link ***/
	stm32fxxx_usart2.instance = USART2;
	// Other
	stm32fxxx_usart2.clock = STM32FXXXUsart2Clock;
	stm32fxxx_usart2.nvic = STM32FXXXUsart2Nvic;
	stm32fxxx_usart2.wordlength = Usart2_WordLength;
	stm32fxxx_usart2.stopbits = Usart2_StopBits;
	stm32fxxx_usart2.samplingmode = Usart2_SamplingMode;
	stm32fxxx_usart2.tx_enable = NULL;
	stm32fxxx_usart2.tx_disable = NULL;
	stm32fxxx_usart2.rx_enable = NULL;
	stm32fxxx_usart2.rx_disable = NULL;
	stm32fxxx_usart2.send_char = NULL;
	stm32fxxx_usart2.receive_char = NULL;
	stm32fxxx_usart2.start = USART2_start;
	stm32fxxx_usart2.stop = USART2_stop;
	//return &stm32fxxx_usart2;
}

STM32FXXX_USART2*  usart2(void){ return (STM32FXXX_USART2*) &stm32fxxx_usart2; }

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
	stm32fxxx_usart3.rx_disable = NULL;
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
	stm32fxxx_uart4.send_char = NULL;
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
	stm32fxxx_uart5.send_char = NULL;
	stm32fxxx_uart5.receive_char = NULL;
	stm32fxxx_uart5.start = USART5_start;
	stm32fxxx_uart5.stop = USART5_stop;
	//return &stm32fxxx_uart5;
}

STM32FXXX_UART5*  uart5(void){ return (STM32FXXX_UART5*) &stm32fxxx_uart5; }

#endif

/*** USART6 INIC Procedure & Function Definition ***/
void usart6_enable(void)
{
	STM32FXXXUsart6Clock( ON );
	/*** USART6 Bit Mapping Link ***/
	stm32fxxx_usart6.instance = USART6;
	// Other
	stm32fxxx_usart6.clock = STM32FXXXUsart6Clock;
	stm32fxxx_usart6.nvic = STM32FXXXUsart6Nvic;
	stm32fxxx_usart6.wordlength = Usart6_WordLength;
	stm32fxxx_usart6.stopbits = Usart6_StopBits;
	stm32fxxx_usart6.samplingmode = Usart6_SamplingMode;
	stm32fxxx_usart6.tx_enable = NULL;
	stm32fxxx_usart6.tx_disable = NULL;
	stm32fxxx_usart6.rx_enable = NULL;
	stm32fxxx_usart6.rx_disable = NULL;
	stm32fxxx_usart6.send_char = NULL;
	stm32fxxx_usart6.receive_char = NULL;
	stm32fxxx_usart6.start = USART6_start;
	stm32fxxx_usart6.stop = USART6_stop;
	//return &stm32fxxx_usart6;
}

STM32FXXX_USART6*  usart6(void){ return (STM32FXXX_USART6*) &stm32fxxx_usart6; }

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

/*** Interrupt handler for USART1 ***/
void USART1_IRQHandler(void) {

	if(USART1->CR1 & USART_CR1_RXNEIE) {
		// Check if the RXNE (Receive Not Empty) flag is set
		if (USART1->SR & USART_SR_RXNE) {
			uint8_t received_byte = USART1->DR;
			// Handle received data
			//if (received_byte && received_byte != '\r' && received_byte != '\n') {
			if (received_byte && received_byte != '\n') {
				if (rx_index < RX_BUFFER_SIZE) {
					rx_buffer[rx_index++] = received_byte;
				}
			}else {
				rx_buffer[rx_index] = ZERO;
				rx_index = ZERO;
			}
		}
	}

	if(USART1->CR1 & USART_CR1_TXEIE) {
		// Check if the TXE (Transmit Data Register Empty) flag is set
		if (USART1->SR & USART_SR_TXE) {
			if(tx_buffer[tx_index]) {
				// Disable TXE interrupt if no more data to transmit
				if (tx_index < TX_BUFFER_SIZE) {
					// Transmit the next byte if available
					USART1->DR = tx_buffer[tx_index++];
				}else {
					USART1->CR1 &= ~USART_CR1_TXEIE;
					tx_index = ZERO;
					tx_buffer[tx_index] = ZERO;
				}
			}else{
				#ifdef UART_NULL
					USART1->DR = 0;
				#endif
				tx_index = ZERO;
				tx_buffer[tx_index] = ZERO;
				USART1->CR1 &= ~USART_CR1_TXEIE;
			}
		}
	}

    // Check if the TC (Transmission Complete) flag is set
    if (USART1->SR & USART_SR_TC) {
        // Transmission complete, clear TC flag
        USART1->SR &= ~USART_SR_TC;
        // Optionally disable TC interrupt if no further action is needed
        USART1->CR1 &= ~USART_CR1_TCIE;
    }

    // Check for IDLE line detection
    if (USART1->SR & USART_SR_IDLE) {
        // Clear IDLE flag by reading SR and DR
        volatile uint8_t dummy = USART1->DR;
        (void)dummy;  // Prevent unused variable warning
        // Handle idle condition (e.g., mark end of transmission)
    }

    // Check for CTS flag (if hardware flow control is enabled)
    if (USART1->SR & USART_SR_CTS) {
        // Clear CTS flag by reading SR
        volatile uint8_t dummy = USART1->SR;
        (void)dummy;
        // Handle CTS change (e.g., pause/resume transmission)
    }

    // Check for LIN Break Detection (if LIN mode is enabled)
    if (USART1->SR & USART_SR_LBD) {
        // Clear LBD flag by writing a 0
        USART1->SR &= ~USART_SR_LBD;
        // Handle LIN break detection (e.g., reset communication)
    }

    // Error handling (Overrun, Noise, Framing, Parity)
    if (USART1->SR & (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE)) {
        if (USART1->SR & USART_SR_ORE) {
            // Overrun error: Clear ORE by reading DR
            volatile uint8_t dummy = USART1->DR;
            (void)dummy;
            // Handle overrun error (e.g., discard data)
        }
        if (USART1->SR & USART_SR_NE) {
            // Noise error: Handle noise (e.g., log or recover from error)
        }
        if (USART1->SR & USART_SR_FE) {
            // Framing error: Handle framing issues (e.g., re-sync communication)
        }
        if (USART1->SR & USART_SR_PE) {
            // Parity error: Handle parity mismatch (e.g., request retransmission)
        }

        // Optionally reset USART or take corrective action based on error type
    }

    // Wakeup from STOP mode (if enabled and used)
    //if (USART1->SR & USART_SR_WU) {
        // Clear wakeup flag by writing a 0
        //USART1->SR &= ~USART_SR_WU;
        // Handle wakeup event (e.g., resume communication)
    //}
}

/*** EOF ***/

