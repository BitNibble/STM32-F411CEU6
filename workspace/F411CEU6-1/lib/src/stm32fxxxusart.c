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
#include <math.h>

/*** File Variable ***/
static STM32FXXX_USART1 stm32fxxx_usart1;
static STM32FXXX_USART2 stm32fxxx_usart2;
#ifdef __STM32F446xx_H
	static STM32FXXX_USART3 stm32fxxx_usart3;
	static STM32FXXX_UART4 stm32fxxx_uart4;
	static STM32FXXX_UART5 stm32fxxx_uart5;
#endif
static STM32FXXX_USART6 stm32fxxx_usart6;
/*** USART Procedure & Function Definition ***/
/*** USART1 ***/
void STM32FXXXUsart1Clock( uint8_t bool )
{
	if(bool){ RCC->APB2ENR |= (1 << 4); }else{ RCC->APB2ENR &= ~(1 << 4); }
}
void STM32FXXXUsart1Nvic( uint8_t bool )
{
	if(bool){ set_bit_block(NVIC->ISER, 1, USART1_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART1_IRQn, 1); }
}
void STM32FXXXUsart1Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		USART1->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART1->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART1->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.

	if(samplingmode == 8){
		sampling = 8;
		USART1->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART1->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART1->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}

	USART1->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART1->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART1->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART1->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART1->CR2 |= (1 << 13);

	value = (double) getsysclk() / ( gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	USART1->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART1->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART1->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART1->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART1->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART1->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART1->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** USART2 ***/
void STM32FXXXUsart2Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 17); }else{ RCC->APB1ENR &= ~(1 << 17); }
}
void STM32FXXXUsart2Nvic( uint8_t bool )
{
	if(bool){ set_bit_block(NVIC->ISER, 1, USART2_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART2_IRQn, 1); }
}
void STM32FXXXUsart2Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		USART2->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART2->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART2->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		USART2->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART2->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART2->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	USART2->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART2->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART2->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART2->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART2->CR2 |= (1 << 13);
	value = (double) getsysclk() / ( gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	USART2->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART2->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART2->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART2->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART2->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART2->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART2->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
#ifdef STM32F446xx
/*** USART3 ***/
void STM32FXXXUsart3Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 18); }else{ RCC->APB1ENR &= ~(1 << 18); }
}
void STM32FXXXUsart3Nvic( uint8_t bool )
{
	if(bool){ set_bit_block(NVIC->ISER, 1, USART3_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART3_IRQn, 1); }
}
void STM32FXXXUsart3Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		USART3->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART3->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART3->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		USART3->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART3->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART3->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	USART3->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART3->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART3->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART3->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART3->CR2 |= (1 << 13);
	value = (double) getsysclk() / ( gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	USART3->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART3->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART3->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART3->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART3->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART3->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART3->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** UART4 ***/
void STM32FXXXUart4Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 19); }else{ RCC->APB1ENR &= ~(1 << 19); }

}
void STM32FXXXUart4Nvic( uint8_t bool )
{
	if(bool){ set_bit_block(NVIC->ISER, 1, UART4_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, UART4_IRQn, 1); }
}
void STM32FXXXUart4Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the uart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		UART4->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		UART4->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		UART4->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		UART4->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		UART4->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		UART4->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	UART4->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		UART4->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		UART4->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		UART4->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		UART4->CR2 |= (1 << 13);
	value = (double) getsysclk() / ( gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	UART4->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		UART4->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART4->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		UART4->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		UART4->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		UART4->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART4->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** UART5 ***/
void STM32FXXXUart5Clock( uint8_t bool )
{
	if(bool){ RCC->APB1ENR |= (1 << 20); } // UART5EN: USART5 clock enable
	else{ RCC->APB1ENR &= ~(1 << 20); } // UART5EN: USART5 clock disable
}
void STM32FXXXUart5Nvic( uint8_t bool )
{
	if(bool){ set_bit_block(NVIC->ISER, 1, UART5_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, UART5_IRQn, 1); }
}
void STM32FXXXUart5Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the uart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		UART5->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		UART5->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		UART5->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		UART5->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		UART5->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		UART5->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	UART5->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		UART5->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		UART5->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		UART5->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		UART5->CR2 |= (1 << 13);
	value = (double) getsysclk() / ( gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	UART5->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		UART5->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART5->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		UART5->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		UART5->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		UART5->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		UART5->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}

#endif
/*** USART6 ***/
void STM32FXXXUsart6Clock( uint8_t bool )
{
	if(bool){ RCC->APB2ENR |= (1 << 5); }else{ RCC->APB2ENR &= ~(1 << 5); }
}
void STM32FXXXUsart6Nvic( uint8_t bool )
{
	if(bool){ set_bit_block(NVIC->ISER, 1, USART6_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART6_IRQn, 1); }
}
void STM32FXXXUsart6Parameter( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
// Sets the usart parameters, using real values.
{
	uint8_t sampling;
	double value, fracpart, intpart;
	if(wordlength == 9)
		USART6->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		USART6->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		USART6->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	if(samplingmode == 8){
		sampling = 8;
		USART6->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		USART6->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		USART6->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	USART6->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		USART6->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		USART6->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		USART6->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		USART6->CR2 |= (1 << 13);
	value = (double) getsysclk() / ( gethpre() * sampling * baudrate );
	fracpart = modf(value, &intpart);
	USART6->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		USART6->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART6->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		USART6->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		USART6->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		USART6->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		USART6->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}
/*** USART1 INIC Procedure & Function Definition ***/
STM32FXXX_USART1* usart1_enable(void)
{

	/*** USART1 Bit Mapping Link ***/
	stm32fxxx_usart1.instance = usart1_instance();
	// Other
	stm32fxxx_usart1.clock = STM32FXXXUsart1Clock;
	stm32fxxx_usart1.nvic = STM32FXXXUsart1Nvic;
	stm32fxxx_usart1.parameter = STM32FXXXUsart1Parameter;

	return &stm32fxxx_usart1;
}

STM32FXXX_USART1*  usart1(void){ return (STM32FXXX_USART1*) &stm32fxxx_usart1; }

/*** USART2 INIC Procedure & Function Definition ***/
STM32FXXX_USART2* usart2_enable(void)
{

	/*** USART2 Bit Mapping Link ***/
	stm32fxxx_usart2.instance = usart2_instance();
	// Other
	stm32fxxx_usart2.clock = STM32FXXXUsart2Clock;
	stm32fxxx_usart2.nvic = STM32FXXXUsart2Nvic;
	stm32fxxx_usart2.parameter = STM32FXXXUsart2Parameter;
	return &stm32fxxx_usart2;
}

STM32FXXX_USART2*  usart2(void){ return (STM32FXXX_USART2*) &stm32fxxx_usart2; }

#ifdef STM32F446xx
/*** USART3 INIC Procedure & Function Definition ***/
STM32FXXX_USART3* usart3_enable(void)
{

	/*** USART3 Bit Mapping Link ***/
	stm32fxxx_usart3.instance = usart3_instance();
	// Other
	stm32fxxx_usart3.clock = STM32FXXXUsart3Clock;
	stm32fxxx_usart3.nvic = STM32FXXXUsart3Nvic;
	stm32fxxx_usart3.parameter = STM32FXXXUsart3Parameter;
	return &stm32fxxx_usart3;
}

STM32FXXX_USART3*  usart3(void){ return (STM32FXXX_USART3*) &stm32fxxx_usart3; }

/*** UART4 INIC Procedure & Function Definition ***/
STM32FXXX_UART4* uart4_enable(void)
{

	/*** UART4 Bit Mapping Link ***/
	stm32fxxx_uart4.instance = uart4_instance();
	// Other
	stm32fxxx_uart4.clock = STM32FXXXUart4Clock;
	stm32fxxx_uart4.nvic = STM32FXXXUart4Nvic;
	stm32fxxx_uart4.parameter = STM32FXXXUart4Parameter;
	return &stm32fxxx_uart4;
}

STM32FXXX_UART4*  uart4(void){ return (STM32FXXX_UART4*) &stm32fxxx_uart4; }

/*** UART5 INIC Procedure & Function Definition ***/
STM32FXXX_UART5* uart5_enable(void)
{

	/*** UART5 Bit Mapping Link ***/
	stm32fxxx_uart5.instance = uart5_instance();
	// Other
	stm32fxxx_uart5.clock = STM32FXXXUart5Clock;
	stm32fxxx_uart5.nvic = STM32FXXXUart5Nvic;
	stm32fxxx_uart5.parameter = STM32FXXXUart5Parameter;
	return &stm32fxxx_uart5;
}

STM32FXXX_UART5*  uart5(void){ return (STM32FXXX_UART5*) &stm32fxxx_uart5; }

#endif
/*** USART6 INIC Procedure & Function Definition ***/
STM32FXXX_USART6* usart6_enable(void)
{

	/*** USART6 Bit Mapping Link ***/
	stm32fxxx_usart6.instance = usart6_instance();
	// Other
	stm32fxxx_usart6.clock = STM32FXXXUsart6Clock;
	stm32fxxx_usart6.nvic = STM32FXXXUsart6Nvic;
	stm32fxxx_usart6.parameter = STM32FXXXUsart6Parameter;
	return &stm32fxxx_usart6;
}

STM32FXXX_USART6*  usart6(void){ return (STM32FXXX_USART6*) &stm32fxxx_usart6; }

/*** EOF ***/

