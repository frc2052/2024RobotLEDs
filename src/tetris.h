#ifndef TETRIS_FUNC_H
#define TETRIS_FUNC_H

#include <FastLED.h>
#include "constants.h"
#include "pulse.h"


extern CRGB g_leds[];

class Tetris {
    Pulse pulse = Pulse();
private: 
int bSize1 = 10;
int bSize2 = 8;
int bSize3 = 12;
int bSize4 = 9;
int bSize5 = 11; 
/*int bsize6 = 5; 
int bsize7 = 5;
int bsize8 = 6; */
int bSpeed = 40;
int bPos1 = 0;
int bPos2 = 0;
int bPos3 = 0;
int bPos4 = 0;
int bPos5 = 0;
bool forward1 = true;
bool forward2 = false;
bool forward3 = false;
bool forward4 = false;
bool startBlock3 = false;
bool startBlock4 = false;
bool startBlock5 = false;
int fspeed = 150;
CRGB color1 = CRGB::Blue;
CRGB color2 = CRGB::Red;
CRGB color3 = CRGB::Yellow;
CRGB color4 = CRGB::Green;
CRGB color5 = CRGB::Purple;
int resetSpeed = 6;
bool reset = false;
int waitSpeed = 4.5;
bool startPulse = false;




public:

 void init(CRGB clr1,CRGB clr2, int blockSize1, int speed) {
        bSize1 = blockSize1;
        bSpeed = speed;
        color1 = clr1;
        color2 = clr2;
 }
 /*void makeBlockGo(bool forward, int bPos, int bSize, bool forward2, bool startNextBlock) {

    if(forward1){ //block 1 moving forward
        bPos1 = bPos1 + 1;
            if(bPos1 >= NUM_LEDS - bSize1){
                forward2 = true;
                forward1 = false;
            } else {
            bPos1 = bPos1;
            }
        }
 }*/
 void update() {
    EVERY_N_MILLISECONDS(bSpeed){
        if(forward1){ //block 1 moving forward
        bPos1 = bPos1 + 1;
            if(bPos1 >= NUM_LEDS - bSize1){
                forward2 = true;
                forward1 = false;
            } else {
            bPos1 = bPos1;
            }
        }

       if(forward2){ //block 2 moving forward
        bPos2 = bPos2 + 1;
            if(bPos2 >= ((NUM_LEDS - bSize1) - bSize2)){
                forward3 = true;
                startBlock3 = true;
                forward2 = false;
            } else {
                bPos2 = bPos2;
            }
       }

        if(forward3){ //block 3 moving forward
        bPos3 = bPos3 + 1;
            if(bPos3 >= (((NUM_LEDS - bSize1) - bSize2) - bSize3)){
                forward3 = false;
                forward4 = true;
                startBlock4 = true;
            } else {
                bPos3 = bPos3;
            }
       }
       if(forward4){ //block 4 moving forward
        bPos4 = bPos4 + 1;
            if(bPos4 >= ((((NUM_LEDS - bSize1) - bSize2) - bSize3) - bSize4)){
                forward4 = false;
                startBlock5 = true;
            } else {
                bPos4 = bPos4;
            }
       }

        if(bPos1 < NUM_LEDS - bSize1){ //turns back on block 1 after reset
                forward1 = true;
        }

        if(!forward1){ //activates block 2 in LEDs
                for(int i2 = 0; i2 <= bSize2 -1; i2++)
                g_leds[bPos2 + i2] = color2;
        }

        if(startBlock3){ //activates block 3 in LEDs
                for(int i3 = 0; i3 <= bSize3 -1; i3++)
                g_leds[bPos3 + i3] = color3;
        }
        if(startBlock4){ // activates block 4 in LEDs
                 for(int i4 = 0; i4 <= bSize4 -1; i4++)
                g_leds[bPos4 + i4] = color4;

        }
        if(startBlock5){ // activates block 5 in LEDs
                 for(int i5 = 0; i5 <= bSize5 -1; i5++)
                g_leds[bPos5 + i5] = color5;

        }

        for(int i = 0; i <= bSize1 - 1; i++) // activates block 1 immediately
            g_leds[bPos1 + i ] = color1;

        fadeToBlackBy(g_leds, NUM_LEDS, fspeed);
        FastLED.show();
        }
        if(startBlock5){
            EVERY_N_SECONDS(waitSpeed){
                startPulse = true;}
            if(startPulse){
                EVERY_N_MILLISECONDS(1000){
                pulse.init(CRGB::Black, 10);
                pulse.update();
                }}
            EVERY_N_SECONDS(resetSpeed){
                reset = true;
                startPulse = false;
            }
        }
  
  if(reset){
    bPos1 = 0;
    bPos2 = 0;
    bPos3 = 0;
    bPos4 = 0;
    forward2 = false;
    startBlock3 = false;
    startBlock4 = false;
    startBlock5 = false;
    reset = false;
    waitSpeed = 4.5;
    resetSpeed = 6;
    startPulse = false;
  }
}
};
#endif