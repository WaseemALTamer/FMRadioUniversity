#include <Arduino.h>
#include "infrared.h"

// This function will be called when an IR code is received (and passes your filter)
void onIrReceived(uint16_t address, uint8_t command) {
    // some remotes have an address so you can code it in a way that you
    // only  accept commands  from one specific  address in better words
    // you accept commands from only one sepcific remote

    Serial.print("IR code received: 0x");
    Serial.println(address, HEX);
    Serial.print("Command: 0x");
    Serial.println(command, HEX);
}

void setup() {
    Serial.begin(9600);

    // Initialize the infrared module
    Infrared::init();

    // Register the IR callback
    Infrared::register_reciver_callback(onIrReceived);
}

void loop() {
    // Run the infrared loop so it can detect and fire events
    Infrared::loop();
}