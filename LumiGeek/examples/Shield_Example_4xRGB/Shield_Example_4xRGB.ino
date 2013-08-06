#include <LumiGeek.h>

// create a reference to our shield
LumiGeek4xRGB lg4xRGB;

void setup() {
  // initialize the LumiGeek library
  LumiGeek.begin();
  LumiGeek.setDebug(true);

  // get a new reference to a shield with dip switches = 0x1
  lg4xRGB = LumiGeek.addShield4xRGB(1); 

  // blackout any old header settings and wait one second
  lg4xRGB.blackout();
  delay(1000);

  // setup periodic/automated behavior with just one line of code
  lg4xRGB.autoFadeHeaderBetweenRGBs(1,0,0,255,255,0,0,100);
}

void loop() {
  // call some manual color changes each time through the loop
  lg4xRGB.jumpHeaderToRGB(3,random() % 200,0,random() % 200); 
  delay(3000);
}

