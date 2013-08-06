// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek_h
#define LumiGeek_h

#include <Arduino.h>
#include <inttypes.h>

#include "LumiGeekDefines.h"

// ---------------------------------------------------------------------------
// Abstract Class: LumiGeekShield
// ---------------------------------------------------------------------------

class LumiGeekShield {
	public:
		void blackout();
		void testPattern();
		uint8_t i2cAddress();
  protected:
		LumiGeekShield(uint8_t  i2cOffset, uint8_t productId);
    bool assertOffsetValue(uint8_t i2cOffset);
    bool assertSanityCheck();
    bool assertProductMatchesI2cAddress(uint8_t productId);
    uint8_t _i2cOffset;  // NOTE: tried to use uint8_t but got an ambiguous compiler error.  Weird.
    uint8_t _productId;
    uint8_t _firmwareVersion;    
};

// ---------------------------------------------------------------------------
// Abstract Class: LumiGeekRGB
// For shields that are generally used to control RGB headers.  
// They share commands such as fade, jump, auto-fade, auto-jump.
// ---------------------------------------------------------------------------

class LumiGeekRGB : public LumiGeekShield {
	public:
		LumiGeekRGB(uint8_t offset,uint8_t product) : LumiGeekShield(offset,product) {
			_i2cOffset = offset;
		};
		void genericJumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b);
		void genericFadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void genericAutoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void genericAutoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void genericAutoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed);
};


// ---------------------------------------------------------------------------
// Class: LG4xRGB
// For the 4X shield... 
// ---------------------------------------------------------------------------

class LumiGeek4xRGB : public LumiGeekRGB {
	public:
		LumiGeek4xRGB() : LumiGeekRGB(0,LG_4XRGB) {};
		LumiGeek4xRGB(uint8_t addr) : LumiGeekRGB(addr,LG_4XRGB) {};
    bool assertHeaderValue(uint8_t header);
		void jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b);
		void fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed);
};

// ---------------------------------------------------------------------------
// Class: LG1xRGBMega
// For the 1X shield... 
// ---------------------------------------------------------------------------

class LumiGeek1xRGBMega : public LumiGeekRGB {
	public:
		LumiGeek1xRGBMega() : LumiGeekRGB(0,LG_1XRGBMEGA) {};
		LumiGeek1xRGBMega(uint8_t addr) : LumiGeekRGB(addr,LG_1XRGBMEGA) {};
		void jumpToRGB(uint8_t r, uint8_t g, uint8_t b);
		void fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeToRandomRGBs(uint8_t speed);
};

// ---------------------------------------------------------------------------
// Class: LumiGeek3xCC
// For the 3x Constant Current shield... 
// ---------------------------------------------------------------------------

class LumiGeek3xCC : public LumiGeekRGB {
	public:
		LumiGeek3xCC() : LumiGeekRGB(0,LG_1XRGBMEGA) {};
		LumiGeek3xCC(uint8_t offset) : LumiGeekRGB(offset,LG_1XRGBMEGA) {};
		void jumpToRGB(uint8_t r, uint8_t g, uint8_t b);
		void fadeToRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeBetweenRGBs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeToRandomRGBs(uint8_t speed);
};

// ---------------------------------------------------------------------------
// Class: Addr1XMultiTool
// Used to control various types of Addressable LED products.  See defines file. 
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods
// ---------------------------------------------------------------------------

class LumiGeekAddressable : public LumiGeekShield {
	public:
		LumiGeekAddressable(uint8_t offset,uint8_t product) : LumiGeekShield(offset,product) {};   
		void setMode(uint8_t mode);
		void drawGradient(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t length);
		void drawComet(uint8_t r, uint8_t g, uint8_t b, uint8_t cometLength, uint8_t tailLength, uint8_t speed);
		void drawFrame(uint8_t pixelCount, uint8_t pixelRGBs[]);
		void drawBigFrame(uint16_t pixelCount, uint8_t pixelRGBs[]);
		void shiftBufferOnce(uint8_t direction, uint8_t length);
		void autoShiftBuffer(uint8_t direction, uint8_t length, uint8_t speed);
};

