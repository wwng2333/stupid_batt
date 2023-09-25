#include "main.h"

void Delay12us()		//@11.0592MHz
{
	unsigned char i;

	i = 20;
	while (--i);
}

void Delay30us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 108;
	while (--i);
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 29;
	j = 14;
	k = 54;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
