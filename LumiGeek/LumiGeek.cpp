// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// LumiGeek.cpp
// Classes to support LumiGeek shields on Arduino
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ---------------------------------------------------------------------------

#include "LumiGeekDefines.h"
#include "LumiGeek.h"

// ---------------------------------------------------------------------------
// Methods for LumiGeekShield
// Calls the superclass constructor with the appropriate I2C address
// ---------------------------------------------------------------------------

LumiGeekShield::LumiGeekShield(uint8_t i2cOffset,uint8_t productId) {
  if (assertOffsetValue(i2cOffset)) {
    _i2cOffset = i2cOffset;    
  } else {
    if (LumiGeek.debug()) {
      Serial.println("Bad dip switch value in shield constructor.  Must be in range 0-15.");
    }
    LumiGeek.setInitialized(false);
  }
  if (assertProductMatchesI2cAddress(productId)) {
    if (LumiGeek.debug()) {
      Serial.print("Shield at dip switch setting 0x");
      Serial.print(_i2cOffset,HEX);
      Serial.print(" is product ID 0x");
      Serial.print(_productId,HEX);
      Serial.print(" with firmware v");
      Serial.println(_firmwareVersion);
    }
  } else {
    LumiGeek.setInitialized(false);
    if (LumiGeek.debug()) {
      Serial.print("ERROR: Shield at dip switch setting 0x");
      Serial.print(_i2cOffset,HEX);
      Serial.print(" does not match product ID 0x");
      Serial.print(_productId,HEX);
      Serial.print(".  Check your dip switches and your constructor call.");
      Serial.println(_firmwareVersion,HEX);
    }
  }
}

bool LumiGeekShield::assertProductMatchesI2cAddress(uint8_t productId) {
  uint8_t queryResult[1];
  queryResult[0] = 0x0;
  LumiGeek.read(i2cAddress(),LG_GLOBAL_CMD_QUERY,queryResult,1);
  
  if (queryResult[0] == productId) {
    _productId = queryResult[0];
    _firmwareVersion = queryResult[1];
    return true;
  } else {
    _productId = 0;
    _firmwareVersion = 0;
    return false;
  }
}

bool LumiGeekShield::assertSanityCheck() {
  // do a very simple sanity check right now
  if (!LumiGeek.initialized()) {
    if (LumiGeek.debug()) {
      Serial.println("ERROR: Failed sanity check. Make sure you called LumiGeek.begin() and set your dip switches properly to match your shield constructors.");
    }
    return false;
  }
  return true;
}

bool LumiGeekShield::assertOffsetValue(uint8_t i2cOffset) {
  if (i2cOffset > 15) {
    if (LumiGeek.debug()) {
      Serial.println("LumiGeek I2C dip switch setting must be from 0 to 15.");
    }
    return false;
  } 
  return true;
}

uint8_t LumiGeekShield::i2cAddress() {
	return LG_BASE_I2C_ADDRESS + _i2cOffset;
}

void LumiGeekShield::blackout() {
	LumiGeek.write(i2cAddress(),LG_GLOBAL_CMD_BLACKOUT);
}

void LumiGeekShield::testPattern() {
	LumiGeek.write(i2cAddress(),LG_GLOBAL_CMD_TEST_PATTERN);
}

// ---------------------------------------------------------------------------
// Methods for LumiGeekRGB
// ---------------------------------------------------------------------------

void LumiGeekRGB::genericJumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b) {
  if (assertSanityCheck()) {
  	uint8_t params[4];
  	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = r;
  	params[2] = g;
  	params[3] = b;
  	LumiGeek.write(i2cAddress(),LG_RGB_CMD_JUMP_TO,params,4);
  }
}
		
void LumiGeekRGB::genericFadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[5];
  	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = r;
  	params[2] = g;
  	params[3] = b;
  	params[4] = speed;
  	LumiGeek.write(i2cAddress(),LG_RGB_CMD_FADE_TO,params,5);
  }
}

void LumiGeekRGB::genericAutoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[8];
  	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = r1;
  	params[2] = g1;
  	params[3] = b1;
  	params[4] = r2;
  	params[5] = g2;
  	params[6] = b2;
  	params[7] = speed;
  	LumiGeek.write(i2cAddress(),LG_RGB_CMD_AUTO_JUMP,params,8);
  }
}

