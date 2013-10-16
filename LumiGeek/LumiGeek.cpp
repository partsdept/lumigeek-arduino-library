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
#include <inttypes.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// LumiGeekHelper
// A class to handle I2C and some other global calls 
// ---------------------------------------------------------------------------

void LumiGeekHelper::beginIsDepricated() {  
    
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
}

LumiGeekHelper LumiGeek = LumiGeekHelper();
