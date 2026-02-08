#ifndef FM_RADIO_H
#define FM_RADIO_H

#include <Arduino.h>




namespace FM_Radio
{

    extern float current_channel;


    
    void init();
    void loop();

    void set_channel(int channel);
    void set_volume(int volume);


    int get_current_channel();
    int get_current_volume();
}

#endif