void LumiGeekRGB::genericAutoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[8];
  	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = r1;
  	params[2] = g1;
  	params[3] = b1;
  	params[4] = r2;
  	params[5] = g2;
  	params[6] = b2;
  	params[7] = speed;
  	LumiGeek.write(i2cAddress(),LG_RGB_CMD_AUTO_FADE,params,8);
  }
}

void LumiGeekRGB::genericAutoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed) {
  if (assertSanityCheck()) {
  	uint8_t params[2];
  	params[0] = header; // hardcode the header number... this is only a 1X addressable shield
  	params[1] = speed;
  	LumiGeek.write(i2cAddress(),LG_RGB_CMD_AUTO_RANDOM,params,2);
  }
}

// ---------------------------------------------------------------------------
// Methods for 4xRGB... same RGB macros, but assert header is [1..4]
// ---------------------------------------------------------------------------


bool LumiGeek4xRGB::assertHeaderValue(uint8_t header) {
  if (header == 0) {
    if (LumiGeek.debug()) {
      Serial.println("LumiGeek 4xRGB header numbers start at 1, not zero.");
    }
    return false;
  } else if (header > 4) {
    if (LumiGeek.debug()) {
      Serial.print("LumiGeek 4xRGB header number out of range: ");
      Serial.println(header);
    }
    return false;
  } else {
    return true;
  }
}


void LumiGeek4xRGB::jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b) {
  if (assertHeaderValue(header)) {
  	genericJumpHeaderToRGB(header,r,g,b);
    delay(5);
  }
}
void LumiGeek4xRGB::fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericFadeHeaderToRGB(header,r,g,b,speed);
    delay(5);
  }
}
void LumiGeek4xRGB::autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericAutoJumpHeaderBetweenRGBs(header,r1,g1,b1,r2,g2,b2,speed);
    delay(5);
  }
}
void LumiGeek4xRGB::autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericAutoFadeHeaderBetweenRGBs(header,r1,g1,b1,r2,g2,b2,speed);
    delay(5);
  }
}
void LumiGeek4xRGB::autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed) {
  if (assertHeaderValue(header)) {
  	genericAutoFadeHeaderToRandomRGBs(header,speed);
    delay(5);
  }
}


// ---------------------------------------------------------------------------
// Methods for 1xRGBMega... same RGB macros, but assume header 1
// ---------------------------------------------------------------------------

void LumiGeek1xRGBMega::jumpToRGB(uint8_t r, uint8_t g, uint8_t b) {
	genericJumpHeaderToRGB(1,r,g,b);
  delay(3);
}
void LumiGeek1xRGBMega::fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
	genericFadeHeaderToRGB(1,r,g,b,speed);
  delay(3);
}
void LumiGeek1xRGBMega::autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	genericAutoJumpHeaderBetweenRGBs(1,r1,g1,b1,r2,g2,b2,speed);
  delay(3);
}
void LumiGeek1xRGBMega::autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	genericAutoFadeHeaderBetweenRGBs(1,r1,g1,b1,r2,g2,b2,speed);
  delay(3);
}
void LumiGeek1xRGBMega::autoFadeToRandomRGBs(uint8_t speed) {
	genericAutoFadeHeaderToRandomRGBs(1,speed);
  delay(3);
}

// ---------------------------------------------------------------------------
// Methods for 3xCC... same RGB macros, but assume header 1
// ---------------------------------------------------------------------------

void LumiGeek3xCC::jumpToRGB(uint8_t r, uint8_t g, uint8_t b) {
	genericJumpHeaderToRGB(1,r,g,b);
  delay(3);
}
void LumiGeek3xCC::fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed) {
	genericFadeHeaderToRGB(1,r,g,b,speed);
  delay(3);
}
void LumiGeek3xCC::autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	genericAutoJumpHeaderBetweenRGBs(1,r1,g1,b1,r2,g2,b2,speed);
  delay(3);
}
void LumiGeek3xCC::autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed) {
	genericAutoFadeHeaderBetweenRGBs(1,r1,g1,b1,r2,g2,b2,speed);
  delay(3);
}
void LumiGeek3xCC::autoFadeToRandomRGBs(uint8_t speed) {
	genericAutoFadeHeaderToRandomRGBs(1,speed);
  delay(3);
}

// ---------------------------------------------------------------------------
// Methods for Addr1XMultiTool
// ---------------------------------------------------------------------------

