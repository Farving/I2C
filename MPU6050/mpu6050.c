/** INCLUDES ************************************************************************************/
#include <xc.h>

#include <stdio.h>
#include <stdbool.h>       // Includes true/false definition

#include "config.h"
#include "../i2c_serial/i2c.h"
#include "mpu6050.h"

/** GLOBAL VARIABLES ************************************************************************************/
signed int GYRO_X_OFFSET, GYRO_Y_OFFSET, GYRO_Z_OFFSET = 0;
signed int ACCEL_X_OFFSET, ACCEL_Y_OFFSET, ACCEL_Z_OFFSET = 0;

/** Functions ************************************************************************************/
unsigned char MPU6050_WHO_AM_I()
{
	unsigned char Data;

	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_WHO_AM_I);
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_READ);
	Data = I2C_Rx(I2C_NACK);
	I2C_Stop();

	return Data;
}

signed char MPU6050_Test()
{
	unsigned char Data;
	printf("- Testing connection to MPU6050... ");
	Data = MPU6050_WHO_AM_I();
	if (Data == MPU6050_ADDRESS_AD0_LOW)
	{
		printf("Successful\r\n");
		return 1;
	} else {
		printf("Failed\r\n");
		return -1;
	}
}

signed char MPU6050_Init()
{
	printf("#Initializing MPU6050#\r\n- ");
	I2C_Init();
	if (MPU6050_Test() != 1)
		return -1;

	printf("- Configuring MPU6050.. ");
	MPU6050_Setup();
	printf("Done\r\n");

	printf("- Calibrating MPU6050.. \r\n");
	MPU6050_Gyro_Calibrate();
	printf("Done\r\n");
	printf("#Initialize complete#\r\n");
	return 1;
}

void MPU6050_Setup()
{
	//Sets sample rate to 8000/1+7 = 1000Hz
	MPU6050_SMPLRT_Set(0x07);
	//Disable FSync, 256Hz DLPF
	MPU6050_CONFIG_Set(0x00);
	//Disable gyro self tests, scale of 500 degrees/s
	MPU6050_GYRO_CONFIG_Set(0x08);
	//Disable accel self tests, scale of +-2g, no DHPF
	MPU6050_ACCEL_CONFIG_Set(0x00);
	//Disable sensor output to FIFO buffer
	MPU6050_FIFO_Set(0x00);
	//Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
	MPU6050_USER_CTRL_Set(0x00);
	//Sets clock source to gyro reference w/ PLL
	////Controls frequency of wakeups in accel low power mode plus the sensor standby modes
	MPU6050_PWR_MGMT_Set(0x02, 0x00);
}

//void MPU6050_Calibrate_Gyro();
//void MPU6050_Calibrate_Accel();

signed int MPU6050_X_Accel_Get()
{
	unsigned int Data;

	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_ACCEL_XOUT_H);
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_READ);
	Data = I2C_Rx(I2C_ACK);
	Data <<= 8;
	Data |= I2C_Rx(I2C_NACK);
	I2C_Stop();

	return Data;
}

signed int MPU6050_Y_Accel_Get()
{
	unsigned int Data;

	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_ACCEL_YOUT_H);
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_READ);
	Data = I2C_Rx(I2C_ACK);
	Data <<= 8;
	Data |= I2C_Rx(I2C_NACK);
	I2C_Stop();

	return Data;
}

signed int MPU6050_Z_Accel_Get()
{
	unsigned int Data;

	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_ACCEL_ZOUT_H);
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_READ);
	Data = I2C_Rx(I2C_ACK);
	Data <<= 8;
	Data |= I2C_Rx(I2C_NACK);
	I2C_Stop();

	return Data;
}

signed int MPU6050_X_Gyro_Get()
{
	unsigned int Data;

	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_GYRO_XOUT_H);
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_READ);
	Data = I2C_Rx(I2C_ACK);
	Data <<= 8;
	Data |= I2C_Rx(I2C_NACK);
	I2C_Stop();

	return Data - GYRO_X_OFFSET;
}

signed int MPU6050_Y_Gyro_Get()
{
	unsigned int Data;

	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_GYRO_YOUT_H);
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_READ);
	Data = I2C_Rx(I2C_ACK);
	Data <<= 8;
	Data |= I2C_Rx(I2C_NACK);
	I2C_Stop();

	return Data - GYRO_Y_OFFSET;
}

signed int MPU6050_Z_Gyro_Get()
{
	unsigned int Data;

	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_GYRO_ZOUT_H);
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_READ);
	Data = I2C_Rx(I2C_ACK);
	Data <<= 8;
	Data |= I2C_Rx(I2C_NACK);
	I2C_Stop();

	return Data - GYRO_Z_OFFSET;
}

