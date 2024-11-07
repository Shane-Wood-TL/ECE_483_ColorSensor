#ifndef allCppDefines
#define allCppDefines

//amount of colors in checkableColors (in main2.cpp)
#define checkableColorsCount 14


//calibration values
#define redRawLow 1400 //red at black
#define redRawHigh 24000 //red at white
#define redRawRange (redRawHigh-redRawLow)
#define redReferenceLow 0
#define redReferenceRange (255-redReferenceLow)

#define greenRawLow 1600 //green at black
#define greenRawHigh 27000 //green at white
#define greenRawRange (greenRawHigh-greenRawLow)
#define greenReferenceLow 0
#define greenReferenceRange (255-greenReferenceLow)
   
#define blueRawLow 1200 //blue at black
#define blueRawHigh 20000 //blue at white
#define blueRawRange (blueRawHigh-blueRawLow)
#define blueReferenceLow 0
#define blueReferenceRange (255-blueReferenceLow)

//calibration values determined via excel
#define redExp 1.4
#define redM 1
#define redB -10

#define greenExp 1.5
#define greenM 1
#define greenB -30

#define blueExp 1.2
#define blueM 1
#define blueB 0

//size of the queues
#define queueSize 10



//c Includes
#include <string>
#include <iomanip>
#include <cmath>


//color struct
struct color{
        std::string name;
        uint16_t red,green,blue;
};

//our includes
#include "queue.h"
#include "font.h"
#include "ssd1306.h"
#include "tcs3472.h"
#include "pulledUpSwitch.h"






#endif