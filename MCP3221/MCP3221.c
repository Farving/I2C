/** INCLUDES ************************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdbool.h>       // Includes true/false definition

#include "../i2c_serial/i2c.h"
#include "MCP3221.h"

/** Functions ************************************************************************************/
unsigned char MCP3221_Device_Connection_Test()
{
	I2C_Start();
	return I2C_Tx(MCP3221_ADDR << 1 | I2C_WRITE);
}

unsigned char MCP3221_Initialize()
{
	I2C_Init();
	return MCP3221_Device_Connection_Test();
}

unsigned int MCP3221_Read_Conversion()
{
	unsigned int data = 0;

	I2C_Start();
	I2C_Tx(MCP3221_ADDR << 1 | I2C_READ);
	data = I2C_Rx(I2C_ACK) & 0x0F;
        data <<= 8;
	data |= I2C_Rx(I2C_NACK);
	I2C_Stop();

        return data;
}