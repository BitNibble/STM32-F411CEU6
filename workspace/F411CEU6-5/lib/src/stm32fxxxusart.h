/******************************************************************************
	STM32 XXX USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 24022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXUSART_H_
	#define _STM32FXXXUSART_H_
/*** Library ***/
#include "armquery.h"

/*** USART 1..6 Handler TypeDef ***/
// USART -> USART1,2,3,6
typedef struct
{

	/*** Bit Mapping ***/
	TM32FXXXUSARTX_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
	void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
}STM32FXXX_USART1, STM32FXXX_USART2, STM32FXXX_USART3, STM32FXXX_USART6;
// USART -> UART4,5
typedef struct
{

	/*** Bit Mapping ***/
	TM32FXXXUSARTX_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
	void (*parameter)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
}STM32FXXX_UART4, STM32FXXX_UART5;

STM32FXXX_USART1* usart1_enable(void);
STM32FXXX_USART1*  usart1(void);

STM32FXXX_USART2* usart2_enable(void);
STM32FXXX_USART2*  usart2(void);

STM32FXXX_USART3* usart3_enable(void);
STM32FXXX_USART3*  usart3(void);

STM32FXXX_UART4* uart4_enable(void);
STM32FXXX_UART4*  uart4(void);

STM32FXXX_UART5* uart5_enable(void);
STM32FXXX_UART5*  uart5(void);

STM32FXXX_USART6* usart6_enable(void);
STM32FXXX_USART6*  usart6(void);
/*** USART1 Header ***/
void STM32FXXXUsart1Clock( uint8_t bool );
void STM32FXXXUsart1Nvic( uint8_t bool );
void STM32FXXXUsart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
void STM32FXXXUsart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** USART2 Header ***/
void STM32FXXXUsart2Clock( uint8_t bool );
void STM32FXXXUsart2Nvic( uint8_t bool );
void STM32FXXXUsart2Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** USART3 Header ***/
void STM32FXXXUsart3Clock( uint8_t bool );
void STM32FXXXUsart3Nvic( uint8_t bool );
void STM32FXXXUsart3Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** UART4 Header ***/
void STM32FXXXUart4Clock( uint8_t bool );
void STM32FXXXUart4Nvic( uint8_t bool );
void STM32FXXXUart4Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** UART5 Header ***/
void STM32FXXXUart5Clock( uint8_t bool );
void STM32FXXXUart5Nvic( uint8_t bool );
void STM32FXXXUart5Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** USART6 Header ***/
void STM32FXXXUsart6Clock( uint8_t bool );
void STM32FXXXUsart6Nvic( uint8_t bool );
void STM32FXXXUsart6Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
/*** INTERRUPT HEADER ***/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void USART6_IRQHandler(void);

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

