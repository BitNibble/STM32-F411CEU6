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

/************************************************/
/************** Basic AT Commands ***************/
/************************************************/
const char* esp8266_cmd_check(void);
const char* esp8266_cmd_reset(void);
const char* esp8266_cmd_version(void);
const char* esp8266_cmd_setgslp(uint16_t time);
const char* esp8266_cmd_echo(uint8_t state);
const char* esp8266_cmd_restore(void);
const char* esp8266_cmd_setuart(uint32_t baud, uint8_t databits, uint8_t stopbits, uint8_t parity, uint8_t control);
const char* esp8266_cmd_querysleep(void);
const char* esp8266_cmd_setsleep(uint8_t mode);
const char* esp8266_cmd_setrfpower(uint8_t TX_power);
const char* esp8266_cmd_setrfvdd(uint16_t vdd33);
const char* esp8266_cmd_rfvdd(void);
/************************************************/
/********** Wi-Fi Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_querycwmode(void);
const char* esp8266_cmd_setcwmode(uint8_t mode);
const char* esp8266_cmd_queryjap(void);
const char* esp8266_cmd_setjap(const char* ssid, const char* password);
const char* esp8266_cmd_setlapopt(uint8_t sort_enable, uint8_t mask);
const char* esp8266_cmd_setlap(const char* ssid);
const char* esp8266_cmd_lap(void);
const char* esp8266_cmd_disconnect(void);
const char* esp8266_cmd_querysap(void);
const char* esp8266_cmd_setsap(const char* ssid, const char* pwd, uint8_t chl, uint8_t ecn);
const char* esp8266_cmd_lif(void);
const char* esp8266_cmd_querydhcp(void);
const char* esp8266_cmd_setdhcp(uint8_t mode, uint8_t enable);
const char* esp8266_cmd_querydhcps(void);
const char* esp8266_cmd_setdhcps(uint8_t enable, uint8_t mode, const char* start_IP, const char* end_IP);
const char* esp8266_cmd_setautoconn(uint8_t enable);
const char* esp8266_cmd_querystamac(void);
const char* esp8266_cmd_setstamac(const char* mac);
const char* esp8266_cmd_queryapmac(void);
const char* esp8266_cmd_setapmac(const char* mac);
const char* esp8266_cmd_querysta(void);
const char* esp8266_cmd_setsta(const char* IP, const char* gateway, const char* netmask);
const char* esp8266_cmd_queryap(void);
const char* esp8266_cmd_setap(const char* IP, const char* gateway, const char* netmask);
const char* esp8266_cmd_startsmart(void);
const char* esp8266_cmd_setstartsmart(uint8_t type);
const char* esp8266_cmd_stopsmart(void);
const char* esp8266_cmd_setstartdiscover(const char* WeChat_number, const char* dev_type, uint8_t time);
const char* esp8266_cmd_stopdiscover(void);
const char* esp8266_cmd_setwps(uint8_t enable);
const char* esp8266_cmd_setmdns(uint8_t enable, const char* hostname, const char* server_name, uint16_t server_port);
/************************************************/
/********* TCP/IP Related AT Commands ***********/
/************************************************/
const char* esp8266_cmd_status(void);
const char* esp8266_cmd_setdomain(const char* domain_name);
const char* esp8266_cmd_muxstart_tcp(const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_mux0start_udp(const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode);
const char* esp8266_cmd_mux1start_udp(uint8_t link_ID, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port, uint8_t UDP_mode);
const char* esp8266_cmd_muxstart_ssl(const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_sslsize(uint16_t size);
const char* esp8266_cmd_mux0send_udp(uint16_t length);
const char* esp8266_cmd_mux1send_udp(uint8_t link_ID, uint16_t length);
const char* esp8266_cmd_send_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_cipsend(void);
const char* esp8266_cmd_mux0sendex_udp(uint16_t length);
const char* esp8266_cmd_mux1sendex_udp(uint8_t link_ID, uint16_t length);
const char* esp8266_cmd_sendex_udp(uint8_t link_ID, uint16_t length, const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_mux0send_tcp(uint16_t length);
const char* esp8266_cmd_mux1send_tcp(uint8_t link_ID, uint16_t length);
const char* esp8266_cmd_mux0status_tcp(void);
const char* esp8266_cmd_mux1status_tcp(uint8_t link_ID);
const char* esp8266_cmd_mux0checkseq_tcp(uint8_t segment_ID);
const char* esp8266_cmd_mux1checkseq_tcp(uint8_t link_ID, uint8_t segment_ID);
const char* esp8266_cmd_mux0reset_tcp(void);
const char* esp8266_cmd_mux1reset_tcp(uint8_t link_ID);
const char* esp8266_cmd_multiclose(uint8_t link_ID);
const char* esp8266_cmd_singleclose(void);
const char* esp8266_cmd_cifsr(void);
const char* esp8266_cmd_querymux(void);
const char* esp8266_cmd_setmux(uint8_t mode);
const char* esp8266_cmd_mux1server_tcp(uint8_t mode, uint16_t port);
const char* esp8266_cmd_querycipmode(void);
const char* esp8266_cmd_setcipmode(uint8_t mode);
const char* esp8266_cmd_savetranslink_tcp(uint8_t mode, const char* remote_IP, uint16_t remote_port);
const char* esp8266_cmd_savetranslink_udp(uint8_t mode, const char* remote_IP, uint16_t remote_port, uint16_t UDP_local_port);
const char* esp8266_cmd_querysto_tcp(void);
const char* esp8266_cmd_sto_tcp(uint16_t time);
const char* esp8266_cmd_ping(const char* host);
const char* esp8266_cmd_update(void);
const char* esp8266_cmd_cipdinfo(uint8_t mode);
/************************************************/
/************* Main Command Function ************/
/************************************************/
const char* esp8266_cmd(uint16_t num, const char* arg1, const char* arg2);

#endif


/*** EOF ***/
