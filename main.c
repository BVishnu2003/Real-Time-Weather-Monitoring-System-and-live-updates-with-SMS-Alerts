#include "config.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "sensor.h"
#include "uart.h"
#include "gsm.h"
#include "led.h"




static char *SMS_AppendString(char *p, const char *str)
{
    while (*str)
    {
        *p++ = *str++;
    }

    return p;
}

static char *SMS_AppendNumber(char *p, unsigned int num)
{
    char buf[10];
    int i = 0;

    if (num == 0)
    {
        *p++ = '0';
        return p;
    }

    while (num > 0)
    {
        buf[i++] = (num % 10) + '0';
        num = num / 10;
    }

    while (i > 0)
    {
        *p++ = buf[--i];
    }

    return p;
}


static char *SMS_AppendTemperature(char *p, float temperature)
{
    unsigned int integer_part;
    unsigned int decimal_part;

    integer_part = (unsigned int)temperature;

    decimal_part =
        (unsigned int)((temperature - integer_part) * 100);

    p = SMS_AppendNumber(p, integer_part);

    *p++ = '.';

    if (decimal_part < 10)
    {
        *p++ = '0';
    }

    p = SMS_AppendNumber(p, decimal_part);

    return p;
}


int main(void)
{
    float temperature;
    unsigned int rain;
    unsigned int soil;
    unsigned int light;

    unsigned char temp_alert_sent = 0;
    unsigned char rain_alert_sent = 0;
    unsigned char soil_alert_sent = 0;

    char sms_msg[160];
    char *p;


 

    Timer0_Init();
    LCD_Init();
    ADC_Init();
    UART0_INIT();
    LED_INIT();
  

  
    IO0DIR &= ~(1 << 18);

    GSM_INIT();


    LCD_Clear();

    LCD_SetCursor(1, 2);
    LCD_String("WEATHER MONITOR");

    LCD_SetCursor(2, 5);
    LCD_String("SYSTEM");

    Timer0_Delay_ms(1000);

    LCD_Clear();

    LCD_SetCursor(1, 3);
    LCD_String("SYSTEM STARTING");

    Timer0_Delay_ms(1000);



    while (1)
    {


        temperature = Read_Temperature();
        rain = Read_RainSensor();
        soil = Read_SoilMoisture();
        light = Read_Light();




        LCD_Clear();


        LCD_SetCursor(1, 1);
        LCD_String("TEMP: ");
        LCD_PrintFloat(temperature);
        LCD_Data('C');



        LCD_SetCursor(2, 1);
        LCD_String("RAIN: ");

        if (rain == 1)
        {
            LCD_String("DETECTED");
        }
        else
        {
            LCD_String("NO");
        }



        LCD_SetCursor(3, 1);
        LCD_String("SOIL: ");
        LCD_PrintNumber(soil);
        LCD_Data('%');


   

        LCD_SetCursor(4, 1);
        LCD_String("LIGHT: ");

        if (light >= 50)
        {
            LCD_String("DAY");
        }
        else
        {
            LCD_String("NIGHT");
        }



        if (temperature >= 35.0f)
        {
            LED_HIGH();
         

            if (temp_alert_sent == 0)
            {
        

                p = sms_msg;

                p = SMS_AppendString(
                    p,
                    "WEATHER ALERT\r\n"
                );

                p = SMS_AppendString(
                    p,
                    "Temperature: "
                );

                p = SMS_AppendTemperature(
                    p,
                    temperature
                );

                p = SMS_AppendString(
                    p,
                    "C\r\n"
                );

                p = SMS_AppendString(
                    p,
                    "Soil Moisture: "
                );

                p = SMS_AppendNumber(
                    p,
                    soil
                );

                p = SMS_AppendString(
                    p,
                    "%\r\n\r\n"
                    "! High Temperature !\r\n"
                    "Take Necessary Action."
                );

                *p = '\0';

                GSM_SEND_SMS(sms_msg);

                temp_alert_sent = 1;
            }
        }
        else if(temperature <= 34.0f)
        {
            LED_LOW();
        



            temp_alert_sent = 0;
        }



        if (rain == 1)
        {
					  LED_HIGH();
         
            if (rain_alert_sent == 0)
            {
            
                p = sms_msg;

                p = SMS_AppendString(p, "WEATHER ALERT\r\n");

                p = SMS_AppendString(p, "Temperature: ");
                p = SMS_AppendTemperature(p, temperature);
                p = SMS_AppendString(p, "C\r\n");

                p = SMS_AppendString(p, "Soil Moisture: ");
                p = SMS_AppendNumber(p, soil);
                p = SMS_AppendString(p, "%\r\n");

                p = SMS_AppendString(
                p,
                  "Rain: DETECTED\r\n"
                  "\r\n"
                  "! Rain Alert!\r\n"
                  "Take Necessary Action."
                 );

                *p = '\0';

               GSM_SEND_SMS(sms_msg);

                rain_alert_sent = 1;
            }
        }
        else
        {
            rain_alert_sent = 0;
        }


        if (soil < 30)
        {
            if (soil_alert_sent == 0)
            {
             

                p = sms_msg;

                p = SMS_AppendString(
                    p,
                    "WEATHER ALERT\r\n"
                );

                p = SMS_AppendString(
                    p,
                    "Temperature: "
                );

                p = SMS_AppendTemperature(
                    p,
                    temperature
                );

                p = SMS_AppendString(
                    p,
                    "C\r\n"
                );

                p = SMS_AppendString(
                    p,
                    "Soil Moisture: "
                );

                p = SMS_AppendNumber(
                    p,
                    soil
                );

                p = SMS_AppendString(
                    p,
                    "%\r\n\r\n"
                    "! Soil Moisture LOW !\r\n"
                    "Water Required."
                );

                *p = '\0';

                GSM_SEND_SMS(sms_msg);

                soil_alert_sent = 1;
            }
        }
        else
        {
            soil_alert_sent = 0;
        }



        Timer0_Delay_ms(1000);
    }
}

