#include "main.h"

int main(void)
{
	int i = 0, dat = 0;
	UartInit();
	I2C_Init();
	while(1)
	{
		AXP173_Set_Voltage_DCDC2(800); //mV
		I2C_WriteByte(0x12, 0x1F); //Enable ALL Output
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
	