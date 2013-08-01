// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek_h
#define LumiGeek_h

#include <Wire.h>

#include <Arduino.h>
#include <inttypes.h>
#include "LumiGeekDefines.h"

// ---------------------------------------------------------------------------
// Abstract Class: LumiGeekShield
// ---------------------------------------------------------------------------

class LumiGeekShield
{
	public:
		LumiGeekShield(uint8_t  i2cOffset);
		void blackout();
		void testPattern();
		int i2cAddress();
    protected:
        int _i2cOffset;  // NOTE: tried to use uint8_t but got an ambiguous compiler error.  Weird.
};


// ---------------------------------------------------------------------------
// Abstract Class: LumiGeekRGB
// For shields that are generally used to control RGB headers.  
// They share commands such as fade, jump, auto-fade, auto-jump.
// ---------------------------------------------------------------------------

class LumiGeekRGB : public LumiGeekShield
{
	public:
		LumiGeekRGB(uint8_t addr) : LumiGeekShield(addr) {
			_i2cOffset = addr;
		};
		void jumpHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b);
		void fadeHeaderToRGB(uint8_t header, uint8_t r, uint8_t g, uint8_t b, uint8_t speed);
		void autoJumpHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderBetweenRGBs(uint8_t header, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t speed);
		void autoFadeHeaderToRandomRGBs(uint8_t header, uint8_t speed);
};


// ---------------------------------------------------------------------------
// Class: LG4xRGB
// For the 4X shield... 
// ---------------------------------------------------------------------------

class LumiGeek4xRGB : public LumiGeekRGB
{
	public:
		LumiGeek4xRGB() : LumiGeekRGB(0) {};
		LumiGeek4xRGB(uint8_t addr) : LumiGeekRGB(addr) {};
};

// ---------------------------------------------------------------------------
// Class: LG1xRGBMega
// For the 4X shield... 
// ---------------------------------------------------------------------------

class LumiGeek1xRGBMega : public LumiGeekRGB
{
	public:
		LumiGeek1xRGBMega() : LumiGeekRGB(0) {};
		LumiGeek1xRGBMega(uint8_t addr) : LumiGeekRGB(addr) {};
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

class LumiGeekAddressable : public LumiGeekShield
{
	public:
		LumiGeekAddressable(uint8_t addr) : LumiGeekShield(addr) {};   
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

class Addressable1XMultiTool : public LumiGeekAddressable
{
	Addressable1XMultiTool(uint8_t addr) : LumiGeekAddressable(addr) {};   
	Addressable1XMultiTool() : LumiGeekAddressable(0) {};
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

class LumiGeek5x7Headlight : public LumiGeekAddressable
{
	LumiGeek5x7Headlight(uint8_t addr) : LumiGeekAddressable(addr) {};   
	LumiGeek5x7Headlight() : LumiGeekAddressable(0) {};  
	void draw2DFrame(uint8_t pixelRGBs[5][7][3]);
};

// ---------------------------------------------------------------------------
// Class: DMX1XUniverse
// Used to generate and repeatedly transmit a DMX universe framebuffer.
// The I2C address is hardcoded into the abstract superclass constructor call.
// Since this is a 1X board, the header parameter is ommitted from these helper methods.
// ---------------------------------------------------------------------------

class LumiGeek1xDMX : public LumiGeekShield
{
	public:
		LumiGeek1xDMX() : LumiGeekShield(0) {};
		LumiGeek1xDMX(uint8_t addr) : LumiGeekShield(addr) {};
		void setDataStartingAtAddressWithRGB(uint8_t address, uint8_t r, uint8_t g, uint8_t b);
		void setEntireUniverse(uint8_t universe[]);  // does not work with the Wire library... only with modified I2C Rev5 library
};

// ---------------------------------------------------------------------------
// Class: LumiGeekHelper
// TO-DO: Revisit this...  do we want to instantiate helpers for the shields? 
// ---------------------------------------------------------------------------

class LumiGeekHelper 
{
	private:
		static bool _verbose;
	public: 
		LumiGeekHelper() {};

		// how do we track instantitions of the shields? 
		
		void begin();
		void setVerbose(bool b);
		
		void testPattern();
		void blackout();
};


extern LumiGeekHelper LumiGeek;

#endif