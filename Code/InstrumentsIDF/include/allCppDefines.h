#ifndef allCppDefines
#define allCppDefines
#define checkableColorsCount 9

#define redRawLow 391
#define redRawRange 6275-redRawLow
#define redReferenceLow 0
#define redReferenceRange 255-redReferenceLow

#define greenRawLow 388
#define greenRawRange 7253-greenRawLow
#define greenReferenceLow 0
#define greenReferenceRange 255-greenReferenceLow
   
#define blueRawLow 256
#define blueRawRange 4915-blueRawLow
#define blueReferenceLow 0
#define blueReferenceRange 255-blueReferenceLow


#define queueSize 10
#include <string>
#include <iomanip>
#include <cmath>

struct color{
        std::string name;
        uint8_t red,green,blue;
};


#include "queue.h"
#include "font.h"
#include "../include/ssd1306.h"
#include "../include/tcs3472.h"



#endif

