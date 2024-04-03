#ifndef TETRIS_FUNC_H
#define TETRIS_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Tetris {

private:
CRGB color1 = CRGB::Red;
CRGB color2 = CRGB::Blue;
int currentStackSize = 0;
int blockSize = 1;
int pos1 = 0;
int pos2 = 49;
int speed = 10;
bool forward = true;
bool onColor1 = true;
int fSpeed = 80;



public:

    void init(CRGB pulseColor1, CRGB pulseColor2, int pulseWidth, int pulseSpeed, int blockSize) {
        color1 = pulseColor1;
        color2 = pulseColor2;
        pWidth = pulseWidth;
        speed = pulseSpeed; 
        this.blockSize = blockSize;
    }

    void init(CRGB pulseColor1, CRGB pulseColor2, int pulseWidth, int pulseSpeed, int blockSize, int fadeSpeed){
        color1 = pulseColor1;
        color2 = pulseColor2;
        pWidth = pulseWidth;
        speed = pulseSpeed; 
        fSpeed = fadeSpeed;
        this.blockSize = blockSize;
    }

    void update() {
        EVERY_N_MILLISECONDS(speed){
        if ((pos1 == 24-currentStackSize) && (pos2 == 25+currentStackSize)) {
            for (int i = 0; i < currentStackSize - 1; i++) {
                g_leds[24 - i] = color1;
                g_leds[25 + i] = color2;
                currentStackSize++;
                pos1 = 0;
                pos2 = 49;
            }
        } else if (currentStackSize >= 25) {
            currentStackSize = 0
            fadeToBlackBy(g_leds, NUM_LEDS, fSpeed);
        } else {
            pos1++;
            pos2--;
        }
        g_leds[pos1] = color1;
        g_leds[pos2] = color2;

            fadeToBlackBy(g_leds, NUM_LEDS, fSpeed);
            // g_leds[47] = color1;
            // g_leds[48] = color2;
            // g_leds[49] = CRGB::Red;

            FastLED.show();
        }
    }
};
#endif