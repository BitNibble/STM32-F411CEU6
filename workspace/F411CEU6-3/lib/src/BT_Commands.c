/******************************************************************************
	BT AT COMMANDS
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ALL
Date: 20102024
Comment:
	
*******************************************************************************/
#include "BT_Commands.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/*** USER ***/
const char* BT_AT_NAME_1(void) {
	return "HOME1";
}
const char* BT_AT_NAME_2(void) {
	return "BT05";
}
const char* BT_AT_PSWD_1(void) {
	return "916919";
}
/*** 1. General Functions for AT Commands ***/
// Function to get the basic AT command string (for testing the module)
const char* BT_AT_Test(void) {
	return "AT\r\n";
}

// Function to get the reset command string
const char* BT_AT_Reset(void) {
	return "AT+RESET\r\n";
}

// Function to get the firmware version command string
const char* BT_AT_GetVersion(void) {
	return "AT+VERSION\r\n";
}

// Function to get the restore factory settings command string
const char* BT_AT_RestoreDefaults(void) {
	return "AT+ORGL\r\n";
}

// Function to get the command string for getting the Bluetooth address
const char* BT_AT_GetAddress(void) {
	return "AT+ADDR?\r\n";
}

// Function to get the command string to set the Bluetooth name
const char* BT_AT_SetName(const char *name) {
	static char command[50];
	const char* str = NULL;
	uint8_t length = 0;
	if (name == NULL) { length = 0; }else { length = strlen(name); }
	if(length > 0 && length < 12){
		snprintf(command, sizeof(command), "AT+NAME%s\r\n", name);
		str = command;
	}
	return str;
}

// Function to get the command string for retrieving the Bluetooth name
const char* BT_AT_GetName(void) {
	return "AT+NAME\r\n";
}

// Function to get the command string for setting the pairing password
const char* BT_AT_SetPin(uint32_t password) { // Six digits
	const char* str = NULL;
	static char command[50];
	if(password < 1000000) {
		snprintf(command, sizeof(command), "AT+PIN%06lu\r\n", password);
		str = command;
	}
	return str;
}

// Function to get the command string for retrieving the pairing password
const char* BT_AT_GetPassword(void) {
	return "AT+PSWD\r\n";
}

// Function to get the command string for retrieving the pairing password
const char* BT_AT_GetPin(void) {
	return "AT+PIN\r\n";
}

/*** 2. Role and Connection Functions ***/
// Function to get the command string to set the Bluetooth role
const char* BT_AT_SetRole(uint8_t role) {
	const char* str = NULL;
	// Array of baud rate
	const char* rolenum[] = {
			"AT+ROLE0\r\n",		// 0
			"AT+ROLE1\r\n",		// 1
			"AT+ROLE2\r\n",		// 2
			"AT+ROLE3\r\n",		// 3
			"AT+ROLE4\r\n",		// 4
			};
	switch(role){
		case 0: str = rolenum[0]; break;
		case 1: str = rolenum[1]; break;
		case 2: str = rolenum[2]; break;
		case 3: str = rolenum[3]; break;
		case 4: str = rolenum[4]; break;
	}
	return str;
}

// Function to get the command string for retrieving the Bluetooth role
const char* BT_AT_GetRole(void) {
	return "AT+ROLE\r\n";
}

// Function to get the command string for setting the connection mode
const char* BT_AT_SetConnectionMode(uint8_t mode) {
	static char command[20];
	snprintf(command, sizeof(command), "AT+CMODE=%d\r\n", mode);
	return command;
}

// Function to get the command string for retrieving the connection mode
const char* BT_AT_GetConnectionMode(void) {
	return "AT+CMODE?\r\n";
}

// Function to get the command string for binding to a specific address
const char* BT_AT_Bind(const char *address) {
	static char command[50];
	snprintf(command, sizeof(command), "AT+BIND=%s\r\n", address);
	return command;
}

/*** 3. UART and Communication Settings ***/
// Function to get the command string for setting the UART parameters
const char* BT_AT_SetUART(uint32_t baud, uint8_t stopBits, uint8_t parity) {
	static char command[50];
	snprintf(command, sizeof(command), "AT+UART=%ld,%d,%d\r\n", baud, stopBits, parity);
	return command;
}

// Function to get the command string for retrieving the UART parameters
const char* BT_AT_GetUART(void) {
	return "AT+UART\r\n";
}

/*** 4. Inquiry and Device Search Functions ***/
// Function to get the command string for starting an inquiry
const char* BT_AT_StartInquiry(void) {
	return "AT+INQ\r\n";
}

