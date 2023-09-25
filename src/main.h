#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char uint8_t;
#endif /* _UINT8_T */
#ifndef _UINT16_T
#define _UINT16_T
typedef unsigned short uint16_t;
#endif /* _UINT16_T */
#ifndef _UINT32_T
#define _UINT32_T
typedef unsigned int uint32_t;
#endif /* _UINT32_T */

#ifndef __MAIN_H__
#define __MAIN_H__

#include "STC8G.h"
#include "UART.h"
#include "I2C.h"
#include "Delay.h"
#include <string.h>
#include <stdio.h>
#include "intrins.h"

extern bit UartOnMsg;

#endif