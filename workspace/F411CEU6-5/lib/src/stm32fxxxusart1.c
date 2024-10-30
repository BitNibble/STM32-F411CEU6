/******************************************************************************
	STM32 XXX USART1
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 24022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart1.h"
#include <string.h>
#include <math.h>

/*** Define and Macro ***/
#ifndef ZERO
	#define ZERO 0
#endif
#ifndef ONE
	#define ONE 1
#endif
/*** File Variable ***/
static STM32FXXX_USART1 stm32fxxx_usart1 = {ZERO};
/******/
// Buffer for received and transmit data
uint8_t usart1_rx_buffer[USART1_RX_BUFFER_SIZE];
volatile uint16_t usart1_rx_index = ZERO;
static uint8_t usart1_flag = ZERO;
uint8_t usart1_tx_buffer[USART1_TX_BUFFER_SIZE];
volatile uint16_t usart1_tx_index = ZERO;
const uint16_t usart1_rx_buffer_size = (USART1_RX_BUFFER_SIZE - ONE);
const uint16_t usart1_tx_buffer_size = (USART1_TX_BUFFER_SIZE - ONE);
/*** USART Procedure & Function Definition ***/
/*** USART1 ***/
void USART1_Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos); }else{ RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART1EN_Pos); }
}
void USART1_Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, ONE, USART1_IRQn, 1); }else{ set_bit_block(NVIC->ICER, ONE, USART1_IRQn, 1); }
}
void USART1_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART1->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART1->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}
void USART1_StopBits(double stopbits) {
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
void USART1_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
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
void USART1_TransmitChar(char c) {
	USART1->CR1 &= ~USART_CR1_TXEIE;
    while (!(USART1->SR & USART_SR_TXE)); // Wait until TX is empty
    USART1->DR = c;                       // Send the character
}
char USART1_ReceiveChar(void) {
	USART1->CR1 &= ~USART_CR1_RXNEIE;
    while (!(USART1->SR & USART_SR_RXNE)); // Wait until RX is ready
    return (char)USART1->DR;               // Return the received character
}
void USART1_RxFlush(void) {
	usart1_rx_index = ZERO;
	usart1_rx_buffer[ZERO] = ZERO;
	usart1_rx_buffer[ONE] = ZERO;
}
void USART1_TransmitString(const char *str) {
	usart1_tx_index = ZERO;
    // Copy the string into the transmit buffer
    strncpy((char *)usart1_tx_buffer, str, usart1_tx_buffer_size); // Ensure tx_buffer is big enough
    usart1_tx_buffer[usart1_tx_buffer_size] = ZERO;
    // Enable the TXE interrupt to start sending data
    USART1->CR1 |= USART_CR1_TXEIE;
}
void USART1_ReceiveString(char* oneshot, char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - ONE;
	oneshot[buff_size] = ZERO; rx[buff_size] = ZERO;
	if(usart1_flag) { memset(oneshot, 0, buff_size); usart1_flag = ZERO; }
	char *ptr = (char*)usart1_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart1_rx_buffer_size ) {
		size_t endl_length = strlen(endl);
		int32_t diff_length = ptr_length - endl_length;
		int32_t check;
		if( diff_length >= ZERO ) {
			check = strcmp((char*)ptr + diff_length, endl);
			if( !check ) {
				strncpy(oneshot, (const char*)ptr, buff_size);
				oneshot[diff_length] = ZERO;
				strncpy(rx, (const char*)ptr, buff_size);
				rx[diff_length] = ZERO;
				usart1_flag = 0xFF;
				USART1_RxFlush( );
			}
		}
	}else { USART1_RxFlush( ); }
}
void USART1_ReceiveRxString(char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - ONE;
	rx[buff_size] = ZERO;
	char *ptr = (char*)usart1_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart1_rx_buffer_size ) {
		size_t endl_length = strlen(endl);
		int32_t diff_length = ptr_length - endl_length;
		int32_t check;
		if( diff_length >= ZERO ) {
			check = strcmp((char*)ptr + diff_length, endl);
			if( !check ) {
				strncpy(rx, (const char*)ptr, buff_size);
				rx[diff_length] = ZERO;
				USART1_RxFlush( );
			}
		}
	}else { USART1_RxFlush( ); }
}
void USART1_start(void) { USART1->CR1 |= USART_CR1_UE; }
void USART1_stop(void) { USART1->CR1 &= ~USART_CR1_UE; }

