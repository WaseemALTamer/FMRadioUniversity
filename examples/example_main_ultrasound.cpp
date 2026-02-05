#include "ultrasound.h"



// this is a function to be triggred
void onDistance(float distance) {
    Serial.println(distance);
}


void setup() {
    Serial.begin(9600);


    Ultrasound::init(); // initatie the file
    Ultrasound::register_ultrasound_callback(onDistance); // attach function to the event
}


void loop() {
    Ultrasound::loop(); // run the loop so the utrasound system 
}