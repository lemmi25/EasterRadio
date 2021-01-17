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


#include <radio_display.h>
#include <radio_encoder.h>
//#include <hm_radio.h>

//#define CONFIG_INT_WDT_CHECK_CPU1 1 

int rotary_value; 
bool wasButton_clicked = false;
bool wasRotated = false;

unsigned long timeLastActive;
bool saverOff = true;

void task_encoder(void *parameter);

void setup(void) {

  Serial.begin(57600);

  radio_display_init();
  rotary_init();
  timeLastActive = millis();

  xTaskCreate(
      task_encoder,  /* Task function. */
      "TaskEncoder", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      1,         /* Priority of the task. */
      NULL);     /* Task handle. */

}


void loop() {

  if(wasRotated == false){
    rotary_value  =  rotary_loop();
    wasRotated = true;
  }
  
  if(wasButton_clicked == false){
    wasButton_clicked = get_button_clicked_state();
  }

  if (timeLastActive > 10000 && timeLastActive < (millis()-10000) && saverOff )
  {
    Serial.println("Saver");
    show_display_saver();
    saverOff = false;
  }

  delay(100);						 
	if (millis()>2000) rotary_enable();
}

    TaskHandle_t xHandle = NULL;

//encoder Task
void task_encoder(void *parameter){
 
  for(;;){

    if(wasButton_clicked)
    {
      radio_display_clicked();
      wasButton_clicked = false;
      rotary_value = 0;
      set_button_clicked_state(false);
      timeLastActive = millis();
      saverOff = true;
      delay(200);
    }
    else if(wasRotated){
      if(rotary_value){
        Serial.println("Display Update");
        radio_display_update(rotary_value);
        timeLastActive = millis();
        saverOff = true;
        delay(500);
        rotary_value = 0;
      }
      wasRotated = false;
    }
    vTaskDelay(300);
  }
}