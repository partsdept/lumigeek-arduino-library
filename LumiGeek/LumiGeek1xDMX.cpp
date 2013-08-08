// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#include "LumiGeek1xDMX.h"

// ---------------------------------------------------------------------------
// Methods for LumiGeek1xDMX
// ---------------------------------------------------------------------------

void LumiGeek1xDMX::setAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b) {
  if (assertSanityCheck()) {
  	// TODO: assert that address >= 1 && address <= 509 		
  	uint8_t params[4];
  	params[0] = address; // Remember that the DMX on the Encabulator does not want a header number
  	params[1] = r;
  	params[2] = g;
  	params[3] = b;
  	write(i2cAddress(),LG_DMX_CMD_SET_BYTES_FROM_ADDR,params,4);
  }
  delay(15);
}

void LumiGeek1xDMX::setAddressWithRGBW(uint8_t address, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  if (assertSanityCheck()) {
  	// TODO: assert that address >= 1 && address <= 508 		
  	uint8_t params[5];
  	params[0] = address; // Remember that the DMX on the Encabulator does not want a header number
  	params[1] = r;
  	params[2] = g;
  	params[3] = b;
  	params[4] = w;
  	write(i2cAddress(),LG_DMX_CMD_SET_BYTES_FROM_ADDR,params,5);
  }
  delay(15);
}

void LumiGeek1xDMX::setAddressWithBytes(uint8_t address, uint8_t bytes[], uint16_t length) {
  if (assertSanityCheck()) {
  	// TODO: assert that address + length <= 512 		
    write(i2cAddress(),LG_DMX_CMD_SET_BYTES_FROM_ADDR,address,bytes,length);
  }
  delay(15);
}

void LumiGeek1xDMX::setEntireUniverse(uint8_t universe[]) {
  // TODO: chunk in a whole universe
  if (assertSanityCheck()) {
  	write(i2cAddress(),LG_DMX_CMD_SET_ENTIRE_UNIVERSE,universe,512);
  }
  delay(25);
}
