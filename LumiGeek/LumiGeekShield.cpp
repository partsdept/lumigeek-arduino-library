// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// John Parts Taylor and JoeJoe Martin, August 7, 2013
// ---------------------------------------------------------------------------

#include "LumiGeekShield.h"

// ---------------------------------------------------------------------------
// LumiGeekShield
// A class to handle I2C and some other global calls 
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Methods for LumiGeekShield
// Calls the superclass constructor with the appropriate I2C address
// ---------------------------------------------------------------------------

LumiGeekShield::LumiGeekShield(uint8_t dipSwitchSetting,uint8_t targetProductId) {
  _initialized = false;
  _sane = true;
  _i2cOffset = dipSwitchSetting;    
  _expectedProductId = targetProductId;
}

bool LumiGeekShield::assertProductMatchesI2cAddress() {
  _actualProductId = read((uint8_t) i2cAddress(),(uint8_t) LG_GLOBAL_CMD_QUERY);
  if (_expectedProductId == _actualProductId) {
    return true;
  } else {
    return false;
  }
}

bool LumiGeekShield::assertSanityCheck() {
  // only check productId and dip switch range once
  if (!_initialized) {
    _initialized = true;
    if (assertProductMatchesI2cAddress()) {
      if (debug()) {
        Serial.print("LUMIGEEK: Shield with dip switch setting 0x");
        Serial.print(_i2cOffset,HEX);
        Serial.print(" has product ID 0x");
        Serial.println(_actualProductId,HEX);
      }
    } else {
      _sane = false;
      if (debug()) {
        Serial.print("ERROR: A shield class has product ID of 0x");
        Serial.print(_expectedProductId,HEX);
        Serial.print(" but does not match reported product ID 0x");
        Serial.print(_actualProductId,HEX);
        Serial.print("  from shield with dip switch 0x");
        Serial.println(_i2cOffset,HEX);
        Serial.println("TIP: Make sure you are instantiating the right LumiGeek library class for the right physical shield.");
        Serial.println("TIP: Check your dip switches on the shield against the shield class constructor.");
      }
      return false;
    }
    if (!assertOffsetValue(_i2cOffset)) {
      if (debug()) {
        Serial.println("ERROR: Dip switch value in shield constructor must be in range 0-15.");
      }
      _sane = false;
      return false;
    }
  }

  if (!calledBegin()) {
    if (debug()) {
      Serial.println("ERROR: Failed sanity check. Make sure you called LumiGeek.begin() before calling shield functions.");
    }
    return false;
  }
  
  return true;
}

bool LumiGeekShield::assertOffsetValue(uint8_t i2cOffset) {
  if (i2cOffset > 15) {
    if (debug()) {
      Serial.println("LumiGeek I2C dip switch setting must be from 0 to 15.");
    }
    _sane = false;
    return false;
  } 
  return true;
}

uint8_t LumiGeekShield::i2cAddress() {
	return LG_BASE_I2C_ADDRESS + _i2cOffset;
}

void LumiGeekShield::blackout() {
  if (assertSanityCheck()) {
	  write(i2cAddress(),LG_GLOBAL_CMD_BLACKOUT);
  }
}

void LumiGeekShield::testPattern() {
  if (assertSanityCheck()) {
	  write(i2cAddress(),LG_GLOBAL_CMD_TEST_PATTERN);
  }
}





// Debugging Helpers

bool LumiGeekShield::_debug = false;
bool LumiGeekShield::_verbose = false;
bool LumiGeekShield::_calledBegin = false;

bool LumiGeekShield::debug() {
	return _debug;
}

void LumiGeekShield::setDebug(bool b) {
	if (b) {
		_debug = true;
		Serial.begin(9600);
		Serial.println("LUMIGEEK: Welcome to the LumiGeek library for Arduino v0.1.");
	} else {
		_debug = false;
		// close serial port?
	}
}

bool LumiGeekShield::verbose() {
	return _verbose;
}

void LumiGeekShield::setVerbose(bool b) {
	if (b) {
		_verbose = true;
		Serial.println("LUMIGEEK: Verbose debugging enabled.");
	} else {
		_verbose = false;
	}
}

bool LumiGeekShield::calledBegin() {
	return _calledBegin;
}


// I2C helpers

uint8_t LumiGeekShield::bytesAvailable = 0;
uint16_t LumiGeekShield::bufferIndex = 0;
uint8_t LumiGeekShield::totalBytes = 0;
uint16_t LumiGeekShield::timeOutDelay = 10;

void LumiGeekShield::begin() {
	begin(0); // do not use fast I2C
}

