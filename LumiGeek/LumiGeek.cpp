// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Encabulator.cpp
// Classes to support Turbull Encabulator hardware on Arduino
//
// Think of the TurBull Encabulator as several shields on the same I2C bus on
// a single circuit board.   
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ---------------------------------------------------------------------------

#include "LumiGeekDefines.h"
#include "LumiGeek.h"

// ---------------------------------------------------------------------------
// Methods for LumiGeekShield
// Calls the superclass constructor with the appropriate I2C address
// ---------------------------------------------------------------------------

LumiGeekShield::LumiGeekShield(uint8_t i2cOffset) {
	_i2cOffset = i2cOffset;
}

int LumiGeekShield::i2cAddress() {
	return 0x50 + _i2cOffset;
}

void LumiGeekShield::blackout() {
#ifdef  USE_LUMIGEEK_I2C
	// LumiGeekI2C.write(_i2cOffset,LG_GLOBAL_CMD_BLACKOUT);
#else
	Wire.beginTransmission(i2cAddress());	Wire.write(LG_GLOBAL_CMD_BLACKOUT);
	Wire.endTransmission();
#endif
	delay(6);
}

void LumiGeekShield::testPattern() {
#ifdef  USE_LUMIGEEK_I2C
	// LumiGeekI2C.write(_i2cOffset,LG_GLOBAL_CMD_TEST_PATTERN);
#else
	Wire.beginTransmission(i2cAddress());	Wire.write(LG_GLOBAL_CMD_TEST_PATTERN);
	Wire.endTransmission();
#endif
	delay(6);
}

// ---------------------------------------------------------------------------
// Methods for LumiGeekRGB
// ---------------------------------------------------------------------------

void LumiGeekRGB::jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b) {
	// ASSERT: header >= 1 && header <= 4
 
	Serial.print(" here too! ");
	Serial.println(i2cAddress());
	Serial.println(LG_RGB_CMD_JUMP_TO);
	Serial.println(r);
	Serial.println(g);
	Serial.println(b);

#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[4];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r;
	params[2] = g;
	params[3] = b;
	// LumiGeekI2C.write(_i2cOffset,LG_RGB_CMD_JUMP_TO,params,5);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_RGB_CMD_JUMP_TO);
	Wire.write(header);
	Wire.write(r);
	Wire.write(g);
	Wire.write(b);
	Wire.endTransmission();
#endif
    delay(6);
}
		
void LumiGeekRGB::fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[5];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r;
	params[2] = g;
	params[3] = b;
	params[4] = speed;
	// LumiGeekI2C.write(_i2cOffset,LG_RGB_CMD_FADE_TO,params,5);
#else	
    Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_RGB_CMD_FADE_TO);
	Wire.write(header);
	Wire.write(r);
	Wire.write(g);
	Wire.write(b);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);	
}

void LumiGeekRGB::autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[8];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r1;
	params[2] = g1;
	params[3] = b1;
	params[4] = r2;
	params[5] = g2;
	params[6] = b2;
	params[7] = speed;
	// LumiGeekI2C.write(_i2cOffset,LG_RGB_CMD_AUTO_JUMP,params,8);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_RGB_CMD_AUTO_JUMP);
	Wire.write(header);
	Wire.write(r1);
	Wire.write(g1);
	Wire.write(b1);
	Wire.write(r2);
	Wire.write(g2);
	Wire.write(b2);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);
}

void LumiGeekRGB::autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[8];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r1;
	params[2] = g1;
	params[3] = b1;
	params[4] = r2;
	params[5] = g2;
	params[6] = b2;
	params[7] = speed;
	// LumiGeekI2C.write(_i2cOffset,LG_RGB_CMD_AUTO_FADE,params,8);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_RGB_CMD_AUTO_FADE);
	Wire.write(header);
	Wire.write(r1);
	Wire.write(g1);
	Wire.write(b1);
	Wire.write(r2);
	Wire.write(g2);
	Wire.write(b2);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);
}

void LumiGeekRGB::autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed) {
	// ASSERT: header >= 1 && header <= 4
	// ASSERT: speed is within some range?
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[2];
	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
	params[1] = speed;
	// LumiGeekI2C.write(_i2cOffset,LG_RGB_CMD_AUTO_RANDOM,params,2);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_RGB_CMD_AUTO_RANDOM);
	Wire.write(header);
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(6);
}

