// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek4xRGB_h
#define LumiGeek4xRGB_h

#include "LumiGeekDefines.h"
#include "LumiGeekRGB.h"
#include <inttypes.h>
#include <Arduino.h>

class LumiGeek4xRGB : public LumiGeekRGB {
	public:
		LumiGeek4xRGB() : LumiGeekRGB(0,LG_4XRGB) {};
		LumiGeek4xRGB(uint8_t addr) : LumiGeekRGB(addr,LG_4XRGB) {};
    bool assertHeaderValue(uint8_t header);
		void jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b);
		void fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed);
};

#endif
