#ifndef I2C_H
#define	I2C_H
/** DEFINES ************************************************************************************/
/** EXTERNAL ************************************************************************************/
#define I2C_ACK 		0
#define I2C_NACK 		1

#define I2C_READ 		1
#define I2C_WRITE 		0

/** Prototypes ************************************************************************************/
void I2C_Init();
void I2C_Start();
void I2C_Stop();

void I2C_Delay(unsigned int count);

unsigned char I2C_Rx(unsigned char Ack);
unsigned char I2C_Tx(unsigned char data);

#endif	/* I2C_H */

