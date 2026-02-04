#include <Arduino.h>
#include "encoder.h"




void onRotate(int delta) {
    if (delta > 0) Serial.println("Clockwise"); // this is +1 value
    else Serial.println("Counterclockwise"); // this is -1 value
}



void setup() {
    Serial.begin(9600);


    Encoder::init(); // set up the encoder 
    Encoder::register_encoder_callback(onRotate); // attach the function to be excuated
}

void loop() {
    Encoder::loop(); // allow the Encoder to loop and check for its event
}