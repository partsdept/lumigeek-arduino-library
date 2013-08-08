// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#include "LumiGeekDefines.h"
#include "LumiGeek4xRGB.h"

#include <Arduino.h>


// ---------------------------------------------------------------------------
// Methods for 4xRGB... same RGB macros, but assert header is [1..4]
// ---------------------------------------------------------------------------

bool LumiGeek4xRGB::assertHeaderValue(uint8_t header) {
  if (header == 0) {
    if (debug()) {
      Serial.println("LumiGeek 4xRGB header numbers start at 1, not zero.");
    }
    return false;
  } else if (header > 4) {
    if (debug()) {
      Serial.print("LumiGeek 4xRGB header number out of range: ");
      Serial.println(header);
    }
    return false;
  } else {
    return true;
  }
}


void LumiGeek4xRGB::jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b) {
  if (assertHeaderValue(header)) {
    genericJumpHeaderToRGB(header,r,g,b);
    delay(5);
  }
}
void LumiGeek4xRGB::fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericFadeHeaderToRGB(header,r,g,b,speed);
    delay(5);
  }
}
void LumiGeek4xRGB::autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericAutoJumpHeaderBetweenRGBs(header,r1,g1,b1,r2,g2,b2,speed);
    delay(5);
  }
}
void LumiGeek4xRGB::autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericAutoFadeHeaderBetweenRGBs(header,r1,g1,b1,r2,g2,b2,speed);
    delay(5);
  }
}
void LumiGeek4xRGB::autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericAutoFadeHeaderToRandomRGBs(header,speed);
    delay(5);
  }
}
