// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeekRGB_h
#define LumiGeekRGB_h

#include "LumiGeekDefines.h"
#include "LumiGeekShield.h"
#include <inttypes.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// Abstract Class: LumiGeekRGB
// For shields that are generally used to control RGB headers.  
// They share commands such as fade, jump, auto-fade, auto-jump.
// ---------------------------------------------------------------------------

class LumiGeekRGB : public LumiGeekShield {
  protected:
		LumiGeekRGB(uint8_t offset,uint8_t product) : LumiGeekShield(offset,product) {
			_i2cOffset = offset;
		};
		void genericJumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b);
		void genericFadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void genericAutoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void genericAutoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void genericAutoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed);
};

#endif