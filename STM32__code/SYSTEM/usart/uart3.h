#ifndef __UART3_H
#define __UART3_H

void Initial_UART3(unsigned long baudrate);
void UART3_Put_Char(unsigned char DataToSend);
void UART3_Put_String(unsigned char *Str);

#endif
