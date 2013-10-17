#include <LumiGeek.h>

// define a reference to the shield object
LumiGeek24xMono lg24xMono;

uint8_t frame[24];

void setup() {
  // initialize the I2C bus
  lg24xMono.begin();
  // turn on serial debugging
  lg24xMono.setDebug(true);
  // instatiate a shield with its dip switches set to 0x0
  lg24xMono = LumiGeek24xMono(0x0);
  // set all headers to full on
  for (int i = 1 ; i <=24 ; i++) {
    lg24xMono.jumpHeaderToBrightness(i,255);   
  }
  delay(1000);
  // set all headers to off
  for (int i = 1 ; i <=24 ; i++) {
    lg24xMono.jumpHeaderToBrightness(i,0);   
  }
  delay(1000);
}

void loop() {
  // use the bulk frame command to send all 24 values with one I2C call
  for(int i = 1 ; i <= 24 ; i++) {
    frame[i+1%24] = 255;
    frame[i] = 0;
    lg24xMono.drawFrame(frame);
    delay(100);
  }
}

