// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#include "LumiGeekDefines.h"
#include "LumiGeek1xAddressable.h"

#include <Arduino.h>


// ---------------------------------------------------------------------------
// Methods for LumiGeek1xAddressable
// ---------------------------------------------------------------------------

void LumiGeek1xAddressable::setMode(uint8_t mode) {
	// ASSERT: more >= 1 && mode <= 3
	// TODO: document that mode = 1 is WS2811, mode = 2 is WS2801, mode = 3 is ???
  if (assertSanityCheck()) {
  	uint8_t params[2];
  	params[0] = 1; // placehold the header number... it is needed per the macro, but all headers go to the same mode
  	params[1] = mode;
  	write(i2cAddress(),LG_ADDR_CMD_SET_STRIP_MODE,params,2);
  }
}

void LumiGeek1xAddressable::drawGradient(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t length) {
  if (assertSanityCheck()) {
  	uint8_t params[8];
  	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = r1;
  	params[2] = g1;
  	params[3] = b1;
  	params[4] = r2;
  	params[5] = g2;
  	params[6] = b2;
  	params[7] = length;
  	write(i2cAddress(),LG_ADDR_CMD_GRADIENT,params,8);
  }
  delay(5);
}

void LumiGeek1xAddressable::shiftBufferOnce(uint8_t direction, uint8_t length) {
  if (assertSanityCheck()) {
  	uint8_t params[3];
  	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = direction;
  	params[2] = length;
  	write(i2cAddress(),LG_ADDR_CMD_SHIFT_BUFFER_ONCE,params,3);
  }
}

void LumiGeek1xAddressable::autoShiftBuffer(uint8_t direction, uint8_t speed, uint8_t length) {	
  if (assertSanityCheck()) {
  	uint8_t params[4];
  	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = direction;
  	params[2] = speed;
  	params[3] = length;
  	write(i2cAddress(),LG_ADDR_CMD_AUTOSHIFT_BUFFER,params,4); 
  }
}

void LumiGeek1xAddressable::autoComet(uint8_t r, uint8_t g, uint8_t b, uint8_t cometLength, uint8_t tailLength, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[7];
  	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = r;
  	params[2] = g;
  	params[3] = b;
  	params[4] = cometLength;
  	params[5] = tailLength;
  	params[6] = speed;
  	write(i2cAddress(),LG_ADDR_CMD_COMET_CHASE,params,7);
  }
}

void LumiGeek1xAddressable::drawFrame(uint8_t pixelCount, uint8_t pixelRGBs[]) {
  if (assertSanityCheck()) {
    write(i2cAddress(),LG_ADDR_CMD_FRAME,1,pixelRGBs,pixelCount * 3);   // hardcode the header number... this is only a 1X addressable shield
  }
  delay(15);
}
