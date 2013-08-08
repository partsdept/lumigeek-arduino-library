// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#include "LumiGeekDefines.h"
#include "LumiGeekRGB.h"

// ---------------------------------------------------------------------------
// Methods for LumiGeekRGB
// ---------------------------------------------------------------------------

void LumiGeekRGB::genericJumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b) {
  if (assertSanityCheck()) {
  	uint8_t params[4];
  	params[0] = header; 
  	params[1] = r;
  	params[2] = g;
  	params[3] = b;
  	write(i2cAddress(),LG_RGB_CMD_JUMP_TO,params,4);
  }
}
		
void LumiGeekRGB::genericFadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[5];
  	params[0] = header; 
  	params[1] = r;
  	params[2] = g;
  	params[3] = b;
  	params[4] = speed;
  	write(i2cAddress(),LG_RGB_CMD_FADE_TO,params,5);
  }
}

void LumiGeekRGB::genericAutoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[8];
  	params[0] = header;
  	params[1] = r1;
  	params[2] = g1;
  	params[3] = b1;
  	params[4] = r2;
  	params[5] = g2;
  	params[6] = b2;
  	params[7] = speed;
  	write(i2cAddress(),LG_RGB_CMD_AUTO_JUMP,params,8);
  }
}

void LumiGeekRGB::genericAutoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[8];
  	params[0] = header;
  	params[1] = r1;
  	params[2] = g1;
  	params[3] = b1;
  	params[4] = r2;
  	params[5] = g2;
  	params[6] = b2;
  	params[7] = speed;
  	write(i2cAddress(),LG_RGB_CMD_AUTO_FADE,params,8);
  }
}

void LumiGeekRGB::genericAutoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[2];
  	params[0] = header; 
  	params[1] = speed;
  	write(i2cAddress(),LG_RGB_CMD_AUTO_RANDOM,params,2);
  }
}
