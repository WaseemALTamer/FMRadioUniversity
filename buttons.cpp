// this is a base input class, this class  will not  access any  of the other
// files, other files will include this file this file doesnt need to include
// any other file in this project

// i estimated this file to take about 2% of the arduino memeory




#include <Arduino.h>
#include "buttons.h"


namespace Buttons {

    // buttons pins are not exposed you can only change them
    // inside this file only
    const int button_enter_pin = 10;
    const int button_up_pin = 9;
    const int button_down_pin = 8;
    const int button_right_pin = 7;
    const int button_left_pin = 6;



    // we start from <HIGH> as it is not pressed and when the value is <LOW> it is pressed
    // this hase been changed because now am using the arudino internal risistors
    int button_enter_last_state = HIGH;
    int button_up_last_state = HIGH; 
    int button_down_last_state = HIGH;
    int button_right_last_state= HIGH; 
    int button_left_last_state= HIGH;



    const unsigned long buttons_cooldown_ms = 30; // this will make sure that buttons have a cool down effect
                                                // this helps with the internal bouncing effect


    // this is the callback events you simply just attack a function you want to run when
    // the event occures to any of these call events and they will be called for you

    typedef void (*ButtonCallback)(int state); // create the call back type


    const int MAX_CALLBACKS = 5; // each array can only hold 5 callbacks

    ButtonCallback enter_callbacks[MAX_CALLBACKS];
    int enter_callback_count = 0;

    ButtonCallback up_callbacks[MAX_CALLBACKS];
    int up_callback_count = 0;

    ButtonCallback down_callbacks[MAX_CALLBACKS];
    int down_callback_count = 0;

    ButtonCallback right_callbacks[MAX_CALLBACKS];
    int right_callback_count = 0;

    ButtonCallback left_callbacks[MAX_CALLBACKS];
    int left_callback_count = 0;





    bool button_event_cooldown_passed() {
        // this avoid internal bounce effect for the buttons

        static unsigned long last_event_time = 0;
        unsigned long now = millis();

        if (now - last_event_time < buttons_cooldown_ms) {
            return false; // ignore event
        }

        last_event_time = now;
        return true; // accept event
    }


    void on_button_enter_event(int state){
        // state 1 is released and state 0 is pressed

        // now we can loop through the array of callbacks and simply 
        // excuateeach function provided the function exists
        for (int i = 0; i < enter_callback_count; i++) {
            if (enter_callbacks[i] != nullptr) {
                enter_callbacks[i](state);
            }
        }
    }


    void on_button_up_event(int state){
        // state 1 is released and state 0 is pressed

        // now we can loop through the array of callbacks and simply 
        // excuateeach function provided the function exists
        for (int i = 0; i < up_callback_count; i++) {
            if (up_callbacks[i] != nullptr) {
            up_callbacks[i](state);
            }
        }
    }

    void on_button_down_event(int state){
        // state 1 is released and state 0 is pressed

        // now we can loop through the array of callbacks and simply 
        // excuateeach function provided the function exists
        for (int i = 0; i < down_callback_count; i++) {
            if (down_callbacks[i] != nullptr) {
                down_callbacks[i](state);
            }
        }
    }

    void on_button_right_event(int state){
        // state 0 is released and state 0 is pressed

        // now we can loop through the array of callbacks and simply 
        // excuateeach function provided the function exists
        for (int i = 0; i < right_callback_count; i++) {
            if (right_callbacks[i] != nullptr) {
                right_callbacks[i](state);
            }
        }
    }

    void on_button_left_event(int state){
        // state 1 is released and state 0 is pressed

        // now we can loop through the array of callbacks and simply 
        // excuateeach function provided the function exists
        for (int i = 0; i < left_callback_count; i++) {
            if (left_callbacks[i] != nullptr) {
                left_callbacks[i](state);
            }
        }
    }



    void init(){ 
        // we set  up the  buttons, this  function needs to 
        // be excuated at the start to set up the pins feel 
        // free to edit the button  pins before running the
        // init 

        pinMode (button_enter_pin, INPUT_PULLUP); // we use the pull up risistor inside the ardino so less componenst on pcb
        pinMode (button_up_pin, INPUT_PULLUP);
        pinMode (button_down_pin, INPUT_PULLUP);
        pinMode (button_right_pin, INPUT_PULLUP);
        pinMode (button_left_pin, INPUT_PULLUP);
    }


    void loop(){
        // this function should be excuated inside the loop function

        // this will  check the buttons  weather it  is up  down right or left
        // each button will get its own event 0 means it is relased and 1 means 
        // it is pressed


        // this will work by reading the current state comparing it by 


        int button_enter_current_state = digitalRead(button_enter_pin);
        int button_up_current_state = digitalRead(button_up_pin);
        int button_down_current_state = digitalRead(button_down_pin);
        int button_right_current_state = digitalRead(button_right_pin);
        int button_left_current_state = digitalRead(button_left_pin);
        
        if (button_enter_last_state != button_enter_current_state){
            button_enter_last_state = button_enter_current_state;
            if (button_event_cooldown_passed())
                on_button_enter_event(button_enter_current_state);
        }
        if (button_up_last_state != button_up_current_state){
            button_up_last_state = button_up_current_state;
            if (button_event_cooldown_passed())
                on_button_up_event(button_up_current_state);
        }
        if (button_down_last_state != button_down_current_state){
            button_down_last_state = button_down_current_state;
            if (button_event_cooldown_passed())
                on_button_down_event(button_down_current_state);
        }
        if (button_right_last_state != button_right_current_state){
            button_right_last_state = button_right_current_state;
            if (button_event_cooldown_passed())
                on_button_right_event(button_right_current_state);
        }
        if (button_left_last_state != button_left_current_state){
            button_left_last_state = button_left_current_state;
            if (button_event_cooldown_passed())
                on_button_left_event(button_left_current_state);
        }
    }








    // register functions allows you to append a function for the event
    // so your function can  be excuated when the function is triggered

    void register_enter_button_callback(ButtonCallback callback) {
        if (enter_callback_count < MAX_CALLBACKS) {
            enter_callbacks[enter_callback_count++] = callback;
        }
    }

    void register_up_button_callback(ButtonCallback callback) {
        if (up_callback_count < MAX_CALLBACKS) {
            up_callbacks[up_callback_count++] = callback;
        }
    }

    void register_down_button_callback(ButtonCallback callback) {
        if (down_callback_count < MAX_CALLBACKS) {
            down_callbacks[down_callback_count++] = callback;
        }
    }

    void register_right_button_callback(ButtonCallback callback) {
        if (right_callback_count < MAX_CALLBACKS) {
            right_callbacks[right_callback_count++] = callback;
        }
    }

    void register_left_button_callback(ButtonCallback callback) {
        if (left_callback_count < MAX_CALLBACKS) {
            left_callbacks[left_callback_count++] = callback;
        }
    }


}