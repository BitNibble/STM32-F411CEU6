/*************************************************************************
	ARMLCD
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32
Date: 28052023
Comment:
	STM32F446RE and STM32F411CEU6
	- Make sure the delay are working in the inic function.
************************************************************************/
/*** File Library ***/
#include "armlcd.h"
/*** File Constant & Macro ***/
// CMD RS
#define ARMLCD0_INST 0
#define ARMLCD0_DATA 1
#define ARMLCD0_LCDCMDMASK ((1 << ARMLCD0_RS) | (1 << ARMLCD0_RW) | (1 << ARMLCD0_EN))

/*** File Variable ***/
static ARMLCD0 setup_armlcd0;
static GPIO_TypeDef* ireg;
static uint32_t armlcd0_detect;

/*** File Header ***/
void ARMLCD0_inic(void);
void ARMLCD0_write(char c, unsigned short D_I);
char ARMLCD0_read(unsigned short D_I);
void ARMLCD0_BF(void);
void ARMLCD0_putch(char c);
char ARMLCD0_getch(void);
void ARMLCD0_string(const char* s); // RAW
void ARMLCD0_string_size(const char* s, uint32_t size); // RAW
void ARMLCD0_hspace(uint32_t n);
void ARMLCD0_clear(void);
void ARMLCD0_gotoxy(unsigned int y, unsigned int x);
void ARMLCD0_reboot(void);

/*** LCD0 Procedure & Function Definition ***/
ARMLCD0 ARMLCD0_enable(GPIO_TypeDef* reg)
{
	// ALLOCACAO MEMORIA PARA Estrutura

	// import parameters
	ireg = reg;
	// initialize variables
	// Direccionar apontadores para PROTOTIPOS
	setup_armlcd0.write = ARMLCD0_write;
	setup_armlcd0.read = ARMLCD0_read;
	setup_armlcd0.BF = ARMLCD0_BF;
	setup_armlcd0.putch = ARMLCD0_putch;
	setup_armlcd0.getch = ARMLCD0_getch;
	setup_armlcd0.string = ARMLCD0_string; // RAW
	setup_armlcd0.string_size = ARMLCD0_string_size; // RAW
	setup_armlcd0.hspace = ARMLCD0_hspace;
	setup_armlcd0.clear = ARMLCD0_clear;
	setup_armlcd0.gotoxy = ARMLCD0_gotoxy;
	setup_armlcd0.reboot = ARMLCD0_reboot;
	// LCD INIC
	ARMLCD0_inic();
	
	return setup_armlcd0;
}

ARMLCD0* lcd0(void){ return (ARMLCD0*) &setup_armlcd0; }

