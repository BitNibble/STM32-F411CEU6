/******************************************************************************
	STM32 FXXX RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxrtc.h"

static STM32FXXX_RTC stm32fxxx_rtc;
static uint32_t rtc_time_out;

/*** File Procedure & Function Header ***/
/***/
void STM32FXXXPwrClock(uint8_t bool);
void STM32FXXXBckSramClock(uint8_t bool);
void STM32FXXXRtcWriteEnable(void);
void STM32FXXXRtcWriteDisable(void);
void STM32FXXXRtcRegUnlock(void);
void STM32FXXXRtcRegWrite(volatile uint32_t* rtc_reg, uint32_t value);
void STM32FXXXRtcStopRead(void);
void STM32FXXXRtcWaitRead(void);
void STM32FXXXRtcSetTr(uint32_t value);
void STM32FXXXRtcSetDr(uint32_t value);
uint8_t rtc_get_stsu(void);
uint8_t rtc_get_st(void);
uint8_t rtc_get_su(void);
uint16_t rtc_get_ss(void);
char rtc_bcd2dec(char num);
char rtc_dec2bcd(char num);
void rtc_lenable(unsigned int lclock);
void rtc_lselect(uint8_t lclock);
/*** RTC Procedure & Function Definition ***/
STM32FXXX_RTC* rtc_enable(void)
{

	/***/
	stm32fxxx_rtc.Day = STM32FXXXRtcDay;
	stm32fxxx_rtc.Month = STM32FXXXRtcMonth;
	stm32fxxx_rtc.WeekDay = STM32FXXXRtcWeekDay;
	stm32fxxx_rtc.Year = STM32FXXXRtcYear;
	stm32fxxx_rtc.Hour = STM32FXXXRtcHour;
	stm32fxxx_rtc.Minute = STM32FXXXRtcMinute;
	stm32fxxx_rtc.Second = STM32FXXXRtcSecond;
	stm32fxxx_rtc.dr2vec = STM32FXXXRtcdr2vec;
	stm32fxxx_rtc.tr2vec = STM32FXXXRtctr2vec;
	stm32fxxx_rtc.BckWrite = STM32FXXXRtcBckWrite;
	stm32fxxx_rtc.BckRead = STM32FXXXRtcBckRead;
	stm32fxxx_rtc.get_stsu = rtc_get_stsu;
	stm32fxxx_rtc.get_ss = rtc_get_ss;
	/*** Other ***/
	stm32fxxx_rtc.clock = STM32FXXXRtcClock;
	stm32fxxx_rtc.nvic = STM32FXXXRtcNvic;
	stm32fxxx_rtc.inic = STM32FXXXRtcInic;

	return &stm32fxxx_rtc;
}

STM32FXXX_RTC* rtc(void){ return (STM32FXXX_RTC*) &stm32fxxx_rtc; }

/*** Procedure & Function Definition ***/
void STM32FXXXRtcClock(uint8_t bool)
{
	STM32FXXXRtcWriteEnable();
	if(bool){ RCC->BDCR |= (1 <<  15); }else{ RCC->BDCR &= ~(1 <<  15); }
	STM32FXXXRtcWriteDisable();

}
void STM32FXXXRtcNvic(uint8_t value)
{ // 3, 41
	switch(value){
		case 0b01:
			setbit(NVIC->ISER, 1, RTC_WKUP_IRQn, 1);
		break;
		case 0b10:
			setbit(NVIC->ISER, 1, RTC_Alarm_IRQn, 1);
		break;
		case 0b101:
			setbit(NVIC->ICER, 1, RTC_WKUP_IRQn, 1);
		break;
		case 0b110:
			setbit(NVIC->ICER, 1, RTC_Alarm_IRQn, 1);
		break;
	default:
	break;
	}
}
void STM32FXXXRtcInic(uint8_t clock)
{ // RM0390 pg657
	STM32FXXXPwrClock(1);
	STM32FXXXBckSramClock(1);
	STM32FXXXRtcClock(1);

	rtc_lenable(clock);
	rtc_lselect(clock);

	STM32FXXXRtcStopRead();

	//STM32FXXXRtcWriteEnable();
	//STM32FXXXRtcRegUnlock();
	//STM32FXXXRtcRegWrite(&RTC->TR, 0x130000);
	//STM32FXXXRtcRegWrite(&RTC->DR, 0x215124);
	//RTC->CR &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	//STM32FXXXRtcWriteDisable();
}

void STM32FXXXRtcBckWrite(uint8_t n, uint8_t data)
{
	STM32FXXXPwrClock(1);
	STM32FXXXBckSramClock(1);
	STM32FXXXRtcWriteEnable();
	if(n < 80){ setbit(&RTC->BKP0R, 8, (n * 8), data); }
	STM32FXXXRtcWriteDisable();
}

uint8_t STM32FXXXRtcBckRead(uint8_t n)
{
	uint8_t value = 0;
	if(n < 80){
		value = getsetbit(&RTC->BKP0R, 8, (n * 8));
	}
	return value;
}

