#include "main.h"

int main(void)
{
	int i = 0, dat = 0;
	UartInit();
	I2C_Init();
	AXP173_Set_Voltage_DCDC2(800); //mV
	AXP173_Set_Voltage_LDO4(3000);
	I2C_WriteByte(0x12, 0x1F); //Enable ALL Output
	I2C_WriteByte(0x33, 0xC3); //Enable BAT Charge, 4.2v, 360mA
	I2C_WriteByte(0x36, 0x4C); //PEK setting, 4s to shutdown
	I2C_WriteByte(0x82, 0xFF); //Enable BAT, VBUS ADC
	while(1)
	{
		printf("aps:%.2fV\r\n", AXP173_Read_APS_Voltage());
		printf("temp:%.2fC\r\n", AXP173_Read_InternalTemp());
		printf("bat:%.2fV, %.2fmA\r\n", AXP173_Read_BAT_Voltage(), AXP173_Read_BAT_Current());
		printf("vbus:%.2fV, %.2fmA\r\n", AXP173_Read_VBUS_Voltage(), AXP173_Read_VBUS_Current());
		//I2C_Read_2Byte(0x5A); //VBUS Voltage
		//I2C_Read_2Byte(0x5C); //VBUS Current
		if(UartOnMsg) UartOnMessage();
//		for(i=0;i<=0x12;i++)
//		{
//			dat = I2C_ReadByte(i);
//			printf("0x%d=0x%d\r\n", i, dat);
//			Delay30us();
//		}
		//UartSend(dat);
		UartSendOK();
		Delay500ms();
	}
}
	