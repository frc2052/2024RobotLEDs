#ifndef PULSE_FUNC_H
#define PULSE_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Pulse {

private:

    int step = -2;
    CHSV pulseColor = CHSV(0, 0, 255); //initialize to white

public:
    void init(CRGB color, int stepAmount) {
        pulseColor = rgb2hsv_approximate(color);
        if (stepAmount > 0) {
            step = -stepAmount;
        }        
    }

    void update()
    {    
        EVERY_N_MILLISECONDS(10) {
            if (pulseColor.value + step > 255 || pulseColor.value + step < 10)
            {
                step = -step; //reverse direction
            }
            
            pulseColor.value = pulseColor.value + step; //change the brightness of the LED
            fill_solid(g_leds, NUM_LEDS, pulseColor);
            FastLED.show();
        }
    }
};
#endif