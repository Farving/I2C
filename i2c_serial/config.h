#ifndef BB_I2C_H
#define	BB_I2C_H
/** DEFINES ************************************************************************************/
/** INTERNAL ************************************************************************************/
#define SDA_Tx 		TRISBbits.TRISB4		// RB4 pin 11
#define SCL_Tx 		TRISAbits.TRISA4		// RA4 pin 12

#define SDA_Rx 		PORTBbits.RB4			// RB4 pin 11
#define SCL_Rx 		PORTAbits.RA4			// RA4 pin 12

#define SDA_Latch 	LATBbits.LATB4			// RB4 pin 11
#define SCL_Latch 	LATAbits.LATA4			// RA4 pin 12

#define I2C_Speed 	100 					// 100kHz
#define I2C_Multiplier 1
#define I2C_Clock 	(100/I2C_Speed)*I2C_Multiplier

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

#endif	/* BB_I2C_H */

