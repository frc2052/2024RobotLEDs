#ifndef BOUNCE_FUNC_H
#define BOUNCE_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Bounce {

private:
CRGB color1 = CRGB::Red;
CRGB color2 = CRGB::Blue;
int cPos = 0;
int pWidth = 4;
int speed = 10;
bool forward = true;
bool onColor1 = true;
int fSpeed = 80;



public:

    void init(CRGB pulseColor1, CRGB pulseColor2, int pulseWidth, int pulseSpeed) {
        color1 = pulseColor1;
        color2 = pulseColor2;
        pWidth = pulseWidth;
        speed = pulseSpeed; 
    }

    void init(CRGB pulseColor1, CRGB pulseColor2, int pulseWidth, int pulseSpeed, int fadeSpeed){
        color1 = pulseColor1;
        color2 = pulseColor2;
        pWidth = pulseWidth;
        speed = pulseSpeed; 
        fSpeed = fadeSpeed;
    }

    void update() {
        EVERY_N_MILLISECONDS(speed){
            if(forward){
                cPos = cPos + 1;
                if(NUM_LEDS - pWidth <= cPos){
                    forward = false;
                }
            } else {
                cPos = cPos - 1;
                if(cPos <= 0){
                    forward = true;
                    onColor1 = !onColor1;
                }
            }

            for(int i = 0; i < pWidth - 1; i++){
                if(onColor1){
                    g_leds[cPos + i] = color1;
                } else {
                    g_leds[cPos + i] = color2;
                }
            }

            fadeToBlackBy(g_leds, NUM_LEDS, fSpeed);
            // g_leds[47] = color1;
            // g_leds[48] = color2;
            // g_leds[49] = CRGB::Red;

            FastLED.show();
        }
    }
};
#endif