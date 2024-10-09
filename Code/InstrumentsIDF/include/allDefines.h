#ifndef allDefines
//guarding
#define allDefines

//basic headers
#include <stdio.h>
#include <stdint.h>

//esp32 specific headers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"



//i2c setup
#define I2C_MASTER_SCL_IO GPIO_NUM_7     // GPIO for SCL
#define I2C_MASTER_SDA_IO GPIO_NUM_6       // GPIO for SDA
#define I2C_MASTER_FREQ_HZ 100000   // Frequency of I2C (100 kHz)
#define I2C_MASTER_NUM I2C_NUM_0    // I2C port number


//SSD1306 setup
#define SSD1306Address 0x3C           // SSD1306 I2C address
#define SSD1306VerticalRes 64           //64 pixels tall
#define SSD1306HorizontalRes 128    //128 pixels across
#define SSD1306Pages SSD1306VerticalRes/8 //each page is a vertical 8 bits

//TCS3472 setup
#define TCS3472Address 0x29 //Color sensor I2C Address
#define ledPinTCS GPIO_NUM_8 //gpio pin for the sensor led

#endif