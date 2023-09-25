#include "main.h"

void I2C_Init()
{
	P3M0 |= 0x0c;
	P3M1 |= 0x0c; 
}

char I2C_ReadByte(char addr)
{
	char dat = 0;
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

void I2C_Start()
{
    SDA = 1;
    SCL = 1;
    Delay12us();
    SDA = 0;
    Delay12us();
    SCL = 0;
}

void I2C_SendData(char dat)
{
    unsigned int i;
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

void I2C_RecvACK()
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

char I2C_RecvData()
{
    unsigned int i;
    unsigned char dat;
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
