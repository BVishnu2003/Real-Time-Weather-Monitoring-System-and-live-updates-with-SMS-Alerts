#ifndef CONFIG_H
#define CONFIG_H

#include <LPC21xx.h>

 

 
#define FOSC                12000000UL
#define CCLK                60000000UL

   
#define TEMP_CHANNEL       0
//#define RAIN_CHANNEL     1    
#define SOIL_CHANNEL       2
#define LDR_CHANNEL        3

 
#define ADC_VREF           3.3f


#define ADC_MAX_VALUE      4095.0f




#define IR_SENSOR_PIN      18




#define TEMP_HIGH_LIMIT    35.0f

#define SOIL_LOW_LIMIT     30


//#define RAIN_LIMIT         30

#define TEMP_RESET_LIMIT   34.0F


#define LIGHT_LOW_LIMIT    20




#define PHONE_NUMBER       "638XXXXX87"


#define GSM_BAUDRATE       9600



#define SENSOR_INTERVAL_MS 5000




#define LED_ON             1
#define LED_OFF            0



#define NORMAL_STATUS      0
#define ALERT_STATUS       1

#endif
