#ifndef PINREADER_H
#define PINREADER_H
#include <Arduino.h>
#include "constants.h"
class PinReader
{
private:
    int pins[8];

    void setupPinPullup(int pin){
        if (pin > 0){
            pinMode(pin, INPUT_PULLUP);
        }
    }

    //this will return 0 or 1
    //1 indicates the switch was closed (on)
    //0 indicates the switch was open (off)
    int checkPinIsClosed(int pin){
        if (pin <= 0) { //pin is not used - roborio may not have room for 8 pins
            return 0;
        } else if (IS_ON_ROBOT && digitalRead(pin) == HIGH) { // need to read high on robot
            return 1;
        } else if (!IS_ON_ROBOT && digitalRead(pin) == LOW) { // need to read low for testing
            return 1;
        } else {
            return 0;
        }
    }

public:
    void init(int pinArray[8]){
        pins[0] = pinArray[0];
        pins[1] = pinArray[1];
        pins[2] = pinArray[2];
        pins[3] = pinArray[3];
        pins[4] = pinArray[4];
        pins[5] = pinArray[5];
        pins[6] = pinArray[6];
        pins[7] = pinArray[7];

        for (int i = 0; i< 8; i++){
            setupPinPullup(pins[i]);
        }
    }


    int read(){
        int read0 = checkPinIsClosed(pins[0]);
        int read1 = checkPinIsClosed(pins[1]);
        int read2 = checkPinIsClosed(pins[2]);
        int read3 = checkPinIsClosed(pins[3]);
        int read4 = checkPinIsClosed(pins[4]);
        int read5 = checkPinIsClosed(pins[5]);
        int read6 = checkPinIsClosed(pins[6]);
        int read7 = checkPinIsClosed(pins[7]);

        //treat the pins as a binary number
        //00001011 in binary is 0 + 0 + 8 + 0 + 2 + 1 = 11
        int val = (128 * read7) + (64 * read6) + (32 * read5) + (16 * read4) + (8 * read3) + (4 * read2) + (2 * read1) + (1 * read0);
        //the return value will be between 0 - 255
        return val;
    }
};
#endif