void STM32FXXXRtcHour(uint8_t hour)
{
	uint32_t Time;
	uint8_t t, u;
	const uint32_t mask = 0x003F0000;
	
	t = rtc_dec2bcd(hour / 10);
	u = rtc_dec2bcd(hour % 10);
	STM32FXXXRtcWaitRead();
	Time = RTC->TR;
	Time &= (uint32_t) ~mask; // clear ht and hu
	// hu, ht
	Time |= (uint32_t) ((u << 16) | (t << 20));
	STM32FXXXRtcSetTr(Time);
}

void STM32FXXXRtcMinute(uint8_t minute)
{
	uint32_t Time;
	uint8_t t, u;
	const uint32_t mask = 0x00007F00;
	
	t = rtc_dec2bcd(minute / 10);
	u = rtc_dec2bcd(minute % 10);
	STM32FXXXRtcWaitRead();
	Time = RTC->TR;
	Time &= (uint32_t) ~mask; // clear mnt and mnu
	// mnu, mnt
	Time |= (uint32_t) ((u << 8) | (t << 12));
	STM32FXXXRtcSetTr(Time);
}

void STM32FXXXRtcSecond(uint8_t second)
{
	uint32_t Time;
	uint8_t t, u;
	const uint32_t mask = 0x0000007F;
	
	t = rtc_dec2bcd(second / 10);
	u = rtc_dec2bcd(second % 10);
	STM32FXXXRtcWaitRead();
	Time = RTC->TR;
	Time &= (uint32_t) ~mask; // clear st and su
	// su, st
	Time |= (uint32_t) ((u << 0) | (t << 4));
	STM32FXXXRtcSetTr(Time);
}

void STM32FXXXRtcYear(uint8_t year)
{
	uint32_t Date;
	uint8_t t, u;
	const uint32_t mask = 0x00FF0000;
	
	t = rtc_dec2bcd(year / 10);
	u = rtc_dec2bcd(year % 10);
	STM32FXXXRtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear YT and YU
	// YU, YT
	Date |= (uint32_t) ((u << 16) | (t << 20));
	STM32FXXXRtcSetDr(Date);
}

void STM32FXXXRtcMonth(uint8_t month)
{
	uint32_t Date;
	uint8_t t, u;
	const uint32_t mask = 0x00001F00;
	
	t = rtc_dec2bcd(month / 10);
	u = rtc_dec2bcd(month % 10);
	STM32FXXXRtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear MT and MU
	// MU, MT
	Date |= (uint32_t) ((u << 8) | (t << 12));
	STM32FXXXRtcSetDr(Date);
}

void STM32FXXXRtcWeekDay(uint8_t weekday)
{
	uint32_t Date;
	uint8_t u;
	const uint32_t mask = 0x0000E0000;
	
	u = rtc_dec2bcd(weekday % 10);
	STM32FXXXRtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear WDU
	// WDU
	Date |= (uint32_t) (u << 13);
	STM32FXXXRtcSetDr(Date);
}

void STM32FXXXRtcDay(uint8_t day)
{
	uint32_t Date;
	uint8_t t, u;
	const uint32_t mask = 0x0000003F;
	
	t = rtc_dec2bcd(day / 10);
	u = rtc_dec2bcd(day % 10);
	STM32FXXXRtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear DT and DU
	// DU, DT
	Date |= (uint32_t) ((u << 0) | (t << 4));
	STM32FXXXRtcSetDr(Date);
}

void STM32FXXXRtcdr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronisation flag
		uint32_t dr = RTC->DR;
		// YT
		rtc_vect[0] = (uint8_t) (dr >> 20) & 0x0F;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// YU
		rtc_vect[1] = (uint8_t) (dr >> 16) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// WDU
		rtc_vect[2] = (uint8_t) (dr >> 13) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// MT
		rtc_vect[3] = (uint8_t) (dr >> 12) & 0x01;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// MU
		rtc_vect[4] = (uint8_t) (dr >> 8) & 0x0F;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// DT
		rtc_vect[5] = (uint8_t) (dr >> 4) & 0x03;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// DU
		rtc_vect[6] = (uint8_t) dr & 0x0F;
		rtc_vect[6] = rtc_bcd2dec(rtc_vect[6]);
		// Store Value
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

void STM32FXXXRtctr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronisation flag
		uint32_t tr = RTC->TR;
		// ht
		rtc_vect[0] = (uint8_t) (tr >> 20) & 0x03;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// hu
		rtc_vect[1] = (uint8_t) (tr >> 16) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// mnt
		rtc_vect[2] = (uint8_t) (tr >> 12) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// mnu
		rtc_vect[3] = (uint8_t) (tr >> 8) & 0x0F;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// st
		rtc_vect[4] = (uint8_t) (tr >> 4) & 0x07;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// su
		rtc_vect[5] = (uint8_t) tr & 0x0F;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// Store value
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

