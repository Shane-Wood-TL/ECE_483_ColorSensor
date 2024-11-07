#ifndef pulledUpSwitch__
#define pulledUpSwitch__
#include "allCppDefines.h"

class pulledUpSwitch{
    gpio_num_t pinNum; //pin number
    Inputqueue *inputQueue; //queue to enqueue data to
    public: 
        pulledUpSwitch(gpio_num_t pin, Inputqueue *inputQueueInstance);
        void readPin(); //read the pin
};


#endif