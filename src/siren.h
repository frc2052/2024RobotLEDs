#ifndef SIREN_FUNC_H
#define SIREN_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Siren {

private:
CRGB color1 = CRGB::Red;
CRGB color2 = CRGB::Gold;
CRGB color3 = CRGB::Crimson;
int fSpeed = 50;
int currentSwapLED = 0;
int halfNum = NUM_LEDS/2;

public:
    void init() {

    }



    void update() {
        EVERY_N_MILLISECONDS(50) {
            FastLED.setBrightness(255);
            currentSwapLED = 100;
            // for (int i = 33; i < NUM_LEDS; i++) {
            //     g_leds[i].red   = 25;
            //     g_leds[i].green = 0;
            //     g_leds[i].blue  = 0;
            // }
            for (int i = 34; i < NUM_LEDS; i++) {
                g_leds[i].red   = 25;
                g_leds[i].green = 0;
                g_leds[i].blue  = 0;
            }
            // fadeToBlackBy(g_leds, NUM_LEDS, fSpeed);


            FastLED.show();
        }
    }
};
#endif