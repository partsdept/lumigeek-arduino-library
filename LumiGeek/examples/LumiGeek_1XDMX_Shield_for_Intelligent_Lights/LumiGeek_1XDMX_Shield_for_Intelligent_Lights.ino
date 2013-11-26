#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek1xDMX lg1xDMX;
byte loopCounter = 0;

void setup() {
  // instatiate a shield with its dip switches set to 0x0
  lg1xDMX = LumiGeek1xDMX(0x0);
  // initialize the I2C bus
  lg1xDMX.begin();
  // set all values to black
  for (int i = 0 ; i < 256 / 3 ; i++) {
    lg1xDMX.setAddressWithRGB(i*3 + 1,0,0,0);
  }
}

void loop() {
  // fill the DMX universe with a red to blue gradient that shifts with the loopCounter
  lg1xDMX.setAddressWithRGB(1,loopCounter % 255,0,255 - loopCounter % 255);
  loopCounter++;  
}
