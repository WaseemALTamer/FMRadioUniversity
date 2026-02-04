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



void setup() {
    Serial.begin(9600);

    
    Buttons::init(); // Initialize the buttons
    Buttons::register_enter_button_callback(onEnterPressed); // register the button call back so it is excuated when there is an event


    Encoder::init(); // set up the encoder 
    Encoder::register_encoder_callback(onRotate); // attach the function to be excuated

}



void loop() {
  // run the main Button loop so the buttons can detect 
  // and trigger the event
  
  Buttons::loop();
  Encoder::loop();
}
