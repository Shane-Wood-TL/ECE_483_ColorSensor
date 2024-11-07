#ifndef tcs3472
#define tcs3472
#include "../include/allDefines.h"
#include "../include/allCppDefines.h"

class tcs3472C{
private:
//setup
    void initTCS3472();

    //i2c based functions
    esp_err_t sendCommandTCS3472(uint8_t command, uint8_t registerToChange);
    uint16_t readDataTCS3472(uint8_t reg);

    //read values from the sensor
    void getNewValues();

    //fix values based on correction values
    void correctValues();


    queue *colorQueue; //place to put corrected readings
    
    //raw r,g,b values
    uint16_t r; 
    uint16_t g;
    uint16_t b;

    //corrected r,g,b values
    uint8_t correctedRedINT;
    uint8_t correctedGreenINT;
    uint8_t correctedBlueINT;
public:
    //queue to put data in constructor
    tcs3472C(queue *colorQueueI);

    //control the led on the sensor (not used)
    void turnOnLed();
    void turnOffLed();

    //update the display
    void update();
};
#endif