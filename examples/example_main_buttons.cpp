#include <Arduino.h>
#include "buttons.h"




// This is the function that will be called when the Up button is pressed
void onUpPressed(int state) {
    if (state) // state is 1 is released
        Serial.println("Up button relased!");
    else{ // state of 0 is pressed
        Serial.println("Up button pressed!");
    }
}


void setup() {
    Serial.begin(9600);

    // Initialize the buttons
    Buttons::init();

    // register the button call back so it is excuated when there is an event
    Buttons::register_up_button_callback(onUpPressed);
}



void loop() {
  // run the main Button loop so the buttons can detect 
  // and trigger the event
  
  Buttons::loop();
}