void LumiGeek1xRGBMega::jumpToRGB(uint8_t r, uint8_t g, uint8_t b) {
	jumpHeaderToRGB(0,r,g,b);
}
void LumiGeek1xRGBMega::fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
	fadeHeaderToRGB(0,r,g,b,speed);
}
void LumiGeek1xRGBMega::autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	autoJumpHeaderBetweenRGBs(0,r1,g1,b1,r2,g2,b2,speed);
}
void LumiGeek1xRGBMega::autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	autoFadeHeaderBetweenRGBs(0,r1,g1,b1,r2,g2,b2,speed);
}
void LumiGeek1xRGBMega::autoFadeToRandomRGBs(uint8_t speed) {
	autoFadeHeaderToRandomRGBs(0,speed);
}



// ---------------------------------------------------------------------------
// Methods for Addr1XMultiTool
// ---------------------------------------------------------------------------

void Addressable1XMultiTool::setMode(uint8_t mode) {
	// ASSERT: more >= 1 && mode <= 3
	// TODO: document that mode = 1 is WS2811, mode = 2 is WS2801, mode = 3 is ???
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[2];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = mode;
	// LumiGeekI2C.write(_i2cOffset,LG_ADDR_CMD_SET_STRIP_MODE,params,2);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_ADDR_CMD_SET_STRIP_MODE);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(mode);	
	Wire.endTransmission();
#endif
    delay(5);
}

void Addressable1XMultiTool::drawGradient(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t length) {
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[8];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r1;
	params[2] = g1;
	params[3] = b1;
	params[4] = r1;
	params[5] = g2;
	params[6] = b2;
	params[7] = length;
	// LumiGeekI2C.write(_i2cOffset,LG_ADDR_CMD_GRADIENT,params,8);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_ADDR_CMD_GRADIENT);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(r1);	
	Wire.write(g1);	
	Wire.write(b1);	
	Wire.write(r2);	
	Wire.write(g2);	
	Wire.write(b2);	
	Wire.write(length);	
	Wire.endTransmission();
#endif
    delay(5);
}

void Addressable1XMultiTool::drawComet(uint8_t r, uint8_t g, uint8_t b, uint8_t cometLength, uint8_t tailLength, uint8_t speed) {
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[7];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r;
	params[2] = g;
	params[3] = b;
	params[4] = cometLength;
	params[5] = tailLength;
	params[6] = speed;
	// LumiGeekI2C.write(_i2cOffset,LG_ADDR_CMD_COMET_CHASE,params,7);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_ADDR_CMD_COMET_CHASE);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(r);	
	Wire.write(g);	
	Wire.write(b);	
	Wire.write(cometLength);	
	Wire.write(tailLength);	
	Wire.write(speed);	
	Wire.endTransmission();
#endif
    delay(5);
}

void Addressable1XMultiTool::shiftBufferOnce(uint8_t direction, uint8_t length) {
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[3];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = direction;
	params[2] = length;
	// LumiGeekI2C.write(_i2cOffset,LG_ADDR_CMD_SHIFT_BUFFER_ONCE,params,3);
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_ADDR_CMD_SHIFT_BUFFER_ONCE);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(direction);	
	Wire.write(length);
	Wire.endTransmission();
#endif
    delay(5);
}

void Addressable1XMultiTool::autoShiftBuffer(uint8_t direction, uint8_t speed, uint8_t length) {	
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[4];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = direction;
	params[2] = speed;
	params[3] = length;
	// LumiGeekI2C.write(_i2cOffset,LG_ADDR_CMD_AUTOSHIFT_BUFFER,params,4); 
#else	
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_ADDR_CMD_AUTOSHIFT_BUFFER);
	Wire.write(1);  // hardcode the header number... this is only a 1X addressable shield
	Wire.write(direction);	
	Wire.write(speed);	     // JOEJOE: Remember to swap the length and speed in the headlight and 1X as well.
	Wire.write(length);		
	Wire.endTransmission();
#endif
    delay(5);
}