void Addressable1XMultiTool::setMode(uint8_t mode) {
	// ASSERT: more >= 1 && mode <= 3
	// TODO: document that mode = 1 is WS2811, mode = 2 is WS2801, mode = 3 is ???
#if  USE_LUMIGEEK_I2C
	uint8_t params[2];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = mode;
	LumiGeek.write(i2cAddress(),LG_ADDR_CMD_SET_STRIP_MODE,params,2);
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
#if  USE_LUMIGEEK_I2C
	uint8_t params[8];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r1;
	params[2] = g1;
	params[3] = b1;
	params[4] = r1;
	params[5] = g2;
	params[6] = b2;
	params[7] = length;
	LumiGeek.write(i2cAddress(),LG_ADDR_CMD_GRADIENT,params,8);
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
#if  USE_LUMIGEEK_I2C
	uint8_t params[7];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = r;
	params[2] = g;
	params[3] = b;
	params[4] = cometLength;
	params[5] = tailLength;
	params[6] = speed;
	LumiGeek.write(i2cAddress(),LG_ADDR_CMD_COMET_CHASE,params,7);
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
#if  USE_LUMIGEEK_I2C
	uint8_t params[3];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = direction;
	params[2] = length;
	LumiGeek.write(i2cAddress(),LG_ADDR_CMD_SHIFT_BUFFER_ONCE,params,3);
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
#if  USE_LUMIGEEK_I2C
	uint8_t params[4];
	params[0] = 1; // hardcode the header number... this is only a 1X addressable shield
	params[1] = direction;
	params[2] = speed;
	params[3] = length;
	LumiGeek.write(i2cAddress(),LG_ADDR_CMD_AUTOSHIFT_BUFFER,params,4); 
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

#if  USE_LUMIGEEK_I2C
	LumiGeek.write(i2cAddress(),LG_ADDR_CMD_FRAME,--pixelRGBs,pixelCount * 3);  // HACK: I fake the header number param with the '--' on the pointer    
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
#if  USE_LUMIGEEK_I2C
	uint8_t params[4];
	params[0] = address; // Remember that the DMX on the Encabulator does not want a header number
	params[1] = r;
	params[2] = g;
	params[3] = b;
	LumiGeek.write(i2cAddress(),LG_DMX_CMD_SET_BYTES_FROM_ADDR,params,4);
#else	
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
#if  USE_LUMIGEEK_I2C
	// the MAX_BUFFER_LENGTH and some data types need to be modified in the I2C Rev5 library for this to work properly
	// see the frame method in the Addressable 1X class for more info
#else	
	// KNOWN ISSUE:  This is not possible due to the single byte index/buffer limitations in the Wire library.
#endif
    delay(10);
}



// ---------------------------------------------------------------------------
// LumiGeekHelper
// A class to handle I2C and some other global calls 
// ---------------------------------------------------------------------------

// Debugging Helpers

bool LumiGeekHelper::_debug = false;
bool LumiGeekHelper::_initialized = false;

bool LumiGeekHelper::debug() {
	return _debug;
}

void LumiGeekHelper::setDebug(bool b) {
	if (b) {
		_debug = true;
		Serial.begin(9600);
		Serial.println("LumiGeek verbose debugging enabled.");
	} else {
		_debug = false;
		// close serial port?
	}
}

bool LumiGeekHelper::initialized() {
	return _initialized;
}

void LumiGeekHelper::setInitialized(bool i) {
		_initialized = i;
}

// Global macro helpers

void LumiGeekHelper::testPattern() {
	sendCommandToEveryAddress(LG_GLOBAL_CMD_TEST_PATTERN);
}

void LumiGeekHelper::blackout() {
	sendCommandToEveryAddress(LG_GLOBAL_CMD_BLACKOUT);
}

void LumiGeekHelper::sendCommandToEveryAddress(uint8_t _cmd) {
  // someday this could be more intelligent, only sending to known LumiGeek shields instead of 
  // sending to everything from 0x50 to 0x5F
  for(uint8_t s = 0; s <= 0x0F; s++) {
	write(LG_BASE_I2C_ADDRESS + s,_cmd);
  }
}

// I2C helpers

uint8_t LumiGeekHelper::bytesAvailable = 0;
uint16_t LumiGeekHelper::bufferIndex = 0;
uint8_t LumiGeekHelper::totalBytes = 0;
uint16_t LumiGeekHelper::timeOutDelay = 0;

