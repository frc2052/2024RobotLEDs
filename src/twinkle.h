#ifndef TWINKLE_FUNC_H
#define TWINKLE_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Twinkle {

private:
    CRGB color = CRGB::White;
    int num = 10;

public:
    void init(CRGB sparlkeColor, int density) {
        color = sparlkeColor;
        num = density;
    }

    void update() {
        EVERY_N_MILLISECONDS(100) {
            
            for (int i = 0; i < num; i++) {
               g_leds[random8(NUM_LEDS)] = color;
            }

            fadeToBlackBy(g_leds, NUM_LEDS, 50);
            FastLED.show();
        }
    }

};
#endif