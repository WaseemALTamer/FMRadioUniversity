// this is a base input class, this class  will not  access any  of the other
// files, other files will include this file this file doesnt need to include
// any other file in this project

// i estimated this  file to take  about 3% of  the arduino memeory
// the memeory usage is not right it should be lower check it later



#include <Arduino.h>
#include "encoder.h"





namespace Encoder {


    // encoder global varables
    int encoder_clock_pin = 10; // Connected to CLK on KY-040
    int encoder_dt_pin = 9; // dt pin
    const unsigned long encoder_cooldown_ms = 30;   // this is the cool down after the encoder has been rotated
                                                    // this will help avoid the encoder internal bounce effect

    int local_last_encoder_clock; // this will be used to detect the change after every step


    typedef void (*EncoderCallback)(int state); // create the call back type


    const int MAX_CALLBACKS = 5; // each array can only hold 5 callbacks if you try to add 
                                 // more than 5 callbacks then what  comes after 5 will be
                                 // ignored

    EncoderCallback callbacks[MAX_CALLBACKS];
    int callbacks_count = 0;


    void on_encoder_event(int delta) {  
        // this is where the event is routed when we detect it
        for (int i = 0; i < callbacks_count; i++) {
            if (callbacks[i] != nullptr) {
                callbacks[i](delta);
            }
        }
    }


    bool encoder_event_cool_down_passed(){
        // this function will filter out the encoer internal boundce
        // and it will also trigger the event so we can code without
        // worry in the upper parts

        static unsigned long last_event_time = 0;
        unsigned long now = millis();

        if (now - last_event_time < encoder_cooldown_ms) {
            return false; // too soon, ignore
        }

        last_event_time = now;
        return true; // accept event
    }


    void init(){
        // encoder
        pinMode(encoder_clock_pin, INPUT);
        pinMode(encoder_dt_pin, INPUT);
        local_last_encoder_clock = (digitalRead(encoder_clock_pin) << 1) | digitalRead(encoder_dt_pin); // store the current state of the encoder

    }


    void loop(){
        // this will check if the encoder state changes if it did run it run it back
        // and detect the change, then map the change to the transitino that we know
        // that are either clockwise or anticlock wise

  
        int current_state = (digitalRead(encoder_clock_pin) << 1) | digitalRead(encoder_dt_pin); // detect the current state



        if (current_state != local_last_encoder_clock) { // check if a change had occured

            // Clockwise we only accpet them if they are in these transitions [00 → 01 → 11 → 10 → 00]
            if ((local_last_encoder_clock == 0b00 && current_state == 0b01) ||
                (local_last_encoder_clock == 0b01 && current_state == 0b11) ||
                (local_last_encoder_clock == 0b11 && current_state == 0b10) ||
                (local_last_encoder_clock == 0b10 && current_state == 0b00)) 
            {
                if (encoder_event_cool_down_passed()) // apply the cool down 
                    on_encoder_event(1); // the filter will decide if to trigger the event
                local_last_encoder_clock = current_state;
            }
            // Counter-clockwise we only accpet them if they are in these transitions [00 → 10 → 11 → 01 → 00]
            else if ((local_last_encoder_clock == 0b00 && current_state == 0b10) ||
                (local_last_encoder_clock == 0b10 && current_state == 0b11) ||
                (local_last_encoder_clock == 0b11 && current_state == 0b01) ||
                (local_last_encoder_clock == 0b01 && current_state == 0b00)) 
            {
                if (encoder_event_cool_down_passed()) // apply the cool down 
                on_encoder_event(-1); // the filter will decide if to trigger the event
                local_last_encoder_clock = current_state;

            }

        }

    }


    void register_encoder_callback(EncoderCallback callback) {
        if (callbacks_count < MAX_CALLBACKS) {
            callbacks[callbacks_count++] = callback;
        }
    }

}