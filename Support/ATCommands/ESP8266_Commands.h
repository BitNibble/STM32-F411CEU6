/******************************************************************************
	ESP8266 AT COMMANDS
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ALL
Date: 20102024
Comment:
	
*******************************************************************************/
#ifndef _ESP8266_COMMANDS_
	#define _ESP8266_COMMANDS_
 
#include <stdint.h>
#include <inttypes.h>
 
/*** Function Prototypes ***/
const char* esp8266_cmd(uint16_t num, const char* arg1, const char* arg2);
const char* esp8266_cmd_test(void);
const char* esp8266_cmd_version(void);
const char* esp8266_cmd_mode(void);
const char* esp8266_cmd_connect(const char* ssid, const char* password);
const char* esp8266_cmd_disconnect(void);
const char* esp8266_cmd_start_tcp(const char* ip, uint16_t port);
const char* esp8266_cmd_send(void);
const char* esp8266_cmd_close(void);
const char* esp8266_cmd_set_uart(void);
const char* esp8266_cmd_ping(const char* host);
/******/
const char* esp8266_cmd_reset(void);


#endif