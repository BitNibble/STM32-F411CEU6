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
#include "stm32fxxxusart1.h"
#include "armlcd.h"
#include "armfunction.h"
#include "armsystick.h"

#define TM_LOCKED 0x03
#define TM_OPEN 0
#define FEEDBACK TM_OPEN
#define STEP 1
#define DELAY 2
#define TM_END 0
#define PORT_NUMBER 80

#define ESP8266_BUFF_SIZE 513
// Static buffer for command strings
static char ESP8266AT_str[ESP8266_BUFF_SIZE];
const uint32_t esp8266_buff_size = (ESP8266_BUFF_SIZE - 1);
// Turing parameters
static uint32_t tm_par[3] = {TM_OPEN,0,0};

char ESP8266_str[ESP8266_BUFF_SIZE];
const uint16_t esp8266_str_size = (ESP8266_BUFF_SIZE - 1);

/************************************************/
/******************** TOOLS *********************/
/************************************************/
// EXECUTE
const char* esp8266_cmd_execute(const char* cmd) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s\r\n", cmd);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
// QUERY
const char* esp8266_cmd_query(const char* cmd) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s?\r\n", cmd);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
// QUERY PAR
const char* esp8266_cmd_querypar(const char* cmd) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=?\r\n", cmd);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
// SET
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
const char* esp8266_cmd_set1ui16par(const char* cmd, uint16_t par1) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d\r\n", cmd, par1);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui81ui16par(const char* cmd, uint8_t par1, uint16_t par2) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,%d\r\n", cmd, par1, par2);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set2spar(const char* cmd, const char* par1, const char* par2) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\"\r\n", cmd, par1, par2);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set2s1ui8par(const char* cmd, const char* par1, const char* par2, uint8_t par3) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",%d\r\n", cmd, par1, par2, par3);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set2s2ui8par(const char* cmd, const char* par1, const char* par2, uint8_t par3, uint8_t par4) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",%d,%d\r\n", cmd, par1, par2, par3, par4);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set2ui82spar(const char* cmd, uint8_t par1, uint8_t par2, const char* par3, const char* par4) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,%d,\"%s\",\"%s\"\r\n", cmd, par1, par2, par3, par4);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set2ui8par(const char* cmd, uint8_t par1, uint8_t par2) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,%d\r\n", cmd, par1, par2);
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
const char* esp8266_cmd_set2s1ui16par(const char* cmd, const char* par1, const char* par2, uint16_t par3) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",%d\r\n", cmd, par1, par2, par3);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set3ui8par(const char* cmd, uint8_t par1, uint8_t par2, uint8_t par3) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,%d,%d\r\n", cmd, par1, par2, par3);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set4spar(const char* cmd, const char* par1, const char* par2, const char* par3, const char* par4) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",\"%s\",\"%s\"\r\n", cmd, par1, par2, par3, par4);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui81s1ui161spar(const char* cmd, uint8_t par1, const char* par2, uint16_t par3, const char* par4) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,\"%s\",%d,\"%s\"\r\n", cmd, par1, par2, par3, par4);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui81ui161s1ui16par(const char* cmd, uint8_t par1, uint16_t par2, const char* par3, uint16_t par4) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,%d,\"%s\",%d\r\n", cmd, par1, par2, par3, par4);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui82s1ui16par(const char* cmd, uint8_t par1, const char* par2, const char* par3, uint16_t par4) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,\"%s\",\"%s\",%d\r\n", cmd, par1, par2, par3, par4);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set5spar(const char* cmd, const char* par1, const char* par2, const char* par3, const char* par4, const char* par5) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\r\n", cmd, par1, par2, par3, par4, par5);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui81s1ui161s1ui16par(const char* cmd, uint8_t par1, const char* par2, uint16_t par3, const char* par4, uint16_t par5) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,\"%s\",%d,\"%s\",%d\r\n", cmd, par1, par2, par3, par4, par5);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set2s2ui161ui8par(const char* cmd, const char* par1, const char* par2, uint16_t par3, uint16_t par4, uint8_t par5) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",%d,%d,%d\r\n", cmd, par1, par2, par3, par4, par5);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui324ui8par(const char* cmd, unsigned int par1, uint8_t par2, uint8_t par3, uint8_t par4, uint8_t par5) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%u,%d,%d,%d,%d\r\n", cmd, par1, par2, par3, par4, par5);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set6spar(const char* cmd, const char* par1, const char* par2, const char* par3, const char* par4, const char* par5, const char* par6) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\r\n", cmd, par1, par2, par3, par4, par5, par6);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_set1ui82s2ui161ui8par(const char* cmd, uint8_t par1, const char* par2, const char* par3, uint16_t par4, uint16_t par5, uint8_t par6) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "AT+%s=%d,\"%s\",\"%s\",%d,%d,%d\r\n", cmd, par1, par2, par3, par4, par5, par6);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_1ui16par(const char* cmd, uint16_t par1) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "%s,%d\r\n", cmd, par1);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_1ui81ui16par(const char* cmd, uint8_t par1, uint16_t par2) {
	snprintf(ESP8266AT_str, sizeof(ESP8266AT_str), "%s,%d,%d\r\n", cmd, par1, par2);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
/************************************************/
/************** Basic AT Commands ***************/
/************************************************/
const char* esp8266_cmd_check(void) {
	// AT – Test AT startup
	// Response:
		//OK
	strncpy(ESP8266AT_str, "AT\r\n", esp8266_buff_size);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_reset(void) {
	// AT+RST – Restart module
	// Response:
		//OK
	return esp8266_cmd_execute("RST");
}
const char* esp8266_cmd_version(void) {
	// AT+GMR – View version info
	// Response:
		//<AT version info><SDK version info><compile time> OK
	return esp8266_cmd_execute("GMR");
}
const char* esp8266_cmd_setgslp(uint16_t time) {
	// AT+GSLP=<time>
	// Response:
		//<time> OK
	return esp8266_cmd_set1ui16par("GSLP", time);
}
const char* esp8266_cmd_echo(uint8_t enable) {
	// ATE – AT commands echo
	// Response:
		//OK
	if(enable){
		strncpy(ESP8266AT_str, "ATE1\r\n", esp8266_buff_size);
		ESP8266AT_str[esp8266_buff_size] = 0;
	}else{
		strncpy(ESP8266AT_str, "ATE0\r\n", esp8266_buff_size);
		ESP8266AT_str[esp8266_buff_size] = 0;
	}
	return ESP8266AT_str;
}
const char* esp8266_cmd_restore(void) {
	// AT+RESTORE – Factory reset
	// Response:
		//OK
	return esp8266_cmd_execute("RESTORE");
}
const char* esp8266_cmd_setuart(uint32_t baud, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t control) {
	// AT+UART_DEF=<baudrate>, <databits>, <stopbits>, <parity>, <flow control>
	// Response:
		//OK
	return esp8266_cmd_set1ui324ui8par("UART_DEF", baud, databits, stopbits, parity, control);
}
const char* esp8266_cmd_querysleep(void) {
	// AT+SLEEP – sleep mode
	// Response:
		//+SLEEP : <sleep mode> OK
	return esp8266_cmd_query("SLEEP");
}
const char* esp8266_cmd_setsleep(uint8_t mode) {
	// AT+SLEEP – sleep mode
	// Response:
		//OK
	return esp8266_cmd_set1ui8par("SLEEP", mode);
}
const char* esp8266_cmd_setrfpower(uint8_t TX_power) {
	// AT+RFPOWER – set RF TX Power
	// Response:
		//OK
	return esp8266_cmd_set1ui8par("RFPOWER", TX_power);
}
const char* esp8266_cmd_queryrfvdd(void) {
	// AT+RFVDD – set RF TX power according to VDD33
	// Response:
		//+RFVDD:<VDD33> OK
	return esp8266_cmd_query("RFVDD");
}
const char* esp8266_cmd_setrfvdd(uint16_t vdd33) {
	// AT+RFVDD – set RF TX power according to VDD33
	// Response:
		//OK
	return esp8266_cmd_set1ui16par("RFVDD", vdd33);
}
const char* esp8266_cmd_rfvdd(void) {
	// AT+RFVDD – set RF TX power according to VDD33
	// Response:
		//OK
	return esp8266_cmd_execute("RFVDD");
}
/************************************************/
/********** Wi-Fi Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_queryparwmode(void) {
	// AT+CWMODE – WiFi mode
	// Response:
		//+CWMODE:( value scope of <mode>) OK
	return esp8266_cmd_querypar("CWMODE_DEF");
}
const char* esp8266_cmd_querywmode(void) {
	// AT+CWMODE – WiFi mode
	// Response:
		//+CWMODE:<mode> OK
	return esp8266_cmd_query("CWMODE_DEF");
}
const char* esp8266_cmd_setwmode(uint8_t mode) {
	// AT+CWMODE – WiFi mode 1 2 or 3
	// Response:
		//OK
	return esp8266_cmd_set1ui8par("CWMODE_DEF", mode);
}
const char* esp8266_cmd_querywjap(void) {
	// AT+CWJAP – Connect to AP
	// Response:
		//+CWJAP_DEF:<ssid>, <bssid>, <channel>, <rssi> OK
	return esp8266_cmd_query("CWJAP_DEF");
	//return esp8266_cmd_query("CWJAP");
}
const char* esp8266_cmd_setwjap(const char* ssid, const char* password) {
	// AT+CWJAP – Connect to AP
	// Response:
		//OK or +CWJAP:<error code> FAIL
	return esp8266_cmd_set2spar("CWJAP_DEF", ssid, password);
	//return esp8266_cmd_set2spar("CWJAP", ssid, password);
}
const char* esp8266_cmd_setwlapopt(uint8_t sort_enable, uint8_t mask) {
	// AT+CWLAPOPT - Set configuration for command AT+CWLAP
	// Response:
		//OK or ERROR
	mask &= 0x7F;
	if(sort_enable)
		return esp8266_cmd_set2ui8par("CWLAPOPT", 1, mask);
	else
		return esp8266_cmd_set2ui8par("CWLAPOPT", 0, mask);
}
const char* esp8266_cmd_setwlap(const char* ssid) {
	// AT+CWLAP - Lists available APs
	// Response:
		//+CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration>
		//OK or ERROR
	return esp8266_cmd_set1spar("CWLAP", ssid);
}
const char* esp8266_cmd_wlap(void) {
	// AT+CWLAP - Lists available APs
	// Response:
		//+CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration>
		//OK or ERROR
	return esp8266_cmd_execute("CWLAP");
}
const char* esp8266_cmd_wqap(void) {
	// AT+CWQAP - Disconnect from AP
	// Response:
		//OK
	return esp8266_cmd_execute("CWQAP");
}
const char* esp8266_cmd_querywsap(void) {
	// AT+ CWSAP – Configuration of softAP mode
	// Response:
		//+CWSAP:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
	return esp8266_cmd_query("CWSAP_DEF");
}
const char* esp8266_cmd_setwsap(const char* ssid, const char* pwd, uint8_t chl, uint8_t ecn) {
	// AT+ CWSAP – Configuration of softAP mode
	// Response:
		//OK or ERROR
	return esp8266_cmd_set2s2ui8par("CWSAP_DEF", ssid, pwd, chl, ecn);
}
const char* esp8266_cmd_wlif(void) {
	// AT+ CWLIF– IP of stations which are connected to ESP8266 softAP
	// Response: <IP addr>, <mac>
		//OK
	return esp8266_cmd_execute("CWLIF");
}
const char* esp8266_cmd_querywdhcp(void) {
	// AT+ CWDHCP – Enable/Disable DHCP
	// Response:
		//DHCP disabled or enabled now?
	return esp8266_cmd_query("CWDHCP_DEF");
}
const char* esp8266_cmd_setwdhcp(uint8_t mode, uint8_t enable) {
	// AT+ CWDHCP – Enable/Disable DHCP
	const char* str = NULL;
	// Response:
		//OK
	mode &= 0x03;
	if(enable)
		str = esp8266_cmd_set2ui8par("CWDHCP_DEF", mode, 1);
	else
		str = esp8266_cmd_set2ui8par("CWDHCP_DEF", mode, 0);
	// mode 0, 1 or 2
	return str;
}
const char* esp8266_cmd_querywdhcps(void) {
	// AT+CWDHCPS_CUR – Set the IP address allocated by ESP8266 soft-AP DHCP, not be stored in flash
	// Response:
		//+CWDHCPS_DEF=<lease time>, <start IP>, <end IP>
	return esp8266_cmd_query("CWDHCPS_DEF");
}
const char* esp8266_cmd_setwdhcps(uint8_t enable, uint8_t mode, const char* start_IP, const char* end_IP) {
	// AT+CWDHCPS_CUR – Set the IP address allocated by ESP8266 soft-AP DHCP, not be stored in flash
	// Response:
		//OK
	return esp8266_cmd_set2ui82spar("CWDHCPS_DEF", enable, mode, start_IP, end_IP);
}
const char* esp8266_cmd_setwautoconn(uint8_t enable) {
	// AT+CWAUTOCONN – Connect to AP automatically or not
	// Response:
		//OK
	const char* str;
	if(enable)
		str = esp8266_cmd_set1ui8par("CWAUTOCONN", 1);
	else
		str = esp8266_cmd_set1ui8par("CWAUTOCONN", 0);
	return str;
}
const char* esp8266_cmd_queryipstamac(void) {
	// AT+ CIPSTAMAC – Set MAC address of ESP8266 station
	// Response:
		//+CIPSTAMAC_DEF:<mac> OK
	return esp8266_cmd_query("CIPSTAMAC_DEF");
}
const char* esp8266_cmd_setipstamac(const char* mac) {
	// AT+ CIPSTAMAC – Set MAC address of ESP8266 station
	// Response:
		//OK
	return esp8266_cmd_set1spar("CIPSTAMAC_DEF", mac);
}
const char* esp8266_cmd_queryipapmac(void) {
	// AT+ CIPAPMAC – Set MAC address of ESP8266 softAP
	// Response:
		//+CIPAPMAC_DEF:<mac> OK
	return esp8266_cmd_query("CIPAPMAC_DEF");
}
const char* esp8266_cmd_setipapmac(const char* mac) {
	// AT+ CIPAPMAC – Set MAC address of ESP8266 softAP
	// Response:
		//OK
	return esp8266_cmd_set1spar("CIPAPMAC_DEF", mac);
}
const char* esp8266_cmd_queryipsta(void) {
	// AT+ CIPSTA – Set IP address of ESP8266 station
	// Response:
		//+CIPSTA:<IP> OK
	return esp8266_cmd_query("CIPSTA_DEF");
}
const char* esp8266_cmd_setipsta(const char* IP, const char* gateway, const char* netmask) {
	// AT+ CIPSTA – Set IP address of ESP8266 station
	// Response:
		//OK
	return esp8266_cmd_set3spar("CIPSTA_DEF", IP, gateway, netmask);
}
const char* esp8266_cmd_queryipap(void) {
	// AT+ CIPAP – Set IP address of ESP8266 softAP
	// Response:
		//+CIPAP_DEF:<IP> OK
	return esp8266_cmd_query("CIPAP_DEF");
}
const char* esp8266_cmd_setipap(const char* IP, const char* gateway, const char* netmask) {
	// AT+ CIPAP – Set IP address of ESP8266 softAP
	// Response:
		//OK
	return esp8266_cmd_set3spar("CIPAP_DEF", IP, gateway, netmask);
}
const char* esp8266_cmd_wstartsmart(void) {
	// AT+CWSTARTSMART – Start SmartConfig
	// Response:
		//OK or ERROR
	return esp8266_cmd_execute("CWSTARTSMART");
}
const char* esp8266_cmd_setwstartsmart(uint8_t type) {
	// AT+CWSTARTSMART – Start SmartConfig
	// Response:
		//OK or ERROR
	type &= 0x03;
	return esp8266_cmd_set1ui8par("CWSTARTSMART", type);
}
const char* esp8266_cmd_wstopsmart(void) {
	// AT+CWSTOPSMART stop SmartConfig
	// Response:
		//OK or ERROR
	return esp8266_cmd_execute("CWSTOPSMART");
}
const char* esp8266_cmd_setwstartdiscover(const char* WeChat_number, const char* dev_type, uint8_t time) {
	// AT+CWSTARTDISCOVER
	// – Start the mode that ESP8266 can be found by WeChat which is in the same LAN
	// Response:
		//OK or ERROR
	return esp8266_cmd_set2s1ui8par("CWSTARTDISCOVER", WeChat_number, dev_type, time);
}
const char* esp8266_cmd_wstopdiscover(void) {
	// AT+CWSTOPDISCOVER
	// – Stop the mode that ESP8266 can be found by WeChat which is in the same LAN
	// Response:
		//OK or ERROR
	return esp8266_cmd_execute("CWSTOPDISCOVER");
}
const char* esp8266_cmd_setwps(uint8_t enable) {
	// AT+WPS – Set WPS function
	// Response:
		//OK or ERROR
	const char* str;
	if(enable)
		str = esp8266_cmd_set1ui8par("WPS", 1);
	else
		str = esp8266_cmd_set1ui8par("WPS", 0);
	return str;
}
const char* esp8266_cmd_setmdns(uint8_t enable, const char* hostname, const char* server_name, uint16_t server_port) {
	// AT+MDNS – Set MDNS function
	// Response:
		//OK or ERROR
	const char* str = NULL;
	if(enable)
		str = esp8266_cmd_set1ui82s1ui16par("MDNS", 1, hostname, server_name, server_port);
	else
		str = esp8266_cmd_set1ui82s1ui16par("MDNS", 0, hostname, server_name, server_port);
	return str;
}
/************************************************/
/********* TCP/IP Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_ipstatus(void) {
	// AT+CIPSTATUS – Check network connection status
	// Response:
		//STATUS:<stat>
		//+CIPSTATUS:<link ID>, <type>, <remote_IP>, <remote_port>, <local_port>, <tetype>
	return esp8266_cmd_execute("CIPSTATUS");
}
const char* esp8266_cmd_setipdomain(const char* domain_name) {
	// AT+CIPDOMAIN – DNS function
	// Response:
		//+CIPDOMAIN:<IP address>
	return esp8266_cmd_set1spar("CIPDOMAIN", domain_name);
	// ex:
	//AT+CWMODE=1 // Set station mode
	//AT+CWJAP="SSID","password"  access to the internet
	//AT+CIPDOMAIN="iot.espressif.cn"  DNS function
}
const char* esp8266_cmd_muxipstart_tcp(const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSTART – Function 1: Establish TCP connection
	// Response:
		//OK or ERROR
		//If TCP is connected already, returns ALREADY CONNECT
	return esp8266_cmd_set2s1ui16par("CIPSTART", "TCP", remote_IP, remote_port);
}
const char* esp8266_cmd_mux0ipstart_udp(const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode) {
	// AT+CIPSTART – Function 2: Register UDP port
	// Response:
		//OK or ERROR
		//If connection already exists, returns ALREADY CONNECT
	return esp8266_cmd_set2s2ui161ui8par("CIPSTART", "UDP", remote_IP, remote_port, UDP_local_port, UDP_mode);
}
const char* esp8266_cmd_mux1ipstart_udp(uint8_t link_ID, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode) {
	// AT+CIPSTART – Function 2: Register UDP port
	// Response:
		//OK or ERROR
		//If connection already exists, returns ALREADY CONNECT
	return esp8266_cmd_set1ui82s2ui161ui8par("CIPSTART", link_ID, "UDP", remote_IP, remote_port, UDP_local_port, UDP_mode);
}
const char* esp8266_cmd_muxipstart_ssl(const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSTART – Function 3: Establish SSL connection
	// Response:
		//OK or ERROR
		//If TCP is connected already, returns ALREADY CONNECT
	return esp8266_cmd_set2s1ui16par("CIPSTART", "SSL", remote_IP, remote_port);
}
const char* esp8266_cmd_ipsslsize(uint16_t size) {
	// AT+CIPSSLSIZE – Set the size of SSL buffer
	// Response:
		//OK or ERROR
	return esp8266_cmd_set1ui16par("CIPSSLSIZE", size);
}
const char* esp8266_cmd_mux0ipsend_udp(uint16_t length) {
	// AT+CIPSEND – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length is met, starts transmission of data.
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui16par("CIPSEND", length);
}
const char* esp8266_cmd_mux1ipsend_udp(uint8_t link_ID, uint16_t length) {
	// AT+CIPSEND – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length is met, starts transmission of data.
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui81ui16par("CIPSEND", link_ID, length);
}
const char* esp8266_cmd_ipsend_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSEND – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length is met, starts transmission of data.
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui81ui161s1ui16par("CIPSEND", link_ID, length, remote_IP, remote_port);
}
const char* esp8266_cmd_ipsend(void) {
	// AT+CIPSEND – Send data
	// Response:
	//Wrap return ">" after execute command. Enters unvarnished transmission,
	//20ms interval between each packet, maximum 2048 bytes per packet. When
	//single packet containing "+++" is received, it returns to normal command
	//mode. Please wait at least 1 second before sending next AT command.
	//This command can only be used in transparent transmission mode which
	//require to be single connection mode.
	//For UDP transparent transmission, <UDP mode> has to be 0 in command "AT+CIPSTART"
	return esp8266_cmd_execute("CIPSEND");
}
const char* esp8266_cmd_mux0ipsendex(uint16_t length) {
	// AT+CIPSENDEX – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length or "\0" is met, starts transmission of data.
		//So if sending "\0" is needed, please send it as "\\0"
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui16par("CIPSENDEX", length);
}
const char* esp8266_cmd_mux1ipsendex(uint8_t link_ID, uint16_t length) {
	// AT+CIPSENDEX – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length or "\0" is met, starts transmission of data.
		//So if sending "\0" is needed, please send it as "\\0"
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui81ui16par("CIPSENDEX", link_ID, length);
}
const char* esp8266_cmd_ipsendex(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSENDEX – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length or "\0" is met, starts transmission of data.
		//So if sending "\0" is needed, please send it as "\\0"
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui81ui161s1ui16par("CIPSENDEX", link_ID, length, remote_IP, remote_port);
}
const char* esp8266_cmd_mux0ipsend_tcp(uint16_t length) {
	// AT+CIPSENDBUF – Write data into TCP-send-buffer
	// Response:
		//<current segment ID>, <segment ID of which sent successfully>
		//OK
		//Wrap return ">" begins receiving of serial data, when data <length> is met,
		//send it; data more than <length> will be discarded, and returns "busy"
		//If connection cannot be established, or it’s not a TCP connection , or buffer
		//full, or some other error occurred, returns ERROR
		//If data is transmitted successfully,
		//(1) for single connection, returns
		//<segment ID>, SEND OK
		//(2) for multiple connection, returns
		//<link ID>, <segment ID>, SEND OK
	return esp8266_cmd_set1ui16par("CIPSENDBUF", length);
}
const char* esp8266_cmd_mux1ipsend_tcp(uint8_t link_ID, uint16_t length) {
	// AT+CIPSENDBUF – Write data into TCP-send-buffer
	// Response:
		//<current segment ID>, <segment ID of which sent successfully>
		//OK
		//Wrap return ">" begins receiving of serial data, when data <length> is met,
		//send it; data more than <length> will be discarded, and returns "busy"
		//If connection cannot be established, or it’s not a TCP connection , or buffer
		//full, or some other error occurred, returns ERROR
		//If data is transmitted successfully,
		//(1) for single connection, returns
		//<segment ID>, SEND OK
		//(2) for multiple connection, returns
		//<link ID>, <segment ID>, SEND OK
	return esp8266_cmd_set1ui81ui16par("CIPSENDBUF", link_ID, length);
}
const char* esp8266_cmd_mux0ipstatus_tcp(void) {
	// AT+CIPBUFSTATUS – Check status of TCP-send-buffer
	// Response:
		//<next segment ID>, < segment ID of which has sent >, < segment ID of
		//which sent successfully>, <remain buffer size>, <queue number>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_execute("CIPBUFSTATUS");
}
const char* esp8266_cmd_mux1ipstatus_tcp(uint8_t link_ID) {
	// AT+CIPBUFSTATUS – Check status of TCP-send-buffer
	// Response:
		//<next segment ID>, < segment ID of which has sent >, < segment ID of
		//which sent successfully>, <remain buffer size>, <queue number>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_set1ui8par("CIPBUFSTATUS", link_ID);
}
const char* esp8266_cmd_mux0ipcheckseq_tcp(uint8_t segment_ID) {
	// AT+CIPCHECKSEQ – Check if specific segment sent successfully or not
	// Response:
		//[<link ID>, ]<segment ID> , <status>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_set1ui8par("CIPCHECKSEQ", segment_ID);
}
const char* esp8266_cmd_mux1ipcheckseq_tcp(uint8_t link_ID, uint8_t segment_ID) {
	// AT+CIPCHECKSEQ – Check if specific segment sent successfully or not
	// Response:
		//[<link ID>, ]<segment ID> , <status>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_set2ui8par("CIPCHECKSEQ", link_ID, segment_ID);
}
const char* esp8266_cmd_mux0ipreset_tcp(void) {
	// AT+CIPBUFRESET – Reset segment ID count
	// Response:
		//OK If connection is not established or there are still TCP data wait for sending,
		//returns ERROR
	return esp8266_cmd_execute("CIPBUFRESET");
}
const char* esp8266_cmd_mux1ipreset_tcp(uint8_t link_ID) {
	// AT+CIPBUFRESET – Reset segment ID count
	// Response:
		//OK If connection is not established or there are still TCP data wait for sending,
		//returns ERROR
	return esp8266_cmd_set1ui8par("CIPBUFRESET", link_ID);
}
const char* esp8266_cmd_multipclose(uint8_t link_ID) {
	// AT+CIPCLOSE – Close TCP, UDP or SSL connection
	// Response:
		//OK or ERROR
	return esp8266_cmd_set1ui8par("CIPCLOSE", link_ID);
}
const char* esp8266_cmd_singipclose(void) {
	// AT+CIPCLOSE – Close TCP, UDP or SSL connection
	// Response:
		//OK or If no such connection, returns ERROR
	return esp8266_cmd_execute("CIPCLOSE");
}
const char* esp8266_cmd_ifsr(void) {
	// AT+CIFSR – Get local IP address
	// Response:
		//+ CIFSR:<IP address> OK ERROR
	return esp8266_cmd_execute("CIFSR"); // important to get IP
}
const char* esp8266_cmd_queryipmux(void) {
	// AT+ CIPMUX – Enable multiple connections or not
	// Response:
		//+ CIPMUX:<mode> OK
	return esp8266_cmd_query("CIPMUX");
}
const char* esp8266_cmd_setipmux(uint8_t mode) {
	// AT+ CIPMUX – Enable multiple connections or not
	// Response:
		//OK If already connected, returns Link is builded
	const char* str;
	if(mode)
		str = esp8266_cmd_set1ui8par("CIPMUX", 1);
	else
		str = esp8266_cmd_set1ui8par("CIPMUX", 0);
	return str;
}
const char* esp8266_cmd_muxipserver_tcp(uint8_t mode, uint16_t port) {
	// AT+CIPSERVER – Configure as TCP server
	// Response:
		//OK
	return esp8266_cmd_set1ui81ui16par("CIPSERVER", mode, port);
}
const char* esp8266_cmd_queryipmode(void) {
	// AT+ CIPMODE – Set transfer mode
	// Response:
		//+ CIPMODE:<mode> OK
	return esp8266_cmd_query("CIPMODE");
}
const char* esp8266_cmd_setipmode(uint8_t mode) {
	// AT+ CIPMODE – Set transfer mode
	// Response:
		//OK If already connected, returns Link is builded
	const char* str;
	if(mode)
		str = esp8266_cmd_set1ui8par("CIPMODE", 1);
	else
		str = esp8266_cmd_set1ui8par("CIPMODE", 0);
	return str;
}
const char* esp8266_cmd_savetranslink_tcp(uint8_t mode, const char* remote_IP, uint16_t remote_port) {
	// AT+SAVETRANSLINK – Save transparent transmission link to Flash
	// Response:
		//OK or ERROR
	return esp8266_cmd_set1ui81s1ui161spar("SAVETRANSLINK", mode, remote_IP, remote_port, "TCP");
}
const char* esp8266_cmd_savetranslink_udp(uint8_t mode, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port) {
	// AT+SAVETRANSLINK – Save transparent transmission link to Flash
	// Response:
		//OK or ERROR
	return esp8266_cmd_set1ui81s1ui161s1ui16par("SAVETRANSLINK", mode, remote_IP, remote_port, "UDP", UDP_local_port);
}
const char* esp8266_cmd_queryipsto_tcp(void) {
	// AT+ CIPSTO – Set TCP server timeout
	// Response:
		//+ CIPSTO:<time> OK
	return esp8266_cmd_query("CIPSTO");
}
const char* esp8266_cmd_ipsto_tcp(uint16_t time) {
	// AT+ CIPSTO – Set TCP server timeout
	// Response:
		//OK
	return esp8266_cmd_set1ui16par("CIPSTO", time);
}
const char* esp8266_cmd_ping(const char* host) {
	// AT+PING – Function Ping
	// Response:
		//+<time> OK Or ERROR // means ping fail
	return esp8266_cmd_set1spar("PING", host);
}
const char* esp8266_cmd_iupdate(void) {
	// AT+ CIUPDATE – update through network
	// Response:
		//+CIUPDATE:<n> OK
	return esp8266_cmd_execute("CIUPDATE"); // AT+CIFSR – Get local IP address
}
const char* esp8266_cmd_ipdinfo(uint8_t mode) {
	// AT+CIPDINFO – Show remote IP and port with "+IPD" ( received data from network )
	// Response:
		//OK or ERROR
	const char* str;
	if(mode)
		str = esp8266_cmd_set1ui8par("CIPDINFO", 1);
	else
		str = esp8266_cmd_set1ui8par("CIPDINFO", 0);
	return str;
}
/***
const char* esp8266_cmd_mux0ipd(uint16_t length) {
	// AT+CIPSEND – Send data
	// Response:
		//<data> data received
	return esp8266_cmd_1ui16par("+IPD", length);
	// ID 0
}
const char* esp8266_cmd_mux1ipd(uint8_t ID, uint16_t length) {
	// AT+CIPSEND – Send data
	// Response:
		//<data> data received
	return esp8266_cmd_1ui81ui16par("+IPD", ID, length);
	// ID 0 to 4
}
***/
/************************************************/
/*************** Turing Machines ****************/
/************************************************/
void tm_step( const char* tm_cmd, uint32_t tm_delay ) {
	if( tm_par[FEEDBACK] != TM_LOCKED ) { // ONESHOT
		tm_par[FEEDBACK] = TM_LOCKED;

		usart1()->transmit_string( tm_cmd ); // Access point
		tm_par[DELAY] = tm_delay; // wait com
	}
	if( !tm_par[DELAY] ){ tm_par[FEEDBACK] = TM_OPEN; tm_par[STEP]++; }else{ tm_par[DELAY]--; }
}
void tm_delay( uint32_t tm_delay ) {
	if( tm_par[FEEDBACK] != TM_LOCKED ){
		tm_par[FEEDBACK] = TM_LOCKED;
		tm_par[DELAY] = tm_delay; // wait com
	}
	if( !tm_par[DELAY] ){ tm_par[FEEDBACK] = TM_OPEN; }else{ tm_par[DELAY]--; }
}
void tm_delaystep( uint32_t tm_delay ) {
	if( tm_par[FEEDBACK] != TM_LOCKED ){
		tm_par[FEEDBACK] = TM_LOCKED;
		tm_par[DELAY] = tm_delay; // wait com
	}
	if( !tm_par[DELAY] ){ tm_par[FEEDBACK] = TM_OPEN; tm_par[STEP]++; }else{ tm_par[DELAY]--; }
}
uint32_t tm_getstep( void ) {
		return tm_par[STEP];
}
void tm_setstep( uint32_t tm_step ) {
	if( !tm_par[FEEDBACK] ){
		tm_par[STEP] = tm_step;
	}
}
void tm_jumpstep( uint32_t from, uint32_t to ) {
	if( !tm_par[FEEDBACK] ) {
		if( tm_getstep( ) == from ) {
			tm_par[STEP] = to;
		}
	}
}
void tm_purge( void ) {
	if( tm_par[FEEDBACK] != TM_LOCKED ) { // ONESHOT
		tm_par[FEEDBACK] = TM_LOCKED;
		usart1()->rx_flush();
		tm_par[FEEDBACK] = TM_OPEN;
	}
}
/************************************************/
/************************************************/
void Turingi0to6_Wifi_Connect( uint8_t mode, const char* ssid, const char* password ) {
	//mode: 1-STATION, 2-ACCESS POINT, 3-BOTH (number)
	//ssid; WIFI NAME (string)
	//password: WIFI PASSWORD (Router) (string)
	const char* str_connect = ESP8266_str;
	uint8_t i_connect = 0;
	if( mode == 1 || mode == 3 ) { // Filter par
		mode &= 0x03;
	}else {
		(void)i_connect;
		return;
	}
	while( tm_par[STEP] < 7 ){
		switch( tm_par[STEP] ) {
			case 0:
				tm_delay( 200 );
				tm_step( esp8266_cmd_version(), 2400 );
				//tm_step( esp8266_cmd_setuart(115200, 8, 1, 0, 0), 1000 );
				//tm_step( esp8266_cmd_setuart(38400, 8, 1, 0, 0), 1000 );
				i_connect = 0;
			break;
			case 1:
				tm_step( esp8266_cmd_setwmode(mode), 2400 );
				i_connect = 3;
			break;
			case 2:
				tm_step( esp8266_cmd_setipsta("192.168.1.53", "192.168.1.1", "255.255.255.0"), 4000 );
				i_connect = 3;
			break;
			case 3:
				//tm_step( esp8266_cmd_setwjap( ssid, password ), 14000 );
				tm_step( esp8266_cmd_setwjap( ssid, password ), 9000 );
				i_connect = 0;
			break;
			case 4:
				tm_step( esp8266_cmd_querywjap(), 4700 );
				i_connect = 17;
			break;
			case 5:
				tm_step( esp8266_cmd_ifsr(), 2100 );
				i_connect = 18;
			break;

			case 6:
				//tm_step( esp8266_cmd_reset(), 4000 );
				//tm_step( esp8266_cmd_restore(), 4000 );
				tm_step( esp8266_cmd_echo(1), 900 );
				i_connect = 0;
			break;
		}
		usart1()->receive_rxstring( ESP8266_str, esp8266_str_size, "\r\n" );
		lcd0()->gotoxy( 0, 0 );
		lcd0()->string_size( str_connect + i_connect, 20 );
	}
	lcd0()->clear();
	tm_setstep( TM_END );
}

void Turingi7to10_Wifi_Setting( void ) {
	switch( tm_par[STEP] ) {
		case 7:
			tm_step( esp8266_cmd_echo(1), 300 );
		break;
		case 8:
			tm_step( esp8266_cmd_setwlapopt(1, 0x1F), 300 );
		break;
		case 9:
			tm_step( esp8266_cmd_setwdhcp(2, 1), 300 );
		break;
		case 10:
			tm_step( esp8266_cmd_setwstartsmart(3), 300 );
			tm_setstep( TM_END );
		break;
	}
}

void Turingi11to17_Station_Mux0ClientSend_tcp( const char* server, const char * send, size_t size ) {
	switch( tm_par[STEP] ) {
		case 11:
			tm_step( esp8266_cmd_muxipstart_tcp(server, PORT_NUMBER), 900 );
		break;
		case 12:
			tm_step( esp8266_cmd_mux0ipsend_tcp(size), 800 ); // 1200
		break;
		case 13:
			tm_setstep(14);
			// Transmit data
			usart1()->transmit_string(send);
		break;
		case 14:
			tm_delaystep( 10 );
		break;
		case 15:
			tm_step( esp8266_cmd_singipclose(), 400 );
		break;
		case 16:
			tm_delaystep( 1000 );
		break;
		case 17:
			tm_step( esp8266_cmd_ipstatus(), 600 );
			tm_setstep( TM_END );
		break;
	}
}

void Turingi18to20_Station_Mux1Server( void ) {
	switch( tm_par[STEP] ) {
		case 18:
			tm_step( esp8266_cmd_setipmux(1), 450 );
		break;
		case 19:
			tm_step( esp8266_cmd_muxipserver_tcp(1, PORT_NUMBER), 800 ); // 1200
		break;
		case 20:
			//tm_state( esp8266_cmd_ifsr(), 500 );
			tm_delaystep( 200 );
			tm_setstep( TM_END );
		break;
	}
}

void Turingi21to26_Station_Mux1ServerSend_tcp( uint8_t link_ID, const char * send, size_t size ) {
	switch( tm_par[STEP] ) {
		case 21:
			tm_delaystep( 0 ); //50
		break;
		case 22:
			tm_step( esp8266_cmd_mux1ipsend_tcp( link_ID, size ), 300 ); // 400
		break;
		case 23:
			tm_setstep(24); // ##  24 do not change!  ##
			// Transmit data
			usart1()->transmit_string(send);
		break;
		case 24:
			tm_delaystep( 300 ); // 300
		break;
		case 25:
			if( link_ID )
				tm_step( esp8266_cmd_multipclose( link_ID ), 0 ); // 20
			else
				tm_delaystep( 0 ); // 20
			tm_purge();
		break;
		case 26:
			tm_delaystep( 0 ); // 0
			tm_setstep( TM_END );
		break;
	}
}

void Turingi500to504_Machine( void ) {
	switch( tm_par[STEP] ) {
		case 500:
			tm_step( esp8266_cmd_version(), 500 );
		break;
		case 501:
			tm_step( esp8266_cmd_querywjap(), 400 );
		break;
		case 502:
			tm_step( esp8266_cmd_ifsr(), 500 );
		break;
		case 503:
			tm_step( esp8266_cmd_ping("www.google.com"), 600 );
		break;
		case 504:
			tm_step( esp8266_cmd_echo(0), 200 );
			tm_setstep( TM_END );
		break;
	}
}

/***
tm_state( 10, esp8266_cmd_wlap(), 1300 );
Initialize -> Filter -> Execute -> return
str = esp8266_cmd_set1ui324ui8par("UART_DEF", 38400, 8, 1, 0, 0);
str = esp8266_cmd_set1ui324ui8par("UART_CUR", 38400, 8, 1, 0, 0);
str = esp8266_cmd_setuart(38400, 8, 1, 0, 0);
str = esp8266_cmd_restore(); // (115200, 8, 1, 0, 3);
str = esp8266_cmd_set1ui8par("RFPOWER", 50); // Max 82
str = esp8266_cmd_setmode(3);
str = esp8266_cmd_connect("NOS-9C64", "RUSXRCKL");
<remote IP or domain name>
ws -> work station
ip -> IP
ap -> access point
***/

/*** EOF ***/
