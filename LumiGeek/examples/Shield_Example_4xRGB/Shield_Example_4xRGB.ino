#include <LumiGeek.h>
#include <Wire.h>  // we need to includ Wire.h until we have our own LG I2C implementation

LumiGeek4xRGB lumigeekShield;

void setup() {
  
  Wire.begin();  // we need this until we have our own LG I2C implementation
 
  // create a reference to our shield with its current DIP switch setting 

  lumigeekShield = LumiGeek4xRGB(1);  
 
  // setup some periodic/automated behaviors with just one call
  
  lumigeekShield.autoJumpHeaderBetweenRGBs(2,random() % 255,0,0,0,0,random() % 255,5);
  lumigeekShield.autoFadeHeaderBetweenRGBs(4,0,random() % 255,0,0,0,random() % 255,5);
 
}

void loop() {
  
  // call some manual color changes each time through the loop
  
  lumigeekShield.jumpHeaderToRGB(1,random() % 255,0,random() % 255); 
  lumigeekShield.fadeHeaderToRGB(3,0,random() % 255,random() % 255,10); 
  delay(3000);
 
}
		