// Function to get the command string for retrieving the inquiry access code
const char* BT_AT_GetInquiryAccessCode(void) {
	return "AT+IAC?\r\n";
}

// Function to get the command string for setting the inquiry access code
const char* BT_AT_SetInquiryAccessCode(const char *iac) {
	static char command[50];
	snprintf(command, sizeof(command), "AT+IAC=%s\r\n", iac);
	return command;
}

// Function to get the command string for retrieving the inquiry mode
const char* BT_AT_GetInquiryMode(void) {
	return "AT+INQM?\r\n";
}

// Function to get the command string for setting the inquiry mode
const char* BT_AT_SetInquiryMode(uint8_t mode) {
	static char command[20];
	snprintf(command, sizeof(command), "AT+INQM=%d\r\n", mode);
	return command;
}

// Function to get the command string for retrieving a remote device's name
const char* BT_AT_GetRemoteDeviceName(const char *address) {
	static char command[50];
	snprintf(command, sizeof(command), "AT+RNAME?%s\r\n", address);
	return command;
}

/*** 5. Power Management and Sleep Functions ***/
// Function to get the command string for setting the power mode
const char* BT_AT_SetPowerMode(uint8_t mode) {
	static char command[20];
	snprintf(command, sizeof(command), "AT+PWRM=%d\r\n", mode);
	return command;
}

// Function to get the command string for retrieving the power mode
const char* BT_AT_GetPowerMode(void) {
	return "AT+PWRM?\r\n";
}

// Function to get the command string for entering sleep mode
const char* BT_AT_EnterSleep(void) {
	return "AT+SLEEP\r\n";
}

/*** 6. Pairing and Linking Functions ***/
// Function to get the command string for pairing with a device
const char* BT_AT_Pair(const char *address, uint16_t timeout) {
	static char command[50];
	snprintf(command, sizeof(command), "AT+PAIR=%s,%d\r\n", address, timeout);
	return command;
}

// Function to get the command string for linking to a specific device
const char* BT_AT_Link(const char *address) {
	static char command[50];
	snprintf(command, sizeof(command), "AT+LINK=%s\r\n", address);
	return command;
}

// Function to get the command string for disconnecting the link
const char* BT_AT_Disconnect(void) {
	return "AT+DISC\r\n";
}

/*** 7. Special Baud Rate Commands ***/
// Function to get the command string for setting the baud rate to 1200
const char* BT_AT_SetBaud1200(void) {
	return "AT+BAUD1\r\n";
}

// Function to get the command string for setting the baud rate to 2400
const char* BT_AT_SetBaud2400(void) {
	return "AT+BAUD2\r\n";
}

// Function to get the command string for setting the baud rate to 4800
const char* BT_AT_SetBaud4800(void) {
	return "AT+BAUD3\r\n";
}

// Function to get the command string for setting the baud rate to 9600 (default)
const char* BT_AT_SetBaud9600(void) {
	return "AT+BAUD4\r\n";
}

// Function to get the command string for setting the baud rate to 19200
const char* BT_AT_SetBaud19200(void) {
	return "AT+BAUD5\r\n";
}

// Function to get the command string for setting the baud rate to 38400
const char* BT_AT_SetBaud38400(void) {
	return "AT+BAUD6\r\n";
}

// Function to get the command string for setting the baud rate to 57600
const char* BT_AT_SetBaud57600(void) {
	return "AT+BAUD7\r\n";
}

// Function to get the command string for setting the baud rate to 115200
const char* BT_AT_SetBaud115200(void) {
	return "AT+BAUD8\r\n";
}

// Function to get the command string for setting the chosen baud
const char* BT_AT_SetBaud(uint32_t baud) {
	const char* str = NULL;
	// Array of baud rate
	const char* baudrate[] = {
			"AT+BAUD1\r\n",		// 1200
			"AT+BAUD2\r\n",		// 2400
			"AT+BAUD3\r\n",		// 4800
			"AT+BAUD4\r\n",		// 9600
			"AT+BAUD5\r\n",		// 19200
			"AT+BAUD6\r\n",		// 38400
			"AT+BAUD7\r\n",		// 57600
			"AT+BAUD8\r\n"		// 115200
			};
	switch(baud){
		case 1200: str = baudrate[0]; break;
		case 2400: str = baudrate[1]; break;
		case 4800: str = baudrate[2]; break;
		case 9600: str = baudrate[3]; break;
		case 19200: str = baudrate[4]; break;
		case 38400: str = baudrate[5]; break;
		case 57600: str = baudrate[6]; break;
		case 115200: str = baudrate[7]; break;
	}
	return str;
}

/*** EOF ***/

