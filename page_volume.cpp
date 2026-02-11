#include "fm_radio.h"
#include "structure.h"



namespace PageVolume{


    Page page;

    void volume_apply(){

        char *buf = page.value; // for simplisty
        if (!isdigit((unsigned char)buf[0]) || !isdigit((unsigned char)buf[1])){
            // invalid input ignore or handle error this
            // error should not  occure unless something
            // goes really really wrong
            return;
        }

        // convert two ASCII digits to integer
        int volume = (buf[0] - '0') * 10 + (buf[1] - '0');

        // we double check the numbers just in case even though the clock already
        // checks them for us but just in case something goes wrong
        if (volume < 0) volume = 0;
        if (volume > 15) volume = 15;

        // apply the volume
        FM_Radio::set_volume(volume);

    }






    void init(){

        size_t value_size = sizeof(page.value); // get the size of the string array
        size_t title_size = sizeof(page.title); // get the size of the string array


        strncpy(page.title,  "< VOLUME(1-15) >", title_size);
        snprintf(page.value, value_size, "%02d              ", FM_Radio::get_current_volume());

        page.value[value_size - 1] = "\0"; // add the terminator

        page.is_editable = true;
        page.apply_function = volume_apply;
    }
}