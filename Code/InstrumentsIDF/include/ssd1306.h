#ifndef ssd1306
#define ssd1306
#include "../include/allDefines.h"
#include "../include/allCppDefines.h"

class ssd1306C{
private:
    queue *colorQueue;
    color currentColor;
    uint8_t buffer[128 * 64 / 8] = {0};//SSD1306 display buffer
    color *checkColors;
    Inputqueue *switchQ;
    bool isSwitched = false;


    esp_err_t sendCommandSSD1306(uint8_t command);
    esp_err_t sendDataSSD1306(uint8_t *data, size_t len);
    void initSSD1306();
    void clearSSD1306();
    void drawPixelSSD1306(uint8_t x, uint8_t y, bool color);
    void writeBufferSSD1306();
    void writeLetterSSD1306(uint8_t letter, uint8_t xPos, uint8_t yPos);
    double calculateDistance(uint8_t red0, uint8_t red1,uint8_t green0,uint8_t green1, uint8_t blue0,uint8_t blue1);
    std::string findColor(uint8_t r, uint8_t g, uint8_t b, color *colorList, uint8_t colorCount);
    void clearBuffer();
    void writeStringSSD1306(std::string Word, uint8_t xPos, uint8_t yPos);
    void percentColors();
    void namedColors();
    const uint16_t* getLetter(uint8_t letter);
public:
    ssd1306C(queue *colorQueueI, color *checkColorsI, Inputqueue *switchI);
    void update();
};
#endif