void MPU6050_Gyro_Calibrate()
{
	unsigned int x;
	signed int GYRO_X, GYRO_Y, GYRO_Z;
	for ( x=0 ; x<MPU6050_CALIBRATE_AVG_LENGTH ; x++)
	{
		GYRO_X += MPU6050_X_Gyro_Get();
		GYRO_Y += MPU6050_Y_Gyro_Get();
		GYRO_Z += MPU6050_Z_Gyro_Get();
	}

	GYRO_X_OFFSET = GYRO_X / MPU6050_CALIBRATE_AVG_LENGTH;
	GYRO_Y_OFFSET = GYRO_Y / MPU6050_CALIBRATE_AVG_LENGTH;
	GYRO_Z_OFFSET = GYRO_Z / MPU6050_CALIBRATE_AVG_LENGTH;
	printf("- GYRO OFFSETS: % 5i % 5i % 5i\r\n", GYRO_X_OFFSET, GYRO_Y_OFFSET, GYRO_Z_OFFSET);

	signed int ACCEL_X, ACCEL_Y, ACCEL_Z;
	for ( x=0 ; x<MPU6050_CALIBRATE_AVG_LENGTH ; x++)
	{
		ACCEL_X += MPU6050_X_Accel_Get();
		ACCEL_Y += MPU6050_Y_Accel_Get();
		ACCEL_Z += MPU6050_Z_Accel_Get();
	}

	ACCEL_X_OFFSET = ACCEL_X / MPU6050_CALIBRATE_AVG_LENGTH;
	ACCEL_Y_OFFSET = ACCEL_Y / MPU6050_CALIBRATE_AVG_LENGTH;
	ACCEL_Z_OFFSET = ACCEL_Z / MPU6050_CALIBRATE_AVG_LENGTH;
	printf("- ACCEL OFFSETS: % 5i % 5i % 5i\r\n", ACCEL_X_OFFSET, ACCEL_Y_OFFSET, ACCEL_Z_OFFSET);
}

void MPU6050_SMPLRT_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_SMPLRT_DIV);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_CONFIG_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_CONFIG);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_GYRO_CONFIG_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_GYRO_CONFIG);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_ACCEL_CONFIG_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_ACCEL_CONFIG);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_FF_TH_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_FF_THR);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_FF_DUR_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_FF_DUR);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_MOT_TH_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_MOT_THR);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_MOT_DUR_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_MOT_DUR);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_ZRMOT_TH_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_ZRMOT_THR);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_ZRMOT_DUR_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_ZRMOT_DUR);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_FIFO_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_FIFO_EN);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_I2C_MST_CTRL_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_I2C_MST_CTRL);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_I2C_SVL0_Set(unsigned char ADDR, unsigned char REG, unsigned char CTRL)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_I2C_SLV0_ADDR);
	I2C_Tx(ADDR);
	I2C_Tx(REG);
	I2C_Tx(CTRL);
	I2C_Stop();
}

void MPU6050_I2C_SVL1_Set(unsigned char ADDR, unsigned char REG, unsigned char CTRL)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_I2C_SLV1_ADDR);
	I2C_Tx(ADDR);
	I2C_Tx(REG);
	I2C_Tx(CTRL);
	I2C_Stop();
}

void MPU6050_I2C_SVL2_Set(unsigned char ADDR, unsigned char REG, unsigned char CTRL)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_I2C_SLV2_ADDR);
	I2C_Tx(ADDR);
	I2C_Tx(REG);
	I2C_Tx(CTRL);
	I2C_Stop();
}

void MPU6050_I2C_SVL3_Set(unsigned char ADDR, unsigned char REG, unsigned char CTRL)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_I2C_SLV3_ADDR);
	I2C_Tx(ADDR);
	I2C_Tx(REG);
	I2C_Tx(CTRL);
	I2C_Stop();
}

void MPU6050_I2C_SVL4_Set(unsigned char ADDR, unsigned char REG, unsigned char CTRL)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_I2C_SLV4_ADDR);
	I2C_Tx(ADDR);
	I2C_Tx(REG);
	I2C_Tx(0x00); // Dummy write due to SVL4_D0 is between Reg and ctrl register
	I2C_Tx(CTRL);
	I2C_Stop();
}

void MPU6050_INT_PIN_CONFIG_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_INT_PIN_CFG);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_INT_CONFIG_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_INT_ENABLE);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_I2C_MST_DELAY_CTRL_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_I2C_MST_DELAY_CTRL);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_SIGNAL_PATH_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_SIGNAL_PATH_RESET);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_MOT_DET_CTRL_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_MOT_DETECT_CTRL);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_USER_CTRL_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_USER_CTRL);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

void MPU6050_PWR_MGMT_Set(unsigned char CONFIG1, unsigned char CONFIG2)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_PWR_MGMT_1);
	I2C_Tx(CONFIG1);
	I2C_Tx(CONFIG2);
	I2C_Stop();
}

void MPU6050_FIFO_RW_Set(unsigned char CONFIG)
{
	I2C_Start();
	I2C_Tx((MPU6050_ADDRESS_DEFAULT << 1) | I2C_WRITE);
	I2C_Tx(MPU6050_RA_FIFO_R_W);
	I2C_Tx(CONFIG);
	I2C_Stop();
}

