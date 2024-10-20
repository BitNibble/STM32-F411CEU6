#include <stdint.h>
#include <string.h>

// Static buffer for command strings
static char ESP8266ATstr[64];

/*** Function Prototypes ***/
static const char* esp8266_cmd_test(void);
static const char* esp8266_cmd_version(void);
static const char* esp8266_cmd_reset(void);
static const char* esp8266_cmd_mode(void);
static const char* esp8266_cmd_connect(const char* ssid, const char* password);
static const char* esp8266_cmd_disconnect(void);
static const char* esp8266_cmd_start_tcp(const char* ip, uint16_t port);
static const char* esp8266_cmd_send(void);
static const char* esp8266_cmd_close(void);
static const char* esp8266_cmd_set_uart(void);
static const char* esp8266_cmd_ping(const char* host);

/*** Command Functions ***/
static const char* esp8266_cmd_test(void) {
	strcpy(ESP8266ATstr, "AT\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_version(void) {
	strcpy(ESP8266ATstr, "AT+GMR\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_reset(void) {
	strcpy(ESP8266ATstr, "AT+RST\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_mode(void) {
	strcpy(ESP8266ATstr, "AT+CWMODE?\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_connect(const char* ssid, const char* password) {
	snprintf(ESP8266ATstr, sizeof(ESP8266ATstr), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
	return ESP8266ATstr;
}

static const char* esp8266_cmd_disconnect(void) {
	strcpy(ESP8266ATstr, "AT+CWQAP\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_start_tcp(const char* ip, uint16_t port) {
	snprintf(ESP8266ATstr, sizeof(ESP8266ATstr), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
	return ESP8266ATstr;
}

static const char* esp8266_cmd_send(void) {
	strcpy(ESP8266ATstr, "AT+CIPSEND\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_close(void) {
	strcpy(ESP8266ATstr, "AT+CIPCLOSE\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_set_uart(void) {
	strcpy(ESP8266ATstr, "AT+UART=115200,8,1,0,0\r\n");
	return ESP8266ATstr;
}

static const char* esp8266_cmd_ping(const char* host) {
	snprintf(ESP8266ATstr, sizeof(ESP8266ATstr), "AT+PING=\"%s\"\r\n", host);
	return ESP8266ATstr;
}

/*** Main Command Function ***/
static const char* esp8266_cmd(uint16_t num, const char* arg1, const char* arg2) {
	switch (num) {
		case 1: return esp8266_cmd_test();
		case 2: return esp8266_cmd_version();
		case 3: return esp8266_cmd_reset();
		case 4: return esp8266_cmd_mode();
		case 5: return esp8266_cmd_connect(arg1, arg2);
		case 6: return esp8266_cmd_disconnect();
		case 7: return esp8266_cmd_start_tcp(arg1, (uint16_t)atoi(arg2)); // arg2 is expected to be a number in string format
		case 8: return esp8266_cmd_send();
		case 9: return esp8266_cmd_close();
		case 10: return esp8266_cmd_set_uart();
		case 11: return esp8266_cmd_ping(arg1);
		default: return esp8266_cmd_test(); // Default command
	}
}

/*** EOF ***/

