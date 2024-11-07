#include "pulledUpSwitch.h"

pulledUpSwitch::pulledUpSwitch(gpio_num_t pin, Inputqueue *inputQueueInstance){
    pinNum = pin;
    inputQueue = inputQueueInstance;
    gpio_set_direction(pinNum, GPIO_MODE_INPUT); //set as input
    gpio_pullup_en(pinNum); //enable pullup
    gpio_pulldown_dis(pinNum); //disable pulldown
}

void pulledUpSwitch::readPin(){
    int8_t pinState = gpio_get_level(pinNum); //read pin
    bool pin = (pinState == 1); //convert to bool
    inputQueue->enqueue(pin); //enqueue status
}