void ARMLCD0_inic(void)
{
	//uint8_t repeat;
	// LCD INIC
	ireg->MODER &= (uint32_t) ~((3 << (ARMLCD0_RS * 2)) | (3 << (ARMLCD0_RW * 2)) | (3 << (ARMLCD0_EN * 2))); // reset control pins
	ireg->MODER |= ((1 << (ARMLCD0_RS * 2)) | (1 << (ARMLCD0_RW * 2)) | (1 << (ARMLCD0_EN * 2))); // control pins as output
	
	ireg->PUPDR &= (uint32_t) ~((3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2))); // reset pull up resistors
	ireg->PUPDR |= ((1 << (ARMLCD0_DB4 * 2)) | (1 << (ARMLCD0_DB5 * 2)) | (1 << (ARMLCD0_DB6 * 2)) | (1 << (ARMLCD0_DB7 * 2))); // enable pull up resistors

	ireg->MODER &= (uint32_t) ~(3 << (ARMLCD0_NC * 2)); // reboot detect input
	
	ireg->PUPDR &= (uint32_t) ~(3 << (ARMLCD0_NC * 2)); // reset pull up resistors
	ireg->PUPDR |= (1 << (ARMLCD0_NC * 2)); // pull up resistors

	ireg->OSPEEDR &= (uint32_t) ~( (3 << (ARMLCD0_RS * 2)) | (3 << (ARMLCD0_RW * 2)) | (3 << (ARMLCD0_EN * 2)) | (3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2)) ); // reset speed
	//ireg->OSPEEDR |= ( (3 << (ARMLCD0_RS * 2)) | (3 << (ARMLCD0_RW * 2)) | (3 << (ARMLCD0_EN * 2)) | (3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2)) ); // set speed
	 
	armlcd0_detect = ireg->IDR & (1 << ARMLCD0_NC);
	
	// INICIALIZACAO LCD datasheet
	_delay_ms(20); // using clock at 16Mhz
	ARMLCD0_write(0x38, ARMLCD0_INST); // function set
	_delay_10us(4);
	ARMLCD0_write(0x38, ARMLCD0_INST); // function set
	_delay_10us(10);
	ARMLCD0_write(0x38, ARMLCD0_INST); // function set
	_delay_10us(4);
	ARMLCD0_write(0x28, ARMLCD0_INST); // function set 2B
	_delay_10us(4);
	ARMLCD0_write(0x28, ARMLCD0_INST); // function set 2B
	_delay_10us(4);
	
	//for(repeat = 1 ; repeat ; repeat--){
		// repeat twice in 4 bit length
		ARMLCD0_write(0x28, ARMLCD0_INST); // function set 2B
		ARMLCD0_BF();
		ARMLCD0_write(0x28, ARMLCD0_INST); // function set 2B
		ARMLCD0_BF();

		ARMLCD0_write(0x0C, ARMLCD0_INST); // display on/off control
		ARMLCD0_BF();
		ARMLCD0_write(0x0C, ARMLCD0_INST); // display on/off control
		ARMLCD0_BF();

		ARMLCD0_write(0x01, ARMLCD0_INST); // clear display
		ARMLCD0_BF();
		ARMLCD0_write(0x01, ARMLCD0_INST); // clear display
		ARMLCD0_BF();

		ARMLCD0_write(0x06, ARMLCD0_INST); // entry mode set (crazy settings)
		ARMLCD0_BF();
		ARMLCD0_write(0x06, ARMLCD0_INST); // entry mode set (crazy settings)
		ARMLCD0_BF();
	//}
	// INICIALIZATION END
	// ARMLCD0_write(0x1F, ARMLCD0_INST); // cursor or display shift
	// _delay_10us(4);
	// ARMLCD0_write(0x03, ARMLCD0_INST); // return home
	// _delay_ms(10);
	ARMLCD0_gotoxy(0,0);
}
void ARMLCD0_write(char c, unsigned short D_I)
{ // write to LCD
	resetpin(ireg,ARMLCD0_RW); // lcd as input
	ireg->MODER &= (uint32_t) ~((3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2))); // reset mcu output
	ireg->MODER |= ((1 << (ARMLCD0_DB4 * 2)) | (1 << (ARMLCD0_DB5 * 2)) | (1 << (ARMLCD0_DB6 * 2)) | (1 << (ARMLCD0_DB7 * 2))); // mcu as output
	
	if(D_I) setpin(ireg, ARMLCD0_RS); else resetpin(ireg, ARMLCD0_RS);
	
	setpin(ireg, ARMLCD0_EN);
	if(c & 0x80) setpin(ireg,ARMLCD0_DB7); else resetpin(ireg,ARMLCD0_DB7);
	if(c & 0x40) setpin(ireg,ARMLCD0_DB6); else resetpin(ireg,ARMLCD0_DB6);
	if(c & 0x20) setpin(ireg,ARMLCD0_DB5); else resetpin(ireg,ARMLCD0_DB5);
	if(c & 0x10) setpin(ireg,ARMLCD0_DB4); else resetpin(ireg,ARMLCD0_DB4);
	resetpin(ireg, ARMLCD0_EN);
	
	if(D_I) setpin(ireg, ARMLCD0_RS); else resetpin(ireg, ARMLCD0_RS);
	
	setpin(ireg, ARMLCD0_EN);
	if(c & 0x08) setpin(ireg,ARMLCD0_DB7); else resetpin(ireg,ARMLCD0_DB7);
	if(c & 0x04) setpin(ireg,ARMLCD0_DB6); else resetpin(ireg,ARMLCD0_DB6);
	if(c & 0x02) setpin(ireg,ARMLCD0_DB5); else resetpin(ireg,ARMLCD0_DB5);
	if(c & 0x01) setpin(ireg,ARMLCD0_DB4); else resetpin(ireg,ARMLCD0_DB4);
	resetpin(ireg, ARMLCD0_EN);
}

