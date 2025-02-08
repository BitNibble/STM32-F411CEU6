#include "stm32f4xx_hal.h"
#include "i2c.h"

int main(void) {
	HAL_Init(); // Initialize HAL
	I2C_Init(); // Initialize I2C

	uint8_t data;

	// Write 0x55 to register 0x01 of device with address 0x50
	I2C_WriteByte(0x50, 0x01, 0x55);

	// Read from register 0x01 of device with address 0x50
	I2C_ReadByte(0x50, 0x01, &data);

	while (1) {
		// Main loop
	}
}
