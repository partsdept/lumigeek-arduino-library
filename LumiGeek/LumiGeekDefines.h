// ----------------------------------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Authors: John Parts Taylor and JoeJoe Martin, March 12, 2013
// ----------------------------------------------------------------------------------------------------

#ifndef LumiGeekDefines_h
#define LumiGeekDefines_h

// TEMPORARILY USE THIS DEFINE WHILE PORTING I2C...  NUKE EVENTUALLY
#define USE_LUMIGEEK_I2C 1    

// ----------------------------------------------------------------------------------------------------
// I2C defines

#define LG_I2C_BUFFER_LENGTH 204  // will drive RGB for 1m of 68px/m strip
#define LG_BASE_I2C_ADDRESS 0x50	

#define START           0x08
#define REPEATED_START  0x10
#define MT_SLA_ACK	0x18
#define MT_SLA_NACK	0x20
#define MT_DATA_ACK     0x28
#define MT_DATA_NACK    0x30
#define MR_SLA_ACK	0x40
#define MR_SLA_NACK	0x48
#define MR_DATA_ACK     0x50
#define MR_DATA_NACK    0x58
#define LOST_ARBTRTN    0x38
#define TWI_STATUS      (TWSR & 0xF8)
#define SLA_W(address)  (address << 1)
#define SLA_R(address)  ((address << 1) + 0x01)
#define cbi(sfr, bit)   (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit)   (_SFR_BYTE(sfr) |= _BV(bit))


// ----------------------------------------------------------------------------------------------------
// LumiGeek Shield Product IDs
	
#define LG_4XRGB 0x20				    // 4X RGB Strip Shield		
#define LG_1XRGBMEGA 0x22			  // 1X RGB Mega Strip Shield	
#define LG_3XCC_1W 0x23				  // 3X CC 1W Shield	
#define LG_24XMONO 0x1F				  // 24X Mono LED Shield

// TODO: get these product IDs from JoeJoe

#define LG_1XDMX 0x00				    // 1X DMX Universe Generator	
#define LG_5X7_HEADLIGHT 0x00	  // 5x7 Headlight
#define LG_1XADDR 0x00				  // 1X Addressable MultiTool  	

// ----------------------------------------------------------------------------------------------------
// LumiGeek Global Commands
// Any of our shields respond to these commands

#define LG_GLOBAL_CMD_QUERY 0x01
#define LG_GLOBAL_CMD_BLACKOUT 0xAA
#define LG_GLOBAL_CMD_TEST_PATTERN 0xBB 


// ----------------------------------------------------------------------------------------------------
// LumiGeek Generic RGB Commands 
// These commands apply to the 4xRGB, 1xMega RGB, and the 3xCC 

#define LG_RGB_CMD_JUMP_TO 0x21				// 0x21 Header R G B  
#define LG_RGB_CMD_FADE_TO 0x22				// 0x22 Header R G B Speed 
#define LG_RGB_CMD_AUTO_FADE 0x23			// 0x23 Header R1 G1 B1 R2 G2 B2 Speed
#define LG_RGB_CMD_AUTO_JUMP 0x24			// 0x24 Header R1 G1 B1 R2 G2 B2 Speed
#define LG_RGB_CMD_AUTO_RANDOM 0x25			// 0x25 Header Speed  


// ----------------------------------------------------------------------------------------------------
// LumiGeek 1X Addressable Strip MultiTool Commands
// There is just single header for the addressable shield on the TurBull Encabulator.  
// Always set header = 1 in the I2C commands.

// You can set the type of addressable strip to be driven by this shield.  
// The default is WS2811, used in the strip that arrived with the TurBull Encabulator.
// StripMode: 1 = WS2811  e.g. http://adafruit.com/products/1138
//       	  2 = WS2801  e.g. http://sparkfun.com/products/11272, http://sparkfun.com/products/11020, http://adafruit.com/products/322, http://adafruit.com/products/738
//            3 = LPD8806 e.g. http://adafruit.com/products/306

#define LG_ADDR_CMD_SET_STRIP_MODE 0x58		// 0x58 Header StripMode 

// Here are some generative macros, limited for now to 256 pixels by the length byte

#define LG_ADDR_CMD_GRADIENT 0x51			// 0x51 Header R1 G1 B1 R2 G2 B1 Length 
#define LG_ADDR_CMD_COMET_CHASE 0x55			// 0x55 Header R G B LengthOfComet LengthOfTail Speed 

// Here is how to clock in raw RGB pixel data. Unlike the generative macros, the frame command can handle more than 256 pixels.
// Issues concerning power and voltage drop on long runs of strip will likely crop up before hitting any pixel limit on the I2C bus.
// The strip driver chips themselves may have limitations.  Please see their respective datasheets. (i.e. WS2811 appears to have a 1024 pixel limit)

#define LG_ADDR_CMD_FRAME 0x53				// 0x51 Header R1 G1 B1 ... RN GN BN

// Now that you have pixel data in our 1024 buffer on the shield, you can rotate or autorotate portions of the buffer
// The length of the buffer "wrap around" effect is limited to 256

#define LG_ADDR_CMD_SHIFT_BUFFER_ONCE 0x56	// 0x56 Header Direction(0=left,1=right) BufferLengthForWrap
#define LG_ADDR_CMD_AUTOSHIFT_BUFFER 0x57	// 0x57 Header Direction(0=left,1=right) BufferLengthForWrap Speed


// ----------------------------------------------------------------------------------------------------
// LumiGeek 1X DMX Driver Commands 
// There is just single header for the DMX shield on the Encabulator.  
// Always set header = 1 in the I2C commands.

#define LG_DMX_CMD_SET_BYTES_FROM_ADDR 0x41	// 0x41 Header BaseAddress [R1 G1 B1 ... RN GN BN]
#define LG_DMX_CMD_SET_ENTIRE_UNIVERSE 0x42	// 0x42 Header [512 bytes of DMX data]

// ----------------------------------------------------------------------------------------------------
// "Light is not so much something that reveals, as it is itself the revelation." – James Turrell
// ----------------------------------------------------------------------------------------------------

#endif
