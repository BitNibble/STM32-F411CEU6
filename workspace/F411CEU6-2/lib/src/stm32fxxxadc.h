/******************************************************************************
	STM32 XXX ADC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC_H_
	#define _STM32FXXXADC_H_

/*** Library ***/
#include "armquery.h"

/*** ADC 1..3 BitField TypeDef ***/
// SR
volatile typedef union {
	struct SR_1{
		uint32_t awd:1;
		uint32_t eoc:1;
		uint32_t jeoc:1;
		uint32_t jstrt:1;
		uint32_t strt:1;
		uint32_t ovr:1;
		uint32_t fill:26;
	}par;
	uint32_t reg;
}STM32FXXXADC_SR_TypeDef;
// CR1
volatile typedef union {
	struct CR1_1{
		uint32_t awdch:5;
		uint32_t eocie:1;
		uint32_t awdie:1;
		uint32_t jeocie:1;
		uint32_t scan:1;
		uint32_t awd_sgl:1;
		uint32_t jauto:1;
		uint32_t discen:1;
		uint32_t jdiscen:1;
		uint32_t discnum:3;
		uint32_t reserved1:6;
		uint32_t jawden:1;
		uint32_t awden:1;
		uint32_t res:2;
		uint32_t ovrie:1;
		uint32_t reserved2:5;
	}par;
	uint32_t reg;
}STM32FXXXADC_CR1_TypeDef;
// CR2
volatile typedef union {
	struct CR2_1{
		uint32_t adon:1;
		uint32_t cont:1;
		uint32_t reserved1:6;
		uint32_t dma:1;
		uint32_t dds:1;
		uint32_t eocs:1;
		uint32_t align:1;
		uint32_t reserved2:4;
		uint32_t jextsel:4;
		uint32_t jexten:2;
		uint32_t jswstart:1;
		uint32_t reserved3:1;
		uint32_t extsel:4;
		uint32_t exten:2;
		uint32_t swstart:1;
		uint32_t reserved4:1;
	}par;
	uint32_t reg;
}STM32FXXXADC_CR2_TypeDef;
// SMPR1
volatile typedef union {
	struct SMPR1_1{
		uint32_t smp10:3;
		uint32_t smp11:3;
		uint32_t smp12:3;
		uint32_t smp13:3;
		uint32_t smp14:3;
		uint32_t smp15:3;
		uint32_t smp16:3;
		uint32_t smp17:3;
		uint32_t smp18:3;
		uint32_t reserved:5;
	}par;
	uint32_t reg;
}STM32FXXXADC_SMPR1_TypeDef;
// SMPR2
volatile typedef union {
	struct SMPR2_1{
		uint32_t smp0:3;
		uint32_t smp1:3;
		uint32_t smp2:3;
		uint32_t smp3:3;
		uint32_t smp4:3;
		uint32_t smp5:3;
		uint32_t smp6:3;
		uint32_t smp7:3;
		uint32_t smp8:3;
		uint32_t smp9:3;
		uint32_t reserved:2;
	}par;
	uint32_t reg;
}STM32FXXXADC_SMPR2_TypeDef;
// JOFRx
volatile typedef union {
	struct JOFRx_1{
		uint32_t joffset:12;
		uint32_t reserved:20;
	}par;
	uint32_t reg;
}STM32FXXXADC_JOFRx_TypeDef;
// HTR
volatile typedef union {
	struct HTR_1{
		uint32_t ht:12;
		uint32_t reserved:20;
	}par;
	uint32_t reg;
}STM32FXXXADC_HTR_TypeDef;
// LTR
volatile typedef union {
	struct LTR_1{
		uint32_t lt:12;
		uint32_t reserved:20;
	}par;
	uint32_t reg;
}STM32FXXXADC_LTR_TypeDef;
// SQR1
volatile typedef union {
	struct SQR1_1{
		uint32_t sq13:5;
		uint32_t sq14:5;
		uint32_t sq15:5;
		uint32_t sq16:5;
		uint32_t l:4;
		uint32_t reserved:8;
	}par;
	uint32_t reg;
}STM32FXXXADC_SQR1_TypeDef;
// SQR2
volatile typedef union {
	struct SQR2_1{
		uint32_t sq7:5;
		uint32_t sq8:5;
		uint32_t sq9:5;
		uint32_t sq10:5;
		uint32_t sq11:5;
		uint32_t sq12:5;
		uint32_t reserved:2;
	}par;
	uint32_t reg;
}STM32FXXXADC_SQR2_TypeDef;
// SQR3
volatile typedef union {
	struct SQR3_1{
		uint32_t sq1:5;
		uint32_t sq2:5;
		uint32_t sq3:5;
		uint32_t sq4:5;
		uint32_t sq5:5;
		uint32_t sq6:5;
		uint32_t reserved:2;
	}par;
	uint32_t reg;
}STM32FXXXADC_SQR3_TypeDef;
// JSQR
volatile typedef union {
	struct JSQR_1{
		uint32_t jsq1:5;
		uint32_t jsq2:5;
		uint32_t jsq3:5;
		uint32_t jsq4:5;
		uint32_t jl:2;
		uint32_t reserved:10;
	}par;
	uint32_t reg;
}STM32FXXXADC_JSQR_TypeDef;
// JDRx
volatile typedef union {
	struct JDRx_1{
		uint16_t jdata;
		uint16_t reserved;
	}par;
	uint32_t reg;
}STM32FXXXADC_JDRx_TypeDef;
// DR
volatile typedef union {
	struct DR_1{
		uint16_t data;
		uint16_t reserved;
	}par;
	uint32_t reg;
}STM32FXXXADC_DR_TypeDef;
// CSR
volatile typedef union {
	struct CSR_1{
		uint32_t awd1:1;
		uint32_t eoc1:1;
		uint32_t jeoc1:1;
		uint32_t jstrt1:1;
		uint32_t strt1:1;
		uint32_t ovr1:1;
		uint32_t reserved1:2;
		uint32_t awd2:1;
		uint32_t eoc2:1;
		uint32_t jeoc2:1;
		uint32_t jstrt2:1;
		uint32_t strt2:1;
		uint32_t ovr2:1;
		uint32_t reserved2:2;
		uint32_t awd3:1;
		uint32_t eoc3:1;
		uint32_t jeoc3:1;
		uint32_t jstrt3:1;
		uint32_t strt3:1;
		uint32_t ovr3:1;
		uint32_t reserved3:10;
	}par;
	struct CSR_2{
		uint32_t awd1:1;
		uint32_t eoc1:1;
		uint32_t jeoc1:1;
		uint32_t jstrt1:1;
		uint32_t strt1:1;
		uint32_t ovr1:1;
		uint32_t reserved:26;
	}adc1_par;
	struct CSR_3{
		uint32_t reserved1:8;
		uint32_t awd2:1;
		uint32_t eoc2:1;
		uint32_t jeoc2:1;
		uint32_t jstrt2:1;
		uint32_t strt2:1;
		uint32_t ovr2:1;
		uint32_t reserved2:18;
	}adc2_par;
	struct CSR_4{
		uint32_t reserved1:16;
		uint32_t awd3:1;
		uint32_t eoc3:1;
		uint32_t jeoc3:1;
		uint32_t jstrt3:1;
		uint32_t strt3:1;
		uint32_t ovr3:1;
		uint32_t reserved2:10;
	}adc3_par;
	uint32_t reg;
}STM32FXXXADC_CSR_TypeDef;
// CCR
volatile typedef union {
	struct CCR_1{
		uint16_t reserved1;
		uint16_t adcpre:2;
		uint16_t reserved2:4;
		uint16_t vbate:1;
		uint16_t tsvrefe:1;
		uint16_t reserved3:8;
	}par;
	uint32_t reg;
}STM32FXXXADC_CCR_TypeDef;
/*** ADC_Common TypeDef ***/
typedef struct
{

	STM32FXXXADC_CSR_TypeDef* csr;
	STM32FXXXADC_CCR_TypeDef* ccr;
	uint32_t (*cdr)(void);
}STM32FXXXADC_COMMON;
/*** ADC1 ADC2 ADC3 Auxiliary TypeDef ***/
typedef struct
{
	void (*inic)(void);
	void (*vbat)(void);
	void (*temp)(void);
	void (*start)(void);
}STM32FXXXADC1single, STM32FXXXADC2single, STM32FXXXADC3single;

STM32FXXXADC_COMMON* stm32fxxx_adc_common_inic(void);
/*** ADC Common Header ***/
// CDR
uint32_t STM32FXXXADC_cdr(void);
/*** INTERRUPT HEADER ***/
void ADC_IRQHandler(void);

#endif

/***EOF***/

