// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#include "LumiGeekDefines.h"
#include "LumiGeek3xCC.h"

#include <Arduino.h>


// ---------------------------------------------------------------------------
// Methods for 3xCC... same RGB macros, but assume header 1
// ---------------------------------------------------------------------------

void LumiGeek3xCC::jumpToRGB(uint8_t r, uint8_t g, uint8_t b) {
	genericJumpHeaderToRGB(1,r,g,b);
  delay(3);
}
void LumiGeek3xCC::fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
	genericFadeHeaderToRGB(1,r,g,b,speed);
  delay(3);
}

/*

// NEXT FIRMWARE REV

void LumiGeek3xCC::autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	genericAutoJumpHeaderBetweenRGBs(1,r1,g1,b1,r2,g2,b2,speed);
  delay(3);
}
void LumiGeek3xCC::autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	genericAutoFadeHeaderBetweenRGBs(1,r1,g1,b1,r2,g2,b2,speed);
  delay(3);
}
void LumiGeek3xCC::autoFadeToRandomRGBs(uint8_t speed) {
	genericAutoFadeHeaderToRandomRGBs(1,speed);
  delay(3);
}

*/
