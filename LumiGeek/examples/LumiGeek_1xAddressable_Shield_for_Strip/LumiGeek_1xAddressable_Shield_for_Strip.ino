#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek1xAddressable lg1xAddr;

uint8_t frame[300];
uint8_t loopCounter;

void setup() {
  // instatiate a shield with its dip switches set to 0x0
  lg1xAddr = LumiGeek1xAddressable(0x0);
  // initialize the I2C bus
  lg1xAddr.begin();
  // turn on serial debugging
  lg1xAddr.setDebug(true);
  //set the type of strip being used
  lg1xAddr.setMode(LG_ADDR_MODE_WS2811);

  lg1xAddr.blackout();    
  delay(500);

  // grow a gradient from red to blue over increasing length of strip
  for (int i = 0 ; i <= 51 ; i++) {
    lg1xAddr.drawGradient(255,0,0,0,0,255,i);    
    delay(20);
  }
  delay(5000);
  
  // rotate/shift a 50px buffer containing above gradient
  //lg1xAddr.autoShiftBuffer(1,1,100);
  //delay(2000);
  
  // do a red comet chase over 50px of addressable strip
  // lg1xAddr.autoComet(255,0,0,51,5,1);
  delay(10000);

}

void loop() {
  // create an animation of random purple sparkles
  for(int i = 0; i < 50 ; i++) {
    if (i == random() % 50) {
      frame[i*3] = random() % 255;
      frame[i*3+1] = 0;
      frame[i*3+2] = random() % 255;
    } else {
      frame[i*3] = 0;
      frame[i*3+1] = 0;
      frame[i*3+2] = 0;
    }
  }
 // lg1xAddr.drawFrame(50,frame);
  loopCounter++;
  if (loopCounter > 50) {
     loopCounter = 0; 
  }
}
