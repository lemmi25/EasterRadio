#include <radio_encoder.h>


AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);

bool button_clicked = false;

void rotary_init(){

    //we must initialize rorary encoder 
	rotaryEncoder.begin();
	rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
	//optionally we can set boundaries and if values should cycle or not
	rotaryEncoder.setBoundaries(0, 10, true); //minValue, maxValue, cycle values (when max go to min and vice versa)


}


int test_limits = 2;
void rotary_onButtonClick() {
	//rotaryEncoder.reset();
	//rotaryEncoder.disable();
    Serial.println("buttonClicked");

    button_clicked = true;
	//rotaryEncoder.setBoundaries(-test_limits, test_limits, false);
	//test_limits *= 2;
}

int rotary_loop() {
	//first lets handle rotary encoder button click
	if (rotaryEncoder.currentButtonState() == BUT_RELEASED) {
		//we can process it here or call separate function like:
        Serial.println("released");
		rotary_onButtonClick();
        
	}

	//lets see if anything changed
	int16_t encoderDelta = rotaryEncoder.encoderChanged();
	
	//optionally we can ignore whenever there is no change
	if (encoderDelta == 0) return 0;
	
	//for some cases we only want to know if value is increased or decreased (typically for menu items)
	if (encoderDelta>0) Serial.println("+");
	if (encoderDelta<0) Serial.println("-");

	//for other cases we want to know what is current value. Additionally often we only want if something changed
	//example: when using rotary encoder to set termostat temperature, or sound volume etc
	
	//if value is changed compared to our last read
    int16_t encoderValue = 0;

	if (encoderDelta!=0) {
		//now we need current value
		encoderValue = rotaryEncoder.readEncoder();
		//process new value. Here is simple output.
		Serial.print("Value: ");
		Serial.println(encoderValue);
	} 

    //return encoderValue;
    return encoderDelta;
	
}

    void rotary_enable()
    {
        rotaryEncoder.enable ();
    }

    bool get_button_clicked_state(){

        return button_clicked;
    }

    void set_button_clicked_state(bool new_state){

        button_clicked = new_state;
    }