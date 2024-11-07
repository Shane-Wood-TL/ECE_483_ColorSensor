#ifndef ssd1306
#define ssd1306
#include "../include/allDefines.h"
#include "../include/allCppDefines.h"

class ssd1306C{
private:
    queue *colorQueue; //color data input queue
    color currentColor; //currently displayed info
    uint8_t buffer[128 * 64 / 8] = {0};//SSD1306 display buffer
    color *checkColors; //the list of checkable colors (for named mode)
    Inputqueue *switchQ; //switch queue
    bool isSwitched = false; //what mode the display is in


    //i2c commands
    esp_err_t sendCommandSSD1306(uint8_t command);
    esp_err_t sendDataSSD1306(uint8_t *data, size_t len);

    //display setup
    void initSSD1306();

    //clears display
    void clearSSD1306();

    //draws a pixel
    void drawPixelSSD1306(uint8_t x, uint8_t y);
    
    //writes entire buffer to the display
    void writeBufferSSD1306();

    //write a letter to the display
    void writeLetterSSD1306(uint8_t letter, uint8_t xPos, uint8_t yPos);
    
    //finds the differents between 2 3d cordinates (for color matching)
    double calculateDistance(uint8_t red0, uint8_t red1,uint8_t green0,uint8_t green1, uint8_t blue0,uint8_t blue1);
    
    //given the color and list, find what color the input is closest to
    std::string findColor(uint8_t r, uint8_t g, uint8_t b, color *colorList, uint8_t colorCount);
    
    //clear the buffer variable
    void clearBuffer();

    //write a string to the display
    void writeStringSSD1306(std::string Word, uint8_t xPos, uint8_t yPos);
    
    //handles percent mode
    void percentColors();

    //handles named colors mode
    void namedColors();

    //gets the pixel data for a char from the fontMap
    const uint16_t* getLetter(uint8_t letter);
public:
    ssd1306C(queue *colorQueueI, color *checkColorsI, Inputqueue *switchI);
    void update(); //check queues, update display
};
#endif