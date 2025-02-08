#include "stm32fxxxusart1.h"
#include "stm32f4xx_hal.h" // Include HAL library

/*** USART1 Handler ***/
static STM32FXXX_USART1 usart1_handler;

/*** Buffers ***/
static char rxbuff[USART1_RX_BUFFER_SIZE];
static char txbuff[USART1_TX_BUFFER_SIZE];

/*** USART1 Initialization ***/
void usart1_enable(void) {
	// Initialize buffers
	usart1_handler.rxbuff = rxbuff;
	usart1_handler.txbuff = txbuff;

	// Set USART1 instance
	usart1_handler.instance = USART1;

	// Configure clock
	usart1_handler.clock = [](uint8_t state) {
		if (state) {
			__HAL_RCC_USART1_CLK_ENABLE();
			} else {
			__HAL_RCC_USART1_CLK_DISABLE();
		}
	};

	// Configure NVIC
	usart1_handler.nvic = [](uint8_t state) {
		if (state) {
			HAL_NVIC_EnableIRQ(USART1_IRQn);
			} else {
			HAL_NVIC_DisableIRQ(USART1_IRQn);
		}
	};

	// Configure word length
	usart1_handler.wordlength = [](uint8_t wordlength) {
		usart1_handler.instance->CR1 &= ~USART_CR1_M; // Clear word length bits
		usart1_handler.instance->CR1 |= (wordlength << USART_CR1_M_Pos);
	};

	// Configure stop bits
	usart1_handler.stopbits = [](double stopbits) {
		usart1_handler.instance->CR2 &= ~USART_CR2_STOP; // Clear stop bits
		if (stopbits == 1.5) {
			usart1_handler.instance->CR2 |= USART_STOPBITS_1_5;
			} else if (stopbits == 2.0) {
			usart1_handler.instance->CR2 |= USART_STOPBITS_2;
			} else {
			usart1_handler.instance->CR2 |= USART_STOPBITS_1;
		}
	};

	// Configure sampling mode
	usart1_handler.samplingmode = [](uint8_t samplingmode, uint32_t baudrate) {
		usart1_handler.instance->CR1 &= ~USART_CR1_OVER8; // Clear oversampling bit
		if (samplingmode == 8) {
			usart1_handler.instance->CR1 |= USART_CR1_OVER8;
		}
		usart1_handler.instance->BRR = SystemCoreClock / baudrate;
	};

	// Enable/disable TX
	usart1_handler.tx = [](uint8_t state) {
		if (state) {
			usart1_handler.instance->CR1 |= USART_CR1_TE;
			} else {
			usart1_handler.instance->CR1 &= ~USART_CR1_TE;
		}
	};

	// Enable/disable RX
	usart1_handler.rx = [](uint8_t state) {
		if (state) {
			usart1_handler.instance->CR1 |= USART_CR1_RE;
			} else {
			usart1_handler.instance->CR1 &= ~USART_CR1_RE;
		}
	};

	// Enable/disable TX interrupt
	usart1_handler.tx_interrupt = [](uint8_t state) {
		if (state) {
			usart1_handler.instance->CR1 |= USART_CR1_TXEIE;
			} else {
			usart1_handler.instance->CR1 &= ~USART_CR1_TXEIE;
		}
	};

	// Enable/disable RX interrupt
	usart1_handler.rx_interrupt = [](uint8_t state) {
		if (state) {
			usart1_handler.instance->CR1 |= USART_CR1_RXNEIE;
			} else {
			usart1_handler.instance->CR1 &= ~USART_CR1_RXNEIE;
		}
	};

	// Transmit a character
	usart1_handler.transmit_char = [](char c) {
		while (!(usart1_handler.instance->SR & USART_SR_TXE)); // Wait for TX buffer empty
		usart1_handler.instance->DR = c;
	};

	// Receive a character
	usart1_handler.receive_char = []() -> char {
		while (!(usart1_handler.instance->SR & USART_SR_RXNE)); // Wait for RX buffer not empty
		return usart1_handler.instance->DR;
	};

	// Flush RX buffer
	usart1_handler.rx_flush = []() {
		while (usart1_handler.instance->SR & USART_SR_RXNE) {
			(void)usart1_handler.instance->DR; // Read and discard data
		}
	};

	// Purge RX buffer
	usart1_handler.rx_purge = []() {
		memset(usart1_handler.rxbuff, 0, USART1_RX_BUFFER_SIZE);
	};

	// Transmit a string
	usart1_handler.transmit_string = [](const char *str) {
		while (*str) {
			usart1_handler.transmit_char(*str++);
		}
	};

	// Receive a string
	usart1_handler.receive_string = [](char* oneshot, char* rx, size_t size, const char* endl) {
		// Implementation depends on specific requirements
	};

	// Receive RX string
	usart1_handler.receive_rxstring = [](char* rx, size_t size, const char* endl) {
		// Implementation depends on specific requirements
	};

	// Start USART1
	usart1_handler.start = []() {
		usart1_handler.instance->CR1 |= USART_CR1_UE; // Enable USART
	};

	// Stop USART1
	usart1_handler.stop = []() {
		usart1_handler.instance->CR1 &= ~USART_CR1_UE; // Disable USART
	};
}

/*** Get USART1 Handler ***/
STM32FXXX_USART1* usart1(void) {
	return &usart1_handler;
}
