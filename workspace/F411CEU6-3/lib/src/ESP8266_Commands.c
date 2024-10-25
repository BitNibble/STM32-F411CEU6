/******************************************************************************
	ESP8266 AT COMMANDS
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ALL
Date: 20102024
Comment:
	
*******************************************************************************/
#include "ESP8266_Commands.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#define STATION 1
#define SOFTAP 2
#define SOFTAP_STATION 3

#define ESP8266_BUFF_SIZE 128
// Static buffer for command strings
static char ESP8266AT_str[ESP8266_BUFF_SIZE];
const uint32_t esp8266_buff_size = (ESP8266_BUFF_SIZE - 1);

/************************************************/
/************ Command Model Function ************/
/************************************************/
const char* esp8266_cmd_check(void) {
	strncpy(ESP8266AT_str, "AT\r\n", esp8266_buff_size);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_echo(uint8_t state) {
	if(state){
		strncpy(ESP8266AT_str, "ATE1\r\n", esp8266_buff_size);
		ESP8266AT_str[esp8266_buff_size] = 0;
	}else{
		strncpy(ESP8266AT_str, "ATE0\r\n", esp8266_buff_size);
		ESP8266AT_str[esp8266_buff_size] = 0;
	}
	return ESP8266AT_str;
}
/******/
const char* esp8266_cmd_execute(const char* cmd) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s\r\n", cmd);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_query(const char* cmd) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s?\r\n", cmd);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_querypar(const char* cmd) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=?\r\n", cmd);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1spar(const char* cmd, const char* par1) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\"\r\n", cmd, par1);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui8par(const char* cmd, uint8_t par1) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d\r\n", cmd, par1);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set2spar(const char* cmd, const char* par1, const char* par2) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\"\r\n", cmd, par1, par2);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1s1ui16par(const char* cmd, const char* par1, uint16_t par2) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",%d\r\n", cmd, par1, par2);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set3spar(const char* cmd, const char* par1, const char* par2, const char* par3) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",\"%s\"\r\n", cmd, par1, par2, par3);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set4spar(const char* cmd, const char* par1, const char* par2, const char* par3, const char* par4) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",\"%s\",\"%s\"\r\n", cmd, par1, par2, par3, par4);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set5spar(const char* cmd, const char* par1, const char* par2, const char* par3, const char* par4, const char* par5) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\r\n", cmd, par1, par2, par3, par4, par5);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui324ui8par(const char* cmd, unsigned int par1, uint8_t par2, uint8_t par3, uint8_t par4, uint8_t par5) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%u,%d,%d,%d,%d\r\n", cmd, par1, par2, par3, par4, par5);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
/************************************************/
/*************** Command Functions **************/
/************************************************/
const char* esp8266_cmd_version(void) {
	return esp8266_cmd_execute("GMR");
}
const char* esp8266_cmd_querymode(void) {
	return esp8266_cmd_query("CWMODE");
}
const char* esp8266_cmd_setmode(uint8_t mode) {
	return esp8266_cmd_set1ui8par("CWMODE", mode);
}
const char* esp8266_cmd_queryjap(void) {
	return esp8266_cmd_query("CWJAP");
}
const char* esp8266_cmd_connect(const char* ssid, const char* password) {
	return esp8266_cmd_set2spar("CWJAP", ssid, password);
}
const char* esp8266_cmd_disconnect(void) {
	return esp8266_cmd_execute("CWQAP");
}
const char* esp8266_cmd_start_tcp(const char* ip, uint16_t port) {
	return esp8266_cmd_set1s1ui16par("CIPSTART=TCP", ip, port);
}
const char* esp8266_cmd_send(void) {
	return esp8266_cmd_execute("CIPSEND");
}
const char* esp8266_cmd_close(void) {
	return esp8266_cmd_execute("CIPCLOSE");
}
const char* esp8266_cmd_set_uart(uint32_t baud, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t control) {
	return esp8266_cmd_set1ui324ui8par("UART", baud, databits, stopbits, parity, control);
}
const char* esp8266_cmd_ping(const char* host) {
	return esp8266_cmd_set1spar("PING", host);
}
/************************************************/
/******/
/************************************************/
const char* esp8266_cmd_reset(void) {
	return esp8266_cmd_execute("RST");
}
const char* esp8266_cmd_restore(void) {
	return esp8266_cmd_execute("RESTORE");
}
/************************************************/
/************* Main Command Function ************/
/************************************************/
const char* esp8266_cmd(uint16_t num, const char* arg1, const char* arg2) {
	const char* str = NULL;
	switch (num) {
		case 0:
			//str = "ATE0\r\n"; break; // No echo
			//str = esp8266_cmd_check();
			str = esp8266_cmd_echo(0);
		break;
		case 1:
			//str = esp8266_cmd_check();
			str = esp8266_cmd_connect("NOS-9C64", "RUSXRCKL");
		break;
		case 2:
			str = esp8266_cmd_querypar("TEST");
			//str = esp8266_cmd_execute("CWLAP"); // ??

		break;
		case 3:
			str = esp8266_cmd_version();
		break;
		case 4:
			str = esp8266_cmd_querymode();
		break;
		case 5:
			str = esp8266_cmd_ping("example.microsoft.com");
			//str = esp8266_cmd_ping("127.0.0.1");
			//for(uint32_t roll = 300; roll; roll--);
		break;
	}
	return str;
}

/***
Initialize -> Filter -> Execute -> return
str = esp8266_cmd_set1ui324ui8par("UART_DEF", 38400, 8, 1, 0, 0);
str = esp8266_cmd_set1ui324ui8par("UART_CUR", 38400, 8, 1, 0, 0);
str = esp8266_cmd_set_uart(38400, 8, 1, 0, 0);
str = esp8266_cmd_restore(); // (115200, 8, 1, 0, 3);
str = esp8266_cmd_set1ui8par("RFPOWER", 50); // Max 82
str = esp8266_cmd_setmode(SOFTAP_STATION);
***/

/*** EOF ***/

