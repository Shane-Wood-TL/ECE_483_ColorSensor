#include "allCppDefines.h"
extern const uint16_t *fontMap[128];//ASCII table


//map indexs to fonts based on using ASCII as a indxe
void initializeFontMap(){
    fontMap['0'] = zero;
    fontMap['1'] = one;
    fontMap['2'] = two;
    fontMap['3'] = three;
    fontMap['4'] = four;
    fontMap['5'] = five;
    fontMap['6'] = six;
    fontMap['7'] = seven;
    fontMap['8'] = eight;
    fontMap['9'] = nine;
    fontMap['#'] = hash;
    fontMap['A'] = capA;
    fontMap['B'] = capB;
    fontMap['C'] = capC;
    fontMap['D'] = capD;
    fontMap['E'] = capE;
    fontMap['F'] = capF;
    fontMap['G'] = capG;
    fontMap['H'] = capH;
    fontMap['I'] = capI;
    fontMap['J'] = capJ;
    fontMap['K'] = capK;
    fontMap['L'] = capL;
    fontMap['M'] = capM;
    fontMap['N'] = capN;
    fontMap['O'] = capO;
    fontMap['P'] = capP;
    fontMap['Q'] = capQ;
    fontMap['R'] = capR;
    fontMap['S'] = capS;
    fontMap['T'] = capT;
    fontMap['U'] = capU;
    fontMap['V'] = capV;
    fontMap['W'] = capW;
    fontMap['X'] = capX;
    fontMap['Y'] = capY;
    fontMap['Z'] = capZ;
    fontMap['a'] = lowA;
    fontMap['b'] = lowB;
    fontMap['c'] = lowC;
    fontMap['d'] = lowD;
    fontMap['e'] = lowE;
    fontMap['f'] = lowF;
    fontMap['g'] = lowG;
    fontMap['h'] = lowH;
    fontMap['i'] = lowI;
    fontMap['j'] = lowJ;
    fontMap['k'] = lowK;
    fontMap['l'] = lowL;
    fontMap['m'] = lowM;
    fontMap['n'] = lowN;
    fontMap['o'] = lowO;
    fontMap['p'] = lowP;
    fontMap['q'] = lowQ;
    fontMap['r'] = lowR;
    fontMap['s'] = lowS;
    fontMap['t'] = lowT;
    fontMap['u'] = lowU;
    fontMap['v'] = lowV;
    fontMap['w'] = lowW;
    fontMap['x'] = lowX;
    fontMap['y'] = lowY;
    fontMap['z'] = lowZ;
    fontMap['-'] = Dash;
    fontMap['.'] = Decimal;
    fontMap['%'] = percent;
    fontMap['|'] = verticalBar;
}

//gets a pointer to the pixel data for a letter
const uint16_t* getLetter(uint8_t letter){
	return fontMap[(uint8_t)letter];
}