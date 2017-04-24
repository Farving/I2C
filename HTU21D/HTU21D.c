/** INCLUDES ************************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdbool.h>       // Includes true/false definition

#include "../i2c_serial/i2c.h"
#include "HTU21D.h"

/** Functions ************************************************************************************/
unsigned char HTU21D_set_resolution(char resolution) 
{
/*	unsigned char ack;
	I2C_Start();
	I2C_Tx(HTU21D_ADDR << 1 | I2C_WRITE);
	I2C_Tx()
	I2C_Stop();
	return ack;
*/
}

unsigned char HTU21D_check_CRC(unsigned int message, unsigned char checksum)
{
	unsigned long remainder = (unsigned long)message << 8;
	remainder |= checksum;

	unsigned long divisor = (unsigned long)SHIFTED_DIVISOR

	for (int i = 0; i < 16; i++)
	{
		if (remainder & (unsigned long)1<<(23-i))
			remainder ^= divisor;

		divisor >> 1;
	}

	return (unsigned char)remainder;
}

float HTU21D_get_humidity()
{
	unsigned char msb, lsb, checksum;

	I2C_Start();
	I2C_Tx(HTU21D_ADDR << 1 | I2C_WRITE);
	I2C_Tx(HTU21D_TRIGGER_HUMD_MEASURE_NOHOLD);
	I2C_Stop();

	// delay 55ms

	I2C_Start();
	I2C_Tx(HTU21D_ADDR << 1 | I2C_READ);
	msb = I2C_Rx(I2C_ACK);
	lsb = I2C_Rx(I2C_ACK);
	checksum = I2C_Rx(I2C_ACK);
	I2C_Stop();

	unsigned int raw_humidity = (unsigned int)msb << 8 | (unsigned int)lsb;

	if (HTU21D_check_CRC(raw_humidity, checksum) != 0)
		return 999;

	float tmpRH = (raw_humidity & 0xFFFC) / (float)65536; // 2^16
	return -6 + (125 * tmpRH);
}

float HTU21D_get_temperature()
{
	unsigned char msb, lsb, checksum;

	I2C_Start();
	I2C_Tx(HTU21D_ADDR << 1 | I2C_WRITE);
	I2C_Tx(HTU21D_TRIGGER_TEMP_MEASURE_NOHOLD);
	I2C_Stop();

	// delay 55ms

	I2C_Start();
	I2C_Tx(HTU21D_ADDR << 1 | I2C_READ);
	msb = I2C_Rx(I2C_ACK);
	lsb = I2C_Rx(I2C_ACK);
	checksum = I2C_Rx(I2C_ACK);
	I2C_Stop();

	unsigned int raw_temperature = (unsigned int)msb << 8 | (unsigned int)lsb;

	if (HTU21D_check_CRC(raw_temperature, checksum) != 0)
		return 999;

	float tmpT = (raw_temperature & 0xFFFC) / (float)65536; // 2^16
	return (float)(-46.85 + (175.72 * tmpT));
}
