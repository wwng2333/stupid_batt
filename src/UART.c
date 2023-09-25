#include "main.h"

bit busy;
char wptr;
char rptr;
char buffer[16];

bit UartOnMsg = 0;
char code *STCISPCMD = "@STCISP#";
char ISP_INDEX;

void UartIsr() interrupt 4
{
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
    if (RI)
    {
        RI = 0;
        buffer[wptr++] = SBUF;
        wptr &= 0x0f;
        if (SBUF == STCISPCMD[ISP_INDEX])
        {
            ISP_INDEX++;
            if (STCISPCMD[ISP_INDEX] == '\0')
                IAP_CONTR = 0x60;
        }
        else
        {
            ISP_INDEX = 0;
            if (SBUF == STCISPCMD[ISP_INDEX])
                ISP_INDEX++;
        }
        if (wptr > 16)
        {
            // UartSendErr();
            wptr = 0; // clear
        }
        else if (SBUF == 0x0A)
        {
            buffer[wptr++] = '\0';
            wptr = 0;
            UartOnMsg = 1;
        }
    }
}

void UartOnMessage(void)
{
    UartSendStr(buffer);
    UartSendOK();
    UartOnMsg = 0;
}

void UartInit()
{
    P_SW2 |= 0x80;
    SCON = 0x50;
    TMOD = 0x00;
    TL1 = BRT;
    TH1 = BRT >> 8;
    TR1 = 1;
    AUXR = 0x40;
    wptr = 0x00;
    rptr = 0x00;
    busy = 0;
    ES = 1;
    EA = 1;
    UartSendOK();
    P_SW2 &= ~0x80;
}

void UartSend(char dat)
{
    while (busy)
        ;
    busy = 1;
    SBUF = dat;
}

char putchar(char ch)
{
    SBUF = ch;
    while (TI == 0)
        ;
    TI = 0;
    return ch;
}

void UartSendStr(char *p)
{
    while (*p != '\0')
    {
        UartSend(*p++);
    }
}

// void UartSendErr(void)
//{
//     UartSendStr("Error\r\n");
// }

void UartSendOK(void)
{
    UartSendStr("OK\r\n");
}