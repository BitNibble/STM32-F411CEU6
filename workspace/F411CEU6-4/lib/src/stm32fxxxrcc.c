/******************************************************************************
	STM32 FXXX RCC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 07032024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include <stm32fxxxrcc.h>

/*** File Variables ***/
static STM32FXXXRCCPLL stm32fxxx_rcc_pll;
static STM32FXXXRCCPLLI2S stm32fxxx_rcc_plli2s;
static STM32FXXXRCCPLLSAI stm32fxxx_rcc_pllsai;
static STM32FXXX_RCC stm32fxxx_rcc;

/*** File Procedure & Function Header ***/
/*** Extended ***/
STM32FXXXRCCPLL* stm32fxxx_rcc_pll_inic(void);
STM32FXXXRCCPLLI2S* stm32fxxx_rcc_plli2s_inic(void);
STM32FXXXRCCPLLSAI* stm32fxxx_rcc_pllsai_inic(void);
/******/
void STM32FXXXRccPwrClock(uint8_t bool);
void STM32FXXXRccWriteEnable(void);
void STM32FXXXRccWriteDisable(void);
uint8_t STM32FXXXRccPLLSelect(uint8_t hclock);

/*******   0 -> HSI    1->HSE   *********/
#ifndef H_Clock_Source
	#define H_Clock_Source 0
#endif
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#ifndef PLL_ON_OFF
	#define PLL_ON_OFF 0
#endif
/****************************************/

