extern "C" {void cppMain();} //makes cppMain callable from main.c
#include "../include/allDefines.h"
#include "../include/allCppDefines.h"

//font map that the display uses
const uint16_t *fontMap[128] = {0}; //ASCII table


void cppMain(){
    //list of colors that the display can check for
    color checkableColors[checkableColorsCount] = {
    {"Red", 206, 60, 53},
    {"Orange", 255, 142, 38},
    {"Yellow", 255, 255, 120},
    {"Green", 25, 255, 43},
    {"Blue", 2, 140, 180},
    {"Violet", 138, 52, 111},
    {"White", 255, 255, 255},
    {"Gray", 128, 128, 128},
    {"Black", 0, 0, 0},
    {"DarkBlue", 0, 40, 70},
    {"Pink", 255, 200, 125},
    {"Green",235,255,73},
    {"Orange",255,255,70},
    {"Magenta", 255,22,91}
    // {"DarkGreen", 25, 92, 52},
    // {"LightGray",225,243,196}
    };

    
    initializeFontMap(); //map font map
    queue colorQueue; //queue for sensor to display
    Inputqueue switchInput; //queue for switch to display
    pulledUpSwitch switchMode(switchPin,&switchInput); //switch constructor
    ssd1306C display(&colorQueue,checkableColors, &switchInput);//display constructor
    tcs3472C colorSensor(&colorQueue); //clor sensor setup

    //either the sensor updates or the display does per cycle
    bool run = false;


    while (1){
        if(run){
            //update the sensor + switch
            run = false;
            colorSensor.update();
            switchMode.readPin(); //read switch
        }else{
            //update the display
            run = true;   
            display.update();
        }
    }
}