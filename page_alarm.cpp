#include "clock.h"
#include "structure.h"








namespace PageAlarm{



    Page page;


    void alarm_apply_time(){ 
        // same funcality as before but this one sets the alarm

        int hours = 0, minutes = 0, seconds = 0;


        const char* buf = page.value; // am using buf for simplisty

        // simple validation expect format "hh:mm"
        // we will check for : values just in case

        if (buf[2] == ':') {
            hours   = (buf[0] - '0') * 10 + (buf[1] - '0');
            minutes = (buf[3] - '0') * 10 + (buf[4] - '0');

            if (hours >= 0 && hours < 24 &&
                minutes >= 0 && minutes < 60) 
            {
                // now hours minutes seconds are ready as integers
                Clock::set_alarm(
                    hours,
                    minutes
                );
            }
            else {
                size_t value_size = sizeof(page.value);

                // invalid time dont set and re display the previouse correct time
                strncpy(page.value, "                ", value_size);
                snprintf(page.value, 
                    value_size, 
                    "%02d:%02d            ",
                    Clock::get_alarm_hour(), 
                    Clock::get_alarm_mintues()
                ); // write time when we start
                page.value[value_size - 1] = "\0"; // add the terminator since snprintf doesnt add it for you

                // now we can update the screen for the user to see the correct time

                
                //update_page(current_page); // this is outdated schdual and update instead

                page.schedul_update = true;

                return;
            }
        }
        else {
            // invalid format dont set
        }
    }


    void init(){

        size_t title_size = sizeof(page.title);
        size_t value_size = sizeof(page.value);

        strncpy(page.title, "<  ALARM TIME  >\0", title_size);
        // we need to set the time on start we get it from the clock
        
        
        strncpy(page.value, "                \0", value_size);
        snprintf(page.value, 
            value_size, 
            "%02d:%02d            ", 
            Clock::get_alarm_hour(), 
            Clock::get_alarm_mintues()
        ); // write time when we start
        page.value[value_size - 1] = "\0"; // add the terminator since snprintf doesnt add it for you


        page.is_editable = true;
        page.apply_function = alarm_apply_time;



    }


}






