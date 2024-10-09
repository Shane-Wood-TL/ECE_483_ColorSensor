#include "allCppDefines.h"

extern const uint16_t *fontMap[128];//ASCII table

esp_err_t ssd1306C::sendCommandSSD1306(uint8_t command)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // this is the current i2c "event" that is occuring
    // cmd stores all commands before executing them

    i2c_master_start(cmd); // start the event
    // set up writing the the correct address (master is writing to the address of the 1306)
    // i2c_master_write_byte(cmd, (ESP_SLAVE_ADDR << 1) | I2C_MASTER_WRITE, ACK_EN);
    i2c_master_write_byte(cmd, (SSD1306Address << 1) | I2C_MASTER_WRITE, true);

    i2c_master_write_byte(cmd, 0x00, true);    // if data == 0, then command is being sent
    i2c_master_write_byte(cmd, command, true); // set the command that was given in parameter

    i2c_master_stop(cmd); // stop the transaction

    // this line actually does all of the lines above with a timeout period
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);

    i2c_cmd_link_delete(cmd); // delete the link/event
    return ret;               // return if the writing was sucessful
}

esp_err_t ssd1306C::sendDataSSD1306(uint8_t *data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // this is the current i2c "event" that is occuring
    // cmd stores all commands before executing them
    i2c_master_start(cmd); // start the event

    // set up writing to the display
    i2c_master_write_byte(cmd, (SSD1306Address << 1) | I2C_MASTER_WRITE, true);

    // seting up data more (writting 0100_0000 to set D/C# to 1 (Data mode) in the control byte
    i2c_master_write_byte(cmd, 0x40, true);

    // write the data that was given to this function
    i2c_master_write(cmd, data, len, true);

    // stop the event
    i2c_master_stop(cmd);

    // this line actually does all of the lines above with a timeout period to the bus
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    // delete the link/event
    i2c_cmd_link_delete(cmd);
    return ret; // return if the writing was sucessful
}

void ssd1306C::initSSD1306()
{
    // command list taken from mircocontrollers lab
    sendCommandSSD1306(0xAE);
    sendCommandSSD1306(0xA8); // Set MUX ratio
    sendCommandSSD1306(0x3F); // Set MUX ratio, 0x1F for 128x32 and 0x3F for 128x64
    sendCommandSSD1306(0xD3); // Set Display Offset
    sendCommandSSD1306(0x00); // Set Display Offset
    sendCommandSSD1306(0x40); // Set Display Start Line
    sendCommandSSD1306(0x20); // Set Display Mode to Horizontal
    sendCommandSSD1306(0x00); // Set Display Mode to Horizontal
    sendCommandSSD1306(0xA1); // Set Segment Re-map
    sendCommandSSD1306(0xC8); // Set COM Output Scan Direction
    sendCommandSSD1306(0xDA); // Set COM Pins hardware configuration
    sendCommandSSD1306(0x12); // Set COM Pins hardware configuration, 0x02 for 128x32 and 0x12 for 128x64
    sendCommandSSD1306(0x81); // Set Contrast Control
    sendCommandSSD1306(0x9F); // Set Contrast Control Value from 0x00 to 0xFF minimum to maximum
    sendCommandSSD1306(0xA4); // Disable Entire Display
    sendCommandSSD1306(0xA6); // Set Normal Display
    sendCommandSSD1306(0xD5); // Set Oscillation Frequency
    sendCommandSSD1306(0x80); // Set Oscillation Frequency
    sendCommandSSD1306(0x8D); // Enable Charge Pump Regulator
    sendCommandSSD1306(0x14); // Enable Charge Pump Regulator
    sendCommandSSD1306(0xAF); // Turn Display On
}

void ssd1306C::clearSSD1306()
{
    uint8_t emptyBuffer[SSD1306HorizontalRes] = {0}; // each page is 128 x 8
    // display is 128 x 64, each page is 8 pixels high
    for (uint8_t i = 0; i < SSD1306Pages; i++)
    {
        sendCommandSSD1306(0xB0 + i); // 0B0 - 0B7 are the 8 vertical pages

        // sets the column address from 0-127
        sendCommandSSD1306(0x00);
        sendCommandSSD1306(0x10);

        // write the empty buffer to the display
        sendDataSSD1306(emptyBuffer, sizeof(emptyBuffer));
    }
}

