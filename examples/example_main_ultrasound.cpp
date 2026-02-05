#include "ultrasound.h"



// this is a function to be triggred
void onDistance(float distance) {
    Serial.println(distance);
}


void setup() {
    Serial.begin(9600);
    Ultrasound::init();
    Ultrasound::register_ultrasound_callback(onDistance);
}


void loop() {
    Ultrasound::loop();
}