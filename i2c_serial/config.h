#ifndef I2C_CONFIG_H
#define	I2C_CONFIG_H

/** Microchip PIC24 ************************************************************************************/
#define SDA_Tx 		TRISBbits.TRISB4		// RB4 pin 11
#define SCL_Tx 		TRISAbits.TRISA4		// RA4 pin 12

#define SDA_Rx 		PORTBbits.RB4			// RB4 pin 11
#define SCL_Rx 		PORTAbits.RA4			// RA4 pin 12

#define SDA_Latch 	LATBbits.LATB4			// RB4 pin 11
#define SCL_Latch 	LATAbits.LATA4			// RA4 pin 12

#define I2C_Speed 	100 					// 100kHz
#define I2C_Multiplier 1
#define I2C_Clock 	(100/I2C_Speed)*I2C_Multiplier

#endif	/* I2C_CONFIG_H */

