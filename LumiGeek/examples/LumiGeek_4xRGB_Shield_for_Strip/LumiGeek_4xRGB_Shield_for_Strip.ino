#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek4xRGB lg4xRGB;

void setup() {
  // instatiate a shield with its dip switches set to 0x0
  lg4xRGB = LumiGeek4xRGB(0x0);
  // initialize the I2C bus
  lg4xRGB.begin();
  // turn on serial debugging
  lg4xRGB.setDebug(true);
  
  // setup some macros that run on the shield, separate from the arduino

  // setup header #1 to do a periodic jump from red to blue
  lg4xRGB.autoJumpHeaderBetweenRGBs(1,255,0,0,0,0,255,5); 
  // setup header #2 to a pulsing fade from green to black
  lg4xRGB.autoFadeHeaderBetweenRGBs(2,0,255,0,0,0,0,10);  
  // setup header #3 to do a periodic jump from blue to green
  lg4xRGB.autoJumpHeaderBetweenRGBs(3,0,0,255,0,255,0,5); 
  // setup header #4 to a pulsing fade from black to red
  lg4xRGB.autoFadeHeaderBetweenRGBs(4,0,0,0,255,0,0,10); 

  // remember to only call the auto fade/jump macros from setup() or other controlled areas.
  // do not call the above auto fade/jump macros from the main loop() or they will just restart themselves

  delay(1000);
}

void loop() {
  
  // uncomment these to jump/fade colors from the arduino every second
  
  // jump header #1 to a random red color
  //lg4xRGB.jumpHeaderToRGB(1,random() % 255,0,0); 
  // jump header #2 to a random green
  //lg4xRGB.jumpHeaderToRGB(2,0,random() % 255,0);  
  // fade header #3 to a random blue
  //lg4xRGB.fadeHeaderToRGB(3,0,0,random() % 255,15); 
  // jump header #4 to a random  color
  //lg4xRGB.jumpHeaderToRGB(4,random() % 255,random() % 255,random() % 255); 
  
  delay(1000);
}