#include <radio_encoder.h>


//AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);


bool button_clicked = false;

void rotary_init(){

    //we must initialize rorary encoder 
	rotaryEncoder.begin();
	//rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
	rotaryEncoder.setup(
		[] { rotaryEncoder.readEncoder_ISR(); },
		[] { rotary_onButtonClick(); });
	//optionally we can set boundaries and if values should cycle or not
	//in this example we will set possible values between 0 and 1000;
	bool circleValues = false;
	rotaryEncoder.setBoundaries(0, 1000, circleValues); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)

	
	//rotaryEncoder.setBoundaries(-100, 100, true); //minValue, maxValue, cycle values (when max go to min and vice versa)
    //rotaryEncoder.reset(); 


	/*Rotary acceleration introduced 25.2.2021.
   * in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
   * without accelerateion you need long time to get to that number
   * Using acceleration, faster you turn, faster will the value raise.
   * For fine tuning slow down.
   */
	//rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
	rotaryEncoder.setAcceleration(250); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
}


//int test_limits = 2;
void rotary_onButtonClick() {


	static unsigned long lastTimePressed = 0;
	//ignore multiple press in that time milliseconds
	if (millis() - lastTimePressed < 500)
	{
		return;
	}
	lastTimePressed = millis();
	Serial.print("button pressed at ");
	Serial.println(millis());

	button_clicked = true;
	/*
	rotaryEncoder.reset();
	//rotaryEncoder.disable();
    Serial.println("buttonClicked");

    button_clicked = true;*/
}

int rotary_loop() {


	//dont print anything unless value changed
	if (!rotaryEncoder.encoderChanged())
	{
		return 0;
	}

	int16_t encoderValue = rotaryEncoder.readEncoder();
	Serial.print("Value: ");
	Serial.println(encoderValue);

	return encoderValue;

	/*
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
		Serial.print(encoderValue);
		Serial.print("Delta: ");
		Serial.print(encoderDelta);
	} 

    return encoderDelta;
	*/
}

    void rotary_enable()
    {
        rotaryEncoder.enable ();
    }

    bool get_button_clicked_state()
	{
        return button_clicked;
    }

    void set_button_clicked_state(bool new_state)
	{
        button_clicked = new_state;
    }