void ssd1306C::drawPixelSSD1306(uint8_t x, uint8_t y, bool color)
{
    if (x >= 128 || y >= 64)
        return; // Out of bounds
    if (color)
    {
        buffer[x + (y / 8) * 128] |= (1 << (y % 8));
    }
    else
    {
        buffer[x + (y / 8) * 128] &= ~(1 << (y % 8));
    }
}

void ssd1306C::writeBufferSSD1306()
{
    for (uint8_t i = 0; i < 8; i++)
    {                                 // Send each page
        sendCommandSSD1306(0xB0 + i); // Set page start address
        sendCommandSSD1306(0x00);     // Set lower column address
        sendCommandSSD1306(0x10);     // Set higher column address

        sendDataSSD1306(&buffer[128 * i], 128);
    }
}

void ssd1306C::writeLetterSSD1306(uint8_t letter, uint8_t xPos, uint8_t yPos)
{
    const uint16_t *matrix = getLetter(letter);
    for (int i = 0; i < 16; i++)
    { // 16 tall
        for (int j = 0; j < 12; j++)
        { // 12 wide
            if ((matrix[i]) & (1 << (12 - j)))
            {
                drawPixelSSD1306(xPos + j, yPos + i, true);
            }
        }
    }
}

void ssd1306C::writeStringSSD1306(std::string Word, uint8_t xPos, uint8_t yPos)
{

    for (uint8_t i = 0; i < Word.length(); i++)
    {
        writeLetterSSD1306(Word[i], xPos + i * 12, yPos);
    }
}

ssd1306C::ssd1306C(queue *colorQueueI, color *checkColorsI, Inputqueue *switchI)
{
    colorQueue = colorQueueI;
    checkColors = checkColorsI;
    switchQ = switchI;
    initSSD1306(); // set up display
    clearSSD1306();

    // Send the buffer to the display
    writeBufferSSD1306();
}

double ssd1306C::calculateDistance(uint8_t red0, uint8_t red1, uint8_t green0, uint8_t green1, uint8_t blue0, uint8_t blue1)
{
    return (double)sqrt(pow((double)(red1 - red0), 2) + pow((double)(green1 - green0), 2) + pow((double)(blue1 - blue0), 2));
}

std::string ssd1306C::findColor(uint8_t r, uint8_t g, uint8_t b, color *colorList, uint8_t colorCount)
{
    double closest = 1000;
    std::string currentClosestName = "Black";
    for (uint8_t i = 0; i < colorCount; i++)
    {
        double currentClosest = calculateDistance(r, colorList[i].red, g, colorList[i].green, b, colorList[i].blue);
        if (currentClosest < closest)
        {
            currentClosestName = colorList[i].name;
            closest = currentClosest;
        }
    }
    return currentClosestName;
}

// empties buffer so that new data can be put into it
void ssd1306C::clearBuffer()
{
    for (uint16_t i = 0; i < 1024; i++)
    {
        buffer[i] = 0;
    }
    return;
}

void ssd1306C::percentColors()
{
    float percentR;
    float percentG;
    float percentB;

    float sum = currentColor.red + currentColor.green + currentColor.green;
    if (sum > 10)
    {
        percentR = currentColor.red / sum;
        percentG = currentColor.blue / sum;
        percentB = currentColor.green / sum;
    }
    else
    {
        percentR = 0;
        percentG = 0;
        percentB = 0;
    }
    writeStringSSD1306(std::to_string((uint8_t)(percentR * 100)), 0, 15);
    writeStringSSD1306(std::to_string((uint8_t)(percentG * 100)), 0, 31);
    writeStringSSD1306(std::to_string((uint8_t)(percentB * 100)), 0, 47);
}

void ssd1306C::namedColors()
{
    std::string colorL = findColor(currentColor.red, currentColor.green, currentColor.blue, checkColors, checkableColorsCount);
    // writeStringSSD1306(std::to_string(correctedRedINT),buffer,0,15);
    // writeStringSSD1306(std::to_string(correctedGreenINT),buffer,0,31);
    // writeStringSSD1306(std::to_string(correctedBlueINT),buffer,0,47);
    writeStringSSD1306(colorL, 0, 0);
}

void ssd1306C::update(){
    switchQ->enqueue(isSwitched); //check which mode it is in
    isSwitched = false;
    if(colorQueue->dequeue(&currentColor)){
        clearBuffer();
        if(isSwitched){
            percentColors();
        }else{
            namedColors();
        }

    }
    writeBufferSSD1306();
    
}

const uint16_t* ssd1306C::getLetter(uint8_t letter){
	return fontMap[letter];
}