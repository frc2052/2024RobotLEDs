#include <Arduino.h>
#include <FastLED.h>
#include <U8g2lib.h>
#include "pinReader.h"
#include "constants.h"
#include "pulse.h"
#include "fire.h"
#include "ice.h"
#include "beats.h"
#include "bounce.h"
#include "twinkle.h"

CRGB g_leds[NUM_LEDS]; //create our LED array object for all our LEDs
int lastCode = -1;
unsigned long lastScreenUpdate = 0;

PinReader reader = PinReader();
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
Pulse pulse = Pulse();
Fire fire = Fire();
Ice ice = Ice();
Beats beats = Beats();
Bounce bounce = Bounce();
Twinkle twinkle = Twinkle();

void updateCodeOnScreen(int code){
  if (lastCode != code || (millis() - lastScreenUpdate) > 5000) //update if code changed or it has been X seconds since last update
  {
    lastScreenUpdate = millis();
    std::string intStr = "Code " + std::to_string(code);

    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_fub20_tr);	// choose a suitable font
    u8g2.drawStr(0,30, intStr.c_str());	// write something to the internal memory
    u8g2.sendBuffer();					// transfer internal memory to the display
  }
}

void initLightPattern(int code){
  FastLED.clear();
  FastLED.show();
  FastLED.setBrightness(BRIGHTNESS);

  switch (code)
  {
    case 0: {
      fill_solid(g_leds, NUM_LEDS, CRGB::White);
      FastLED.show();
      break;
    }
    case 1: {
        pulse.init(CRGB::Green, 2);
        break;
    }
    case 2: {
        pulse.init(CRGB::Red,  10);
        break;
    }
    case 3: {
        fire.init();
        break;
    }
    case 4: {
        ice.init();
        break;
    }
    case 5: {
        CRGB color = CRGB(255,50,0); //orange
        beats.init(color,color,color,color);
        break;
    }
    case 6: {
        CRGB c1 = CRGB::Red;
        CRGB c2 = CRGB::Blue;
        beats.init(c1, c2, c1, c2);
        break;
    }
    case 7: {
      // CRGB color1 = CRGB();
     bounce.init(CRGB::Purple, CRGB::Blue, 3, 10);
      break;
    }
    case 8: {
      bounce.init(CRGB::Red, CRGB::Blue, 4, 30, 15);
      break;
    }
    case 9: {
      twinkle.init(CRGB::Yellow, 2);
    }
  }
}

void updateLightPattern(int code){
  switch (code)
  {
    case 0: {

      break;
    }
    case 1:
    case 2: {
      pulse.update();    
      break;
    }
    case 3: {
      fire.updateSplit();
      break;
    }
    case 4: {
      ice.updateSplit();
      break;
    }
    case 5:
    case 6: {
      beats.update();
      break;
    }
    case 7: 
    case 8: {
      bounce.update();
      break;
    }
    case 9: {
      twinkle.update();
      break;
    }
  }
}

void setup(void) {
  u8g2.begin();
  reader.init();
  
  FastLED.addLeds<CHIP_SET, DATA_PIN, COLOR_ORDER>(g_leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop(void) {
  int code = reader.read();
  updateCodeOnScreen(code);

  if (lastCode != code)
  {
    initLightPattern(code);    
  }
  updateLightPattern(code);
  lastCode = code;
}


// void DoSomething() {    
//     EVERY_N_MILLISECONDS(10) {


//     }
//}