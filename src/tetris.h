#ifndef TETRIS_FUNC_H
#define TETRIS_FUNC_H

#include <FastLED.h>
#include "constants.h"
#include <iostream>


extern CRGB g_leds[];

class Tetris {
private: 
int bSize1 = 4;
int bSize2 = 6;
// int bsize3 = 9;
// int bsize4 = 11;
// int bsize5 = 4; 
/*int bsize6 = 5; 
int bsize7 = 5;
int bsize8 = 6; */
int bSpeed = 40;
int bPos1 = 0;
bool forward = true;
bool forward2 = false;
int fspeed = 150;
CRGB color1 = CRGB::Blue;
CRGB color2 = CRGB::Red;
int resetSpeed = 6;
int bPos2 = 0;



public:

 void init(CRGB clr1,CRGB clr2, int blockSize1, int speed) {
        bSize1 = blockSize1;
        bSpeed = speed;
        color1 = clr1;
        color2 = clr2;
 }

 void update() {
    EVERY_N_MILLISECONDS(bSpeed){



        if(forward){ //block 1 moving forward
        bPos1 = bPos1 + 1;
            if(bPos1 >= NUM_LEDS - bSize1){
                forward2 = true;
                forward = false;
            } else {
            bPos1 = bPos1;
            }
        }


       if(forward2){ //block 2 moving forward
        bPos2 = bPos2 + 1;
            if(bPos2 >= ((NUM_LEDS - bSize1) - bSize2)){
                forward2 = false;
            } else {
                bPos2 = bPos2;
            }
       }


        if(bPos1 < NUM_LEDS - bSize1){ //turns back on block 1 after reset
                forward = true;
        }

        if(!forward){ //activates block 2 in LEDs
                for(int i2 = 0; i2 <= bSize2 -1; i2++)
                g_leds[bPos2 + i2] = color2;
        }

        for(int i = 0; i <= bSize1 - 1; i++) // activates block 1 immediately
            g_leds[bPos1 + i ] = color1;


         fadeToBlackBy(g_leds, NUM_LEDS, fspeed);

        FastLED.show();
  }
  EVERY_N_SECONDS(resetSpeed){
    bPos1 = 0;
    bPos2 = 0;
  }
 }
};
#endif