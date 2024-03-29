#ifndef PINREADER_H
#define PINREADER_H
#include <Arduino.h>
class PinReader
{
private:
    #define PIN0 13
    #define PIN1 12
    #define PIN2 14
    #define PIN3 27
    #define PIN4 26
    #define PIN5 25
    #define PIN6 33
    #define PIN7 32

    bool isInitComplete = false;

    //this will return 0 or 1
    //1 indicates the switch was closed (on)
    //0 indicates the switch was open (off)
    int checkPinIsClosed(int pin){
        if (digitalRead(pin) == LOW) {
            return 1;
        } else {
            return 0;
        }
    }
public:
    void init(){
        pinMode(PIN0, INPUT_PULLUP);
        pinMode(PIN1, INPUT_PULLUP);
        pinMode(PIN2, INPUT_PULLUP);
        pinMode(PIN3, INPUT_PULLUP);
        pinMode(PIN4, INPUT_PULLUP);
        pinMode(PIN5, INPUT_PULLUP);
        pinMode(PIN6, INPUT_PULLUP);
        pinMode(PIN7, INPUT_PULLUP);
        isInitComplete = true;
    }
    int read(){
        if (!isInitComplete)
        {
            init();
        }

        int read0 = checkPinIsClosed(PIN0);
        int read1 = checkPinIsClosed(PIN1);
        int read2 = checkPinIsClosed(PIN2);
        int read3 = checkPinIsClosed(PIN3);
        int read4 = checkPinIsClosed(PIN4);
        int read5 = checkPinIsClosed(PIN5);
        int read6 = checkPinIsClosed(PIN6);
        int read7 = checkPinIsClosed(PIN7);
        //treat the pins as a binary number
        //00001011 in binary is 0 + 0 + 8 + 0 + 2 + 1 = 11
        //int val = (32 * read5) + (16 * read4) + (8 * read3) + (4 * read2) + (2 * read1) + (1 * read0);
        int val = (128 * read7) + (64 * read6) + (32 * read5) + (16 * read4) + (8 * read3) + (4 * read2) + (2 * read1) + (1 * read0);
        //the return value will be between 0 - 255
        return val;
    }
};
#endif