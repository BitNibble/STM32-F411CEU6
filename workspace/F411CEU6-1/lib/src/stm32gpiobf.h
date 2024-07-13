/******************************************************************************
	STM32 XXX GPIOBF
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 25032024
Comment:
	wrapper
*******************************************************************************/
#ifndef _STM32GPIOBF_H_
	#define _STM32GPIOBF_H_

#include <inttypes.h>

volatile typedef struct{
	/*** GPIO -> MODER ***/
	union {
		struct MODER_1{
		  uint32_t pin_0:2;
		  uint32_t pin_1:2;
		  uint32_t pin_2:2;
		  uint32_t pin_3:2;
		  uint32_t pin_4:2;
		  uint32_t pin_5:2;
		  uint32_t pin_6:2;
		  uint32_t pin_7:2;
		  uint32_t pin_8:2;
		  uint32_t pin_9:2;
		  uint32_t pin_10:2;
		  uint32_t pin_11:2;
		  uint32_t pin_12:2;
		  uint32_t pin_13:2;
		  uint32_t pin_14:2;
		  uint32_t pin_15:2;
		} par;
		uint32_t reg;
	} moder; //0x00
	/*** GPIO -> OTYPER ***/
	union {
		struct OTYPER_1{
		  uint32_t pin_0:1;
		  uint32_t pin_1:1;
		  uint32_t pin_2:1;
		  uint32_t pin_3:1;
		  uint32_t pin_4:1;
		  uint32_t pin_5:1;
		  uint32_t pin_6:1;
		  uint32_t pin_7:1;
		  uint32_t pin_8:1;
		  uint32_t pin_9:1;
		  uint32_t pin_10:1;
		  uint32_t pin_11:1;
		  uint32_t pin_12:1;
		  uint32_t pin_13:1;
		  uint32_t pin_14:1;
		  uint32_t pin_15:1;
		  uint32_t fill:16;
		} par;
		struct OTYPER_2{
		  uint16_t t;
		  uint16_t fill;
		} word;
		uint32_t reg;
	} otyper; //0x04
	/*** GPIO -> OSPEEDR ***/
	union {
		struct OSPEEDR_1{
		  uint32_t pin_0:2;
		  uint32_t pin_1:2;
		  uint32_t pin_2:2;
		  uint32_t pin_3:2;
		  uint32_t pin_4:2;
		  uint32_t pin_5:2;
		  uint32_t pin_6:2;
		  uint32_t pin_7:2;
		  uint32_t pin_8:2;
		  uint32_t pin_9:2;
		  uint32_t pin_10:2;
		  uint32_t pin_11:2;
		  uint32_t pin_12:2;
		  uint32_t pin_13:2;
		  uint32_t pin_14:2;
		  uint32_t pin_15:2;
		} par;
		uint32_t reg;
	} ospeedr; //0x08
	/*** GPIO -> PUPDR ***/
	union{
		struct PUPDR_1{
		  uint32_t pin_0:2;
		  uint32_t pin_1:2;
		  uint32_t pin_2:2;
		  uint32_t pin_3:2;
		  uint32_t pin_4:2;
		  uint32_t pin_5:2;
		  uint32_t pin_6:2;
		  uint32_t pin_7:2;
		  uint32_t pin_8:2;
		  uint32_t pin_9:2;
		  uint32_t pin_10:2;
		  uint32_t pin_11:2;
		  uint32_t pin_12:2;
		  uint32_t pin_13:2;
		  uint32_t pin_14:2;
		  uint32_t pin_15:2;
		} par;
		uint32_t reg;
	} pupdr; //0x0C
	/*** GPIO -> IDR ***/
	union {
		struct IDR_1{
		  uint32_t pin_0:1;
		  uint32_t pin_1:1;
		  uint32_t pin_2:1;
		  uint32_t pin_3:1;
		  uint32_t pin_4:1;
		  uint32_t pin_5:1;
		  uint32_t pin_6:1;
		  uint32_t pin_7:1;
		  uint32_t pin_8:1;
		  uint32_t pin_9:1;
		  uint32_t pin_10:1;
		  uint32_t pin_11:1;
		  uint32_t pin_12:1;
		  uint32_t pin_13:1;
		  uint32_t pin_14:1;
		  uint32_t pin_15:1;
		  uint32_t fill:16;
		} par;
		struct IDR_2{
		  uint16_t i;
		  uint16_t fill;
		} word;
		uint32_t reg;
	} idr; //0x10
	/*** GPIO -> ODR ***/
	union {
		struct ODR_1{
		  uint32_t pin_0:1;
		  uint32_t pin_1:1;
		  uint32_t pin_2:1;
		  uint32_t pin_3:1;
		  uint32_t pin_4:1;
		  uint32_t pin_5:1;
		  uint32_t pin_6:1;
		  uint32_t pin_7:1;
		  uint32_t pin_8:1;
		  uint32_t pin_9:1;
		  uint32_t pin_10:1;
		  uint32_t pin_11:1;
		  uint32_t pin_12:1;
		  uint32_t pin_13:1;
		  uint32_t pin_14:1;
		  uint32_t pin_15:1;
		  uint32_t fill:16;
		} par;
		struct ODR_2{
		  uint16_t o;
		  uint16_t fill;
		} word;
		uint32_t reg;
	} odr; //0x14
	/*** GPIO -> BSRR ***/
	union {
		struct BSRR_1{
		  uint32_t setpin_0:1;
		  uint32_t setpin_1:1;
		  uint32_t setpin_2:1;
		  uint32_t setpin_3:1;
		  uint32_t setpin_4:1;
		  uint32_t setpin_5:1;
		  uint32_t setpin_6:1;
		  uint32_t setpin_7:1;
		  uint32_t setpin_8:1;
		  uint32_t setpin_9:1;
		  uint32_t setpin_10:1;
		  uint32_t setpin_11:1;
		  uint32_t setpin_12:1;
		  uint32_t setpin_13:1;
		  uint32_t setpin_14:1;
		  uint32_t setpin_15:1;
		  uint32_t resetpin_0:1;
		  uint32_t resetpin_1:1;
		  uint32_t resetpin_2:1;
		  uint32_t resetpin_3:1;
		  uint32_t resetpin_4:1;
		  uint32_t resetpin_5:1;
		  uint32_t resetpin_6:1;
		  uint32_t resetpin_7:1;
		  uint32_t resetpin_8:1;
		  uint32_t resetpin_9:1;
		  uint32_t resetpin_10:1;
		  uint32_t resetpin_11:1;
		  uint32_t resetpin_12:1;
		  uint32_t resetpin_13:1;
		  uint32_t resetpin_14:1;
		  uint32_t resetpin_15:1;
		} par;
		struct BSRR_2{
		 uint32_t set:16;
		 uint32_t reset:16;
		} word;
		uint32_t reg;
	} bsrr; //0x18
	/*** GPIO -> LCKR ***/
	union {
		struct LCKR_1{
		  uint32_t pin_0:1;
		  uint32_t pin_1:1;
		  uint32_t pin_2:1;
		  uint32_t pin_3:1;
		  uint32_t pin_4:1;
		  uint32_t pin_5:1;
		  uint32_t pin_6:1;
		  uint32_t pin_7:1;
		  uint32_t pin_8:1;
		  uint32_t pin_9:1;
		  uint32_t pin_10:1;
		  uint32_t pin_11:1;
		  uint32_t pin_12:1;
		  uint32_t pin_13:1;
		  uint32_t pin_14:1;
		  uint32_t pin_15:1;
		  uint32_t fill:16;
		} par;
		struct LCKR_2{
		  uint16_t l;
		  uint16_t fill;
		} word;
		uint32_t reg;
	} lckr; //0x1C
	/*** GPIO -> AFR ***/
	union {
		struct AFR_1{
		  uint32_t pin_0:4;
		  uint32_t pin_1:4;
		  uint32_t pin_2:4;
		  uint32_t pin_3:4;
		  uint32_t pin_4:4;
		  uint32_t pin_5:4;
		  uint32_t pin_6:4;
		  uint32_t pin_7:4;
		  uint32_t pin_8:4;
		  uint32_t pin_9:4;
		  uint32_t pin_10:4;
		  uint32_t pin_11:4;
		  uint32_t pin_12:4;
		  uint32_t pin_13:4;
		  uint32_t pin_14:4;
		  uint32_t pin_15:4;
		} par;
		uint32_t regl; //0x20
		uint32_t regh; //0x24
	} afr;
} STM32FXXXGPIOX_TypeDef;

#endif

/*** EOF ***/

