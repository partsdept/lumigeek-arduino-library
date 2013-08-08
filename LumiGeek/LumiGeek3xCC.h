// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek3xCC_h
#define LumiGeek3xCC_h

#include "LumiGeekDefines.h"
#include "LumiGeekRGB.h"
#include <inttypes.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// Class: LumiGeek3xCC
// For the 3x Constant Current shield... 
// ---------------------------------------------------------------------------

class LumiGeek3xCC : public LumiGeekRGB {
	public:
		LumiGeek3xCC() : LumiGeekRGB(0,LG_3XCC_1W) {};
		LumiGeek3xCC(uint8_t offset) : LumiGeekRGB(offset,LG_3XCC_1W) {};
		void jumpToRGB(uint8_t r, uint8_t g, uint8_t b);
		void fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeToRandomRGBs(uint8_t speed);
};

#endif