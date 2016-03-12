/*Flash Frames
Mary Floren ECE 387 Midterm Project
Edited RGBShades Code to use an audio sensor to direct the LEDs
Original Code:
   RGB Shades Demo Code
   Copyright (c) 2015 macetech LLC
   This software is provided under the MIT License (see license.txt)
Code included in this project is from the RGB Shades Demo Code, macetech.com, and Mary Floren 
Note: all time values are in milliseconds
*/

// data output to LEDs is on pin 5
#define PIN_LEDOUT 5

// Global maximum brightness value, maximum 255 (original max: 72, start: 102)
//keeping it rather low because the glasses tend to be really bright
#define MAXBRIGHTNESS 36
#define STARTBRIGHTNESS 51

// time between pattern changes
#define patternTime 15000

// time between hue increments)
#define hueTime 30

// Time after changing settings before settings are saved to EEPROM
#define EEPROMDELAY 2000

// Include FastLED library, audio.h, and other files
#include <FastLED.h>
#include <EEPROM.h>
#include "messages.h"
#include "font.h"
#include "XYmap.h"
#include "utils.h"
#include "audio.h"
#include "effects.h"
#include "buttons.h"


// when Flash Frames are turned on
void setup() {
Serial.begin(9600);
  // write FastLED configuration data
  FastLED.addLeds<WS2811, PIN_LEDOUT, GRB>(leds, LAST_VISIBLE_LED + 1);
  
  // set global brightness value
  FastLED.setBrightness( scale8(STARTBRIGHTNESS, MAXBRIGHTNESS) );

  // configure input buttons
  pinMode(MODEBUTTON, INPUT_PULLUP);
  pinMode(BRIGHTNESSBUTTON, INPUT_PULLUP);
  pinMode(STROBEPIN, OUTPUT);
  pinMode(RESETPIN, OUTPUT);

  digitalWrite(RESETPIN, LOW);
  digitalWrite(STROBEPIN, HIGH);

  random16_add_entropy(analogRead(ANALOGPIN));

}

// list of functions that will be displayed
functionList effectList[] = {scrollTextThree, 
                              drawAnalyzer, 
                              drawVU,
                              RGBpulse};

/* functionList effectLista[] = {threeSine,
                             threeDee,
                             scrollTextZero,
                             plasma,
                             confetti,
                             rider,
                             scrollTextOne,
                             glitter,
                             slantBars,
                             scrollTextTwo,
                             colorFill,
                             sideRain };
functionList effectListb[] = {threeSine,
                             threeDee,
                             scrollTextZero,
                             plasma};
*/

const byte totalEffects = (sizeof(effectList)/sizeof(effectList[0]));

// continuous loop while Flash Frames are on
void loop()
{
  currentMillis = millis(); // save the current timer value
  updateButtons();          // read, debounce, and process the buttons
  doButtons();              // perform actions based on button state
  checkEEPROM();            // update the EEPROM if necessary

  //if audio input played long enough, get next analog input
  if (AUDIODELAY < currentMillis - audioTime) {
    audioTime = currentMillis;  
    doAnalogs();
  }
  
  // switch to a new effect every patternTime milliseconds
  if (currentMillis - cycleMillis > patternTime && autoCycle == true) {
    cycleMillis = currentMillis; 
    if (++currentEffect >= totalEffects) currentEffect = 0; // loop to start of effect list
    effectInit = false; // trigger effect initialization when new effect is selected
  }
  
  // increment the global hue value every hueTime milliseconds
  if (currentMillis - hueMillis > hueTime) {
    hueMillis = currentMillis;
    hueCycle(1); // increment the global hue value
  }
  
  // run the currently selected effect every effectDelay milliseconds
  if (currentMillis - effectMillis > effectDelay) {
    effectMillis = currentMillis;
    effectList[currentEffect](); // run the selected effect function
    random16_add_entropy(1); // make the random values a bit more random-ish
  }
  
  // run a fade effect too if the confetti effect is running
  if (effectList[currentEffect] == confetti) fadeAll(1);
      
  FastLED.show(); // send the contents of the led memory to the LEDs

}





