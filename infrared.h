#ifndef INFRARED_H
#define INFRARED_H


#include <Arduino.h>
#include <stdint.h> // this is for the uint32_t data type 

namespace Infrared {

    // Callback type: called when a valid IR event is accepted
    typedef void (*ReciverCallback)(uint16_t address, uint8_t command);

    // Initialize the infrared receiver module
    void init();

    // Must be called repeatedly from the main loop
    void loop();

    // Register a callback to receive IR events
    void register_reciver_callback(ReciverCallback callback);
}

#endif // INFRARED_H