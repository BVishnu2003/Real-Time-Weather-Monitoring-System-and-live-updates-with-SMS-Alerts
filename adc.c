#include "adc.h"
#include "spi.h"
#include "config.h"


void ADC_Init(void)
{
    
    SPI_Init();
}

unsigned int MCP3204_Read(unsigned char channel)
{
    unsigned char tx;
    unsigned char highByte;
    unsigned char lowByte;

    unsigned int adcValue;



    if (channel > 3)
    {
        return 0;
    }


    SPI_CS_Low();
 

    tx = 0x06 | ((channel & 0x04) >> 2);

    SPI_Write(tx);



    tx = (channel & 0x03) << 6;

    highByte = SPI_Write(tx);

  
    lowByte = SPI_Write(0x00);


    SPI_CS_High();

   

    adcValue = ((highByte & 0x0F) << 8) | lowByte;


    return adcValue;
}