void LumiGeekHelper::begin() {
	begin(0); // do not use fast I2C
}

void LumiGeekHelper::begin(uint8_t _fast) {
  _initialized = true;
  
#ifdef  USE_WIRE_I2C
  Serial.println("Initializing Wire");
  Wire.begin();
#else
	Serial.println("Initializing LumiGeek I2C library");
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
  // activate internal pull-ups for twi
  // as per note from atmega8 manual pg167
  sbi(PORTC, 4);
  sbi(PORTC, 5);
#else
  // activate internal pull-ups for twi
  // as per note from atmega128 manual pg204
  sbi(PORTD, 0);
  sbi(PORTD, 1);
#endif
  // initialize twi prescaler and bit rate
  cbi(TWSR, TWPS0);
  cbi(TWSR, TWPS1);
  TWBR = ((F_CPU / 100000) - 16) / 2;
  // enable twi module and acks
  TWCR = _BV(TWEN) | _BV(TWEA);
#endif
}

void LumiGeekHelper::end() {
  TWCR = 0;
}

void LumiGeekHelper::setTimeOut(uint16_t _timeOut) {
  timeOutDelay = _timeOut;
}

void LumiGeekHelper::lockUp() {
  TWCR = 0; //releases SDA and SCL lines to high impedance
  TWCR = _BV(TWEN) | _BV(TWEA); //reinitialize TWI 
}

void LumiGeekHelper::scan() {
  uint8_t lgDeviceCount = 0;
  uint8_t totalDeviceCount = 0;
  uint16_t tempTime = timeOutDelay;
  setTimeOut(80);
  Serial.println("Scanning for devices...please wait");
  Serial.println();
  for(uint8_t s = 0; s <= 0x7F; s++) {
    returnStatus = 0;
    returnStatus = start();
    if(!returnStatus)
    { 
      returnStatus = sendAddress(SLA_W(s));
    }
    if(returnStatus)
    {
      if(returnStatus == 1)
      {
        Serial.println("There is a problem with the bus, could not complete scan");
        timeOutDelay = tempTime;
        return;
      }
    } else {      
      Serial.print("Found device at address - ");
      Serial.print(" 0x");
      Serial.println(s,HEX);

      // modify this to return info about the LumiGeek shields on the bus
      // call up to the device to see if it is a LumiGeek device???

      totalDeviceCount++;
    }
    stop();
  }
  if(!totalDeviceCount){Serial.println("No devices found");}
  timeOutDelay = tempTime;
}

uint8_t LumiGeekHelper::read(uint8_t address, uint8_t registerAddress, uint8_t *data, uint8_t numberBytes) {
  bytesAvailable = 0;
  bufferIndex = 0;
  if(numberBytes == 0){numberBytes++;}
  nack = numberBytes - 1;
  returnStatus = 0;
  returnStatus = start();
  if(returnStatus){return(returnStatus);}
  returnStatus = sendAddress(SLA_W(address));
  if(returnStatus)
  {
    if(returnStatus == 1){return(2);}
    return(returnStatus);
  }
  returnStatus = sendByte(registerAddress);
  if(returnStatus)
  {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }
  returnStatus = start();
  if(returnStatus)
  {
    if(returnStatus == 1){return(4);}
    return(returnStatus);
  }
  returnStatus = sendAddress(SLA_R(address));
  if(returnStatus)
  {
    if(returnStatus == 1){return(5);}
    return(returnStatus);
  }
  for(uint8_t i = 0; i < numberBytes; i++)
  {
    if( i == nack )
    {
      returnStatus = receiveByte(0);
      if(returnStatus == 1){return(6);}
      if(returnStatus != MR_DATA_NACK){return(returnStatus);}
    }
    else
    {
      returnStatus = receiveByte(1);
      if(returnStatus == 1){return(6);}
      if(returnStatus != MR_DATA_ACK){return(returnStatus);}
    }
    data[i] = TWDR;
    bytesAvailable = i+1;
    totalBytes = i+1;
  }
  returnStatus = stop();
  if(returnStatus)
  {
    if(returnStatus == 1){return(7);}
    return(returnStatus);
  }
  return(returnStatus);
}

