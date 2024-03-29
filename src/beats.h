  #ifndef BEATS_FUNC_H
#define BEATS_FUNC_H

#include <FastLED.h>
#include "constants.h"

extern CRGB g_leds[];

class Beats {

private:
CRGB c1 = CRGB::White;
CRGB c2 = CRGB::White; 
CRGB c3 = CRGB::White;
CRGB c4 = CRGB::White;
public:

    void init(CRGB color1, CRGB color2, CRGB color3, CRGB color4) {
        c1 = color1;
        c2 = color2;
        c3 = color3;
        c4 = color4;
    }

    void update() {
        EVERY_N_MILLISECONDS(1){
            uint8_t sinBeat   = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
            uint8_t sinBeat2  = beatsin8(30, 0, NUM_LEDS - 1, 0, 60);
            uint8_t sinBeat3  = beatsin8(30, 0, NUM_LEDS - 1, 0, 120);
            uint8_t sinBeat4  = beatsin8(30, 0, NUM_LEDS - 1, 0, 180);

            // If you notice that your pattern is missing out certain LEDs, you
            // will need to use the higher resolution beatsin16 instead. In this
            // case remove the 3 lines above and replace them with the following:
            // uint16_t sinBeat   = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
            // uint16_t sinBeat2  = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
            // uint16_t sinBeat3  = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

            g_leds[sinBeat]   = c1;
            g_leds[sinBeat2]  = c2;
            g_leds[sinBeat3]  = c3;
            g_leds[sinBeat4]  = c4;

            fadeToBlackBy(g_leds, NUM_LEDS, 5);

            FastLED.show();
        }
    }
};
#endif