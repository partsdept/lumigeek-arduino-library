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

void LumiGeek1xDMX::setDataStartingAtAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b) {
	// TO-DO: assert that address >= 1 && address <= 509 		
	uint8_t params[4];
	params[0] = address; // Remember that the DMX on the Encabulator does not want a header number
	params[1] = r;
	params[2] = g;
	params[3] = b;
	write(i2cAddress(),LG_DMX_CMD_SET_BYTES_FROM_ADDR,params,4);
  delay(15);
}

void LumiGeek1xDMX::setEntireUniverse(uint8_t universe[]) {
  // TODO: chunk in a whole universe
	write(i2cAddress(),LG_DMX_CMD_SET_ENTIRE_UNIVERSE,universe,512);
  delay(25);
}
