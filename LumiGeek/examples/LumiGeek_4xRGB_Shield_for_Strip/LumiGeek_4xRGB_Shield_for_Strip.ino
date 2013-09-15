#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek4xRGB lg4xRGB;

void setup() {
  // initialize the I2C bus
  LumiGeek.begin();
  // turn on serial debugging
  lg4xRGB.setDebug(true);
  // instatiate a shield with its dip switches set to 0x0
  lg4xRGB = LumiGeek4xRGB(0x0);
  // setup header #1 to do a periodic jump from green to blue
  lg4xRGB.autoJumpHeaderBetweenRGBs(1,0,255,0,0,0,255,5); 
  // setup header #2 to a pulsing fade from black to red
  lg4xRGB.autoFadeHeaderBetweenRGBs(2,0,0,0,255,0,0,10); 
}

void loop() {
  // jump header #3 to a random purple-ish color
  lg4xRGB.jumpHeaderToRGB(3,random() % 255,0,random() % 255); 
  // fade header #4 to a random blue color
  lg4xRGB.fadeHeaderToRGB(4,0,0,random() % 255,15); 
  delay(3000);
}

