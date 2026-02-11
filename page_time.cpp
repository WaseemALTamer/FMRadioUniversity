



#include "structure.h"
#include "clock.h"












namespace PageTime{

    Page page;



    void page_apply_time(){ 
        // this function is for the time page, it will set the
        // current time to something else  based on the values
        // you provided in  the page .value  string array this
        // this function  will convert  the  string  buffer to
        // relevent data hh:mm:ss

        // this function will not set the value is  your value
        // was invalid time

        int hours = 0, minutes = 0, seconds = 0;


        const char* buf = page.value; // am using buf for simplisty

        // simple validation expect format "hh:mm:ss"
        // we will check for : : values just in case

        if (buf[2] == ':' && buf[5] == ':') {
            hours   = (buf[0] - '0') * 10 + (buf[1] - '0');
            minutes = (buf[3] - '0') * 10 + (buf[4] - '0');
            seconds = (buf[6] - '0') * 10 + (buf[7] - '0');

            if (hours >= 0 && hours < 24 &&
                minutes >= 0 && minutes < 60 &&
                seconds >= 0 && seconds < 60) 
            {
                // now hours minutes seconds are ready as integers

                Clock::set_time(
                    hours,
                    minutes,
                    seconds
                );
            }
            else {
                // invalid time dont set
                return;
            }
        }
        else {
            // invalid format dont set
        }
    }

    void on_time_event(int seconds, int minutes, int hours){
        // this will be triggered by the event from the clock module

        if (page.is_editing){ 
            // again we dont not update the page if  we are editing it please make 
            // sure thats the case i didnt pre build it into the code architecture 
            // so make sure you do it
            return;
        }

        size_t value_buffer_size = sizeof(page.value); // get the size of the string array


        memset(page.value, ' ', value_buffer_size); // fill entire buffer with spaces
        snprintf(page.value, 
            value_buffer_size, 
            "%02d:%02d:%02d        ", 
            hours, 
            minutes, 
            seconds
        ); // write time at the start

        page.schedul_update = true;
        //update_page(&time_page); // pass the page to the updator <outdated>
    }




    void init(){ // this initate the page it self
        // same structure and buffer size most importantly
        size_t title_size = sizeof(page.title); // get the size of the string array
        size_t value_size = sizeof(page.value); // get the size of the string array

        //________________________<time page>________________________   
        strncpy(page.title, "<     TIME     >", title_size);
        page.title[title_size - 1] = '\0'; // add terminator since strncpy doesnt garntee it
        strncpy(page.value, "                ", value_size);
        page.value[value_size - 1] = '\0'; // add terminator since strncpy doesnt garntee it


        page.is_editable = true;
        page.apply_function = page_apply_time; // store the apply function
        Clock::register_time_callback(on_time_event); // regester the function for the time module
                                                    // we will update  the values right there in
                                                    // the function

    }


}
