#ifndef __I2C_H__
#define __I2C_H__

#define AXP173_ADDR 0x68

sbit SDA = P3^2;
sbit SCL = P3^3;

float AXP173_Read_VBUS_Voltage();
float AXP173_Read_APS_Voltage();
float AXP173_Read_BAT_Voltage();
float AXP173_Read_InternalTemp();

void AXP173_Set_Voltage_DCDC2(uint16_t voltage);
void AXP173_Set_Voltage_LDO4(uint16_t voltage);

uint8_t I2C_ReadByte(uint8_t addr);
void I2C_WriteByte(uint8_t addr, uint8_t dat);
uint16_t I2C_Read_2Byte(uint8_t addr);
	
void I2C_Init();
void I2C_Start();
void I2C_SendData(uint8_t dat);
void I2C_RecvACK();
void I2C_SendACK();
uint8_t I2C_RecvData();
void I2C_SendNAK();
void I2C_Stop();

#endif