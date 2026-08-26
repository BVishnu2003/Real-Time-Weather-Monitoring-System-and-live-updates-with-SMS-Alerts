#include <LPC21xx.h>
#include "lcd.h"
#include "timer.h"





#define LCD_DATA_SHIFT     14


#define LCD_RS             (1 << 8)
#define LCD_EN             (1 << 9)



static void LCD_SendNibble(unsigned char nibble)
{
    
    IO0CLR = (0x0F << LCD_DATA_SHIFT);

    
    IO0SET = ((unsigned long)(nibble & 0x0F)
              << LCD_DATA_SHIFT);

    IO0SET = LCD_EN;

    Timer0_Delay_ms(1);

    IO0CLR = LCD_EN;

    Timer0_Delay_ms(1);
}




void LCD_Init(void)
{

    IO0DIR |= (0x0F << LCD_DATA_SHIFT);

   
    IO0DIR |= LCD_RS;
    IO0DIR |= LCD_EN;
    IO0CLR = (0x0F << LCD_DATA_SHIFT);
    IO0CLR = LCD_RS;
    IO0CLR = LCD_EN;

   
    Timer0_Delay_ms(20);

    LCD_SendNibble(0x03);

    Timer0_Delay_ms(5);

    LCD_SendNibble(0x03);

    Timer0_Delay_ms(1);

    LCD_SendNibble(0x03);

    Timer0_Delay_ms(1);

    LCD_SendNibble(0x02);

    Timer0_Delay_ms(1);


    LCD_Command(0x28);

    LCD_Command(0x0C);

    LCD_Command(0x06);


    LCD_Command(0x01);

    Timer0_Delay_ms(2);
}

void LCD_Command(unsigned char cmd)
{
  
    IO0CLR = LCD_RS;

    LCD_SendNibble(cmd >> 4);

    LCD_SendNibble(cmd & 0x0F);

    Timer0_Delay_ms(2);
}



void LCD_Data(unsigned char data)
{
  
    IO0SET = LCD_RS;

    LCD_SendNibble(data >> 4);

   
    LCD_SendNibble(data & 0x0F);

    Timer0_Delay_ms(1);
}



void LCD_String(char *str)
{
    while (*str != '\0')
    {
        LCD_Data(*str);
        str++;
    }
}

/* =========================================================
   Clear LCD
   ========================================================= */

void LCD_Clear(void)
{
    LCD_Command(0x01);

    Timer0_Delay_ms(2);
}



void LCD_SetCursor(unsigned char row, unsigned char column)
{
    unsigned char address;

    if (row == 1)
        address = 0x80 + (column - 1);

    else if (row == 2)
        address = 0xC0 + (column - 1);

    else if (row == 3)
        address = 0x94 + (column - 1);

    else
        address = 0xD4 + (column - 1);

    LCD_Command(address);
}




void LCD_PrintNumber(unsigned int num)
{
    char buffer[10];
    int i = 0;

    if (num == 0)
    {
        LCD_Data('0');
        return;
    }

    while (num > 0)
    {
        buffer[i] = (num % 10) + '0';

        num = num / 10;

        i++;
    }

    while (i > 0)
    {
        i--;

        LCD_Data(buffer[i]);
    }
}


void LCD_PrintFloat(float num)
{
    unsigned int integerPart;
    unsigned int decimalPart;

    integerPart = (unsigned int)num;

    decimalPart =
        (unsigned int)((num - integerPart) * 100);

    LCD_PrintNumber(integerPart);

    LCD_Data('.');

    if (decimalPart < 10)
    {
        LCD_Data('0');
    }

    LCD_PrintNumber(decimalPart);
}
