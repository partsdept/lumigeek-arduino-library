#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek1xAddressable lg1xAddr;

uint8_t frame[300];

void setup() {
  // initialize the I2C bus
  lg1xAddr.begin();
  // turn on serial debugging
  lg1xAddr.setDebug(true);
  // instatiate a shield with its dip switches set to 0x0
  lg1xAddr = LumiGeek1xAddressable(0x0);
  //set the type of strip being used
  lg1xAddr.setMode(LG_ADDR_MODE_WS2811);
  // grow a gradient from red to blue over increasing length of strip
  for (int i = 0 ; i < 100 ; i++) {
    lg1xAddr.drawGradient(255,0,0,0,0,255,i);    
    delay(20);
  }
  delay(250);  
  // rotate/shift a 100px buffer containing above gradient
  lg1xAddr.autoShiftBuffer(1,10,100);
  delay(2000);
  // do a red comet chase over 100px of addressable strip
  lg1xAddr.autoComet(255,0,0,100,5,10);
  delay(2000);
}

void loop() {
  for(int i = 0; i < 100 ; i++) {
    frame[i] = 255 * sin(i/100 * PI);
    frame[i+2] = 255 * cos(i/100 * PI/2);
  }
  lg1xAddr.drawFrame(100,frame);
}

