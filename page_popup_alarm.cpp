#include "clock.h"
#include "structure.h"
#include "fm_radio.h"





namespace PagePopupAlarm{


    Page page;

    void on_alarm_event(){

            Clock::reset_alarm(); // we reset the alarm so it  doesnt retrigger later on 
                                // reboot as the clock module will rememeber its state


            // because i want the alarm to make sound as well am going
            // to set the  volume to max  for the FM_Radio and them am
            // going to a static only channel 

            FM_Radio::set_volume(15); // we set it to max
            FM_Radio::set_channel(FM_Radio::current_channel); // set the current channel remember current channel
                                                            // is always there as the 

            // note if you miss your alarm the system will tell you
            // that the alarm went of on boot, we  want that  to be
            // honest, not a bug that a feature



            page.show_page = true;


            // outdated code
            // make both buttons lead to the page that you where on
            //alarm_popup_page.next_page = current_page;
            //alarm_popup_page.prev_page = current_page;

            
            //display_page(&alarm_popup_page); // we now display the popup page
        }


    void init(){

        size_t title_size = sizeof(page.title); // get the size of the string array
        size_t value_size = sizeof(page.value); // get the size of the string array

        strncpy(page.title, "< WAKEY  WAKEY >\0", title_size);
        strncpy(page.value, "TIME FOR SCHOOL\0", value_size);
        
        page.is_popup = true;
        
        Clock::register_alarm_callback(on_alarm_event);


    }
}