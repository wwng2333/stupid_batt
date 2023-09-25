#ifndef __UART_H__
#define __UART_H__

#define FOSC 11059200UL
#define BRT (65536 - FOSC / 115200 / 4)

void UartIsr();
void UartInit();
void UartSend(char dat);
void UartSendStr(char *p);
void UartInitReport(char *p);
void UartOnMessage(void);
static void UartSendErr(void);
static void UartSendOK(void);
#endif