#include "stm32f4xx.h"
#include "i2c.h"

int main(void) {
	// Initialize I2C1 with 100 kHz clock speed
	I2C_Init(I2C1, 100000);

	// Write data to a device with address 0x50, register 0x00
	I2C_Write(I2C1, 0x50, 0x00, 0x55);

	// Read data from a device with address 0x50, register 0x00
	uint8_t data = I2C_Read(I2C1, 0x50, 0x00);

	while (1) {
		// Main loop
	}
}