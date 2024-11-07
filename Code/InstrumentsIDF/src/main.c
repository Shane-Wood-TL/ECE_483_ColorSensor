#include "../include/allDefines.h"


extern void cppMain();


void setupI2CMaster() {
    //i2c device setup

    /*
    int i2c_master_port = 0; //same as I2C_NUM_0
    i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = I2C_MASTER_SDA_IO,         // select SDA GPIO specific to your project
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_io_num = I2C_MASTER_SCL_IO,         // select SCL GPIO specific to your project
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = I2C_MASTER_FREQ_HZ,  // select frequency specific to your project
    .clk_flags = 0,                          // optional; you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here
    };
    https://docs.espressif.com/projects/esp-idf/en/v5.1/esp32/api-reference/peripherals/i2c.html
    */

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER, //esp32s2 will be master
        .master.clk_speed = I2C_MASTER_FREQ_HZ, //clock speed for i2c
        .scl_io_num = I2C_MASTER_SCL_IO, //scl pin
        .sda_io_num = I2C_MASTER_SDA_IO, //sda pin  
        //.scl_pullup_en = GPIO_PULLUP_ENABLE,
        //.sda_pullup_en = GPIO_PULLUP_ENABLE
    };
    //map the config to the i2c number
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

void app_main() {
    setupI2CMaster();
    cppMain();

    //code never gets here
    while (1) {
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        // Draw some pixels
        // for(uint8_t i =0;i < 128; i++){
        //     for(uint8_t j =0;j < 64; j++){
        //         ssd1306_draw_pixel(i, j, true, buffer);
        //     }   
        // }
        
        //ssd1306_draw_text(0, 0, "Hello, World!", buffer);
        //ssd1306_update(buffer);

        // Send the buffer to the display
        //ssd1306_update(buffer);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //ssd1306_clear();


    }
}

