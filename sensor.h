#ifndef SENSORS_H
#define SENSORS_H


typedef struct
{
    float temperature;         

    unsigned int soilMoisture;  
    unsigned int rainfall;      

    unsigned int light;         

} SensorData;


float Read_Temperature(void);


unsigned int Read_SoilMoisture(void);


unsigned int Read_RainSensor(void);

unsigned int Read_Light(void);


void Display_SensorData(SensorData *data);

#endif
