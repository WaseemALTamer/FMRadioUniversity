// this file uses all 3 modules that we tested in lab




#include "buttons.h"
#include "encoder.h"
#include "infrared.h"



// This is the function that will be called when the Up button is pressed
void onEnterPressed(int state) {
    Serial.println(state);
    if (state) // state is 1 is released
        Serial.println("enter button relased!");
    else{ // state of 0 is pressed
        Serial.println("enter button pressed!");
    }
}

void onRotate(int delta) {
    if (delta > 0) Serial.println("Clockwise"); // this is +1 value
    else Serial.println("Counterclockwise"); // this is -1 value
}

// This function will be called when an IR code is received (and passes your filter)
void onIrReceived(uint16_t address, uint8_t command) {
    Serial.print("IR code received: 0x");
    Serial.println(address, HEX);
    Serial.println(command, HEX);
}


void setup() {
    Serial.begin(9600);

    
    Buttons::init(); // Initialize the buttons
    Buttons::register_enter_button_callback(onEnterPressed); // register the button call back so it is excuated when there is an event


    Encoder::init(); // set up the encoder 
    Encoder::register_encoder_callback(onRotate); // attach the function to be excuated

    Infrared::init(); // set up the Infrared
    Infrared::register_reciver_callback(onIrReceived);

}



void loop() {
  // run the main Button loop so the buttons can detect 
  // and trigger the event
  
  //Buttons::loop();
  //Encoder::loop();
  Infrared::loop();
}
