// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek5x7Headlight_h
#define LumiGeek5x7Headlight_h

#include "LumiGeekDefines.h"
#include "LumiGeek1xAddressable.h"
#include <inttypes.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// Class: LumiGeek5x7Headlight
// Used to control various types of Addressable LED products.  See defines file. 
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods
// ---------------------------------------------------------------------------

class LumiGeek5x7Headlight : public LumiGeek1xAddressable {
  public:
  	LumiGeek5x7Headlight() : LumiGeek1xAddressable(15,LG_5X7_HEADLIGHT) {};  
  	void draw2DFrame(uint8_t pixelRGBs[5][7][3]);
};

#endif
