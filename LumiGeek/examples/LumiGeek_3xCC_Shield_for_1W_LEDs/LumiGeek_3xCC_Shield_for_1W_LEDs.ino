#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek3xCC lg3xCC;

uint8_t counter;
boolean countUp = true;

void setup() {
  // instatiate a shield with its dip switches set to 0x0
  lg3xCC = LumiGeek3xCC(0x0);
  // initialize the I2C bus
  lg3xCC.begin();
  // turn on serial debugging
  lg3xCC.setDebug(true);
}

void loop() {
  // do a red fado up / fade down
  lg3xCC.jumpToRGB(counter, 0, 255 - counter);
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
  }
}