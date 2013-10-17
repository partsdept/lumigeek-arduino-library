#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek1xDMX lg1xDMX;
byte loopCounter = 0;

void setup() {
  // initialize the I2C bus
  lg1xDMX.begin();
  // turn on serial debugging
  lg1xDMX.setDebug(true);
  // instatiate a shield with its dip switches set to 0x0
  lg1xDMX = LumiGeek1xDMX(0x0);
  // set all values to black
  for (int i = 0 ; i < 256 / 3 ; i++) {
    lg1xDMX.setAddressWithRGB(i*3 + 1,0,0,0);
  }
}

void loop() {
  // fill the DMX universe with a red to blue gradient that shifts with the loopCounter
  for (int i = 0 ; i < 256 / 3 ; i++) {
    lg1xDMX.setAddressWithRGB(i*3 + 1,loopCounter + i % 255,0,255 - loopCounter + i % 255);
  }
  // advance the counter
  loopCounter++;  
}

