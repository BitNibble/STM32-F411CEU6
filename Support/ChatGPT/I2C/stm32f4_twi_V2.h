#ifndef _STM32F4_TWI_H_
#define _STM32F4_TWI_H_

/*** Global Library ***/
#include "stm32f4xx.h"  // Include your STM32F4 header

/*** Global Constant & Macro ***/
#ifndef _TWI_MODULE_
#define _TWI_MODULE_
#endif

#define TWI_SCL_CLOCK 100000UL
#define TWI_ACK 1
#define TWI_NACK 0

/*** Global Variable ***/
typedef struct {
	I2C_TypeDef* instance;
	void (*start)(void);
	void (*connect)(uint16_t address, uint8_t rw);
	void (*master_write)(uint8_t data);
	uint8_t (*master_read)(uint8_t ack_nack);
	void (*stop)(void);
	uint8_t (*status)(void);
} TWI_HandleTypeDef;

/*** Global Header ***/
TWI_HandleTypeDef* TWI(void);
TWI_HandleTypeDef TWI_enable(I2C_TypeDef* instance);

#endif
