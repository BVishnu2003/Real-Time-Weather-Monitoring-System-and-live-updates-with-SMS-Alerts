#include <LPC21xx.h>
#include "config.h"
#include "timer.h"

void Timer0_Init(void)
{
    T0TCR = 0x02;          

    T0PR = 15000 - 1;      
                            

    T0TCR = 0x01;         
}

void Timer0_Delay_ms(unsigned int ms)
{
    unsigned int i;

    for (i = 0; i < ms; i++)
    {
        T0TC = 0;          
        T0TCR = 0x01;       

        while (T0TC < 1);  

        T0TCR = 0x00;      
    }
}
