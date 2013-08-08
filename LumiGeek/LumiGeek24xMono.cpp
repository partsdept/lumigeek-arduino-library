// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#include "LumiGeek24xMono.h"

// ---------------------------------------------------------------------------
// Methods for LumiGeek24xMono
// ---------------------------------------------------------------------------

bool LumiGeek24xMono::assertHeaderValue(uint8_t header) {
  if (header == 0) {
    if (debug()) {
      Serial.println("LumiGeek 24xMono header numbers start at 1, not zero.");
    }
    return false;
  }
  if (header > 24) {
    if (debug()) {
      Serial.print("LumiGeek 24xMono header number out of range: ");
      Serial.println(header);
    }
    return false;
  }
  return true;
}

void LumiGeek24xMono::jumpHeaderToBrightness(uint8_t header, uint8_t value){
  if (assertSanityCheck()) {
    if (assertHeaderValue(header)) {
    	uint8_t params[2];
    	params[0] = header; 
    	params[1] = value;
    	write(i2cAddress(),LG_MONO_CMD_JUMP_TO,params,2);
    }
  }
  delay(5);  
}

void LumiGeek24xMono::fadeHeaderToBrightness(uint8_t header, uint8_t value, uint8_t speed){
  if (assertSanityCheck()) {
    if (assertHeaderValue(header)) {
    	uint8_t params[3];
    	params[0] = header; 
    	params[1] = value;
    	params[2] = speed;
    	write(i2cAddress(),LG_MONO_CMD_FADE_TO,params,3);
    }
  }
  delay(5);  
}

void LumiGeek24xMono::autoJumpHeaderBetweenBrightnesses(uint8_t header, uint8_t value1, uint8_t value2, uint8_t speed){
  if (assertSanityCheck()) {
    if (assertHeaderValue(header)) {
    	uint8_t params[4];
    	params[0] = header; 
    	params[1] = value1;
    	params[2] = value2;
    	params[3] = speed;
    	write(i2cAddress(),LG_MONO_CMD_AUTO_JUMP,params,4);
    }
  }
  delay(5);  
}

void LumiGeek24xMono::autoFadeHeaderBetweenBrightnesses(uint8_t header, uint8_t value1, uint8_t value2, uint8_t speed){
  if (assertSanityCheck()) {
    if (assertHeaderValue(header)) {
    	uint8_t params[4];
    	params[0] = header; 
    	params[1] = value1;
    	params[2] = value2;
    	params[3] = speed;
    	write(i2cAddress(),LG_MONO_CMD_AUTO_FADE,params,4);
    }
  }
  delay(5);  
}

void LumiGeek24xMono::autoFadeHeaderToRandomBrightnesses(uint8_t header, uint8_t speed){
  if (assertSanityCheck()) {
    if (assertHeaderValue(header)) {
    	uint8_t params[2];
    	params[0] = header; 
    	params[1] = speed;
    	write(i2cAddress(),LG_MONO_CMD_AUTO_RANDOM,params,2);
    }
  }
  delay(5);
}

void LumiGeek24xMono::drawFrame(uint8_t brightnessValues[]) {
  // TODO
  if (assertSanityCheck()) {
    write(i2cAddress(),*brightnessValues,brightnessValues+1,23);
  }
  delay(5);
}
