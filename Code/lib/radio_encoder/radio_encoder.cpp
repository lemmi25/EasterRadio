#include <radio_encoder.h>


//AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);


bool button_clicked = false;
encoderData encoder1;

void rotary_init(){

    //we must initialize rorary encoder 
	rotaryEncoder.begin();
	//rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
	rotaryEncoder.setup(
		[] { rotaryEncoder.readEncoder_ISR(); },
		[] { rotary_onButtonClick(); });
	//optionally we can set boundaries and if values should cycle or not
	//in this example we will set possible values between 0 and 1000;
	bool circleValues = true;
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

	encoder1.pushed = true;
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

	encoder1.roationDelta = encoderValue;
	encoder1.rotated = true;



	return encoderValue;

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

	encoderData* get_encoder_data(){
    return &encoder1;
}