void LumiGeekShield::begin(uint8_t _fast) {
  _calledBegin = true;
  
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
  // activate internal pull-ups for twi
  // as per note from atmega8 manual pg167
  sbi(PORTC, 4);
  sbi(PORTC, 5);
#else
  // activate internal pull-ups for twi
  // as per note from atmega128 manual pg204
  sbi(PORTD, 0);
  sbi(PORTD, 1);
#endif
  // initialize twi prescaler and bit rate
  cbi(TWSR, TWPS0);
  cbi(TWSR, TWPS1);
  if(!_fast) {
    TWBR = ((F_CPU / 100000) - 16) / 2;
  } else {
    TWBR = ((F_CPU / 400000) - 16) / 2;
  }
  // enable twi module and acks
  TWCR = _BV(TWEN) | _BV(TWEA);
}

void LumiGeekShield::end() {
  TWCR = 0;
}

void LumiGeekShield::setTimeOut(uint16_t _timeOut) {
  timeOutDelay = _timeOut;
}

void LumiGeekShield::lockUp() {
  TWCR = 0; //releases SDA and SCL lines to high impedance
  TWCR = _BV(TWEN) | _BV(TWEA); //reinitialize TWI 
}

void LumiGeekShield::scan() {
  uint8_t lgDeviceCount = 0;
  uint8_t totalDeviceCount = 0;
  uint16_t tempTime = timeOutDelay;
  setTimeOut(80);
  // TODO: put the Serial printing in a debug conditional
  Serial.println("LUMIGEEK: Scanning for devices...");
  Serial.print("  ");
  for(uint8_t s = 0; s <= 0x7F; s++) {
    Serial.print(".");
    returnStatus = 0;
    returnStatus = start();
    if(!returnStatus)
    { 
      returnStatus = sendAddress(SLA_W(s));
    }
    if(returnStatus)
    {
      if(returnStatus == 1)
      {
        Serial.println();    
        Serial.println("  There is a problem with the bus, could not complete scan");
//        timeOutDelay = tempTime;
        return;
      }
    } else {  
      Serial.println();    
      Serial.print("  Found device at address 0x");
      Serial.println(s,HEX);

      // modify this to return info about the LumiGeek shields on the bus
      // call up to the device to see if it is a LumiGeek device???

      totalDeviceCount++;
    }
    stop();
  }
  if(!totalDeviceCount){
    Serial.println();
    Serial.println("  No devices found");
  } else {
    Serial.println();
    Serial.print("  I2C device count is "); 
    Serial.println(totalDeviceCount);    
  }
  timeOutDelay = tempTime;
}


uint8_t LumiGeekShield::read(uint8_t address, uint8_t registerAddress) {
  start();  
  sendAddress(SLA_W(address));
  sendByte(registerAddress);
  start();
  sendAddress(SLA_R(address));
  receiveByte(0);
  stop();
  return TWDR;
}


uint8_t LumiGeekShield::write(uint8_t address, uint8_t command) {
  if (debug() && verbose()) {
    Serial.print("LUMIGEEK: I2C writing to address 0x");	
    Serial.print(address,HEX);	
    Serial.print(" with command 0x");
    Serial.println(command,HEX);
  }	
  returnStatus = 0;
  returnStatus = start();
  if(returnStatus){return(returnStatus);}
  returnStatus = sendAddress(SLA_W(address));
  if(returnStatus) {
    if(returnStatus == 1){return(2);}
    return(returnStatus);
  }
  returnStatus = sendByte(command);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }
  returnStatus = stop();
  if(returnStatus) {
    if(returnStatus == 1){return(7);}
    return(returnStatus);
  }
  return(returnStatus);
}

uint8_t LumiGeekShield::write(uint8_t address, uint8_t command, uint8_t hi_addr, uint8_t lo_addr, uint8_t* buffer, uint16_t numberBytes) {
  if (debug() && verbose()) {
    Serial.print("LUMIGEEK: I2C writing to address 0x");	
    Serial.print(address,HEX);	
    Serial.print(" with command 0x");
    Serial.print(command,HEX);
    Serial.print(" and hi_addr ");
    Serial.print(hi_addr);
    Serial.print(" and lo_addr ");
    Serial.print(lo_addr);
    Serial.print(" and ");
    Serial.print(numberBytes);
    Serial.println(" bytes of data.");    
  }	
  
  returnStatus = 0;
  returnStatus = start();
  if(returnStatus){return(returnStatus);}
  returnStatus = sendAddress(SLA_W(address));
  if(returnStatus) {
    if(returnStatus == 1){return(2);}
    return(returnStatus);
  }
  returnStatus = sendByte(command);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }
  returnStatus = sendByte(hi_addr);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }    
  returnStatus = sendByte(lo_addr);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }  
  for (uint16_t i = 0; i < numberBytes; i++) {
    returnStatus = sendByte(buffer[i]);
    if(returnStatus) {
        if(returnStatus == 1){return(3);}
        return(returnStatus);
      }
  }
  returnStatus = stop();
  if(returnStatus) {
    if(returnStatus == 1){return(7);}
    return(returnStatus);
  }
  return(returnStatus);
}

