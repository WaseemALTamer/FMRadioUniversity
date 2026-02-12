// this is a base input class, this class will not access any of the other
// files, other files will include this file this file doesn't need to include
// any other file in this project

#ifndef HUMIDITY_H // ensures that the file doesn't get imported again
#define HUMIDITY_H

#include <Arduino.h>

namespace Environment {


    typedef void (*EnvironmentCallback)(float temperature, float humidity);


    void init();


    void loop();


    void register_environment_callback(EnvironmentCallback callback);

}

#endif
