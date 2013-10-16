// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeekShield_h
#define LumiGeekShield_h

#include "LumiGeekDefines.h"
#include <inttypes.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// Abstract Class: LumiGeekShield
// ---------------------------------------------------------------------------

class LumiGeekShield { 
  protected:
	  LumiGeekShield(uint8_t  i2cOffset, uint8_t productId);

  	uint8_t i2cAddress();    

    uint8_t read(uint8_t, uint8_t);
    uint8_t read(uint8_t, uint8_t, uint8_t*, uint8_t);  
  
  	uint8_t write(uint8_t, uint8_t);
  	uint8_t write(uint8_t, uint8_t, uint8_t*, uint16_t);
  	uint8_t write(uint8_t, uint8_t, uint8_t, uint8_t*, uint16_t);  // special case for passing in a header byte separate from a big RGB byte array
  	uint8_t write(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*, uint16_t);  // special case for 16bit DMX address and RGB byte array
      
      
    uint8_t _i2cOffset;  // NOTE: tried to use uint8_t but got an ambiguous compiler error.  Weird.
    uint8_t _actualProductId;
    uint8_t _expectedProductId;      
     
    bool _initialized;
    bool _sane;
       
      
  	bool debug();

    bool assertProductMatchesI2cAddress();
    bool assertOffsetValue(uint8_t i2cOffset);

  	static bool _debug;
  	static bool _verbose;
    static bool _calledBegin;

  	static bool calledBegin();

  	bool verbose();

    static uint8_t bytesAvailable;
    static uint16_t bufferIndex;
    static uint8_t totalBytes;
    static uint16_t timeOutDelay;
		
    uint8_t start();
    uint8_t stop();

    uint8_t sendAddress(uint8_t);
    uint8_t sendByte(uint8_t);
    uint8_t receiveByte(uint8_t);

    uint8_t returnStatus;
    uint8_t nack;

   // uint8_t data[LG_I2C_BUFFER_LENGTH];  
	
  	void end();
    void setTimeOut(uint16_t);
    void lockUp();
    

  public:    
  	void begin();
  	void begin(uint8_t);
  	void setDebug(bool b);
  	void setVerbose(bool b);
  	void scan();
    bool assertSanityCheck();
  	void blackout();
  	void testPattern();
};

#endif