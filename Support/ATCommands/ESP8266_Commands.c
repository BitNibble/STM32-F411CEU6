/******************************************************************************
	ESP8266 AT COMMANDS
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ALL
Date: 20102024
Comment:
	
*******************************************************************************/
#include <stdint.h>
#include <string.h>

// Static buffer for command strings
static char ESP8266ATstr[64];


/*** Command Functions ***/
const char* esp8266_cmd_test(void) {
	strcpy(ESP8266ATstr, "AT\r\n");
	return ESP8266ATstr;
}

const char* esp8266_cmd_version(void) {
	strcpy(ESP8266ATstr, "AT+GMR\r\n");
	return ESP8266ATstr;
}

const char* esp8266_cmd_mode(void) {
	strcpy(ESP8266ATstr, "AT+CWMODE?\r\n");
	return ESP8266ATstr;
}

const char* esp8266_cmd_connect(const char* ssid, const char* password) {
	snprintf(ESP8266ATstr, sizeof(ESP8266ATstr), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
	return ESP8266ATstr;
}

const char* esp8266_cmd_disconnect(void) {
	strcpy(ESP8266ATstr, "AT+CWQAP\r\n");
	return ESP8266ATstr;
}

const char* esp8266_cmd_start_tcp(const char* ip, uint16_t port) {
	snprintf(ESP8266ATstr, sizeof(ESP8266ATstr), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
	return ESP8266ATstr;
}

const char* esp8266_cmd_send(void) {
	strcpy(ESP8266ATstr, "AT+CIPSEND\r\n");
	return ESP8266ATstr;
}

const char* esp8266_cmd_close(void) {
	strcpy(ESP8266ATstr, "AT+CIPCLOSE\r\n");
	return ESP8266ATstr;
}

const char* esp8266_cmd_set_uart(void) {
	strcpy(ESP8266ATstr, "AT+UART=115200,8,1,0,0\r\n");
	return ESP8266ATstr;
}

const char* esp8266_cmd_ping(const char* host) {
	snprintf(ESP8266ATstr, sizeof(ESP8266ATstr), "AT+PING=\"%s\"\r\n", host);
	return ESP8266ATstr;
}
/******/
const char* esp8266_cmd_reset(void) {
	strcpy(ESP8266ATstr, "AT+RST\r\n");
	return ESP8266ATstr;
}

/*** Main Command Function ***/
const char* esp8266_cmd(uint16_t num, const char* arg1, const char* arg2) {
	switch (num) {
		case 2: esp8266_cmd_version(); break;
		case 4: esp8266_cmd_mode(); break;
		default: esp8266_cmd_test(); break; // Default command
	}
}

/*** EOF ***/

