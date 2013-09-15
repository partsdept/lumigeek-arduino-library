#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek3xCC lg3xCC;

uint8_t counter;
boolean countUp = true;
uint8_t channel = 0;

void setup() {
  // initialize the I2C bus
  LumiGeek.begin();
  // turn on serial debugging
  lg3xCC.setDebug(true);
  // instatiate a shield with its dip switches set to 0x0
  lg3xCC = LumiGeek3xCC(0x0);
}

void loop() {
  // do a full breath of color fade on each channel 
  if (channel == 0) {  
    lg3xCC.jumpToRGB(counter, 0, 0);
  } else if (channel == 1) {
    lg3xCC.jumpToRGB(0,counter, 0);
  } else {
    lg3xCC.jumpToRGB(0, counter, 0);
  }
  // palendrome the counter  
  if (countUp) {
   counter++;     
  } else {
   counter--; 
  }
  // check our limits
  if (counter == 255) {
   countUp = false; 
  } else if (counter == 0) {
    countUp = true;
    // switch the channel after a full palendrome cycle
    channel++;
  }
  // roll over the channel variable
  if (channel == 3) {
    channel = 0; 
  }
}

