// this is a base input class, this class  will not  access any  of the other
// files, other files will include this file this file doesnt need to include
// any other file in this project




#ifndef BUTTONS_H // these insure that the file doesnt get imported again
#define BUTTONS_H

#include <Arduino.h>






namespace Buttons {

    // Callback type for button events
    typedef void (*ButtonCallback)(int state);

    // Initializes the button pins (call in setup)
    void init();

    // Call this in your main loop to update button states
    void loop();

    // Register callback functions for each button
    void register_enter_button_callback(ButtonCallback callback);
    void register_up_button_callback(ButtonCallback callback);
    void register_down_button_callback(ButtonCallback callback);
    void register_right_button_callback(ButtonCallback callback);
    void register_left_button_callback(ButtonCallback callback);
}

#endif // BUTTONS_H
