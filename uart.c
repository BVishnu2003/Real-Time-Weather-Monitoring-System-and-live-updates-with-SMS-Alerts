   #include <LPC21xx.h>
#include "uart.h"

void UART0_INIT(void)
{

    PINSEL0 &= ~0x0F;
    PINSEL0 |= 0x05;
   
    U0LCR = 0x83;
    U0DLL = 97;
    U0DLM = 0;

    U0LCR = 0x03;
}

void UART0_TX(unsigned char ch)
{
    while (!(U0LSR & (1 << 5)))
    {
    }

    U0THR = ch;
}

unsigned char UART0_RX(void)
{
    while (!(U0LSR & (1 << 0)))
    {
    }

    return U0RBR;
}

void UART0_STRING(char *str)
{
    while (*str)
    {
        UART0_TX(*str);
        str++;
    }
}


