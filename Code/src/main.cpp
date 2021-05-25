/*
 An example analogue clock using a TFT LCD screen to show the time
 use of some of the drawing commands with the library.

 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo. 
 
 This sketch uses font 4 only.

 Make sure all the display driver and pin comnenctions are correct by
 editting the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 
 Based on a sketch by Gilchrist 6/2/2014 1.0
 */

#include <lvgl.h>
#include <radio_display.h>
#include <radio_encoder.h>
#include <SI4844.h>
#include <Shifty.h>

#include "MCP3X21.h"  // https://github.com/pilotak/MCP3X21



//#include <hm_radio.h>

//#define CONFIG_INT_WDT_CHECK_CPU1 1 

// Tested on Arduino Pro Mini
#define INTERRUPT_PIN 32//2  
#define RESET_PIN 35//12
// Pages 17 and 18 from Si48XX ATDD PROGRAMMING GUIDE
#define DEFAULT_BAND 0   // FM => 0 to 19; AM => 20 to 24; SW => 25 to 40



const uint8_t address = 0x4E;
const uint16_t ref_voltage = 3300;  // in mV

MCP3221 mcp3221(address);
SI4844 si4844; 
// Declare the shift register
Shifty shift; 



int rotary_value; 
bool wasButton_clicked = false;

unsigned long timeLastActive;
bool saverOff = true;

void task_lvgl(void *parameter);
void task_enc2disp(void *parameter);


enum color{
  RED = 0, 
  GREEN, 
  BLUE
};

void set_LED(int led_num, color led_col, bool highlow);






//TFT_eSPI tft = TFT_eSPI(); /* TFT instance */


/*
void my_lv_drivers_init(void);


// Display flushing
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}
*/
void setup(void) {

  // Set the number of bits you have (multiples of 8)
  shift.setBitCount(24);

  // Set the clock, data, and latch pins you are using
  // This also sets the pinMode for these pins
  shift.setPins(33, 25, 26); 

  
  Wire.begin(SDA, SCL);

  
  //delay(500);  

    //mcp3221.init();

   // Wire.begin(SDA, SCL);
   // mcp3221.init(&Wire);

  //comment if no radio chip connected
  //si4844.setup(RESET_PIN, INTERRUPT_PIN, DEFAULT_BAND);

  //Comment if no display connected
  //radio_display_init();
  Serial.begin(9600);

  radio_display_init();


  rotary_init();

  //tft.begin(); /* TFT init */
  //tft.setRotation(1); /* Landscape orientation */
    
  


  timeLastActive = millis();

  Serial.println("Creating task...");

  //pinMode(19, INPUT);
    set_LED(1, RED, false);
    set_LED(2, RED, false);
    set_LED(3, RED, false);
    set_LED(4, GREEN, false);
    set_LED(5, GREEN, false);

    lv_radio_encoder();
}


void loop() {

  //lv_tick_inc(10);

  //  if (si4844.hasStatusChanged())
  // {
  //   Serial.print("[Band..: ");
  //   Serial.print(si4844.getBandMode());
  //   Serial.print(" - Frequency: ");    
  //   Serial.print(si4844.getFrequency(),0);
  //   Serial.print(" KHz");
  //   if (si4844.getStatusBandMode() == 0) {
  //     Serial.print(" - Stereo ");
  //     Serial.print(si4844.getStereoIndicator());
  //   }
  //   Serial.println("]");
  // }
   // writeBit works just like digitalWrite
  /*
    uint16_t result = mcp3221.read();

    Serial.print(F("ADC: "));
    Serial.print(result);
    Serial.print(F(", mV: "));
    Serial.println(mcp3221.toVoltage(result, ref_voltage));
    */

  lv_task_handler();
  delay(5);
  lv_tick_inc(5);
}


void set_LED(int led_num, color led_col, bool highlow)
{

  //LED 1: 0,1,2
  //LED 2: 11,12,13
  //LED 3: 8,9,10
  //LED 4: 17,18,19
  //LED 5: 14, 15, 16

  int color_bit; 
  int r_bit = 0;

  //set initial val for LED to set: 
  switch(led_num){
    case 1:
      r_bit = 0;
      break;
    case 2:
      r_bit = 11;
      break;
    case 3:
      r_bit = 8;
      break;
    case 4: 
      r_bit = 19;
      break;
    case 5:
      r_bit = 16;
      break;
  }

  color_bit = r_bit + led_col;
  shift.writeBit(color_bit, highlow);


}