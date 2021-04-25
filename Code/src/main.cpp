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
const uint16_t ref_voltage = 4200;  // in mV

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
  shift.setBitCount(8);

  // Set the clock, data, and latch pins you are using
  // This also sets the pinMode for these pins
  shift.setPins(33, 25, 26); 

  
  Wire.begin(SDA, SCL);

  
  delay(500);  

  mcp3221.init();

  //comment if no radio chip connected
  //si4844.setup(RESET_PIN, INTERRUPT_PIN, DEFAULT_BAND);

  //Comment if no display connected
  //radio_display_init();
  Serial.begin(115200);
  rotary_init();

  //tft.begin(); /* TFT init */
  //tft.setRotation(1); /* Landscape orientation */
    
  radio_display_init();
  

  timeLastActive = millis();

  Serial.println("Creating task...");

  
  //Check Encoder Changes and transfer to display etc
  xTaskCreate(
      task_enc2disp,  /* Task function. */
      "TaskEncoder", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      1,         /* Priority of the task. */
      NULL);     /* Task handle. */

  xTaskCreate(
      task_lvgl,  /* Task function. */
      "TaskLVGL", /* String with name of task. */
      10000,         /* Stack size in bytes. */
      NULL,          /* Parameter passed as input of the task */
      5,             /* Priority of the task. */
      NULL);         /* Task handle. */


  //pinMode(19, INPUT);
}


void loop() {


  //lv_tick_inc(10);
/*
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
  }*/
    // writeBit works just like digitalWrite
  /*
  shift.writeBit(2, LOW);
  
  shift.writeBit(5, LOW);
  shift.writeBit(6, LOW);
  
  shift.writeBit(9, LOW);
  delay(1);
  shift.writeBit(2, LOW);
  shift.writeBit(5, LOW);
  delay(14);

  delay(10);
  lv_tick_inc(10);
*/
    //lv_task_handler();
  delay(10);
  lv_tick_inc(10);
}


void task_lvgl(void *parameter){
  for(;;){
  lv_task_handler();
  vTaskDelay(100);
  }
}


TaskHandle_t xHandle = NULL;

//encoder Task
void task_enc2disp(void *parameter){
 
  for(;;){

    wasButton_clicked = get_button_clicked_state();
    rotary_value  =  rotary_loop();

    if(wasButton_clicked)
    {
      //radio_display_clicked();
      wasButton_clicked = false;
      //rotary_value = 0;
      set_button_clicked_state(false);
      timeLastActive = millis();
      saverOff = true;
      //delay(200);
    }
    //else if(wasRotated){
    else if(rotary_value){
        Serial.println("Display Update");
        //radio_display_update(rotary_value);
        timeLastActive = millis();
        saverOff = true;
        //delay(500);
        rotary_value = 0;
      }

    vTaskDelay(300);
  }
}




