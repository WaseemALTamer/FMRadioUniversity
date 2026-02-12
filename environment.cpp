// this is a base input class, this class  will not  access any  of the other
// files, other files will include this file this file doesnt need to include
// any other file in this project

// i estimate this file to take about 1% of the arduino memeory and the 
// libraries are taking 2%


#include "Libraries/SparkFun/SparkFunHTU21D.h"
#include "Libraries/SparkFun/SparkFunHTU21D.cpp"






namespace Environment{


    float last_temperature = 0;
    float last_humidity = 0;


    HTU21D sensor; // Create an HTU21D object
    int sensor_cooldown_ms = 1000; // we only check the tempreture every second 




    typedef void (*EnvironmentCallback)(float tempreture, float humidity); // create the call back type


    const int MAX_CALLBACKS = 1; // each array can only hold 5 callbacks

    EnvironmentCallback environment_callbacks[MAX_CALLBACKS];
    int environment_callback_count = 0;


    void on_environment_event(float tempreture, float humidity){


        for (int i = 0; i < environment_callback_count; i++) {
            if (environment_callbacks[i] != nullptr) {
                environment_callbacks[i](tempreture,humidity);
            }
        }
    }





    bool sensor_cooldown_passed() {
        // this avoid internal bounce effect for the buttons

        static unsigned long last_event_time = 0;
        unsigned long now = millis();

        if (now - last_event_time < sensor_cooldown_ms) {
            return false; // ignore event
        }

        last_event_time = now;
        return true; // accept event
    }





    void init(){
        sensor.begin(); // initate the humidity sensor

    }



    void loop(){

        if (!sensor_cooldown_passed()) return; // we return if the cool down has not passed


        // check the humidity and check if it changed
        float current_tempreture = sensor.readTemperature();
        float current_humidity = sensor.readHumidity();

        if (current_tempreture != last_temperature || // check tempreture
            last_humidity != current_humidity)        // check humidity
        {

            // yes i made them into one event am low on memeory other 
            // wise i would have made them into two event

            last_temperature = current_tempreture;
            last_humidity = current_humidity;

            on_environment_event(current_tempreture, current_humidity);
        }


    }



    void register_environment_callback(EnvironmentCallback callback) {
        if (environment_callback_count < MAX_CALLBACKS) {
            environment_callbacks[environment_callback_count++] = callback;
        }
    }


}
