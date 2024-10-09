#include "allCppDefines.h"

#ifndef ___queue___
#define ___queue___

class queue {
	color buffer[queueSize]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    queue(); //constructor
	bool enqueue(color msg); //add values
	bool dequeue(color* msg); //remove values
};

class Inputqueue {
	bool buffer[queueSize]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    Inputqueue(); //constructor
	bool enqueue(bool msg); //add values
	bool dequeue(bool* msg); //remove values
};
#endif