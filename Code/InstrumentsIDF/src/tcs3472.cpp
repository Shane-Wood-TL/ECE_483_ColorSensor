#include "../include/tcs3472.h"

void tcs3472C::turnOnLed()
{
    // set the led on the breakout board to high
    gpio_set_level(ledPinTCS, 1);
}

void tcs3472C::turnOffLed()
{
    // set the led on the breakout board low
    gpio_set_level(ledPinTCS, 0);
}

esp_err_t tcs3472C::sendCommandTCS3472(uint8_t command, uint8_t registerToChange)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // this is the current i2c "event" that is occuring
    // cmd stores all commands before executing them
    i2c_master_start(cmd); // start the event

    // set up writing to the sensor
    i2c_master_write_byte(cmd, (TCS3472Address << 1) | I2C_MASTER_WRITE, true);

    // In a combined protocol, the first byte written is the
    // command byte followed by reading a series of bytes.
    // set up register for writing
    i2c_master_write_byte(cmd, 0x80 | registerToChange, true);

    // write the change
    i2c_master_write_byte(cmd, command, true);

    // stop the event
    i2c_master_stop(cmd);

    // this line actually does all of the lines above with a timeout period to the bus
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);

    // delete the link/event
    i2c_cmd_link_delete(cmd);
    return ret; // return if the writing was sucessful
}

uint16_t tcs3472C::readDataTCS3472(uint8_t reg)
{
    // colors are stored in 2 registers, high and low btyes
    uint8_t registerData[2];

    i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // this is the current i2c "event" that is occuring
    i2c_master_start(cmd);                        // start the event

    // Send the COMMAND and the register to be read
    i2c_master_write_byte(cmd, (TCS3472Address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x80 | reg, true);

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (TCS3472Address << 1) | I2C_MASTER_READ, true);

    // read 2 consectuive registesters for each color
    i2c_master_read(cmd, registerData, 2, I2C_MASTER_LAST_NACK);

    // stop the event
    i2c_master_stop(cmd); // need to stop when switching from writing to reading

    // this line actually does all of the lines above with a timeout period to the bus
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd); // delete the link/event

    return (registerData[1] << 8) | registerData[0]; // shift the higher over eight
    // to make room for the lower eight and combine them using or
}

void tcs3472C::initTCS3472()
{
    // set the pin driving the led to output
    gpio_set_direction(ledPinTCS, GPIO_MODE_OUTPUT);
    // turn on the led
    turnOnLed();

    // send init commands to the sensor

    // enable register pg 22 (0x00)
    // https://files.waveshare.com/upload/e/e4/TCS3472_Datasheet.pdf
    // 4 AIEN RBGC Interupt / dont care
    // 3 WEN wait time enabled / dont care
    // 1 (0x02) AEN RGBC enabled, starts ADC on-board, yes need
    // 0 (0x01) PON power on, powers on clock, yes need first
    // sendCommandTCS34725(TCS34725_ENABLE, TCS34725_ENABLE_PON);
    // command, register
    sendCommandTCS3472(0x01, 0x00);

    // now that there is power, start taking measurements
    // dont lose the power though
    //
    // sendCommandTCS34725(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
    sendCommandTCS3472(0x01 | 0x02, 0x00);

    // set gain
    // 0x0F Control register
    // 0x01 4x gain
    // 0x10 16x gain
    // 0x11 60x gain
    // enable register pg 26
    // https://files.waveshare.com/upload/e/e4/TCS3472_Datasheet.pdf
    sendCommandTCS3472(0x10, 0x0F);

    // set the integration time for color averaging
    // enable register pg 23
    // https://files.waveshare.com/upload/e/e4/TCS3472_Datasheet.pdf
    // 0x01 rgbc timing register
    // 0xD5 42 integration cycles in 101ms
    sendCommandTCS3472(0x01, 0xD6);
}
tcs3472C::tcs3472C(queue *colorQueueI)
{
    colorQueue = colorQueueI;
    initTCS3472();
}

void tcs3472C::getNewValues()
{
    r = readDataTCS3472(0x16); // readings from the red channel registers
    g = readDataTCS3472(0x18); // readings from the green channel registers
    b = readDataTCS3472(0x1A); // readings from the blue channel registers
    
}


void tcs3472C::correctValues(){
    //run the correction based on the values in #allCppDefines.h

    //do the inital uint16 to uint8_t conversion
    correctedRedINT = (uint8_t)(((r - redRawLow) * redReferenceRange) / (redRawRange));
    correctedGreenINT = (uint8_t)(((g - greenRawLow) * greenReferenceRange) / (greenRawRange));
    correctedBlueINT = (uint8_t)(((b - blueRawLow) * blueReferenceRange) / (blueRawRange));
    
    //run the exponential part of the correction for red
    float tempRed = pow(correctedRedINT, redExp);
    tempRed = ((tempRed * redM) + redB);
    if (tempRed > 255)
    {
        tempRed = 255;
    }else if(tempRed < 0){
        tempRed = 0;
    }
    correctedRedINT = (uint8_t)tempRed; //ensure that it is still a uint8_t

    //run the exponential part of the correction for green
    float tempGreen = pow(correctedGreenINT, greenExp);
    tempGreen = ((tempGreen*greenM) + greenB);
    if (tempGreen > 255)
    {
        tempGreen = 255;
    }else if(tempGreen < 0){
        tempGreen = 0;
    }
    correctedGreenINT = (uint8_t)tempGreen; //ensure that it is still a uint8_t

    //run the exponential part of the correction for blue
    float tempBlue = pow(correctedBlueINT, blueExp);
    tempBlue = ((tempBlue*blueM) + blueB);
    if (tempBlue > 255)
    {
        tempBlue = 255;
        correctedBlueINT = (uint8_t)tempBlue;
    }else if(tempGreen < 0){
        tempGreen = 0;
    }
    correctedBlueINT = (uint8_t)tempBlue; //ensure that it is still a uint8_t
}

void tcs3472C::update(){

    getNewValues(); //check the sensor
    correctValues(); //fix values
    color toSend; //data to send
    toSend.name = ""; //color is not named yet (display does this)
    //send the corrected data to the display
    toSend.red=correctedRedINT; 
    toSend.green=correctedGreenINT;
    toSend.blue=correctedBlueINT;
    // toSend.red=r;
    // toSend.green=g;
    // toSend.blue=b;
    //send the data
    colorQueue->enqueue(toSend);

}