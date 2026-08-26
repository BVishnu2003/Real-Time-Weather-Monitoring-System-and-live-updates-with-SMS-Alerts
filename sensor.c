#include "sensor.h"
#include "adc.h"
#include "config.h"
#include "lcd.h"
#include "timer.h"




float Read_Temperature(void)
{
    unsigned int adcValue;
    float voltage;
    float temperature;

    adcValue = MCP3204_Read(TEMP_CHANNEL);

    voltage = ((float)adcValue * ADC_VREF)
              / ADC_MAX_VALUE;

    temperature = voltage * 100.0f;

    return temperature;
}


unsigned int Read_SoilMoisture(void)
{
    unsigned int adcValue;
    unsigned int moisture;

    adcValue = MCP3204_Read(SOIL_CHANNEL);


    #define SOIL_DRY_ADC  1100
    #define SOIL_WET_ADC  200

  
    if (adcValue <= SOIL_WET_ADC)
    {
        moisture = 100;
    }
 
    else if (adcValue >= SOIL_DRY_ADC)
    {
        moisture = 0;
    }
 
    else
    {
        moisture =
            ((SOIL_DRY_ADC - adcValue) * 100UL) /
            (SOIL_DRY_ADC - SOIL_WET_ADC);
    }

    return moisture;
}




unsigned int Read_RainSensor(void)
{
    if ((IO0PIN & (1 << IR_SENSOR_PIN)) == 0)
    {
        return 1;       
    }
    else
    {
        return 0;       
    }
}



unsigned int Read_Light(void)
{
    unsigned int adcValue;
    unsigned int light;

    
    adcValue = MCP3204_Read(LDR_CHANNEL);

  
    light = (adcValue * 100UL) / 4095UL;

    if (light > 100)
    {
        light = 100;
    }

    return light;
}




void Display_SensorData(SensorData *data)
{

    LCD_Clear();

    LCD_String("TEMP:");

    LCD_PrintFloat(data->temperature);

    LCD_Data('C');

    LCD_SetCursor(2, 1);

    LCD_String("SOIL:");

    LCD_PrintNumber(data->soilMoisture);

    LCD_Data('%');

    Timer0_Delay_ms(2000);


    LCD_Clear();

    LCD_String("RAIN:");

    LCD_PrintNumber(data->rainfall);

    LCD_Data('%');

    LCD_SetCursor(2, 1);

    LCD_String("LIGHT:");

    LCD_PrintNumber(data->light);

    LCD_Data('%');

    Timer0_Delay_ms(2000);
}
