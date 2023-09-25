#ifndef __I2C_H__
#define __I2C_H__

#define AXP173_ADDR (0x68 )

sbit SDA = P3^2;
sbit SCL = P3^3;

char I2C_ReadByte(char addr);

void I2C_Init();
void I2C_Start();
void I2C_SendData(char dat);
void I2C_RecvACK();
char I2C_RecvData();
void I2C_SendNAK();
void I2C_Stop();

#endif