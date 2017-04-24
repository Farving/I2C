#ifndef HTU21D_H
#define HTU21D_H
/** DEFINES ************************************************************************************/
#define HTU21D_ADDR    0x40

#define HTU21D_TRIGGER_TEMP_MEASURE_HOLD  0xE3
#define HTU21D_TRIGGER_HUMD_MEASURE_HOLD  0xE5
#define HTU21D_TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define HTU21D_TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define HTU21D_WRITE_USER_REG  0xE6
#define HTU21D_READ_USER_REG  0xE7
#define HTU21D_SOFT_RESET  0xFE

#define SHIFTED_DIVISOR 0x988000 //This is the 0x0131 polynomial shifted to farthest left of three bytes
/** INTERNAL ************************************************************************************/
unsigned char HTU21D_set_resolution(char resolution);
unsigned char HTU21D_check_CRC(unsigned int message, unsigned char checksum);

/** EXTERNAL ************************************************************************************/
float HTU21D_get_humidity();
float HTU21D_get_temperature();

/** Prototypes ************************************************************************************/


#endif	/* MCP3221_H */