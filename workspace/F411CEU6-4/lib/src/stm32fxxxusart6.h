/******************************************************************************
	STM32 XXX USART6
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 24022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXUSART6_H_
	#define _STM32FXXXUSART6_H_

/*** Library ***/
#include "stm32fxxxinstance.h"
/*** Define and Macros ***/
#define USART6_RX_BUFFER_SIZE 128
#define USART6_TX_BUFFER_SIZE 128
/*** USART 1..6 Handler TypeDef ***/
// USART -> USART6
typedef struct
{
	/*** Bit Mapping ***/
	USART_TypeDef* instance;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*wordlength)(uint8_t wordlength);
	void (*stopbits)(double stopbits);
	void (*samplingmode)(uint8_t samplingmode, uint32_t baudrate);
	void (*tx_enable)(void);
	void (*tx_disable)(void);
	void (*rx_enable)(void);
	void (*rx_disable)(void);
	void (*transmit_char)(char c);
	char (*receive_char)(void);
	void (*rx_flush)(void);
	void (*transmit_string)(const char *str);
	void (*receive_string)(char* oneshot, char* rx, size_t size, const char* endl);
	void (*start)(void);
	void (*stop)(void);
}STM32FXXX_USART6;

void usart6_enable(void); STM32FXXX_USART6*  usart6(void);

#endif

/*** EOF ***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/
