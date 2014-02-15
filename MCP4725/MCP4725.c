/** INCLUDES ************************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdbool.h>       // Includes true/false definition

#include "../i2c_serial/i2c.h"
#include "MCP4725.h"

/** Functions ************************************************************************************/
unsigned char MCP4725_Device_Connection_Test()
{
	I2C_Start();
	return I2C_Tx(MCP4725_ADDR << 1 | I2C_READ);
}

unsigned char MCP4725_Initialize()
{
	I2C_Init();
	return MCP4725_Device_Connection_Test();
}

void MCP4725_Set_Vout(unsigned int data)
{
	printf("Setting DAC out to %X\r\n", data);
	I2C_Start();
	I2C_Tx(MCP4725_ADDR << 1 | I2C_WRITE);
	I2C_Tx(MCP4725_Fast_Mode | MCP4725_Power_Down_00 | data >> 8);
	I2C_Tx(data & 0x00FF);
	I2C_Stop();
}