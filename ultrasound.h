#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Arduino.h>

namespace Ultrasound {

    // Callback type: called with measured distance in cm
    typedef void (*UltrasoundCallback)(float distance);

    // Initialize the ultrasound module (pins, initial state)
    void init();

    // Main loop function, must be called frequently from Arduino loop()
    void loop();

    // Register a callback to receive distance measurements
    // Up to 5 callbacks can be registered
    void register_ultrasound_callback(UltrasoundCallback callback);

}

#endif // ULTRASOUND_H