void Addressable1XMultiTool::drawFrame(uint8_t pixelCount, uint8_t pixelRGBs[]) {

    // KNOWN ISSUE: There is an out-of-the-box 32-byte limit on the buffer in the I2C Rev5 library. 
	// This can easily be overridden up to a maximum 256 bytes (85 pixels) by editing the MAX_BUFFER_SIZE.
	// Note that this cannot be set above the 256 byte limit without some heavier lifting to accomodate a
	// length larger than uint8_t will allow for.
	
	// SOLUTION:  Modify the I2C library
	// You need to change the data types in a few places to uint16_t in the I2C Rev5 library.
	// In particular, you need to change the bufferIndex, numberBytes, and the for loop iterator
	// in the write() method that takes an array. This is a much easier workaround than modifying Wire.
	// You can then set the MAX_BUFFER_SIZE higher than 256 but watch your SRAM limits (2k on Uno).

#ifdef  USE_LUMIGEEK_I2C
	// LumiGeekI2C.write(_i2cOffset,LG_ADDR_CMD_FRAME,--pixelRGBs,pixelCount * 3);  // HACK: I fake the header number param with the '--' on the pointer    
#else
    Wire.beginTransmission(i2cAddress());    
	Wire.write(LG_ADDR_CMD_FRAME);
    Wire.write(1); // hardcode the header number... this is only a 1X addressable shield
    for (int i = 0 ; i < pixelCount  ; i++) {  // TODO: Verify the BRG vs. RGB with JJ
	    Wire.write(pixelRGBs[i * 3 + 0]);  // write blue
	    Wire.write(pixelRGBs[i * 3 + 1]);  // write red
	    Wire.write(pixelRGBs[i * 3 + 2]);  // write green
    } 
    Wire.endTransmission();
#endif
    delay(5);
}




void LumiGeek5x7Headlight::draw2DFrame(uint8_t pixelRGBs[5][7][3]) {
   // draw 2D frame   maybe even 
}

// ---------------------------------------------------------------------------
// Methods for LumiGeek1xDMX
// ---------------------------------------------------------------------------

void LumiGeek1xDMX::setDataStartingAtAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b) {
	// TO-DO: assert that address >= 1 && address <= 509 		
#ifdef  USE_LUMIGEEK_I2C
	uint8_t params[4];
	params[0] = address; // Remember that the DMX on the Encabulator does not want a header number
	params[1] = r;
	params[2] = g;
	params[3] = b;
	// LumiGeekI2C.write(_i2cOffset,LG_DMX_CMD_SET_BYTES_FROM_ADDR,params,4);
#else	
	Serial.print(address);
	Serial.print("-");
	Serial.print(r);
	Serial.print("-");
	Serial.print(g);
	Serial.print("-");
	Serial.println(b);
	Wire.beginTransmission(i2cAddress());	
	Wire.write(LG_DMX_CMD_SET_BYTES_FROM_ADDR);
	// Wire.write(1);  // The DMX on the Encabulator does not want a header number
	Wire.write(address);	
	Wire.write(r);	
	Wire.write(g);	
	Wire.write(b);	
	Wire.endTransmission();
#endif
    delay(15);
}

void LumiGeek1xDMX::setEntireUniverse(uint8_t universe[]) {
#ifdef  USE_LUMIGEEK_I2C
	// the MAX_BUFFER_LENGTH and some data types need to be modified in the I2C Rev5 library for this to work properly
	// see the frame method in the Addressable 1X class for more info
#else	
	// KNOWN ISSUE:  This is not possible due to the single byte index/buffer limitations in the Wire library.
#endif
    delay(10);
}



// ---------------------------------------------------------------------------
// LumiGeekHelper
// ---------------------------------------------------------------------------

void LumiGeekHelper::testPattern() {
	// call for each shield on the stack... call all 16 I2C addresses? 
}

void LumiGeekHelper::blackout() {
	// call for each shield on the stack... call all 16 I2C addresses? 
}

void LumiGeekHelper::begin() {

#ifdef  USE_LUMIGEEK_I2C
	I2c.begin();	
	I2c.setSpeed(1);
#else
 	Wire.begin();
#endif

}

bool LumiGeekHelper::_verbose = false;

void LumiGeekHelper::setVerbose(bool b) {
	if (b) {
		_verbose = true;
		Serial.begin(9600);
		Serial.println("TurBull Encabulator has been initialized.  All your bulls are belong to us.");
	} else {
		_verbose = false;
		// close serial port?
	}
}


