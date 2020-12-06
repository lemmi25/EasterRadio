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


void setup(void) {

  Serial.begin(9600);

  radio_display_init();
  rotary_init();
}


void loop() {

  int rotary_value  =  rotary_loop();


  if(rotary_value){
    Serial.println("Display Update");
    radio_display_update(rotary_value);
  }

  if(get_button_clicked_state() == true)
  {
    set_button_clicked_state(false);
    radio_display_clicked();
  }
	
	delay(100);															 
	if (millis()>20000) rotary_enable();
  
}