/*** RCC Procedure & Function Definition ***/
void rcc_start(void)
{	// Configure -> Enable -> Select
    // AHB 1,2,4,8,16,64,128,256,512;  APB1 1,2,4,8,16;  APB2 1,2,4,8,16;  RTC 2 to 31
	//STM32FXXXPrescaler(8, 1, 1, 1); // (8, 1, 1, 0)
	STM32FXXXPrescaler(1, 1, 1, 0); // (1, 1, 1, 0)
	STM32FXXXRccHEnable(0); // 0 - HSI
	STM32FXXXRccHEnable(1); // 1 - HSE
	STM32FXXXRccPLLSelect(H_Clock_Source); // 0 - HSI, 1 - HSE, H_Clock_Source
	// M 2 to 63;  N 50 to 432;  P 2,4,6,8;  Q 2 to 15;
	STM32FXXXPLLDivision((uint32_t)getpllclk()/1000000, 240, 2, 4);
	if(PLL_ON_OFF){
		STM32FXXXRccPLLCLKEnable();
		// System Clock Switch
		STM32FXXXRccHSelect(2); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
	}else{
		// System Clock Switch
		STM32FXXXRccHSelect(H_Clock_Source); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
	}
}
// RCC
void STM32FXXXRccHEnable(uint8_t hclock)
{
	uint8_t set;
	uint8_t rdy;
	set_reg_block(&RCC->CR, 1, 19, 1); // CSSON
	for( set = 1, rdy = 1; rdy ; ){
		if(hclock == 0){ // HSION: Internal high-speed clock enable
			if( set ){ RCC->CR |= ( 1 << 0); set = 0; }else if( RCC->CR & ( 1 << 1) ) rdy = 0;
		}
		else if(hclock == 1){ // HSEON: HSE clock enable
			if( set ){ RCC->CR |= ( 1 << 16); set = 0; }else if( RCC->CR & ( 1 << 17) ) rdy = 0;
		}
		else if(hclock == 2){ // HSEBYP: HSE clock bypass
			if( set ){ RCC->CR |= ( 1 << 18 ); }
			hclock = 1;
		}
		else hclock = 0; // default
	}
}
void STM32FXXXRccHSelect(uint8_t hclock)
{ // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	switch(hclock){
		case 0:
			set_reg_block(&RCC->CFGR, 2, 0, 0);
		break;
		case 1: // HSE oscillator selected as system clock
			set_reg_block(&RCC->CFGR, 2, 0, 1);
		break;
		case 2: // PLL_P selected as system clock
			set_reg_block(&RCC->CFGR, 2, 0, 2);
		break;
		case 3: // PLL_R selected as system clock
			#ifdef STM32F446xx
				STM32FXXXRccWriteEnable();
				set_reg_block(&RCC->CFGR, 2, 0, 3);
				STM32FXXXRccWriteDisable();
			#else
				set_reg_block(&RCC->CFGR, 2, 0, 0);
			#endif
		break;
		default: // 00: HSI oscillator selected as system clock
			set_reg_block(&RCC->CFGR, 2, 0, 0);
		break;
	}
}
uint8_t STM32FXXXRccPLLSelect(uint8_t hclock)
{ // This bit can be written only when PLL and PLLI2S are disabled
	set_reg_block(&RCC->CR, 1, 24, 0); set_reg_block(&RCC->CR, 1, 26, 0);
	switch(hclock){
		case 0: // HSI
			set_reg_block(&RCC->PLLCFGR, 1, 22, 0);
		break;
		case 1: // HSE
			set_reg_block(&RCC->PLLCFGR, 1, 22, 1);
		break;
		default: // HSI
			set_reg_block(&RCC->PLLCFGR, 1, 22, 0);
		break;
	}
	return get_reg_block(RCC->PLLCFGR, 1, 22);
}
void STM32FXXXRccLEnable(uint8_t lclock)
{
	uint8_t set;
	uint8_t rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(lclock == 0){ // LSION: Internal low-speed oscillator enable
			if( set ){ RCC->CSR |= ( 1 << 0); set = 0; }else if( RCC->CSR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 1){ // LSEON: External low-speed oscillator enable
			if( set ){ STM32FXXXRccWriteEnable(); RCC->BDCR |= ( 1 << 0); STM32FXXXRccWriteDisable(); set = 0; }else if( RCC->BDCR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 2){ // LSEBYP: External low-speed oscillator bypass
			if( set ){ STM32FXXXRccWriteEnable(); RCC->BDCR |= ( 1 << 2 ); STM32FXXXRccWriteDisable(); }
			lclock = 1;
		}
		else lclock = 0; // default
	}
}
void STM32FXXXRccLSelect(uint8_t lclock)
{
	switch(lclock){
		case 0: // LSI oscillator clock used as the RTC clock
			STM32FXXXRccWriteEnable();
			set_reg_block(&RCC->BDCR, 2, 8, 2);
			STM32FXXXRccWriteDisable();
		break;
		case 1: // LSE oscillator clock used as the RTC clock
			STM32FXXXRccWriteEnable();
			set_reg_block(&RCC->BDCR, 2, 8, 1);
			STM32FXXXRccWriteDisable();
		break;
		case 2: // HSE oscillator clock divided by a programmable prescaler
			STM32FXXXRccWriteEnable();
			set_reg_block(&RCC->BDCR, 2, 8, 3);
			STM32FXXXRccWriteDisable();
		break;
		default: // LSE oscillator clock used as the RTC clock
			STM32FXXXRccWriteEnable();
			set_reg_block(&RCC->BDCR, 2, 8, 1);
			STM32FXXXRccWriteDisable();
		break;
	}
}
void STM32FXXXPrescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre)
{
	set_reg_block(&RCC->CFGR, 5, 16, rtcpre);
	switch(ppre2){ // 13
		case 2:
			set_reg_block(&RCC->CFGR, 3, 13, 4);
		break;
		case 4:
			set_reg_block(&RCC->CFGR, 3, 13, 5);
		break;
		case 8:
			set_reg_block(&RCC->CFGR, 3, 13, 6);
		break;
		case 16:
			set_reg_block(&RCC->CFGR, 3, 13, 7);
		break;
		default:
			set_reg_block(&RCC->CFGR, 3, 13, 0);
		break;
	}
	switch(ppre1){ // 10
		case 2:
			set_reg_block(&RCC->CFGR, 3, 10, 4);
		break;
		case 4:
			set_reg_block(&RCC->CFGR, 3, 10, 5);
		break;
		case 8:
			set_reg_block(&RCC->CFGR, 3, 10, 6);
		break;
		case 16:
			set_reg_block(&RCC->CFGR, 3, 10, 7);
		break;
		default:
			set_reg_block(&RCC->CFGR, 3, 10, 0);
		break;
	}
	switch(ahbpre){ // 4
		case 2:
			set_reg_block(&RCC->CFGR, 4, 4, 8);
		break;
		case 4:
			set_reg_block(&RCC->CFGR, 4, 4, 9);
		break;
		case 8:
			set_reg_block(&RCC->CFGR, 4, 4, 10);
		break;
		case 16:
			set_reg_block(&RCC->CFGR, 4, 4, 11);
		break;
		case 64:
			set_reg_block(&RCC->CFGR, 4, 4, 12);
		break;
		case 128:
			set_reg_block(&RCC->CFGR, 4, 4, 13);
		break;
		case 256:
			set_reg_block(&RCC->CFGR, 4, 4, 14);
			break;
		case 512:
			set_reg_block(&RCC->CFGR, 4, 4, 15);
			break;
		default:
			set_reg_block(&RCC->CFGR, 4, 4, 0);
		break;
	}
}
// PLL
void STM32FXXXPLLDivision(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq)
{
	set_reg_block(&RCC->CR, 1, 24, 0);
	set_reg_block(&RCC->PLLCFGR,4,24,pllq);
	switch(pllp){
		case 2:
			set_reg_block(&RCC->PLLCFGR,2,16,0);
		break;
		case 4:
			set_reg_block(&RCC->PLLCFGR,2,16,1);
		break;
		case 6:
			set_reg_block(&RCC->PLLCFGR,2,16,2);
		break;
		case 8:
			set_reg_block(&RCC->PLLCFGR,2,16,3);
		break;
		default: // 2
			set_reg_block(&RCC->PLLCFGR,2,16,0);
		break;
	}
	set_reg_block(&RCC->PLLCFGR,9,6,plln);
	set_reg_block(&RCC->PLLCFGR,6,0,pllm);
}
void STM32FXXXRccPLLCLKEnable(void)
{
	uint32_t rcc_time_out;
	//if(onoff){
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << 24) ; !(RCC->CR & (1 << 25)) && rcc_time_out; rcc_time_out-- ); // PLLON: Main PLL (PLL) enable
	//}else{
		//RCC->CR &= (unsigned int) ~(1 << 24);
	//}
}
void STM32FXXXRccPLLI2SEnable(void)
{
	uint32_t rcc_time_out;
	//if(onoff)
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << 26) ; !(RCC->CR & (1 << 27)) && rcc_time_out; rcc_time_out-- ); // PLLI2SON: PLLI2S enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 26);
}
void STM32FXXXRccPLLSAIEnable(void)
{
	uint32_t rcc_time_out;
	//if(onoff)
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << 28) ; !(RCC->CR & (1 << 29)) && rcc_time_out; rcc_time_out-- ); // PLLSAION: PLLSAI enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 28);
}
void STM32FXXXRccPwrClock(uint8_t bool)
{
	set_reg_block(&RCC->APB1ENR, 1, 28, bool); // Power interface clock enable
}
void STM32FXXXRccWriteEnable(void)
{
	PWR->CR |= (1 << 8); // Disable protection
}
void STM32FXXXRccWriteDisable(void)
{
	PWR->CR &= (uint32_t) ~(1 << 8); // Enable protection
}
/*** RCC Bit Mapping Definition ***/
/*** Other ***/
void STM32FXXXRCC_nvic(uint8_t bool)
{
	if(bool){ set_bit_block(NVIC->ISER, 1, RCC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, RCC_IRQn, 1); }
}
/*** Extended ***/
STM32FXXXRCCPLL* stm32fxxx_rcc_pll_inic(void)
{

	stm32fxxx_rcc_pll.division = STM32FXXXPLLDivision;
	stm32fxxx_rcc_pll.enable = STM32FXXXRccPLLCLKEnable;
	return &stm32fxxx_rcc_pll;
}
STM32FXXXRCCPLLI2S* stm32fxxx_rcc_plli2s_inic(void)
{

	stm32fxxx_rcc_plli2s.enable = STM32FXXXRccPLLI2SEnable;
	return &stm32fxxx_rcc_plli2s;
}
STM32FXXXRCCPLLSAI* stm32fxxx_rcc_pllsai_inic(void)
{

	stm32fxxx_rcc_pllsai.enable = STM32FXXXRccPLLSAIEnable;
	return &stm32fxxx_rcc_pllsai;
}
/*** INIC Procedure & Function Definition ***/
STM32FXXX_RCC* rcc_enable(void)
{

	/*** RCC Bit Mapping Link ***/
	stm32fxxx_rcc.instance = (STM32FXXXRCC_TypeDef*) RCC;
	stm32fxxx_rcc.prescaler = STM32FXXXPrescaler;
	/*** PLL ***/
	stm32fxxx_rcc.pll = stm32fxxx_rcc_pll_inic();
	stm32fxxx_rcc.plli2s = stm32fxxx_rcc_plli2s_inic();
	stm32fxxx_rcc.pllsai = stm32fxxx_rcc_pllsai_inic();
	/*** Other ***/
	stm32fxxx_rcc.inic = rcc_start;
	stm32fxxx_rcc.henable = STM32FXXXRccHEnable;
	stm32fxxx_rcc.hselect = STM32FXXXRccHSelect;
	stm32fxxx_rcc.lenable = STM32FXXXRccLEnable;
	stm32fxxx_rcc.lselect = STM32FXXXRccLSelect;
	/*** Nvic ***/
	stm32fxxx_rcc.nvic = STM32FXXXRCC_nvic;
	return &stm32fxxx_rcc;
}

STM32FXXX_RCC* rcc(void){ return &stm32fxxx_rcc; };

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

/*** EOF ***/