// ---------------------------------------------------------------------------
// Class: Addr1XMultiTool
// Used to control various types of Addressable LED products.  See defines file. 
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods
// ---------------------------------------------------------------------------

class Addressable1XMultiTool : public LumiGeekAddressable {
	Addressable1XMultiTool(uint8_t offset) : LumiGeekAddressable(offset,LG_1XADDR) {};   
	Addressable1XMultiTool() : LumiGeekAddressable(0,LG_1XADDR) {};
	void setMode(uint8_t mode);
	void drawGradient(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t length);
	void drawComet(uint8_t r, uint8_t g, uint8_t b, uint8_t cometLength, uint8_t tailLength, uint8_t speed);
	void drawFrame(uint8_t pixelCount, uint8_t pixelRGBs[]);
	void drawBigFrame(uint16_t pixelCount, uint8_t pixelRGBs[]);
	void shiftBufferOnce(uint8_t direction, uint8_t length);
	void autoShiftBuffer(uint8_t direction, uint8_t length, uint8_t speed);	
};

// ---------------------------------------------------------------------------
// Class: Addr1XMultiTool
// Used to control various types of Addressable LED products.  See defines file. 
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods
// ---------------------------------------------------------------------------

class LumiGeek5x7Headlight : public LumiGeekAddressable {
	LumiGeek5x7Headlight() : LumiGeekAddressable(15,LG_5X7_HEADLIGHT) {};  
	void draw2DFrame(uint8_t pixelRGBs[5][7][3]);
};

// ---------------------------------------------------------------------------
// Class: DMX1XUniverse
// Used to generate and repeatedly transmit a DMX universe framebuffer.
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods.
// ---------------------------------------------------------------------------

class LumiGeek1xDMX : public LumiGeekShield {
	public:
		LumiGeek1xDMX() : LumiGeekShield(0,LG_1XDMX) {};
		LumiGeek1xDMX(uint8_t offset) : LumiGeekShield(offset,LG_1XDMX) {};
		void setDataStartingAtAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b);
		void setEntireUniverse(uint8_t universe[]);  // does not work with the Wire library... only with modified I2C Rev5 library
};



// ---------------------------------------------------------------------------
// Class: LumiGeekHelper
// ---------------------------------------------------------------------------

class LumiGeekHelper  {
	private:
		static bool _debug;
    static bool _initialized;
		
		void sendCommandToEveryAddress(uint8_t);
		
    uint8_t start();
    uint8_t stop();
    void lockUp();

    uint8_t sendAddress(uint8_t);
    uint8_t sendByte(uint8_t);
    uint8_t receiveByte(uint8_t);

    uint8_t returnStatus;
    uint8_t nack;
    uint8_t data[LG_I2C_BUFFER_LENGTH];


    static uint8_t bytesAvailable;
    static uint16_t bufferIndex;
    static uint8_t totalBytes;
    static uint16_t timeOutDelay;
			
	public: 
		LumiGeekHelper() {};

		// how do we track instantitions of the shields? 
		// for now, we don't have to... but that could be interesting later on.
		
		void setDebug(bool b);
		bool debug();
    
		static void setInitialized(bool i);
		static bool initialized();
		
		void begin();
		void begin(uint8_t);
		
		void end();
		void scan();
	    
	  void setTimeOut(uint16_t);
				
		void testPattern();
		void blackout();
		
    uint8_t read(uint8_t, uint8_t, uint8_t);
    uint8_t read(uint8_t, uint8_t, uint8_t*, uint8_t);
    
		uint8_t write(uint8_t, uint8_t);
		uint8_t write(uint8_t, uint8_t, uint8_t*, uint16_t);
	   
    // Explore this way of constructing the shield objects later on after talking to JJ 
    // LumiGeek4xRGB addShield4xRGB(uint8_t dip); 
    // LumiGeek3xCC addShield3xCC(uint8_t dip); 
     
};

extern LumiGeekHelper LumiGeek;

#endif