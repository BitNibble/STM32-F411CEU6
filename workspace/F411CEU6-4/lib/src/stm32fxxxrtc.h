/******************************************************************************
	STM32 FXXX RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXRTC_H_
	#define _STM32FXXXRTC_H_

/*** Library ***/
#include "armquery.h"

/*** Define & Macro ***/
#ifndef RTC_KEY1
	#define RTC_KEY1 0xCA
#endif
#ifndef RTC_KEY2
	#define RTC_KEY2 0x53
#endif
#ifndef DATA_BITS
	#define DATA_BITS 31
#endif
#ifndef DATA_SIZE
	#define DATA_SIZE 32
#endif

/*** RTC TypeDef ***/
typedef struct
{

	/***/
	void (*Day)(uint8_t day);
	void (*Month)(uint8_t month);
	void (*WeekDay)(uint8_t weekday);
	void (*Year)(uint8_t year);
	void (*Hour)(uint8_t hour);
	void (*Minute)(uint8_t minute);
	void (*Second)(uint8_t second);
	void (*dr2vec)(char* rtc_vect);
	void (*tr2vec)(char* rtc_vect);
	void (*BckWrite)(uint8_t n, uint8_t data);
	uint8_t (*BckRead)(uint8_t n);
	uint8_t (*get_stsu)(void);
	uint16_t (*get_ss)(void);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*inic)(uint8_t clock);
	void (*nvic)(uint8_t value);
}STM32FXXX_RTC;
/***/

/*** Global ***/
STM32FXXX_RTC* rtc_enable(void);
STM32FXXX_RTC* rtc(void);

/*** RTC Procedure & Function Header ***/
void STM32FXXXRtcClock(uint8_t bool);
void STM32FXXXRtcNvic(uint8_t value);
void STM32FXXXRtcInic(uint8_t clock);
void STM32FXXXRtcBckWrite(uint8_t n, uint8_t data);
uint8_t STM32FXXXRtcBckRead(uint8_t n);
void STM32FXXXRtcHour(uint8_t hour);
void STM32FXXXRtcMinute(uint8_t minute);
void STM32FXXXRtcSecond(uint8_t second);
void STM32FXXXRtcDay(uint8_t day);
void STM32FXXXRtcYear(uint8_t year);
void STM32FXXXRtcMonth(uint8_t month);
void STM32FXXXRtcWeekDay(uint8_t weekday);
void STM32FXXXRtcdr2vec(char* rtc_vect);
void STM32FXXXRtctr2vec(char* rtc_vect);

/*** INTERRUPT ***/
void RTC_WKUP_IRQHandler(void);
void RTC_Alarm_IRQHandler(void);

#endif

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


