// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek1xDMX_h
#define LumiGeek1xDMX_h

#include "LumiGeekDefines.h"
#include "LumiGeekShield.h"
#include <inttypes.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// Class: LumiGeek1xDMX
// Used to generate and repeatedly transmit a DMX universe framebuffer.
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods.
// ---------------------------------------------------------------------------

class LumiGeek1xDMX : public LumiGeekShield {
	public:
		LumiGeek1xDMX() : LumiGeekShield(0,LG_1XDMX) {};
		LumiGeek1xDMX(uint8_t offset) : LumiGeekShield(offset,LG_1XDMX) {};
		void setAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b);
		void setAddressWithRGBW(uint8_t address, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    void setAddressWithBytes(uint8_t address, uint8_t bytes[], uint16_t length);
		void setEntireUniverse(uint8_t universe[]);  // does not work with the Wire library... only with modified I2C Rev5 library
};

#endif