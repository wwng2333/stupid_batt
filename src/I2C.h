#ifndef __I2C_H__
#define __I2C_H__

#define AXP173_ADDR 0x68

sbit SDA = P3^2;
sbit SCL = P3^3;

void AXP173_Set_Voltage_DCDC2(uint16_t voltage);

uint8_t I2C_ReadByte(uint8_t addr);
void I2C_WriteByte(uint8_t addr, uint8_t dat);
	
void I2C_Init();
void I2C_Start();
void I2C_SendData(uint8_t dat);
void I2C_RecvACK();
uint8_t I2C_RecvData();
void I2C_SendNAK();
void I2C_Stop();

#endif