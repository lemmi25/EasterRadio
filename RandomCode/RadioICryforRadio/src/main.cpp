/*
 * SI4844 radio. Firmware information example. 
 * This Sketch shows the use of SI4844 Library to extract the device firmware information. 
 * 
 *  SI4844 and Arduino Pro Mini connections
 *  
 *  | SI4844 pin |  Arduino pin |  Description                                       |
 *  | ---------  | ------------ | -------------------------------------------------  |
 *  |    2       |   2          | Arduino interrupt pin                              |
 *  |   15       |  12          | Regurlar arduino digital pin used to RESET control |
 *  |   16       |  A4 (SDA)    | I2C bus (Data)                                     |
 *  |   17       |  A5 (SCL)    | I2C bus (Clocl)                                    |
 * 
 *  By Ricardo Lima Caratti (PU2CLR), Oct, 2019.
 */

#include <SI4844.h>
#include <Shifty.h>

#include "MCP3X21.h"  // https://github.com/pilotak/MCP3X21


// Tested on Arduino Pro Mini
#define INTERRUPT_PIN 32//2  
#define RESET_PIN 35//12
// Pages 17 and 18 from Si48XX ATDD PROGRAMMING GUIDE
#define DEFAULT_BAND 0   // FM => 0 to 19; AM => 20 to 24; SW => 25 to 40

const uint8_t address = 0x4E;
const uint16_t ref_voltage = 4200;  // in mV

MCP3221 mcp3221(address);
SI4844 si4844; 
// Declare the shift register
Shifty shift; 


void setup() {

// Set the number of bits you have (multiples of 8)
  shift.setBitCount(8);

  // Set the clock, data, and latch pins you are using
  // This also sets the pinMode for these pins
  shift.setPins(33, 25, 26); 

  
  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  
  delay(500);  

  mcp3221.init();
  si4844.setup(RESET_PIN, INTERRUPT_PIN, DEFAULT_BAND);

  Serial.println("\nSI4844 -  Firmware information\n");
  // See Si48XX ATDD PROGRAMMING GUIDE, page 22.   
  si4844.getFirmware();
  Serial.print("Final 2 digits of Part Number..: ");
  Serial.println(si4844.getFirmwarePartNumber(), HEX); 
  Serial.print("Firmware Major Revision........: ");
  Serial.println(si4844.getFirmwareMajorRevision());
  Serial.print("Firmware Minor Revision........: ");
  Serial.println(si4844.getFirmwareMinorRevision());
  Serial.print("Component Major Revision.......: ");
  Serial.println(si4844.getFirmwareComponentMajorRevision());
  Serial.print("Component Minor Revision.......: "); 
  Serial.println(si4844.getFirmwareComponentMinorRevision());
  Serial.print("Chip Revision..................: ");
  Serial.println(si4844.getFirmwareChipRevision());

  Serial.println("*****************************");
}

void loop() {
  // If you move the tuner, hasStatusChanged will return true
  if (si4844.hasStatusChanged())
  {
    Serial.print("[Band..: ");
    Serial.print(si4844.getBandMode());
    Serial.print(" - Frequency: ");    
    Serial.print(si4844.getFrequency(),0);
    Serial.print(" KHz");
    if (si4844.getStatusBandMode() == 0) {
      Serial.print(" - Stereo ");
      Serial.print(si4844.getStereoIndicator());
    }
    Serial.println("]");
  }
    // writeBit works just like digitalWrite
  
  shift.writeBit(2, HIGH);
  
  shift.writeBit(5, HIGH);
  delay(1);
  shift.writeBit(2, LOW);
  shift.writeBit(5, LOW);
  delay(14);



    uint16_t result = mcp3221.read();

    Serial.print(F("ADC: "));
    Serial.print(result);
    Serial.print(F(", mV: "));
    Serial.println(mcp3221.toVoltage(result, ref_voltage));
}