uint8_t LumiGeekShield::write(uint8_t address, uint8_t command, uint8_t header, uint8_t* buffer, uint16_t numberBytes) {
  if (debug() && verbose()) {
    Serial.print("LUMIGEEK: I2C writing to address 0x");	
    Serial.print(address,HEX);	
    Serial.print(" with command 0x");
    Serial.print(command,HEX);
    Serial.print(" and header ");
    Serial.print(header);
    Serial.print(" and ");
    Serial.print(numberBytes);
    Serial.println(" bytes of data.");    
  }	
  
  returnStatus = 0;
  returnStatus = start();
  if(returnStatus){return(returnStatus);}
  returnStatus = sendAddress(SLA_W(address));
  if(returnStatus) {
    if(returnStatus == 1){return(2);}
    return(returnStatus);
  }
  returnStatus = sendByte(command);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }
  returnStatus = sendByte(header);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }  
  for (uint16_t i = 0; i < numberBytes; i++) {
    returnStatus = sendByte(buffer[i]);
    if(returnStatus) {
        if(returnStatus == 1){return(3);}
        return(returnStatus);
      }
  }
  returnStatus = stop();
  if(returnStatus) {
    if(returnStatus == 1){return(7);}
    return(returnStatus);
  }
  return(returnStatus);
}


uint8_t LumiGeekShield::write(uint8_t address, uint8_t command, uint8_t* buffer, uint16_t numberBytes) {
  if (debug() && verbose()) {
    Serial.print("LUMIGEEK: I2C writing to address 0x");	
    Serial.print(address,HEX);	
    Serial.print(" with command 0x");
    Serial.print(command,HEX);
    Serial.print(" and ");
    Serial.print(numberBytes);
    Serial.println(" bytes of data.");    
  }	
  
  returnStatus = 0;
  returnStatus = start();
  if(returnStatus){return(returnStatus);}
  returnStatus = sendAddress(SLA_W(address));
  if(returnStatus) {
    if(returnStatus == 1){return(2);}
    return(returnStatus);
  }
  returnStatus = sendByte(command);
  if(returnStatus) {
    if(returnStatus == 1){return(3);}
    return(returnStatus);
  }
  for (uint16_t i = 0; i < numberBytes; i++) {
    returnStatus = sendByte(buffer[i]);
    if(returnStatus) {
        if(returnStatus == 1){return(3);}
        return(returnStatus);
      }
  }
  returnStatus = stop();
  if(returnStatus) {
    if(returnStatus == 1){return(7);}
    return(returnStatus);
  }
  return(returnStatus);
}

uint8_t LumiGeekShield::start() {
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay) {
      lockUp();
      return(1);
    }    
  }
  if ((TWI_STATUS == START) || (TWI_STATUS == REPEATED_START)) {
    return(0);
  }
  if (TWI_STATUS == LOST_ARBTRTN) {
    uint8_t bufferedStatus = TWI_STATUS;
    lockUp();
    return(bufferedStatus);
  }
  return(TWI_STATUS);
}

uint8_t LumiGeekShield::sendAddress(uint8_t i2cAddress) {
  TWDR = i2cAddress;
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay)
    {
      lockUp();
      return(1);
    }     
  }
  if ((TWI_STATUS == MT_SLA_ACK) || (TWI_STATUS == MR_SLA_ACK)) {
    return(0);
  }
  uint8_t bufferedStatus = TWI_STATUS;
  if ((TWI_STATUS == MT_SLA_NACK) || (TWI_STATUS == MR_SLA_NACK)) {
    stop();
    return(bufferedStatus);
  } else {
    lockUp();
    return(bufferedStatus);
  } 
}

uint8_t LumiGeekShield::sendByte(uint8_t i2cData) {
  TWDR = i2cData;
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay) {
      lockUp();
      return(1);
    }   
  }
  if (TWI_STATUS == MT_DATA_ACK) {
    return(0);
  }
  uint8_t bufferedStatus = TWI_STATUS;
  if (TWI_STATUS == MT_DATA_NACK) {
    stop();
    return(bufferedStatus);
  } else {
    lockUp();
    return(bufferedStatus);
  } 
}

uint8_t LumiGeekShield::receiveByte(uint8_t ack) {
  unsigned long startingTime = millis();
  if(ack) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
  } else {
    TWCR = (1<<TWINT) | (1<<TWEN);
  }
  while (!(TWCR & (1<<TWINT))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay)
    {
      lockUp();
      return(1);
    }
  }
  if (TWI_STATUS == LOST_ARBTRTN) {
    uint8_t bufferedStatus = TWI_STATUS;
    lockUp();
    return(bufferedStatus);
  }
  return(TWI_STATUS); 
}

uint8_t LumiGeekShield::stop() {
  unsigned long startingTime = millis();
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
  while ((TWCR & (1<<TWSTO))) {
    if(!timeOutDelay){continue;}
    if((millis() - startingTime) >= timeOutDelay) {
      lockUp();
      return(1);
    }    
  }
  return(0);
}


