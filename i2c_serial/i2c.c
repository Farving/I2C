/** INCLUDES ************************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdbool.h>       // Includes true/false definition

#include "config.h"
#include "i2c.h"

/** Functions ************************************************************************************/
void I2C_Init()
{
	printf("Initializing I2C... ");
	SDA_Tx = 1;			// Set SDA/SCL as inputs, Pull-ups will drive pin high
	SCL_Tx = 1;
	SDA_Latch = 0;		// Latch 0 to SDA/SCL output (Remember pin is input)
	SCL_Latch = 0;
	printf("Done\r\n");
}
void I2C_Start()
{
	SDA_Tx = 1;
	I2C_Delay(I2C_Clock);
	SCL_Tx = 1;
	I2C_Delay(I2C_Clock);
	SDA_Tx = 0;				// Start sequence
	I2C_Delay(I2C_Clock);
	SCL_Tx = 0;
	I2C_Delay(I2C_Clock);
}
void I2C_Stop()
{
	SDA_Tx = 0;				// Stop sequence
	I2C_Delay(I2C_Clock);
	SCL_Tx = 1;
	I2C_Delay(I2C_Clock);
	SDA_Tx = 1;
	I2C_Delay(I2C_Clock);
}

void I2C_Delay(unsigned int count)
{
	while(--count)
		;
}

unsigned char I2C_Rx(unsigned char ACK)
{
	unsigned char x, d = 0;

	SDA_Tx = 1;
	for ( x=0 ; x<8 ; x++)
	{
		d <<= 1;
		do
		{
			SCL_Tx = 1;
		}
		while (SCL_Rx == 0);	// Wait through clock-stretching
		I2C_Delay(I2C_Clock);
		if (SDA_Rx)
			d |= 1;
		SCL_Tx = 0;
		I2C_Delay(I2C_Clock);
	}
	if (!ACK)
		SDA_Tx = 0;
	else
		SDA_Tx = 1;
	I2C_Delay(I2C_Clock);
	SCL_Tx = 1;				// Sending (N)ACK
	I2C_Delay(I2C_Clock);
	SCL_Tx = 0;
	I2C_Delay(I2C_Clock);
	SDA_Tx = 1;

	return d;	
}
unsigned char I2C_Tx(unsigned char data) // Does this comply exactly with I2C??
{
	unsigned char x;
	static unsigned char ACK;
	for ( x=8 ; x>0 ; x-- )
	{
		if (data & 0x80)
			SDA_Tx = 1;
		else 
			SDA_Tx = 0;
		SCL_Tx = 1;
		I2C_Delay(I2C_Clock);
		data <<= 1;
		SCL_Tx = 0;
		I2C_Delay(I2C_Clock);
	}
	SDA_Tx = 1;
	I2C_Delay(I2C_Clock);
	SCL_Tx = 1;
	I2C_Delay(I2C_Clock);
	ACK = SDA_Rx;						// Retrieve ACK bit
	SCL_Tx = 0;

	return ACK;
}