char ARMLCD0_read(unsigned short D_I)
{ // Read from LCD
	uint32_t data = 0;
	uint8_t c = 0;
	ireg->MODER &= (uint32_t) ~((3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2))); // reset mcu input
	setpin(ireg, ARMLCD0_RW); // lcd as output
	
	if(D_I) setpin(ireg, ARMLCD0_RS); else resetpin(ireg, ARMLCD0_RS);
	
	setpin(ireg, ARMLCD0_EN);
	data = ireg->IDR; // read data
	resetpin(ireg, ARMLCD0_EN);
	
	if(data & (1 << ARMLCD0_DB7)) c |= 1 << 7; else c &= ~(1 << 7);
	if(data & (1 << ARMLCD0_DB6)) c |= 1 << 6; else c &= ~(1 << 6);
	if(data & (1 << ARMLCD0_DB5)) c |= 1 << 5; else c &= ~(1 << 5);
	if(data & (1 << ARMLCD0_DB4)) c |= 1 << 4; else c &= ~(1 << 4);
	
	if(D_I) setpin(ireg, ARMLCD0_RS); else resetpin(ireg, ARMLCD0_RS);
	
	setpin(ireg, ARMLCD0_EN);
	data = ireg->IDR; // read data
	resetpin(ireg, ARMLCD0_EN);

	if(data & (1 << ARMLCD0_DB7)) c |= 1 << 3; else c &= ~(1 << 3);
	if(data & (1 << ARMLCD0_DB6)) c |= 1 << 2; else c &= ~(1 << 2);
	if(data & (1 << ARMLCD0_DB5)) c |= 1 << 1; else c &= ~(1 << 1);
	if(data & (1 << ARMLCD0_DB4)) c |= 1 << 0; else c &= ~(1 << 0);

	return c;
}

void ARMLCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = ARMLCD0_read(ARMLCD0_INST);
		if(i > 10) // 1
			break;
	}
}

char ARMLCD0_getch(void)
{
	char c;
	c = ARMLCD0_read(ARMLCD0_DATA);
	ARMLCD0_BF();
	return c;
}

void ARMLCD0_putch(char c)
{
	ARMLCD0_write(c, ARMLCD0_DATA);
	ARMLCD0_BF();
}

void ARMLCD0_string(const char* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		ARMLCD0_putch(tmp);
	}
}

void ARMLCD0_string_size(const char* s, uint32_t size)
{
	char tmp;
	uint32_t pos = 0;
	while(*s){
		tmp=*(s++);
		pos++;
		if(pos > size) // 1 TO SIZE+1
			break;
		ARMLCD0_putch(tmp);
	}
	while(pos < size){ // TO SIZE
		ARMLCD0_putch(' ');
		pos++;
	}
}

void ARMLCD0_hspace(uint32_t n)
{
	for(; n; n--){
		ARMLCD0_putch(' ');
	}
}

void ARMLCD0_clear(void)
{
	ARMLCD0_write(0x01, ARMLCD0_INST);
	_delay_10us(200);
}

void ARMLCD0_gotoxy(unsigned int y, unsigned int x)
{
	switch(y){
		case 0:
			ARMLCD0_write((char)(0x80 + x), ARMLCD0_INST);
			ARMLCD0_BF();
		break;
		case 1:
			ARMLCD0_write((char)(0xC0 + x), ARMLCD0_INST);
			ARMLCD0_BF();
		break;
		case 2:
			ARMLCD0_write((char)(0x94 + x), ARMLCD0_INST); // 0x94
			ARMLCD0_BF();
		break;
		case 3:
			ARMLCD0_write((char)(0xD4 + x), ARMLCD0_INST); // 0xD4
			ARMLCD0_BF();
		break;
		default:
		break;
	}
}

void ARMLCD0_reboot(void)
{
	// low high detect pin NC
	uint32_t i;
	uint32_t tmp;
	tmp = ireg->IDR & (1 << ARMLCD0_NC);
	i = tmp ^ armlcd0_detect;
	i &= tmp;
	if(i)
		ARMLCD0_inic();
	armlcd0_detect = tmp;
}

/******************************************************************************
void ARMLCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	for( ; 0x80 & ARMLCD0_read(ARMLCD0_INST) ; );
}

void ARMLCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = ARMLCD0_read(ARMLCD0_INST);
		if(i > 3)
			break;
	}
}
*******************************************************************************/

/***EOF***/

