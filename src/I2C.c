#include "main.h"

void I2C_Init()
{
	P3M0 |= 0x0c;
	P3M1 |= 0x0c; 
}

//uint16_t AXP173_Read_ADC(uint8_t addr)
//{
//	
//}

float AXP173_Read_VBUS_Voltage()
{
	float ADCLSB = 1.7 / 1000.0;
	return I2C_Read_12Bit(0x5A) * ADCLSB;
}

float AXP173_Read_VBUS_Current()
{
	float ADCLSB = 0.375;
	return I2C_Read_12Bit(0x5C) * ADCLSB;
}

float AXP173_Read_APS_Voltage()
{
	float ADCLSB = 1.4 / 1000.0;
	return I2C_Read_12Bit(0x7E) * ADCLSB;
}

float AXP173_Read_BAT_Voltage()
{
	float ADCLSB = 1.1 / 1000.0;
	return I2C_Read_12Bit(0x78) * ADCLSB;
}

float AXP173_Read_BAT_Current()
{
	float ADCLSB = 0.5;
	uint16_t CurrentIn = I2C_Read_13Bit(0x7A);
	uint16_t CurrentOut = I2C_Read_13Bit(0x7C);
	return (CurrentIn - CurrentOut) * ADCLSB;
}

float AXP173_Read_InternalTemp()
{
	float ADCLSB = 0.1;
	const float OFFSET_DEG_C = -144.7;
	uint16_t ReData = I2C_Read_12Bit(0x5E);
	return OFFSET_DEG_C + ReData * ADCLSB;
}

void AXP173_Set_Voltage_DCDC2(uint16_t voltage)
{
	uint8_t dat = 0;
	if(voltage < 2275 && voltage > 700)
	{
		dat = (voltage-700)/25;
		//printf("DCDC2 %dmV 0x23=%d", voltage, dat);
		I2C_WriteByte(0x23, dat); //DC-DC2
	}
}

void AXP173_Set_Voltage_LDO4(uint16_t voltage)
{
	uint8_t dat = 0;
	if(voltage < 3500 && voltage > 700)
	{
		dat = (voltage-700)/25;
		//printf("DCDC2 %dmV 0x23=%d", voltage, dat);
		I2C_WriteByte(0x27, dat); //DC-DC2
	}
}

uint16_t I2C_Read_13Bit(uint8_t addr)
{
	uint16_t dat = 0;
	uint8_t dat1, dat2;
	I2C_Start();
	I2C_SendData(AXP173_ADDR);
	I2C_RecvACK();
	I2C_SendData(addr);
	I2C_RecvACK();	
	I2C_Start();
	I2C_SendData(AXP173_ADDR + 1);
	I2C_RecvACK();
	dat1 = I2C_RecvData();
	I2C_SendACK();
	dat2 = I2C_RecvData();
	I2C_SendNAK();
	I2C_Stop();
	//UartSend(dat1);
	//UartSend(dat2);
	dat = (dat1 << 5) + dat2;
	return dat;
}

uint16_t I2C_Read_12Bit(uint8_t addr)
{
	uint16_t dat = 0;
	uint8_t dat1, dat2;
	I2C_Start();
	I2C_SendData(AXP173_ADDR);
	I2C_RecvACK();
	I2C_SendData(addr);
	I2C_RecvACK();	
	I2C_Start();
	I2C_SendData(AXP173_ADDR + 1);
	I2C_RecvACK();
	dat1 = I2C_RecvData();
	I2C_SendACK();
	dat2 = I2C_RecvData();
	I2C_SendNAK();
	I2C_Stop();
	//UartSend(dat1);
	//UartSend(dat2);
	dat = (dat1 << 4) + dat2;
	return dat;
}

uint8_t I2C_ReadByte(uint8_t addr)
{
	uint8_t dat = 0;
	I2C_Start();
	I2C_SendData(AXP173_ADDR);
	I2C_RecvACK();
	I2C_SendData(addr);
	I2C_RecvACK();
	
	Delay30us();
	
	I2C_Start();
	I2C_SendData(AXP173_ADDR + 1);
	I2C_RecvACK();
	dat = I2C_RecvData();
	I2C_SendNAK();
	I2C_Stop();
	return dat;
}

void I2C_WriteByte(uint8_t addr, uint8_t dat)
{
	I2C_Start();
	I2C_SendData(AXP173_ADDR);
	I2C_RecvACK();
	I2C_SendData(addr);
	I2C_RecvACK();
	I2C_SendData(dat);
	I2C_RecvACK();
	I2C_Stop();
}

void I2C_Start()
{
    SDA = 1;
    SCL = 1;
    Delay12us();
    SDA = 0;
    Delay12us();
    SCL = 0;
}

void I2C_SendData(uint8_t dat)
{
    uint8_t i;
    for(i=0; i<8; i++)
    {
        SCL = 0;
        Delay12us();
        if(dat & 0x80) 
            SDA = 1;
        else 
            SDA = 0;
        dat <<= 1;
        SCL = 1;
        Delay12us();
    }
    SCL = 0;
}

void I2C_SendACK()
{
    SCL = 0;
    Delay12us();
    SDA = 0;
    SCL = 1;
    Delay12us();
    SCL = 0;
    SDA = 1;
    Delay12us();
}

void I2C_RecvACK()
{
    SCL = 0;
    Delay12us();
    SDA = 1;
    SCL = 1;
    Delay12us();
    SCL = 0;
    Delay12us();
}

uint8_t I2C_RecvData()
{
    uint8_t dat, i;
    for(i=0; i<8; i++)
    {
        dat <<= 1;
        SCL = 0;
        Delay12us();
        SCL = 1;
        Delay12us();
        if(SDA) dat += 1;
    }
    return dat;
}

void I2C_SendNAK()
{
    SCL = 0;
    Delay12us();
    SDA = 1;
    SCL = 1;
    Delay12us();
    SCL = 0;
    Delay12us();
}	

void I2C_Stop()
{
    SDA = 0;
    SCL = 1;
    Delay12us();
    SDA = 1;
    Delay12us();
}
