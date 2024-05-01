#ifndef PULSE_FUNC_H
#define PULSE_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Flash {

private:

    int speedMillis = 25;
    int cycle = 0;
    int numFlashes = 0;
    int maxFlashes = 3;
    CHSV pulseColor = CHSV(0, 0, 255); //initialize to white

public:
    void init(CRGB color, int speedMillis, int maxFlashes) {
        pulseColor = rgb2hsv_approximate(color);
        if (stepAmount > 0) {
            step = -stepAmount;
        }        
    }

    void update()
    {    
        EVERY_N_MILLISECONDS(speedMillis) {
            if(numFlashes < maxFlashes)
            {
                if (cycle == 0)
                {
                    fill_solid(g_leds, NUM_LEDS, pulseColor);
                    cycle = 1;
                    numFlashes = numFlashes + 1;
                }
                if (cycle == 1)
                {
                    fill_solid(g_leds, NUM_LEDS, CHSV(0,0,0));
                    cycle = 1;               
                }
            }

            FastLED.show();
        }
    }
};
#endif