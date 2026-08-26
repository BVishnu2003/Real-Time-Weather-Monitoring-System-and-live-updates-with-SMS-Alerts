#ifndef UART_H
#define UART_H

void UART0_INIT(void);
void UART0_TX(unsigned char ch);
unsigned char UART0_RX(void);
void UART0_STRING(char *str);

#endif
