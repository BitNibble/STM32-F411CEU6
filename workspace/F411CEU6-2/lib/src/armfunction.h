/************************************************************************
	ARMFUNCTION
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 18062023
Update: 07012024
Comment:
	Tested ->  Atemga128, Atmega328, Atmega32U4, Atmega324, Atmega8535, Atmega88, STM32F446RE
	Very Stable
************************************************************************/
#ifndef _ARMFUNCTION_H_
	#define _ARMFUNCTION_H_

/*** Global Library ***/
#include "armquery.h"
#include "armsystick.h"
#include "armlcd.h"
/*** Global Define & Macro ***/
#define FUNCSTRSIZE 31

typedef struct {
    uint32_t Numerator;   // The numerator of the fraction
    uint32_t Denominator; // The denominator of the fraction
    uint32_t Quotient;    // The integer part of the real number
    uint32_t Remainder;   // The remainder part after division
    double Fpart;          // The fractional part as a double
    int8_t sign;          // The sign of the number (-1 for negative, 1 for positive)
} Real;

typedef struct{
	void (*dispar4x20)(ARMLCD0* func_lcd);
}ARM_FUNC;

/*** PROCEDURE & FUNCTION TypeDef ***/
typedef struct
{
	// PROTOTYPES VTABLE
	/*** ARM ***/
	ARM_FUNC* arm;
	/******/
	uint16_t (*SwapByte)(uint16_t num);
	/******/
	Real (*divide)(int32_t numerator, int32_t denominator);
	Real (*realnumber)(double real, uint32_t precision);
	int (*stringlength)(const char string[]);
	void (*reverse)(char* str);
	unsigned int (*mayia)(unsigned int xi, unsigned int xf, uint8_t nbits);
	void (*swap)(long *px, long *py);
	void (*copy)(char to[], char from[]);
	void (*squeeze)(char s[], int c);
	void (*shellsort)(int v[], int n);
	char* (*resizestr)(char *string, int size);
	int (*trim)(char s[]);
	/******/
	uint8_t (*bcd2dec)(uint8_t num);
	uint8_t (*dec2bcd)(uint8_t num);
	char* (*dectohex)(int32_t num);
	uint8_t (*bcd2bin)(uint8_t val);
	int (*twocomptoint8bit)(int twoscomp);
	int (*twocomptoint10bit)(int twoscomp);
	int (*twocomptointnbit)(int twoscomp, uint8_t nbits);
	/******/
	char* (*print_v1)( char* str, uint8_t size_str, const char* format, ... );
	char* (*print_v2)( const char *format, ... );
	char* (*print_binary)(unsigned int n_bits, unsigned int number);
	/*******/
	char* (*i16toa)(int16_t n);
	char* (*ui16toa)(uint16_t n);
	char* (*i32toa)(int32_t n);
	char* (*ui32toa)(uint32_t n);
	char* (*ftoa)(double num, uint32_t precision);
	char* (*floattotext)(float number, int precision);
	/*******/
	int (*strToInt)(const char string[]);
	/*******/
	long (*trimmer)(long x, long in_min, long in_max, long out_min, long out_max);
	int (*pmax)(int a1, int a2);
	int (*gcd_v1)(uint32_t a, uint32_t b);
	long (*gcd_v2)(long a, long b);
	/******/
	uint32_t (*triggerA)(uint32_t hllh_io, uint8_t pin, uint32_t counter);
	uint32_t (*triggerB)(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
	uint32_t (*value)(void);
}FUNC;

FUNC FUNC_enable(void);
FUNC* func(void);

#endif

/***EOF***/

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

