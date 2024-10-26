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
	strncpy(ESP8266AT_str, "AT\r\n", esp8266_buff_size);
	ESP8266AT_str[esp8266_buff_size] = 0;
	return ESP8266AT_str;
}
const char* esp8266_cmd_reset(void) {
	// AT+RST – Restart module
	return esp8266_cmd_execute("RST");
}
const char* esp8266_cmd_version(void) {
	// AT+GMR – View version info
	return esp8266_cmd_execute("GMR");
}
const char* esp8266_cmd_setgslp(uint16_t time) {
	// AT+GSLP=<time>
	return esp8266_cmd_set1ui16par("GSLP", time);
}
const char* esp8266_cmd_echo(uint8_t state) {
	// ATE – AT commands echo
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
	return esp8266_cmd_execute("RESTORE");
}
const char* esp8266_cmd_setuart(uint32_t baud, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t control) {
	// AT+UART_DEF=<baudrate>, <databits>, <stopbits>, <parity>, <flow control>
	return esp8266_cmd_set1ui324ui8par("UART", baud, databits, stopbits, parity, control);
}
const char* esp8266_cmd_querysleep(void) {
	// AT+SLEEP – sleep mode
	return esp8266_cmd_query("SLEEP");
}
const char* esp8266_cmd_setsleep(uint8_t mode) {
	// AT+SLEEP – sleep mode
	return esp8266_cmd_set1ui8par("SLEEP", mode);
}
const char* esp8266_cmd_setrfpower(uint8_t TX_power) {
	// AT+RFPOWER – set RF TX Power
	return esp8266_cmd_set1ui8par("RFPOWER", TX_power);
}
const char* esp8266_cmd_setrfvdd(uint16_t vdd33) {
	// AT+RFVDD – set RF TX power according to VDD33
	return esp8266_cmd_set1ui16par("RFVDD", vdd33);
}
const char* esp8266_cmd_rfvdd(void) {
	// AT+RFVDD – set RF TX power according to VDD33
	return esp8266_cmd_execute("RFVDD");
}
/************************************************/
/********** Wi-Fi Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_querycwmode(void) {
	// AT+CWMODE – WiFi mode
	return esp8266_cmd_query("CWMODE");
}
const char* esp8266_cmd_setcwmode(uint8_t mode) {
	// AT+CWMODE – WiFi mode 1 2 or 3
	return esp8266_cmd_set1ui8par("CWMODE", mode);
}
const char* esp8266_cmd_queryjap(void) {
	// AT+CWJAP – Connect to AP
	return esp8266_cmd_query("CWJAP");
}
const char* esp8266_cmd_setjap(const char* ssid, const char* password) {
	// AT+CWJAP – Connect to AP
	return esp8266_cmd_set2spar("CWJAP", ssid, password);
}
const char* esp8266_cmd_setlapopt(uint8_t sort_enable, uint8_t mask) {
	// AT+CWLAPOPT - Set configuration for command AT+CWLAP
	return esp8266_cmd_set2ui8par("CWLAPOPT", sort_enable, mask);
}
const char* esp8266_cmd_setlap(const char* ssid) {
	// AT+CWLAP - Lists available APs
	return esp8266_cmd_set1spar("CWLAP", ssid);
}
const char* esp8266_cmd_lap(void) {
	// AT+CWLAP - Lists available APs
	return esp8266_cmd_execute("CWLAP");
}
const char* esp8266_cmd_disconnect(void) {
	// AT+CWQAP - Disconnect from AP
	return esp8266_cmd_execute("CWQAP");
}
const char* esp8266_cmd_querysap(void) {
	// AT+ CWSAP – Configuration of softAP mode
	return esp8266_cmd_query("CWSAP");
}
const char* esp8266_cmd_setsap(const char* ssid, const char* pwd, uint8_t chl, uint8_t ecn) {
	// AT+ CWSAP – Configuration of softAP mode
	return esp8266_cmd_set2s2ui8par("CWSAP", ssid, pwd, chl, ecn);
}
const char* esp8266_cmd_lif(void) {
	// AT+ CWLIF– IP of stations which are connected to ESP8266 softAP
	return esp8266_cmd_execute("CWLIF");
}
const char* esp8266_cmd_querydhcp(void) {
	// AT+ CWDHCP – Enable/Disable DHCP
	return esp8266_cmd_query("CWDHCP");
}
const char* esp8266_cmd_setdhcp(uint8_t mode, uint8_t enable) {
	// AT+ CWDHCP – Enable/Disable DHCP
	return esp8266_cmd_set2ui8par("CWDHCP", mode, enable);
}
const char* esp8266_cmd_querydhcps(void) {
	// AT+CWDHCPS_CUR – Set the IP address allocated by ESP8266 soft-AP DHCP, not be stored in flash
	return esp8266_cmd_query("CWDHCPS_DEF");
}
const char* esp8266_cmd_setdhcps(uint8_t enable, uint8_t mode, const char* start_IP, const char* end_IP) {
	// AT+CWDHCPS_CUR – Set the IP address allocated by ESP8266 soft-AP DHCP, not be stored in flash
	return esp8266_cmd_set2ui82spar("CWDHCPS_DEF", enable, mode, start_IP, end_IP);
}
const char* esp8266_cmd_setautoconn(uint8_t enable) {
	// AT+CWAUTOCONN – Connect to AP automatically or not
	const char* str;
	if(enable)
		str = esp8266_cmd_set1ui8par("CWAUTOCONN", 1);
	else
		str = esp8266_cmd_set1ui8par("CWAUTOCONN", 0);
	return str;
}
const char* esp8266_cmd_querystamac(void) {
	// AT+ CIPSTAMAC – Set MAC address of ESP8266 station
	return esp8266_cmd_query("CIPSTAMAC");
}
const char* esp8266_cmd_setstamac(const char* mac) {
	// AT+ CIPSTAMAC – Set MAC address of ESP8266 station
	return esp8266_cmd_set1spar("CIPSTAMAC", mac);
}
const char* esp8266_cmd_queryapmac(void) {
	// AT+ CIPAPMAC – Set MAC address of ESP8266 softAP
	return esp8266_cmd_query("CIPAPMAC");
}
const char* esp8266_cmd_setapmac(const char* mac) {
	// AT+ CIPAPMAC – Set MAC address of ESP8266 softAP
	return esp8266_cmd_set1spar("CIPAPMAC", mac);
}
const char* esp8266_cmd_querysta(void) {
	// AT+ CIPSTA – Set IP address of ESP8266 station
	return esp8266_cmd_query("CIPSTA");
}
const char* esp8266_cmd_setsta(const char* IP, const char* gateway, const char* netmask) {
	// AT+ CIPSTA – Set IP address of ESP8266 station
	return esp8266_cmd_set3spar("CIPSTA", IP, gateway, netmask);
}
const char* esp8266_cmd_queryap(void) {
	// AT+ CIPAP – Set IP address of ESP8266 softAP
	return esp8266_cmd_query("CIPAP");
}
const char* esp8266_cmd_setap(const char* IP, const char* gateway, const char* netmask) {
	// AT+ CIPAP – Set IP address of ESP8266 softAP
	return esp8266_cmd_set3spar("CIPAP", IP, gateway, netmask);
}
const char* esp8266_cmd_startsmart(void) {
	// AT+CWSTARTSMART – Start SmartConfig
	return esp8266_cmd_execute("CWSTARTSMART");
}
const char* esp8266_cmd_setstartsmart(uint8_t type) {
	// AT+CWSTARTSMART – Start SmartConfig
	return esp8266_cmd_set1ui8par("CWSTARTSMART", type);
}
const char* esp8266_cmd_stopsmart(void) {
	// AT+CWSTOPSMART stop SmartConfig
	return esp8266_cmd_execute("CWSTOPSMART");
}
const char* esp8266_cmd_setstartdiscover(const char* WeChat_number, const char* dev_type, uint8_t time) {
	// AT+CWSTARTDISCOVER
	// – Start the mode that ESP8266 can be found by WeChat which is in the same LAN
	return esp8266_cmd_set2s1ui8par("CWSTARTDISCOVER", WeChat_number, dev_type, time);
}
const char* esp8266_cmd_stopdiscover(void) {
	// AT+CWSTOPDISCOVER
	// – Stop the mode that ESP8266 can be found by WeChat which is in the same LAN
	return esp8266_cmd_execute("CWSTOPDISCOVER");
}
const char* esp8266_cmd_setwps(uint8_t enable) {
	// AT+WPS – Set WPS function
	const char* str;
	if(enable)
		str = esp8266_cmd_set1ui8par("WPS", 1);
	else
		str = esp8266_cmd_set1ui8par("WPS", 0);
	return str;
}
const char* esp8266_cmd_setmdns(uint8_t enable, const char* hostname, const char* server_name, uint16_t server_port) {
	// AT+MDNS – Set MDNS function
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
	return esp8266_cmd_execute("CIPSTATUS");
}
const char* esp8266_cmd_setdomain(const char* domain_name) {
	// AT+CIPDOMAIN – DNS function
	return esp8266_cmd_set1spar("CIPDOMAIN", domain_name);
}
const char* esp8266_cmd_muxstart_tcp(const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSTART – Function 1: Establish TCP connection
	return esp8266_cmd_set2s1ui16par("CIPSTART", "TCP", remote_IP, remote_port);
}
const char* esp8266_cmd_mux0start_udp(const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode) {
	// AT+CIPSTART – Function 2: Register UDP port
	return esp8266_cmd_set2s2ui161ui8par("CIPSTART", "UDP", remote_IP, remote_port, UDP_local_port, UDP_mode);
}
const char* esp8266_cmd_mux1start_udp(uint8_t link_ID, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode) {
	// AT+CIPSTART – Function 2: Register UDP port
	return esp8266_cmd_set1ui82s2ui161ui8par("CIPSTART", link_ID, "UDP", remote_IP, remote_port, UDP_local_port, UDP_mode);
}
const char* esp8266_cmd_muxstart_ssl(const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSTART – Function 3: Establish SSL connection
	return esp8266_cmd_set2s1ui16par("CIPSTART", "SSL", remote_IP, remote_port);
}
const char* esp8266_cmd_sslsize(uint16_t size) {
	// AT+CIPSSLSIZE – Set the size of SSL buffer
	return esp8266_cmd_set1ui16par("CIPSSLSIZE", size);
}
const char* esp8266_cmd_mux0send_udp(uint16_t length) {
	// AT+CIPSEND – Send data
	return esp8266_cmd_set1ui16par("CIPSEND", length);
}
const char* esp8266_cmd_mux1send_udp(uint8_t link_ID, uint16_t length) {
	// AT+CIPSEND – Send data
	return esp8266_cmd_set1ui81ui16par("CIPSEND", link_ID, length);
}
const char* esp8266_cmd_send_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSEND – Send data
	return esp8266_cmd_set1ui81ui161s1ui16par("CIPSEND", link_ID, length, remote_IP, remote_port);
}
const char* esp8266_cmd_cipsend(void) {
	// AT+CIPSEND – Send data
	return esp8266_cmd_execute("CIPSEND");
}
const char* esp8266_cmd_mux0sendex_udp(uint16_t length) {
	// AT+CIPSENDEX – Send data
	return esp8266_cmd_set1ui16par("CIPSENDEX", length);
}
const char* esp8266_cmd_mux1sendex_udp(uint8_t link_ID, uint16_t length) {
	// AT+CIPSENDEX – Send data
	return esp8266_cmd_set1ui81ui16par("CIPSENDEX", link_ID, length);
}
const char* esp8266_cmd_sendex_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port) {
	// AT+CIPSENDEX – Send data
	return esp8266_cmd_set1ui81ui161s1ui16par("CIPSENDEX", link_ID, length, remote_IP, remote_port);
}
const char* esp8266_cmd_mux0send_tcp(uint16_t length) {
	// AT+CIPSENDBUF – Write data into TCP-send-buffer
	return esp8266_cmd_set1ui16par("CIPSENDBUF", length);
}
const char* esp8266_cmd_mux1send_tcp(uint8_t link_ID, uint16_t length) {
	// AT+CIPSENDBUF – Write data into TCP-send-buffer
	return esp8266_cmd_set1ui81ui16par("CIPSENDBUF", link_ID, length);
}
const char* esp8266_cmd_mux0status_tcp(void) {
	// AT+CIPBUFSTATUS – Check status of TCP-send-buffer
	return esp8266_cmd_execute("CIPBUFSTATUS");
}
const char* esp8266_cmd_mux1status_tcp(uint8_t link_ID) {
	// AT+CIPBUFSTATUS – Check status of TCP-send-buffer
	return esp8266_cmd_set1ui8par("CIPBUFSTATUS", link_ID);
}
const char* esp8266_cmd_mux0checkseq_tcp(uint8_t segment_ID) {
	// AT+CIPCHECKSEQ – Check if specific segment sent successfully or not
	return esp8266_cmd_set1ui8par("CIPCHECKSEQ", segment_ID);
}
const char* esp8266_cmd_mux1checkseq_tcp(uint8_t link_ID, uint8_t segment_ID) {
	// AT+CIPCHECKSEQ – Check if specific segment sent successfully or not
	return esp8266_cmd_set2ui8par("CIPCHECKSEQ", link_ID, segment_ID);
}
const char* esp8266_cmd_mux0reset_tcp(void) {
	// AT+CIPBUFRESET – Reset segment ID count
	return esp8266_cmd_execute("CIPBUFRESET");
}
const char* esp8266_cmd_mux1reset_tcp(uint8_t link_ID) {
	// AT+CIPBUFRESET – Reset segment ID count
	return esp8266_cmd_set1ui8par("CIPBUFRESET", link_ID);
}
const char* esp8266_cmd_multiclose(uint8_t link_ID) {
	// AT+CIPCLOSE – Close TCP, UDP or SSL connection
	return esp8266_cmd_set1ui8par("CIPCLOSE", link_ID);
}
const char* esp8266_cmd_singleclose(void) {
	// AT+CIPCLOSE – Close TCP, UDP or SSL connection
	return esp8266_cmd_execute("CIPCLOSE");
}
const char* esp8266_cmd_cifsr(void) {
	// AT+CIFSR – Get local IP address
	return esp8266_cmd_execute("CIFSR"); // AT+CIFSR – Get local IP address
}
const char* esp8266_cmd_querymux(void) {
	// AT+ CIPMUX – Enable multiple connections or not
	return esp8266_cmd_query("CIPMUX");
}
const char* esp8266_cmd_setmux(uint8_t mode) {
	// AT+ CIPMUX – Enable multiple connections or not
	const char* str;
	if(mode)
		str = esp8266_cmd_set1ui8par("CIPMUX", 1);
	else
		str = esp8266_cmd_set1ui8par("CIPMUX", 0);
	return str;
}
const char* esp8266_cmd_mux1server_tcp(uint8_t mode, uint16_t port) {
	// AT+CIPSERVER – Configure as TCP server
	return esp8266_cmd_set1ui81ui16par("CIPSERVER", mode, port);
}
const char* esp8266_cmd_querycipmode(void) {
	// AT+ CIPMODE – Set transfer mode
	return esp8266_cmd_query("CIPMODE");
}
const char* esp8266_cmd_setcipmode(uint8_t mode) {
	// AT+ CIPMODE – Set transfer mode
	const char* str;
	if(mode)
		str = esp8266_cmd_set1ui8par("CIPMODE", 1);
	else
		str = esp8266_cmd_set1ui8par("CIPMODE", 0);
	return str;
}
const char* esp8266_cmd_savetranslink_tcp(uint8_t mode, const char* remote_IP, uint16_t remote_port) {
	// AT+SAVETRANSLINK – Save transparent transmission link to Flash
	return esp8266_cmd_set1ui81s1ui161spar("SAVETRANSLINK", mode, remote_IP, remote_port, "TCP");
}
const char* esp8266_cmd_savetranslink_udp(uint8_t mode, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port) {
	// AT+SAVETRANSLINK – Save transparent transmission link to Flash
	return esp8266_cmd_set1ui81s1ui161s1ui16par("SAVETRANSLINK", mode, remote_IP, remote_port, "UDP", UDP_local_port);
}
const char* esp8266_cmd_querysto_tcp(void) {
	// AT+ CIPSTO – Set TCP server timeout
	return esp8266_cmd_query("CIPSTO");
}
const char* esp8266_cmd_sto_tcp(uint16_t time) {
	// AT+ CIPSTO – Set TCP server timeout
	return esp8266_cmd_set1ui16par("CIPSTO", time);
}
const char* esp8266_cmd_ping(const char* host) {
	// AT+PING – Function Ping
	return esp8266_cmd_set1spar("PING", host);
}
const char* esp8266_cmd_update(void) {
	// AT+ CIUPDATE – update through network
	return esp8266_cmd_execute("CIUPDATE"); // AT+CIFSR – Get local IP address
}
const char* esp8266_cmd_cipdinfo(uint8_t mode) {
	// AT+CIPDINFO – Show remote IP and port with "+IPD" ( received data from network )
	const char* str;
	if(mode)
		str = esp8266_cmd_set1ui8par("CIPDINFO", 1);
	else
		str = esp8266_cmd_set1ui8par("CIPDINFO", 0);
	return str;
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
			str = esp8266_cmd_check();
		break;
		case 2:
			str = esp8266_cmd_querydhcp();
		break;
		case 3:
			str = esp8266_cmd_querystamac();
		break;
		case 4:
			str = esp8266_cmd_querysta();
		break;
		case 5:
			str = esp8266_cmd_version();
		break;
		case 6:
			str = esp8266_cmd_querycwmode();
		break;
		case 7:
			str = esp8266_cmd_status();
		break;
		case 8:
			str = esp8266_cmd_cifsr();
		break;
		case 9:
			//str = esp8266_cmd_ping("example.microsoft.com");
			//str = esp8266_cmd_ping("127.0.0.1");
			str = esp8266_cmd_ping("www.google.com");
			//for(uint32_t roll = 300; roll; roll--);
		break;
	}
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