/*** USART1 INIC Procedure & Function Definition ***/
void usart1_enable(void)
{
	USART1_Clock( ON );
	/*** USART1 Bit Mapping Link ***/
	stm32fxxx_usart1.instance = USART1;
	// Other
	stm32fxxx_usart1.clock = USART1_Clock;
	stm32fxxx_usart1.nvic = USART1_Nvic;
	stm32fxxx_usart1.wordlength = USART1_WordLength;
	stm32fxxx_usart1.stopbits = USART1_StopBits;
	stm32fxxx_usart1.samplingmode = USART1_SamplingMode;
	stm32fxxx_usart1.tx_enable = USART1_TxEnable;
	stm32fxxx_usart1.tx_disable = USART1_TxDisable;
	stm32fxxx_usart1.rx_enable = USART1_RxEnable;
	stm32fxxx_usart1.rx_disable = USART1_RxDisable;
	stm32fxxx_usart1.transmit_char = USART1_TransmitChar;
	stm32fxxx_usart1.receive_char = USART1_ReceiveChar;
	stm32fxxx_usart1.rx_flush = USART1_RxFlush;
	stm32fxxx_usart1.transmit_string = USART1_TransmitString;
	stm32fxxx_usart1.receive_string = USART1_ReceiveString;
	stm32fxxx_usart1.receive_rxstring = USART1_ReceiveRxString;
	stm32fxxx_usart1.start = USART1_start;
	stm32fxxx_usart1.stop = USART1_stop;
	// Inic
	usart1_tx_buffer[usart1_tx_buffer_size] = ZERO;
	usart1_rx_buffer[usart1_rx_buffer_size] = ZERO;
}

STM32FXXX_USART1*  usart1(void){ return (STM32FXXX_USART1*) &stm32fxxx_usart1; }

/*** Interrupt handler for USART1 ***/
void USART1_IRQHandler(void) {
	uint32_t sr = USART1->SR;
	uint32_t cr1 = USART1->CR1;

	if(cr1 & USART_CR1_RXNEIE) {
		// Check if the RXNE (Receive Not Empty) flag is set
		if (sr & USART_SR_RXNE) {
			uint8_t received_byte = USART1->DR;
			if (usart1_rx_index < usart1_rx_buffer_size) {
				usart1_rx_buffer[usart1_rx_index++] = received_byte;
				usart1_rx_buffer[usart1_rx_index] = ZERO;
			}
		}
	}

	if(cr1 & USART_CR1_TXEIE) {
		// Check if the TXE (Transmit Data Register Empty) flag is set
		if (sr & USART_SR_TXE) {
			if(usart1_tx_buffer[usart1_tx_index]) {
				USART1->DR = usart1_tx_buffer[usart1_tx_index++];
			}else{
				USART1->CR1 &= ~USART_CR1_TXEIE;
			}
		}
	}

	if(cr1 & USART_CR1_TCIE) {
		// Check if the TC (Transmission Complete) flag is set
		if (sr & USART_SR_TC) {
			// Transmission complete
			(void)USART1->SR;  // Read SR to acknowledge
			USART1->DR = ZERO;    // Write to DR to clear TC flag
			// Optionally disable TC interrupt if no further action is needed
			USART1->CR1 &= ~USART_CR1_TCIE;
		}
	}

    // Check for IDLE line detection
    if (sr & USART_SR_IDLE) {
        // Clear IDLE flag by reading SR and DR
        volatile uint8_t dummy = USART1->DR;
        (void)dummy;  // Prevent unused variable warning
        // Handle idle condition (e.g., mark end of transmission)
    }

    // Check for CTS flag (if hardware flow control is enabled)
    if (sr & USART_SR_CTS) {
        // Clear CTS flag by reading SR
        volatile uint8_t dummy = USART1->SR;
        (void)dummy;
        // Handle CTS change (e.g., pause/resume transmission)
    }

    // Check for LIN Break Detection (if LIN mode is enabled)
    if (sr & USART_SR_LBD) {
        // Clear LBD flag by writing a 0
        USART1->SR &= ~USART_SR_LBD;
        // Handle LIN break detection (e.g., reset communication)
    }

    // Error handling (Overrun, Noise, Framing, Parity)
    if (sr & (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE)) {
        if (sr & USART_SR_ORE) {
            // Overrun error: Clear ORE by reading DR
            volatile uint8_t dummy = USART1->DR;
            (void)dummy;
            // Handle overrun error (e.g., discard data)
        }
        if (sr & USART_SR_NE) {
            // Noise error: Handle noise (e.g., log or recover from error)
        }
        if (sr & USART_SR_FE) {
            // Framing error: Handle framing issues (e.g., re-sync communication)
        }
        if (sr & USART_SR_PE) {
            // Parity error: Handle parity mismatch (e.g., request retransmission)
        }

        // Optionally reset USART or take corrective action based on error type
    }

    // Wakeup from STOP mode (if enabled and used)
    //if (sr & USART_SR_WU) {
        // Clear wakeup flag by writing a 0
        //USART1->SR &= ~USART_SR_WU;
        // Handle wakeup event (e.g., resume communication)
    //}
}

/*** EOF ***/

