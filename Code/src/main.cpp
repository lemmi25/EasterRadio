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

//#define CONFIG_INT_WDT_CHECK_CPU1 1 

int rotary_value; 
bool wasButton_clicked;

void task_encoder(void *parameter);
void task_handle(void *parameter);

void setup(void) {

  Serial.begin(9600);

  radio_display_init();
  rotary_init();


   xTaskCreate(
      task_encoder,  /* Task function. */
      "TaskEncoder", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      1,         /* Priority of the task. */
      NULL);     /* Task handle. */
}


void loop() {


  //Serial.print("loop");
  if(rotary_value == 0){
  rotary_value  =  rotary_loop();
  }
  Serial.print(rotary_value);
  
  if(wasButton_clicked == false){
  wasButton_clicked = get_button_clicked_state();
  }

	vTaskDelay(10);	
  delay(100);						 
	if (millis()>2000) rotary_enable();
}

    TaskHandle_t xHandle = NULL;
void task_encoder(void *parameter){
 
  for(;;){

    if(wasButton_clicked)
    {
      radio_display_clicked();
      wasButton_clicked = false;
      set_button_clicked_state(false);
    }
    else if(rotary_value){
      Serial.println("Display Update");
      radio_display_update(rotary_value);
      rotary_value = 0;
    }
    vTaskDelay(50);
  }
}

void task_handle(void *parameter){

  Serial.print("Call task handle");
  
    vTaskDelete( xHandle );
    
}