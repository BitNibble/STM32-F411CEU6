#ifndef _STM32FXXUART_H_
#define _STM32FXXUART_H_

/*** Library ***/
#include "stm32fxxxinstance.h"

/*** USART Configuration Enum ***/
typedef enum
{
	USART_WORD_LENGTH_8B,
	USART_WORD_LENGTH_9B,
} USART_WordLength_TypeDef;

typedef enum
{
	USART_SAMPLING_MODE_16,
	USART_SAMPLING_MODE_8,
} USART_SamplingMode_TypeDef;

typedef enum
{
	USART_STOP_BITS_1,
	USART_STOP_BITS_0_5,
	USART_STOP_BITS_2,
	USART_STOP_BITS_1_5,
} USART_StopBits_TypeDef;

/*** USART TypeDef ***/
typedef struct
{
	/*** Bit Field ***/
	USART_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	void (*set_baudrate)(uint32_t baudrate);
	void (*set_word_length)(USART_TypeDef* usart, uint8_t wordlength);
	void (*set_sampling_mode)(USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate);
	void (*set_stop_bits)(USART_TypeDef* usart, double stopbits);
} STM32FXXX_USART1, STM32FXXX_USART2, STM32FXXX_USART6;

/************************/
/*** USART Initialization ***/
/************************/
STM32FXXX_USART1* usart1_enable(void);
STM32FXXX_USART1* usart1(void);
STM32FXXX_USART2* usart2_enable(void);
STM32FXXX_USART2* usart2(void);
STM32FXXX_USART6* usart6_enable(void);
STM32FXXX_USART6* usart6(void);

/****************************************/
/*** USART Procedure & Function Header ***/
/****************************************/
void STM32FXXXUsart1Clock(uint8_t state);
void STM32FXXXUsart1Nvic(uint8_t state);
void STM32FXXXUsart2Clock(uint8_t state);
void STM32FXXXUsart2Nvic(uint8_t state);
void STM32FXXXUsart6Clock(uint8_t state);
void STM32FXXXUsart6Nvic(uint8_t state);

/*** USART Configuration Functions ***/
void STM32FXXXUsartSetBaudrate(USART_TypeDef* instance, uint32_t baudrate);
void Usart_WordLength(USART_TypeDef* usart, uint8_t wordlength);
void Usart_StopBits(USART_TypeDef* usart, double stopbits);
void Usart_SamplingMode(USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate);

/*** Interrupt Header ***/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART6_IRQHandler(void);

#endif
