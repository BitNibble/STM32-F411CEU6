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

#define ESPTOUCH 1
#define AIRKISS 2
#define ESPTOUCH_AIRKISS 3

#define ESP8266_BUFF_SIZE 128
// Static buffer for command strings
static char ESP8266AT_str[ESP8266_BUFF_SIZE];
const uint32_t esp8266_buff_size = (ESP8266_BUFF_SIZE - 1);

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
const char* esp8266_cmd_echo(uint8_t state) {
	// ATE – AT commands echo
	// Response:
		//OK
	if(state){
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
const char* esp8266_cmd_queryparcwmode(void) {
	// AT+CWMODE – WiFi mode
	// Response:
		//+CWMODE:( value scope of <mode>) OK
	return esp8266_cmd_querypar("CWMODE_DEF");
}
const char* esp8266_cmd_querycwmode(void) {
	// AT+CWMODE – WiFi mode
	// Response:
		//+CWMODE:<mode> OK
	return esp8266_cmd_query("CWMODE_DEF");
}
const char* esp8266_cmd_setcwmode(uint8_t mode) {
	// AT+CWMODE – WiFi mode 1 2 or 3
	// Response:
		//OK
	return esp8266_cmd_set1ui8par("CWMODE_DEF", mode);
}
const char* esp8266_cmd_queryjap(void) {
	// AT+CWJAP – Connect to AP
	// Response:
		//+CWJAP_DEF:<ssid>, <bssid>, <channel>, <rssi> OK
	return esp8266_cmd_query("CWJAP_DEF");
}
const char* esp8266_cmd_setjap(const char* ssid, const char* password) {
	// AT+CWJAP – Connect to AP
	// Response:
		//OK or +CWJAP:<error code> FAIL
	return esp8266_cmd_set2spar("CWJAP_DEF", ssid, password);
}
const char* esp8266_cmd_setlapopt(uint8_t sort_enable, uint8_t mask) {
	// AT+CWLAPOPT - Set configuration for command AT+CWLAP
	// Response:
		//OK or ERROR
	mask &= 0x7F;
	if(sort_enable)
		return esp8266_cmd_set2ui8par("CWLAPOPT", 1, mask);
	else
		return esp8266_cmd_set2ui8par("CWLAPOPT", 0, mask);
}
const char* esp8266_cmd_setlap(const char* ssid) {
	// AT+CWLAP - Lists available APs
	// Response:
		//+CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration>
		//OK or ERROR
	return esp8266_cmd_set1spar("CWLAP", ssid);
}
const char* esp8266_cmd_lap(void) {
	// AT+CWLAP - Lists available APs
	// Response:
		//+CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration>
		//OK or ERROR
	return esp8266_cmd_execute("CWLAP");
}
const char* esp8266_cmd_qap(void) {
	// AT+CWQAP - Disconnect from AP
	// Response:
		//OK
	return esp8266_cmd_execute("CWQAP");
}
const char* esp8266_cmd_querysap(void) {
	// AT+ CWSAP – Configuration of softAP mode
	// Response:
		//+CWSAP:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
	return esp8266_cmd_query("CWSAP_DEF");
}
const char* esp8266_cmd_setsap(const char* ssid, const char* pwd, uint8_t chl, uint8_t ecn) {
	// AT+ CWSAP – Configuration of softAP mode
	// Response:
		//OK or ERROR
	return esp8266_cmd_set2s2ui8par("CWSAP_DEF", ssid, pwd, chl, ecn);
}
const char* esp8266_cmd_lif(void) {
	// AT+ CWLIF– IP of stations which are connected to ESP8266 softAP
	// Response:
		//<IP addr>, <mac> OK
	return esp8266_cmd_execute("CWLIF");
}
const char* esp8266_cmd_querydhcp(void) {
	// AT+ CWDHCP – Enable/Disable DHCP
	// Response:
		//DHCP disabled or enabled now? 0 or 1
	return esp8266_cmd_query("CWDHCP_DEF");
}
const char* esp8266_cmd_setdhcp(uint8_t mode, uint8_t enable) {
	// AT+ CWDHCP – Enable/Disable DHCP
	// Response:
		//OK
	return esp8266_cmd_set2ui8par("CWDHCP_DEF", mode, enable);
}
const char* esp8266_cmd_querydhcps(void) {
	// AT+CWDHCPS_CUR – Set the IP address allocated by ESP8266 soft-AP DHCP, not be stored in flash
	// Response:
		//+CWDHCPS_DEF=<lease time>, <start IP>, <end IP>
	return esp8266_cmd_query("CWDHCPS_DEF");
}
const char* esp8266_cmd_setdhcps(uint8_t enable, uint8_t mode, const char* start_IP, const char* end_IP) {
	// AT+CWDHCPS_CUR – Set the IP address allocated by ESP8266 soft-AP DHCP, not be stored in flash
	// Response:
		//OK
	return esp8266_cmd_set2ui82spar("CWDHCPS_DEF", enable, mode, start_IP, end_IP);
}
const char* esp8266_cmd_setautoconn(uint8_t enable) {
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
const char* esp8266_cmd_querystamac(void) {
	// AT+ CIPSTAMAC – Set MAC address of ESP8266 station
	// Response:
		//+CIPSTAMAC_DEF:<mac> OK
	return esp8266_cmd_query("CIPSTAMAC_DEF");
}
const char* esp8266_cmd_setstamac(const char* mac) {
	// AT+ CIPSTAMAC – Set MAC address of ESP8266 station
	// Response:
		//OK
	return esp8266_cmd_set1spar("CIPSTAMAC_DEF", mac);
}
const char* esp8266_cmd_queryapmac(void) {
	// AT+ CIPAPMAC – Set MAC address of ESP8266 softAP
	// Response:
		//+CIPAPMAC_DEF:<mac> OK
	return esp8266_cmd_query("CIPAPMAC_DEF");
}
const char* esp8266_cmd_setapmac(const char* mac) {
	// AT+ CIPAPMAC – Set MAC address of ESP8266 softAP
	// Response:
		//OK
	return esp8266_cmd_set1spar("CIPAPMAC_DEF", mac);
}
const char* esp8266_cmd_querysta(void) {
	// AT+ CIPSTA – Set IP address of ESP8266 station
	// Response:
		//+CIPSTA:<IP> OK
	return esp8266_cmd_query("CIPSTA_DEF");
}
const char* esp8266_cmd_setsta(const char* IP, const char* gateway, const char* netmask) {
	// AT+ CIPSTA – Set IP address of ESP8266 station
	// Response:
		//OK
	return esp8266_cmd_set3spar("CIPSTA_DEF", IP, gateway, netmask);
}
const char* esp8266_cmd_queryap(void) {
	// AT+ CIPAP – Set IP address of ESP8266 softAP
	// Response:
		//+CIPAP_DEF:<IP>OK
	return esp8266_cmd_query("CIPAP_DEF");
}
const char* esp8266_cmd_setap(const char* IP, const char* gateway, const char* netmask) {
	// AT+ CIPAP – Set IP address of ESP8266 softAP
	// Response:
		//OK
	return esp8266_cmd_set3spar("CIPAP_DEF", IP, gateway, netmask);
}
const char* esp8266_cmd_startsmart(void) {
	// AT+CWSTARTSMART – Start SmartConfig
	// Response:
		//OK or ERROR
	return esp8266_cmd_execute("CWSTARTSMART");
}
const char* esp8266_cmd_setstartsmart(uint8_t type) {
	// AT+CWSTARTSMART – Start SmartConfig
	// Response:
		//OK or ERROR
	type &= 0x03;
	return esp8266_cmd_set1ui8par("CWSTARTSMART", type);
}
const char* esp8266_cmd_stopsmart(void) {
	// AT+CWSTOPSMART stop SmartConfig
	// Response:
		//OK or ERROR
	return esp8266_cmd_execute("CWSTOPSMART");
}
const char* esp8266_cmd_setstartdiscover(const char* WeChat_number, const char* dev_type, uint8_t time) {
	// AT+CWSTARTDISCOVER
	// – Start the mode that ESP8266 can be found by WeChat which is in the same LAN
	// Response:
		//OK or ERROR
	return esp8266_cmd_set2s1ui8par("CWSTARTDISCOVER", WeChat_number, dev_type, time);
}
const char* esp8266_cmd_stopdiscover(void) {
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
	const char* str;
	if(enable)
		str = esp8266_cmd_set1ui82s1ui16par("MDNS", 1, hostname, server_name, server_port);
	else
		str = esp8266_cmd_set1ui82s1ui16par("MDNS", 0, hostname, server_name, server_port);
	return str;
}
/************************************************/
/********* TCP/IP Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_status(void) {
	// AT+CIPSTATUS – Check network connection status
	// Response:
		//STATUS:<stat>
		//+CIPSTATUS:<link ID>, <type>, <remote_IP>, <remote_port>, <local_port>, <tetype>
	return esp8266_cmd_execute("CIPSTATUS");
}
const char* esp8266_cmd_setdomain(const char* domain_name) {
	// AT+CIPDOMAIN – DNS function
	// Response:
		//+CIPDOMAIN:<IP address>
	return esp8266_cmd_set1spar("CIPDOMAIN", domain_name);
	// ex:
	//AT+CWMODE=1 // Set station mode
	//AT+CWJAP="SSID","password"  access to the internet
	//AT+CIPDOMAIN="iot.espressif.cn"  DNS function
}
const char* esp8266_cmd_muxstart_tcp(const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSTART – Function 1: Establish TCP connection
	// Response:
		//OK or ERROR
		//If TCP is connected already, returns ALREADY CONNECT
	return esp8266_cmd_set2s1ui16par("CIPSTART", "TCP", remote_IP, remote_port);
}
const char* esp8266_cmd_mux0start_udp(const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode) {
	// AT+CIPSTART – Function 2: Register UDP port
	// Response:
		//OK or ERROR
		//If connection already exists, returns ALREADY CONNECT
	return esp8266_cmd_set2s2ui161ui8par("CIPSTART", "UDP", remote_IP, remote_port, UDP_local_port, UDP_mode);
}
const char* esp8266_cmd_mux1start_udp(uint8_t link_ID, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode) {
	// AT+CIPSTART – Function 2: Register UDP port
	// Response:
		//OK or ERROR
		//If connection already exists, returns ALREADY CONNECT
	return esp8266_cmd_set1ui82s2ui161ui8par("CIPSTART", link_ID, "UDP", remote_IP, remote_port, UDP_local_port, UDP_mode);
}
const char* esp8266_cmd_muxstart_ssl(const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSTART – Function 3: Establish SSL connection
	// Response:
		//OK or ERROR
		//If TCP is connected already, returns ALREADY CONNECT
	return esp8266_cmd_set2s1ui16par("CIPSTART", "SSL", remote_IP, remote_port);
}
const char* esp8266_cmd_sslsize(uint16_t size) {
	// AT+CIPSSLSIZE – Set the size of SSL buffer
	// Response:
		//OK or ERROR
	return esp8266_cmd_set1ui16par("CIPSSLSIZE", size);
}
const char* esp8266_cmd_mux0send_udp(uint16_t length) {
	// AT+CIPSEND – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length is met, starts transmission of data.
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui16par("CIPSEND", length);
}
const char* esp8266_cmd_mux1send_udp(uint8_t link_ID, uint16_t length) {
	// AT+CIPSEND – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length is met, starts transmission of data.
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui81ui16par("CIPSEND", link_ID, length);
}
const char* esp8266_cmd_send_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSEND – Send data
	// Response:
		//Wrap return ">" after set command. Begins receive of serial data, when data
		//length is met, starts transmission of data.
		//If connection cannot be established or gets disconnected during send,
		//returns ERROR
		//If data is transmitted successfully, returns SEND OK
	return esp8266_cmd_set1ui81ui161s1ui16par("CIPSEND", link_ID, length, remote_IP, remote_port);
}
const char* esp8266_cmd_cipsend(void) {
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
const char* esp8266_cmd_mux0sendex(uint16_t length) {
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
const char* esp8266_cmd_mux1sendex(uint8_t link_ID, uint16_t length) {
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
const char* esp8266_cmd_sendex(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port) {
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
const char* esp8266_cmd_mux0send_tcp(uint16_t length) {
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
const char* esp8266_cmd_mux1send_tcp(uint8_t link_ID, uint16_t length) {
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
const char* esp8266_cmd_mux0status_tcp(void) {
	// AT+CIPBUFSTATUS – Check status of TCP-send-buffer
	// Response:
		//<next segment ID>, < segment ID of which has sent >, < segment ID of
		//which sent successfully>, <remain buffer size>, <queue number>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_execute("CIPBUFSTATUS");
}
const char* esp8266_cmd_mux1status_tcp(uint8_t link_ID) {
	// AT+CIPBUFSTATUS – Check status of TCP-send-buffer
	// Response:
		//<next segment ID>, < segment ID of which has sent >, < segment ID of
		//which sent successfully>, <remain buffer size>, <queue number>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_set1ui8par("CIPBUFSTATUS", link_ID);
}
const char* esp8266_cmd_mux0checkseq_tcp(uint8_t segment_ID) {
	// AT+CIPCHECKSEQ – Check if specific segment sent successfully or not
	// Response:
		//[<link ID>, ]<segment ID> , <status>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_set1ui8par("CIPCHECKSEQ", segment_ID);
}
const char* esp8266_cmd_mux1checkseq_tcp(uint8_t link_ID, uint8_t segment_ID) {
	// AT+CIPCHECKSEQ – Check if specific segment sent successfully or not
	// Response:
		//[<link ID>, ]<segment ID> , <status>
		//OK If connection is not established, returns ERROR
	return esp8266_cmd_set2ui8par("CIPCHECKSEQ", link_ID, segment_ID);
}
const char* esp8266_cmd_mux0reset_tcp(void) {
	// AT+CIPBUFRESET – Reset segment ID count
	// Response:
		//OK If connection is not established or there are still TCP data wait for sending,
		//returns ERROR
	return esp8266_cmd_execute("CIPBUFRESET");
}
const char* esp8266_cmd_mux1reset_tcp(uint8_t link_ID) {
	// AT+CIPBUFRESET – Reset segment ID count
	// Response:
		//OK If connection is not established or there are still TCP data wait for sending,
		//returns ERROR
	return esp8266_cmd_set1ui8par("CIPBUFRESET", link_ID);
}
const char* esp8266_cmd_multiclose(uint8_t link_ID) {
	// AT+CIPCLOSE – Close TCP, UDP or SSL connection
	// Response:
		//OK or ERROR
	return esp8266_cmd_set1ui8par("CIPCLOSE", link_ID);
}
const char* esp8266_cmd_singleclose(void) {
	// AT+CIPCLOSE – Close TCP, UDP or SSL connection
	// Response:
		//OK or If no such connection, returns ERROR
	return esp8266_cmd_execute("CIPCLOSE");
}
const char* esp8266_cmd_cifsr(void) {
	// AT+CIFSR – Get local IP address
	// Response:
		//+ CIFSR:<IP address> OK ERROR
	return esp8266_cmd_execute("CIFSR"); // AT+CIFSR – Get local IP address
}
const char* esp8266_cmd_querymux(void) {
	// AT+ CIPMUX – Enable multiple connections or not
	// Response:
		//+ CIPMUX:<mode> OK
	return esp8266_cmd_query("CIPMUX");
}
const char* esp8266_cmd_setmux(uint8_t mode) {
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
const char* esp8266_cmd_muxserver_tcp(uint8_t mode, uint16_t port) {
	// AT+CIPSERVER – Configure as TCP server
	// Response:
		//OK
	return esp8266_cmd_set1ui81ui16par("CIPSERVER", mode, port);
}
const char* esp8266_cmd_querycipmode(void) {
	// AT+ CIPMODE – Set transfer mode
	// Response:
		//+ CIPMODE:<mode> OK
	return esp8266_cmd_query("CIPMODE");
}
const char* esp8266_cmd_setcipmode(uint8_t mode) {
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
const char* esp8266_cmd_querysto_tcp(void) {
	// AT+ CIPSTO – Set TCP server timeout
	// Response:
		//+ CIPSTO:<time> OK
	return esp8266_cmd_query("CIPSTO");
}
const char* esp8266_cmd_sto_tcp(uint16_t time) {
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
const char* esp8266_cmd_update(void) {
	// AT+ CIUPDATE – update through network
	// Response:
		//+CIUPDATE:<n> OK
	return esp8266_cmd_execute("CIUPDATE"); // AT+CIFSR – Get local IP address
}
const char* esp8266_cmd_cipdinfo(uint8_t mode) {
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
Initialize -> Filter -> Execute -> return
str = esp8266_cmd_set1ui324ui8par("UART_DEF", 38400, 8, 1, 0, 0);
str = esp8266_cmd_set1ui324ui8par("UART_CUR", 38400, 8, 1, 0, 0);
str = esp8266_cmd_setuart(38400, 8, 1, 0, 0);
str = esp8266_cmd_restore(); // (115200, 8, 1, 0, 3);
str = esp8266_cmd_set1ui8par("RFPOWER", 50); // Max 82
str = esp8266_cmd_setmode(3);
str = esp8266_cmd_connect("NOS-9C64", "RUSXRCKL");
<remote IP or domain name>
***/

/*** EOF ***/

