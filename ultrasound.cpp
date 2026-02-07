// this is a base input class, this class  will not  access any  of the other
// files, other files will include this file this file doesnt need to include
// any other file in this project


// i estimated this file to take about 2% of the arduino memeory




#include <Arduino.h>





namespace Ultrasound{




    const int trig_pin = 3;
    const int eco_pin = 2;


    // this will be used as  a refrence  for how  long  we need to  keep the  trig pin
    // on HIGH, the duration is a minmal pulse but  due to  the  arduino time accuracy
    // we can see 11ms more offten which shouldnt be a problem but just be aware of it
    // just in case it causes errors later on we  can come back  and check  if this is
    // the main issue
    const unsigned long trig_pulse_duration_us = 10; // 10 µs pulse



    // trig measurements
    bool is_trig_active = false; // checks if the trig pin is on high and we are activally using it
    unsigned long trig_start_time = 0; // keeps a time stamp of when the trig pin is set to high and when we started using it 



    // echo measurements
    bool is_measuring_eco = false; // this will be used to tell us if the eco is getting measured
    unsigned long echo_start_time_us = 0; // this will be used as a time stamp when the eco gets to high this value is in micro seconds

    const unsigned long echo_timeout_us = 30000;    // incase the eco pin gets stuck we can reverse it and make it
                                                    // work again 


    // minimum interval between  measurements  this  code ensures that
    // give the ultrasound sensor enough time between each measurement
    const unsigned long min_measuring_intervel_ms = 60; // this value is in milliseconds
    unsigned long last_measurement_time = 0;





    typedef void (*UltrasoundCallback)(float distance);

    const int MAX_CALLBACKS = 5; // each array can only hold 5 callbacks if you try to add 
                                 // more than 5 callbacks then what  comes after 5 will be
                                 // ignored

    UltrasoundCallback callbacks[MAX_CALLBACKS];
    int callbacks_count = 0;




    void on_ultrasound_event(float distance) {      
        for (int i = 0; i < callbacks_count; i++) {
            if (callbacks[i] != nullptr) {
                callbacks[i](distance);
            }
        }
    }





    void init() {
        pinMode(trig_pin, OUTPUT);
        pinMode(eco_pin, INPUT);


        digitalWrite(trig_pin, LOW);    // set the trig pin to low, this is  crusial since we need
                                        // to go from low to high stay in high for 10micro seconds
                                        // and then go back low which what triggers the 
    }



    void loop() {
        unsigned long now_micros = micros();
        unsigned long now_millis = millis();

        // trig pulse start
        if (!is_trig_active && (now_millis - last_measurement_time >= min_measuring_intervel_ms)) {
            digitalWrite(trig_pin, HIGH);
            trig_start_time = now_micros; // store the time stamp
            is_trig_active = true; // tell the rest of the code that trig is active
        }

        // end trig pulse after 10 µs
        if (is_trig_active && (now_micros - trig_start_time >= trig_pulse_duration_us)) {
            digitalWrite(trig_pin, LOW);
            is_trig_active = false;
        }

        // echo measurment starts here


        int echo_current_state = digitalRead(eco_pin); // measure the current eco value

        // rising edge detected -> start measuring
        if (echo_current_state == HIGH && !is_measuring_eco) {
            echo_start_time_us = now_micros; // store the time stamb for the eco
            is_measuring_eco = true; // tell the rest of the code that eco measuring is active
        }


        // If echo stuck HIGH too long, abort measurement this is electrical issue most likely
        // but just to be safe i wrote this code
        if (is_measuring_eco && (now_micros - echo_start_time_us > echo_timeout_us)) {
            is_measuring_eco = false;
            last_measurement_time = now_millis; // allow next measurement
        }



        // falling edge detected -> measurement complete
        if (echo_current_state == LOW && is_measuring_eco) {
            unsigned long eco_pulse_duration = now_micros - echo_start_time_us; // calculates how long the eco pin has been high for
            is_measuring_eco = false; // tell the rest of the code we are not measuring anymore
            last_measurement_time = now_millis; // store the last measurement time stamp

            // convert pulse width to distance cm
            float distance_cm = (eco_pulse_duration * 0.0343) / 2.0; // this uses the speed of sound and calculate how long the singal
                                                                    // took to travel there and back hence why it is devided by 2
            
            // the distance is in cm, the datasheet tells us that it is
            // 0.3mm accurate for a range between 2cm to 4m though note
            // that the arduino will add an overhead and it will not be
            // as accurate as you think it would be

            // we will filter the nosie now

            //if (distance_cm > 400){ 
                // more than 400cm is inaccurate and should not trigger an
                // event, as the  event will  be unrealiable passing noise
                // to upper layers is dangerous for our architecture 
                //return;
            //}
            

            // there is no need to filter by time we already do that when
            // we calculate the interval
            on_ultrasound_event(distance_cm);
        }

    }


    void register_ultrasound_callback(UltrasoundCallback callback) {
        if (callbacks_count < MAX_CALLBACKS) {
            callbacks[callbacks_count++] = callback;
        }
    }

}