// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek1xRGBMega_h
#define LumiGeek1xRGBMega_h

#include "LumiGeekDefines.h"
#include "LumiGeekRGB.h"
#include <inttypes.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// Class: LG1xRGBMega
// For the 1X shield... 
// ---------------------------------------------------------------------------

class LumiGeek1xRGBMega : public LumiGeekRGB {
	public:
		LumiGeek1xRGBMega() : LumiGeekRGB(0,LG_1XRGBMEGA) {};
		LumiGeek1xRGBMega(uint8_t addr) : LumiGeekRGB(addr,LG_1XRGBMEGA) {};
		void jumpToRGB(uint8_t r, uint8_t g, uint8_t b);
		void fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeToRandomRGBs(uint8_t speed);
};

#endif