uint8_t LumiGeekHelper::write(uint8_t address, uint8_t command) {
  if (LumiGeek.debug()) {
    Serial.print("I2C writing to address 0x");	
    Serial.print(address,HEX);	
    Serial.print(" with command 0x");
    Serial.println(command,HEX);
  }	
  returnStatus = 0;
  returnStatus = start();
  if(returnStatus){return(returnStatus);}
  returnStatus = sendAddress(SLA_W(address));
  if(returnStatus) {
    if(returnStatus == 1){return(2);}
    return(returnStatus);
  }
  returnStatus = sendByte(command);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }
  returnStatus = stop();
  if(returnStatus) {
    if(returnStatus == 1){return(7);}
    return(returnStatus);
  }
  return(returnStatus);
}


uint8_t LumiGeekHelper::write(uint8_t address, uint8_t command, uint8_t *data, uint16_t numberBytes) {
  if (LumiGeek.debug()) {
    Serial.print("I2C writing to address 0x");	
    Serial.print(address,HEX);	
    Serial.print(" with command 0x");
    Serial.print(command,HEX);
    Serial.print(" and ");
    Serial.print(numberBytes);
    Serial.println(" bytes of data.");    
  }	
  
  returnStatus = 0;
  returnStatus = start();
  if(returnStatus){return(returnStatus);}
  returnStatus = sendAddress(SLA_W(address));
  if(returnStatus) {
    if(returnStatus == 1){return(2);}
    return(returnStatus);
  }
  returnStatus = sendByte(command);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }
  for (uint16_t i = 0; i < numberBytes; i++) {
    returnStatus = sendByte(data[i]);
    if(returnStatus) {
        if(returnStatus == 1){return(3);}
        return(returnStatus);
      }
  }
  returnStatus = stop();
  if(returnStatus) {
    if(returnStatus == 1){return(7);}
    return(returnStatus);
  }
  return(returnStatus);
}

uint8_t LumiGeekHelper::start() {
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay) {
      lockUp();
      return(1);
    }    
  }
  if ((TWI_STATUS == START) || (TWI_STATUS == REPEATED_START)) {
    return(0);
  }
  if (TWI_STATUS == LOST_ARBTRTN) {
    uint8_t bufferedStatus = TWI_STATUS;
    lockUp();
    return(bufferedStatus);
  }
  return(TWI_STATUS);
}

uint8_t LumiGeekHelper::sendAddress(uint8_t i2cAddress) {
  TWDR = i2cAddress;
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay)
    {
      lockUp();
      return(1);
    }     
  }
  if ((TWI_STATUS == MT_SLA_ACK) || (TWI_STATUS == MR_SLA_ACK)) {
    return(0);
  }
  uint8_t bufferedStatus = TWI_STATUS;
  if ((TWI_STATUS == MT_SLA_NACK) || (TWI_STATUS == MR_SLA_NACK)) {
    stop();
    return(bufferedStatus);
  } else {
    lockUp();
    return(bufferedStatus);
  } 
}

uint8_t LumiGeekHelper::sendByte(uint8_t i2cData) {
  TWDR = i2cData;
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay) {
      lockUp();
      return(1);
    }   
  }
  if (TWI_STATUS == MT_DATA_ACK) {
    return(0);
  }
  uint8_t bufferedStatus = TWI_STATUS;
  if (TWI_STATUS == MT_DATA_NACK) {
    stop();
    return(bufferedStatus);
  } else {
    lockUp();
    return(bufferedStatus);
  } 
}

uint8_t LumiGeekHelper::receiveByte(uint8_t ack) {
  unsigned long startingTime = millis();
  if(ack) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
  } else {
    TWCR = (1<<TWINT) | (1<<TWEN);
  }
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay)
    {
      lockUp();
      return(1);
    }
  }
  if (TWI_STATUS == LOST_ARBTRTN) {
    uint8_t bufferedStatus = TWI_STATUS;
    lockUp();
    return(bufferedStatus);
  }
  return(TWI_STATUS); 
}

uint8_t LumiGeekHelper::stop() {
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
  while ((TWCR & (1<<TWSTO))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay) {
      lockUp();
      return(1);
    }    
  }
  return(0);
}

// Explore this way of constructing the shield objects later on after talking to JJ 
// LumiGeek4xRGB LumiGeekHelper::addShield4xRGB(uint8_t dip) {
  // return LumiGeek4xRGB(dip);
// }

LumiGeekHelper LumiGeek = LumiGeekHelper();
