#include "main.h"

int main(void)
{
	int i = 0, dat = 0;
	UartInit();
	I2C_Init();
	AXP173_Set_Voltage_DCDC2(800); // mV
	AXP173_Set_Voltage_LDO4(3000);
	I2C_WriteByte(0x12, 0x1F); // Enable ALL Output
	I2C_WriteByte(0x30, 0xE0); // Enable VBUS-IPSOUT
	I2C_WriteByte(0x33, 0xC2); // Enable BAT Charge, 4.2v, 280mA
	I2C_WriteByte(0x36, 0x4C); // PEK setting, 4s to shutdown
	I2C_WriteByte(0x82, 0xFF); // Enable BAT, VBUS ADC
	while (1)
	{
		I2C_WriteByte(0x33, 0xC2);
		I2C_ReadByte(0x01);
		I2C_ReadByte(0x33);
		printf("aps :%.3fV\r\n", AXP173_Read_APS_Voltage());
		printf("temp:%.1fC\r\n", AXP173_Read_InternalTemp());
		printf("bat :%.3fV, %.2fmA\r\n", AXP173_Read_BAT_Voltage(), AXP173_Read_BAT_Current());
		printf("vbus:%.3fV, %.2fmA\r\n", AXP173_Read_VBUS_Voltage(), AXP173_Read_VBUS_Current());
		//I2C_Read_32Bit(0xB0);
		if (UartOnMsg)
			UartOnMessage();
		UartSendOK();
		Delay500ms();
	}
}
