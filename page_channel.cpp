#include "fm_radio.h"
#include "structure.h"




namespace PageChannel{



    Page page;

    void frequency_channel_apply(){
        
        char *buf = page.value; // for simplisity

        // double check the chars just in case again if this leads to return
        // we got bigger problems at our hand
        for (int i = 0; i < 4; i++){
            if (!isdigit((unsigned char)buf[i])){
                return;
            }
        }

        // convert four ASCII digits to integer
        int freq10 = 0;
        freq10 += (buf[0] - '0') * 1000;
        freq10 += (buf[1] - '0') * 100;
        freq10 += (buf[2] - '0') * 10;
        freq10 += (buf[3] - '0');


        // again just in case we clamp the channel 
        if (freq10 < 875) freq10 = 875;
        if (freq10 > 1080) freq10 = 1080;

        // we send the channel to the function so it gets set
        FM_Radio::set_channel(freq10);

    }



    void init(){

        size_t value_size = sizeof(page.value); // get the size of the string array
        size_t title_size = sizeof(page.title); // get the size of the string array

        strncpy(page.title, "<CHANNL(MHZx10)>", title_size);
        snprintf(page.value, value_size ,"%04d            ", FM_Radio::get_current_channel());
        page.value[value_size -1] = "\0"; // add the terminator because of snprintf

        page.is_editable = true;
        page.apply_function = frequency_channel_apply;
    }

}