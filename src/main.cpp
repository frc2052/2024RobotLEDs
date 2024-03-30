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

#define MODE_OFF 0
#define MODE_DANGER 1
#define MODE_INTAKE 2
#define MODE_HAS_NOTE 3
#define MODE_AIMING 4
#define MODE_AIMING_ON_TARGET 5
#define MODE_SHOOTING 6
#define MODE_SHOOTING_ON_TARGET 7
#define MODE_DONE_SHOOTING 8
#define MODE_NO_AUTO 9
#define MODE_BLUE_AUTO 10
#define MODE_RED_AUTO 11

#define OLED_CLOCK 18
#define OLED_DATA 17 
#define OLED_RESET 21

CRGB g_leds[NUM_LEDS]; //create our LED array object for all our LEDs
int lastCode = -1;
unsigned long lastScreenUpdate = 0;

PinReader reader = PinReader();

//always use a hardware (HW) version of the screen when possible to avoid studdering in light effects
// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C g_OLED(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, OLED_CLOCK, OLED_DATA, OLED_RESET);

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

    g_OLED.clearBuffer();					// clear the internal memory
    g_OLED.setFont(u8g2_font_fub20_tr);	// choose a suitable font
    g_OLED.drawStr(0,30, intStr.c_str());	// write something to the internal memory
    g_OLED.sendBuffer();					// transfer internal memory to the display
  }
}

void initLightPattern(int code){
  FastLED.clear();
  FastLED.show();
  FastLED.setBrightness(BRIGHTNESS);

  switch (code)
  {
    case MODE_DANGER: {
        pulse.init(CRGB::Red, 20);
        break;
    }
    case MODE_INTAKE: {
        pulse.init(CRGB::Blue,  10);
        break;
    }
    case MODE_HAS_NOTE: {
        CRGB color = CRGB(255,50,0); //orange
        beats.init(color,color,color,color);
        break;
    }
    case MODE_AIMING: {
      fill_solid(g_leds, NUM_LEDS, CRGB::Yellow);
      FastLED.show();
      break;
    }
    case MODE_AIMING_ON_TARGET: {
      fill_solid(g_leds, NUM_LEDS, CRGB::Purple);
      FastLED.show();
      break;
    }
    case MODE_SHOOTING: {
      fill_solid(g_leds, NUM_LEDS, CRGB::White);
      FastLED.show();
      break;
    }
    case MODE_SHOOTING_ON_TARGET: {
      fill_solid(g_leds, NUM_LEDS, CRGB::Green);
      FastLED.show();
      break;
    }
    case MODE_DONE_SHOOTING: {
      fill_solid(g_leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
      break;
    }
    case MODE_NO_AUTO: {
        //police
        CRGB c1 = CRGB::Red;
        CRGB c2 = CRGB::Blue;
        beats.init(c1, c2, c1, c2);
        break;
    }
    case MODE_BLUE_AUTO: {
      ice.init();
      break;
    }
    case MODE_RED_AUTO: {
      fire.init();
      break;
    }
    case 20: {
      bounce.init(CRGB::Red, CRGB::Blue, 4, 30, 15);
      break;
    }
    case 21: {
      twinkle.init(CRGB::Yellow, 2);
    }
  }
}

void updateLightPattern(int code){
  switch (code)
  {
    case 0: {
      FastLED.clear();
      FastLED.show();
      break;
    }
    case MODE_DANGER:
    case MODE_INTAKE: {
      pulse.update();    
      break;
    }
    case MODE_HAS_NOTE: {
      beats.update();
      break;
    }
    case MODE_AIMING:
    case MODE_AIMING_ON_TARGET:
    case MODE_SHOOTING:
    case MODE_SHOOTING_ON_TARGET:
    case MODE_DONE_SHOOTING: {
      //solid color - do nothing
      break;
    }
    case MODE_NO_AUTO: {
      beats.update();
      break;
    }
    case MODE_BLUE_AUTO:{
            ice.updateSplit();
      break;
    }
    case MODE_RED_AUTO: {
      fire.updateSplit();
      break;
    }
    case 20: {
      bounce.update();
      break;
    }
    case 21: {
      twinkle.update();
      break;
    }
  }
}

void setup(void) {
  g_OLED.begin();
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