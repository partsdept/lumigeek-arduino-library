// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek1xAddressable_h
#define LumiGeek1xAddressable_h

#include "LumiGeekShield.h"

#include <inttypes.h>

// ---------------------------------------------------------------------------
// Class: Addr1XMultiTool
// Used to control various types of Addressable LED products.  See defines file. 
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods
// ---------------------------------------------------------------------------

class LumiGeek1xAddressable : public LumiGeekShield {
  public:
  	LumiGeek1xAddressable(uint8_t offset,uint8_t product) : LumiGeekShield(offset,product) {};   
  	LumiGeek1xAddressable(uint8_t offset) : LumiGeekShield(offset,LG_1XADDR) {};   
  	LumiGeek1xAddressable() : LumiGeekShield(0,LG_1XADDR) {};
		void setMode(uint8_t mode);
  	void drawGradient(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t length);
  	void drawFrame(uint8_t pixelCount, uint8_t pixelRGBs[]);
  	void shiftBufferOnce(uint8_t direction, uint8_t length);
  	void autoShiftBuffer(uint8_t direction, uint8_t length, uint8_t speed);	
  	void autoComet(uint8_t r, uint8_t g, uint8_t b, uint8_t cometLength, uint8_t tailLength, uint8_t speed);
};

#endif