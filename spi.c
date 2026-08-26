#include <LPC21xx.h>
#include "spi.h"

 

void SPI_Init(void)
{

    PINSEL0 &= ~(0x00003F00);

    PINSEL0 |=  (0x00001500);


   

    IO0DIR |= (1 << 7);



    IO0SET = (1 << 7);


    S0SPCR = 0x0820;


    S0SPCCR = 60;
}


unsigned char SPI_Write(unsigned char data)
{
  
    S0SPDR = data;


    while ((S0SPSR & 0x80) == 0)
    {
        
    }


    return S0SPDR;
}


void SPI_CS_Low(void)
{

    IO0CLR = (1 << 7);
}


void SPI_CS_High(void)
{
  

    IO0SET = (1 << 7);
}
