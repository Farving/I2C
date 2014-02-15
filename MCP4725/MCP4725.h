#ifndef MCP4725_H
#define	MCP4725_H
/** DEFINES ************************************************************************************/
/** INTERNAL ************************************************************************************/
/* ADDRESS MAP */
#define MCP4725_ADDR    0b1100000

/* REGISTER ADDRESS MAP */


/** EXTERNAL ************************************************************************************/
/* REGISTER BITMAP */
#define MCP4725_Fast_Mode			0b00000000
#define MCP4725_Write_DAC_Only		0b01000000
#define MCP4725_Write_DAC_EEPROM	0b01100000
//#define MCP4725_
#define MCP4725_Power_Down_00		0b00000000
#define MCP4725_Power_Down_01		0b00010000
#define MCP4725_Power_Down_10		0b00100000
#define MCP4725_Power_Down_11		0b00110000


/** Prototypes ************************************************************************************/
unsigned char MCP4725_Device_Connection_Test();

unsigned char MCP4725_Initialize();

void MCP4725_Set_Vout(unsigned int data);

#endif	/* MCP4725_H */