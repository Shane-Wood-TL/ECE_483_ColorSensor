extern "C" {void cppMain();}
#include "../include/allDefines.h"
#include "../include/allCppDefines.h"


const uint16_t *fontMap[128] = {0}; //ASCII table

void cppMain(){
    color checkableColors[checkableColorsCount] = {
    {"Red", 206, 60, 53},
    {"Orange", 232, 141, 52},
    {"Yellow", 255, 253, 66},
    {"Green", 76, 166, 84},
    {"Blue", 38, 95, 177},
    {"Violet", 138, 76, 154},
    {"White", 255, 255, 255},
    {"Gray", 128, 128, 128},
    {"Black", 19, 30, 32},
    // {"DarkBlue", 6, 36, 78},
    // {"DarkPink", 83, 38, 67},
    // {"DarkGreen", 25, 92, 52},
    // {"LightGray",225,243,196}
    };

    //fontFile activeFont;
    initializeFontMap();
    queue colorQueue;
    Inputqueue switchInput;
    ssd1306C display(&colorQueue,checkableColors, &switchInput);
    tcs3472C colorSensor(&colorQueue);

    bool run = false;


    while (1){
        if(run){
            run = false;
            colorSensor.update();
        }else{
            run = true;   
            display.update();
        }
    }
}






























    // float redGTable[256];
    // float greenGTable[256];
    // float blueGTable[256];


    // for (uint16_t i=0; i<256; i++) {
    //     float x = i;
    //     x /= 255;
    //     x = pow(x, 1.04);
    //     x *= 255;
    //     if(x >= 255){
    //         x=255;
    //     }

    //     redGTable[i] = (x);
    // }

    // for (uint16_t i=0; i<256; i++) {
    //     float x = i;
    //     x /= 255;
    //     x = pow(x, 1.11);
    //     x *= 255;
    //     if(x >= 255){
    //         x=255;
    //     }

    //     greenGTable[i] = (x);
    // }

    // for (uint16_t i=0; i<256; i++) {
    //     float x = i;
    //     x /= 255;
    //     x = pow(x, 0.8);
    //     x *= 255;
    //     if(x >= 255){
    //         x=255;
    //     }
    //         blueGTable[i] = x;
    // }







// std::string valueToHex(uint8_t v){
//     //very very cursed way to map numbers to their hex string equivalants
//     switch(v){
//         case 0: return "0";
//         case 1: return "1";
//         case 2: return "2";
//         case 3: return "3";
//         case 4: return "4";
//         case 5: return "5";
//         case 6: return "6";
//         case 7: return "7";
//         case 8: return "8";
//         case 9: return "9";
//         case 10: return "A";
//         case 11: return "B";
//         case 12: return "C";
//         case 13: return "D";
//         case 14: return "E";
//         case 15: return "F";
//         default: return "L"; //if you see L something is very wrong
//     }
// }

// std::string convertToHex(uint8_t singleColor){
//     //break 0-255 into 2 hex numbers
//     //hex is base 16
//     uint8_t upperV = floor(singleColor/16);
//     //get the remainder ready to convert
//     uint8_t lowV = floor(singleColor-upperV*16);
//     //combine the 2 strings
//     std::string upperVS = valueToHex(upperV);
//     std::string lowerVS = valueToHex(lowV);
//     return  upperVS.append(lowerVS);
// }






        // writeStringSSD1306(std::to_string(r),buffer,59,0);
        // writeStringSSD1306(std::to_string(g),buffer,59,15);
        // writeStringSSD1306(std::to_string(b),buffer,59,31);
        //         writeStringSSD1306(std::to_string(clear),buffer,59,47);

        // writeStringSSD1306(std::to_string(correctedRed),buffer,0,0);
        // writeStringSSD1306(std::to_string(correctedGreen),buffer,0,15);
        // writeStringSSD1306(std::to_string(correctedBlue),buffer,0,31);

        // writeStringSSD1306(std::to_string(correctedRedINT),buffer,0,0);
        // writeStringSSD1306(std::to_string(correctedGreenINT),buffer,0,15);
        // writeStringSSD1306(std::to_string(correctedBlueINT),buffer,0,31);
        
        // writeStringSSD1306(std::to_string(redGTable[correctedRedINT]),buffer,59,0);
        // writeStringSSD1306(std::to_string(greenGTable[correctedGreenINT]),buffer,59,15);
        // writeStringSSD1306(std::to_string(blueGTable[correctedBlueINT]),buffer,59,31);


        //     /*
        //     color to text,
        //     Red
        //     Orange
        //     Yellow
        //     Green
        //     Blue
        //     Violet
        //     White
        //     Gray
        //     Black

        //     Red-Orange
        //     Yellow-Orange
        //     Yellow-Green
        //     Blue-Green
        //     Blue-Violet
        //     Red-Violet
        //     */

        //    /*
        //    Color to hex
        //    0xRRGGBB
        //     */
        // redHex = convertToHex(redGTable[correctedRedINT]);
        // greenHex = convertToHex(greenGTable[correctedGreenINT]);
        // blueHex = convertToHex(blueGTable[correctedBlueINT]);

        // // // //writeStringSSD1306("0x"+redHex+greenHex+blueHex,buffer,0,47);
        // writeStringSSD1306("0x",buffer,0,47);
        // writeStringSSD1306(redHex,buffer,23,47);
        // writeStringSSD1306(greenHex,buffer,47,47);
        // writeStringSSD1306(blueHex,buffer,71,47);



        //writeStringSSD1306("Test",buffer,0,0);
