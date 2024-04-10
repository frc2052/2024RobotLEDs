#ifndef TETRIS_FUNC_H
#define TETRIS_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Tetris {

private:
CRGB color1 = CRGB::Red;
CRGB color2 = CRGB::Blue;
CRGB color = CRGB::Red;
int currentStackSize = -1;
int bSize = 1;
int pos1 = 0;
int pos2 = 49;
int speed = 10;
bool forward = true;
bool onColor1 = true;
int fSpeed = 80;
int pWidth = 1;
int pauseCount = 0;
bool isFading;



public:

    void init(CRGB pulseColor1, CRGB pulseColor2, int pulseWidth, int pulseSpeed, int blkSize) {
        color1 = pulseColor1;
        color2 = pulseColor2;
        pWidth = pulseWidth;
        speed = pulseSpeed; 
        bSize = blkSize;
    }

    void init(CRGB pulseColor1, CRGB pulseColor2, int pulseWidth, int pulseSpeed, int blkSize, int fadeSpeed){
        color1 = pulseColor1;
        color2 = pulseColor2;
        pWidth = pulseWidth;
        speed = pulseSpeed; 
        fSpeed = fadeSpeed;
        bSize = blkSize;
    }

    void update() {
        EVERY_N_MILLISECONDS(speed){
        fadeToBlackBy(g_leds, NUM_LEDS, fSpeed);
        if (currentStackSize < 25 && currentStackSize > 0) {
            for (int i = 0; i <= currentStackSize; i++) {
                g_leds[24 - i] = color1;
                g_leds[25 + i] = color2;
            }
        }
        if ((pos1 == 24-currentStackSize) && (pos2 == 25+currentStackSize)) {
            for (int i = 0; i <= currentStackSize; i++) {
                g_leds[24 - i] = color1;
                g_leds[25 + i] = color2;
                pos1 = 0;
                pos2 = 49;
            }
            currentStackSize++;
        } else if (currentStackSize >= 25 || isFading) {
            isFading = true;
            fadeToBlackBy(g_leds, NUM_LEDS, fSpeed);
            pauseCount ++;
            if (pauseCount == 10) {
                isFading = false;
                pauseCount = 0;
                currentStackSize = 0;
            }
        } else {
            pos1++;
            pos2--;
        }
        g_leds[pos1] = color1;
        g_leds[pos2] = color2;

            // fadeToBlackBy(g_leds, NUM_LEDS, fSpeed);
            // g_leds[47] = color1;
            // g_leds[48] = color2;
            // g_leds[49] = CRGB::Red;

            FastLED.show();
        }
    }
};
#endif