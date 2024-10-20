/******************************************************************************
	BT AT COMMANDS
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ALL
Date: 20102024
Comment:
	
*******************************************************************************/
#ifndef _BT_COMMANDS_H_
	#define _BT_COMMANDS_H_

#include <inttypes.h>

/*** USER ***/
const char* BT_AT_NAME_1(void);
const char* BT_AT_NAME_2(void);
const char* BT_AT_PSWD_1(void);
/*** 1. General Functions for AT Commands ***/
// Function to get the basic AT command string (for testing the module)
const char* BT_AT_Test(void);
// Function to get the reset command string
const char* BT_AT_Reset(void);
// Function to get the firmware version command string
const char* BT_AT_GetVersion(void);
// Function to get the restore factory settings command string
const char* BT_AT_RestoreDefaults(void);
// Function to get the command string for getting the Bluetooth address
const char* BT_AT_GetAddress(void);
// Function to get the command string to set the Bluetooth name
const char* BT_AT_SetName(const char *name);
// Function to get the command string for retrieving the Bluetooth name
const char* BT_AT_GetName(void);
// Function to get the command string for setting the pairing password
const char* BT_AT_SetPassword(const char *password);
// Function to get the command string for retrieving the pairing password
const char* BT_AT_GetPassword(void);
// Function to get the command string for retrieving the pairing password
const char* BT_AT_GetPin(void);
/*** 2. Role and Connection Functions ***/
// Function to get the command string to set the Bluetooth role
const char* BT_AT_SetRole(uint8_t role);
// Function to get the command string for retrieving the Bluetooth role
const char* BT_AT_GetRole(void);
// Function to get the command string for setting the connection mode
const char* BT_AT_SetConnectionMode(uint8_t mode);
// Function to get the command string for retrieving the connection mode
const char* BT_AT_GetConnectionMode(void);
// Function to get the command string for binding to a specific address
const char* BT_AT_Bind(const char *address);
/*** 3. UART and Communication Settings ***/
// Function to get the command string for setting the UART parameters
const char* BT_AT_SetUART(uint32_t baud, uint8_t stopBits, uint8_t parity);
// Function to get the command string for retrieving the UART parameters
const char* BT_AT_GetUART(void);
/*** 4. Inquiry and Device Search Functions ***/
// Function to get the command string for starting an inquiry
const char* BT_AT_StartInquiry(void);
// Function to get the command string for retrieving the inquiry access code
const char* BT_AT_GetInquiryAccessCode(void);
// Function to get the command string for setting the inquiry access code
const char* BT_AT_SetInquiryAccessCode(const char *iac);
// Function to get the command string for retrieving the inquiry mode
const char* BT_AT_GetInquiryMode(void);
// Function to get the command string for setting the inquiry mode
const char* BT_AT_SetInquiryMode(uint8_t mode);
// Function to get the command string for retrieving a remote device's name
const char* BT_AT_GetRemoteDeviceName(const char *address);
/*** 5. Power Management and Sleep Functions ***/
// Function to get the command string for setting the power mode
const char* BT_AT_SetPowerMode(uint8_t mode);
// Function to get the command string for retrieving the power mode
const char* BT_AT_GetPowerMode(void);
// Function to get the command string for entering sleep mode
const char* BT_AT_EnterSleep(void);
/*** 6. Pairing and Linking Functions ***/
// Function to get the command string for pairing with a device
const char* BT_AT_Pair(const char *address, uint16_t timeout);
// Function to get the command string for linking to a specific device
const char* BT_AT_Link(const char *address);
// Function to get the command string for disconnecting the link
const char* BT_AT_Disconnect(void);
/*** 7. Special Baud Rate Commands ***/
// Function to get the command string for setting the baud rate to 1200
const char* BT_AT_SetBaud1200(void);
// Function to get the command string for setting the baud rate to 2400
const char* BT_AT_SetBaud2400(void);
// Function to get the command string for setting the baud rate to 4800
const char* BT_AT_SetBaud4800(void);
// Function to get the command string for setting the baud rate to 9600 (default)
const char* BT_AT_SetBaud9600(void);
// Function to get the command string for setting the baud rate to 19200
const char* BT_AT_SetBaud19200(void);
// Function to get the command string for setting the baud rate to 38400
const char* BT_AT_SetBaud38400(void);
// Function to get the command string for setting the baud rate to 57600
const char* BT_AT_SetBaud57600(void);
// Function to get the command string for setting the baud rate to 115200
const char* BT_AT_SetBaud115200(void);
	
#endif

/*** EOF ***/

