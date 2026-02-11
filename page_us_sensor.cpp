#include "ultrasound.h"
#include "structure.h"



namespace PageUltrasound{

    Page page;


    void on_ultrasound_distance_event(float distance){

        if (page.is_editing){ 
            // this if statment is for redundency we dont need it since 
            // this page is not editable
            return;
        }

        int whole = (int)distance;
        int fraction = (int)((distance - whole) * 10);

        int value_buffer_size = sizeof(page.value);


        // add the ultra sound data
        snprintf(
            page.value, 
            value_buffer_size, 
            "%d.%d                     ", 
            whole, 
            fraction
        );

        

        // add the units
        page.value[value_buffer_size - 3] = 'c'; 
        page.value[value_buffer_size - 2] = 'm';

        // add ther terminator
        page.value[value_buffer_size - 1] = '\0'; 


        // update the page
        //update_page(&ultrasuond_sensor_page); // outdated
        page.schedul_update = true;
    }



    void init(){
        size_t title_size = sizeof(page.title); // get the size of the string array
        size_t value_size = sizeof(page.value); // get the size of the string array

        strncpy(page.title, "<  US SENSOR   >\0", title_size);
        strncpy(page.value, "                \0", value_size);
        Ultrasound::register_ultrasound_callback(on_ultrasound_distance_event);
    }
}