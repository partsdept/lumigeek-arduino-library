// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#ifndef LumiGeek24xMono_h
#define LumiGeek24xMono_h

#include "LumiGeekDefines.h"
#include "LumiGeekShield.h"
#include <inttypes.h>
#include <Arduino.h>

class LumiGeek24xMono : public LumiGeekShield {
	public:
		LumiGeek24xMono() : LumiGeekShield(0,LG_24XMONO) {};
		LumiGeek24xMono(uint8_t addr) : LumiGeekShield(addr,LG_24XMONO) {};
    bool assertHeaderValue(uint8_t header);
		void jumpHeaderToBrightness(uint8_t header, uint8_t value);
		void fadeHeaderToBrightness(uint8_t header, uint8_t value, uint8_t speed);
		void autoJumpHeaderBetweenBrightnesses(uint8_t header, uint8_t value1, uint8_t value2, uint8_t speed);
		void autoFadeHeaderBetweenBrightnesses(uint8_t header, uint8_t value1, uint8_t value2, uint8_t speed);
		void autoFadeHeaderToRandomBrightnesses(uint8_t header, uint8_t speed);
    void drawFrame(uint8_t brightnessValues[]);
};

#endif
