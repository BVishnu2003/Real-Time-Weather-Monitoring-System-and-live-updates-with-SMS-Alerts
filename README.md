Real-Time Weather Monitoring System with Live Updates and SMS Alerts

📌 Project Overview

The Real-Time Weather Monitoring System with Live Updates and SMS Alerts is an embedded system developed using the LPC2129 ARM7 microcontroller.

The system monitors environmental conditions using different sensors and displays live readings on a 20×4 LCD. When a predefined threshold is crossed, the system sends an SMS alert through the GSM module.

🌦️ Sensors Used

- 🌡️ LM35 – Temperature Sensor
- 🌱 Soil Moisture Sensor – Soil moisture measurement
- 🌧️ IR Sensor – Rain detection
- 💡 LDR – Light intensity / Day-Night detection

🛠️ Hardware Components

- LPC2129 ARM7 Microcontroller
- MCP3204 ADC
- LM35 Temperature Sensor
- Soil Moisture Sensor
- IR Sensor
- LDR
- SIM800C / SIM900 GSM Module
- 20×4 LCD Display
- LED
- Power Supply

💻 Software & Technologies

- Embedded C
- Keil µVision
- Proteus
- ARM7 LPC2129
- ADC
- SPI Communication
- UART Communication
- GSM AT Commands

⚙️ System Working

1. Sensors collect environmental data.
2. MCP3204 converts analog sensor signals into digital values.
3. LPC2129 processes the sensor values.
4. Temperature, soil moisture, rain, and light conditions are determined.
5. Live sensor values are displayed on the 20×4 LCD.
6. Sensor values are compared with predefined threshold values.
7. If an abnormal condition is detected, an SMS alert is sent through the GSM module.

🚨 Alert Conditions

Parameter| Condition| Action
Temperature| ≥ 35°C| LED ON + SMS Alert
Soil Moisture| < 30%| SMS Alert
Rain| Detected| LED ON + SMS Alert
Light| < 50| NIGHT indication

📱 SMS Alert

Example SMS:

WEATHER ALERT
Temperature: 36.50C
Soil Moisture: 20%
Rain: Detected
! Rain Alert!
Take Necessary Action.

📺 LCD Display

Example:

TEMP: 36.50 C
RAIN: DETECTED
SOIL: 20%
LIGHT: DAY

🔌 Communication

SPI

SPI communication is used between the LPC2129 and MCP3204 ADC.

UART

UART communication is used between the LPC2129 and GSM module.

GSM

The GSM module uses AT commands to send SMS alerts to the configured mobile number.

📂 Project Structure

Real-Time-Weather-Monitoring-System/
│
├── main.c
├── config.h
│
├── sensors.c
├── sensors.h
│
├── adc.c
├── adc.h
│
├── spi.c
├── spi.h
│
├── uart.c
├── uart.h
│
├── gsm.c
├── gsm.h
│
├── timer.c
├── timer.h
│
├── lcd.c
├── lcd.h
│
├── led.c
├── led.h
│
└── README.md

🚀 Applications

- Smart agriculture
- Greenhouse monitoring
- Environmental monitoring
- Weather monitoring
- Smart irrigation
- Remote agricultural monitoring

🔮 Future Enhancements

- IoT / Cloud connectivity
- Mobile application
- Web-based dashboard
- Data logging
- Automatic irrigation control
- Remote monitoring

👨‍💻 Project

Real-Time Weather Monitoring System with Live Updates and SMS Alerts

Technologies: Embedded C, LPC2129 ARM7, MCP3204 ADC, LM35, Soil Moisture Sensor, IR Sensor, LDR, 20×4 LCD, LED, GSM, SPI and UART.
