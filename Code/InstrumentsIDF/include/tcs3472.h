#ifndef tcs3472
#define tcs3472
#include "../include/allDefines.h"
#include "../include/allCppDefines.h"

class tcs3472C{
private:
    void initTCS3472();
    esp_err_t sendCommandTCS3472(uint8_t command, uint8_t registerToChange);
    uint16_t readDataTCS3472(uint8_t reg);
    void getNewValues();
    void correctValues();
    queue *colorQueue;
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint8_t correctedRedINT;
    uint8_t correctedGreenINT;
    uint8_t correctedBlueINT;
public:
    tcs3472C(queue *colorQueueI);
    void turnOnLed();
    void turnOffLed();
    void update();
};
#endif