uint8_t rtc_get_stsu(void)
{ // BCD
	uint32_t tr = RTC->TR;
	return (uint8_t) (tr & 0x007F);
}
uint8_t rtc_get_st(void)
{ // BCD
	uint32_t tr = RTC->TR;
	return (uint8_t) (tr >> 4) & 0x07;
}
uint8_t rtc_get_su(void)
{ // BCD
	uint32_t tr = RTC->TR;
	return (uint8_t) tr & 0x0F;
}
uint16_t rtc_get_ss(void)
{
	return RTC->SSR;
}

/*** AUX Procedure & Function Definition ***/
void STM32FXXXPwrClock(uint8_t bool)
{
	setreg(&RCC->APB1ENR, 1, 28, bool); // Power interface clock enable
}
void STM32FXXXBckSramClock(uint8_t bool)
{
	#ifdef STM32F446xx
		setreg(&RCC->AHB1ENR, 1, 18, bool); // Backup SRAM interface clock enable
	#endif
	setreg(&RCC->AHB1LPENR, 1, 16, bool); // Backup SRAM interface clock enable
}
void STM32FXXXRtcWriteEnable(void)
{
	PWR->CR |= (1 << 8); // Disable protection
}
void STM32FXXXRtcWriteDisable(void)
{
	PWR->CR &= (uint32_t) ~(1 << 8); // Enable protection
}
void STM32FXXXRtcRegUnlock(void)
{
	RTC->WPR |= RTC_KEY1;
	RTC->WPR |= RTC_KEY2;
}
void STM32FXXXRtcRegWrite(volatile uint32_t* rtc_reg, uint32_t value)
{
	RTC->ISR |= (1 << 7); // INIT
	for( rtc_time_out = 100; !(RTC->ISR & (1 << 6)) && rtc_time_out; rtc_time_out-- ); // INITF: Initialisation flag
	*rtc_reg = value;
	RTC->ISR &= (uint32_t) ~(1 << 7);
}
void STM32FXXXRtcStopRead(void)
{
	RTC->ISR &= ~(1 << 5);
}
void STM32FXXXRtcWaitRead(void)
{ // Wait Data Ready
	for(rtc_time_out = 200; !(RTC->ISR & (1 << 5)) && rtc_time_out; rtc_time_out--);
}
//RTC
void STM32FXXXRtcSetTr(uint32_t value)
{
	STM32FXXXRtcWriteEnable();
	STM32FXXXRtcRegUnlock();
	STM32FXXXRtcRegWrite(&RTC->TR, value);
	STM32FXXXRtcWriteDisable();
}
void STM32FXXXRtcSetDr(uint32_t value)
{
	STM32FXXXRtcWriteEnable();
	STM32FXXXRtcRegUnlock();
	STM32FXXXRtcRegWrite(&RTC->DR, value);
	STM32FXXXRtcWriteDisable();
}
/*** COMMON ***/
char rtc_bcd2dec(char num)
{
	return ((num / 16 * 10) + (num % 16));
}
char rtc_dec2bcd(char num)
{
	return ((num / 10 * 16) + (num % 10));
}
void rtc_lenable(unsigned int lclock)
{
	unsigned int set;
	unsigned int rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(lclock == 0){ // LSION: Internal low-speed oscillator enable
			if( set ){ STM32FXXXRtcWriteEnable(); RCC->CSR |= ( 1 << 0); STM32FXXXRtcWriteDisable(); set = 0; }else if( RCC->CSR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 1){ // LSEON: External low-speed oscillator enable
			if( set ){ STM32FXXXRtcWriteEnable(); RCC->BDCR |= ( 1 << 0); STM32FXXXRtcWriteDisable(); set = 0; }else if( RCC->BDCR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 2){ // LSEBYP: External low-speed oscillator bypass
			if( set ){ STM32FXXXRtcWriteEnable(); RCC->BDCR |= ( 1 << 2 ); STM32FXXXRtcWriteDisable(); }
			lclock = 1;
		}
		else lclock = 0; // default
	}
}
void rtc_lselect(uint8_t lclock)
{
	STM32FXXXRtcWriteEnable();
	RCC->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // Clear
	STM32FXXXRtcWriteDisable();
	switch(lclock){
		case 0:
			STM32FXXXRtcWriteEnable();
			RCC->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
			STM32FXXXRtcWriteDisable();
		break;
		case 1:
			STM32FXXXRtcWriteEnable();
			RCC->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
			STM32FXXXRtcWriteDisable();
		break;
		case 3:
			STM32FXXXRtcWriteEnable();
			RCC->BDCR |= ((1 << 8) | (1 << 9)); // HSE oscillator clock divided by a programmable pre-scaler
			STM32FXXXRtcWriteDisable();
		break;
		default:
			STM32FXXXRtcWriteEnable();
			RCC->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
			STM32FXXXRtcWriteDisable();
		break;
	}
}

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

