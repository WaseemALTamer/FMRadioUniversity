// this is the intermeadate stage where it takes the base layer and
// connected it  to the  output  laye, there is  no loop layer this
// only works when an event occures


#include "encoder.h"
#include "buttons.h"
#include "infrared.h"
#include "ultrasound.h"
#include "clock.h"
#include "lcd_I2C.h"
#include "structure.h"





#define LcdDsiplay Lcd_I2C // i call it LcdDisplay so when i import the Lcd without _I2C i dont have
                           // to go through the whole code  just to change  one var  name to another



// PLEASE READ __important__ 
// we dont not update the page if  we are editing it please make sure
// thats the case i didnt pre build it  into the code architecture so
// make sure you do it


namespace PageManager{


    
    Page* current_page; // this will be used to track the current page displayed


    Page time_page;
    Page alarm_time_page;
    Page alarm_popup_page; // this is not accessable only when the clock triggers it
    Page ultrasuond_sensor_page;
    Page volume_page;
    Page frequency_channel_page;
    Page humidity_page;






    void normalize_string_buffer(char* buffer, size_t size) {
        // this function will loop thruogh the array remove all the terminators that
        // you have and it will add it right at the end

        if (size == 0) return; 

        for (size_t i = 0; i < size - 1; i++) {
            if (buffer[i] == '\0') {
                buffer[i] = ' ';
            }
        }

        buffer[size - 1] = '\0';
    }



    void display_page(Page* page){

        // if the current_page is the same as the page then the swap 
        // leads to nothing and this is what we want 

        current_page->is_visiable = false; // tells the other code the old page is not visiable
        page->is_visiable = true; // makes the new page visiable
        current_page = page; // sets the current page as current page

        LcdDsiplay::show(
            page->title,
            page->value
        );

        // place the cursor where it should be
        LcdDsiplay::set_cursor(current_page->cursor_col, current_page->cursor_row); 

    }



    void update_page(Page* page){

        // this function will go from current page to the right page
        // this will also set the  cursor for you at the correct pos

        if (page->is_visiable){
            // we check if the page is visiable to the user and also
            // if the page is not getting edited
            display_page(page);
        }
        
    }


    void on_enter_button_event(int state){

        if (current_page == nullptr) return; // redundency

        if (state){ // mouse release

            if(!current_page->is_editable) return; // this will not let you edit the pages that 
                                                   // are not editable

            current_page->is_editing = !current_page->is_editing; // flip the state
            if (current_page->is_editing){
                // if the it is getting edited


                LcdDsiplay::cursor_on(); // turn on the cursor
                //LcdDsiplay::blink_on(); // this will blink the cursor

                LcdDsiplay::set_cursor(current_page->cursor_col, current_page->cursor_row); // move the cursor to where it belongs
            }
            if (!current_page->is_editing){
                // if it is not getting edited 

                LcdDsiplay::cursor_off();

                // we check if the pointer is null before we excuate it
                // some pages will not have an apply  function be aware
                // of that please 
                if (current_page->apply_function != nullptr){
                    
                    current_page->apply_function(*current_page);
                }
            }
        }

    }

    void on_right_button_event(int state){

        // dont set the cursor location your self

        if (current_page == nullptr) return; // redundency

        if (state){ // mouse release
            if (!current_page->is_editing){
                display_page(current_page->next_page);
            }

            if (current_page->is_editing){
                current_page->cursor_col += 1;

                if (current_page->cursor_col >= 16)
                    current_page->cursor_col = 15;

                display_page(current_page); // this will update the cursor location for us
            }
        }

        
    }


    void on_left_button_event(int state){

        // dont set the cursor location your self

        if (current_page == nullptr) return; // redundency

        if (state){ // mouse release
            if (!current_page->is_editing){
                display_page(current_page->prev_page);
            }

            if (current_page->is_editing){
                current_page->cursor_col -= 1;

                if (current_page->cursor_col < 0)
                    current_page->cursor_col = 0;

                display_page(current_page);// this will update the cursor location for us
            }
        }


    }


    void on_encoder_event(int delta){

        // checks if the page exist this not nessasary but for
        // redundency please keep it
        if (current_page == nullptr) return;

        // encoder is  only used if  the  page is being edited
        // please respect  that rule dont try make the encoder
        // change something that  where you are not in editing
        // a page yes  that  goes for the volume  as  well and
        // any you should not edit the function of the encoder
        // unless its base function is not working, not to add
        // something new
        if (!current_page->is_editing) return;

        // get the current character at the cursor
        char &digit_under_cursor = current_page->value[current_page->cursor_col]; // we access it by getting its pointer

        // check if its a digit
        if (digit_under_cursor >= '0' && digit_under_cursor <= '9') {
            // convert char to int
            int num = digit_under_cursor - '0';

            // add delta and clamp between 0 and 9
            num += delta;
            if (num < 0) num = 0;
            if (num > 9) num = 9;

            // convert back to char and store it
            digit_under_cursor = '0' + num;
        }

        update_page(current_page); // we update the current page so we see the change

    }





    void on_time_event(int seconds, int minutes, int hours){
        // this will be triggered by the event from the clock module

        if (time_page.is_editing){ 
            // again we dont not update the page if  we are editing it please make 
            // sure thats the case i didnt pre build it into the code architecture 
            // so make sure you do it
            return;
        }

        size_t value_buffer_size = sizeof(time_page.value); // get the size of the string array


        memset(time_page.value, ' ', value_buffer_size); // fill entire buffer with spaces
        snprintf(time_page.value, 
            value_buffer_size, 
            "%02d:%02d:%02d", 
            hours, 
            minutes, 
            seconds
        ); // write time at the start


        // remove all the terminators and add it at the end
        normalize_string_buffer(time_page.value, value_buffer_size);

        update_page(&time_page); // pass the page to the updator
    }


    void page_apply_time(){ 
        // this function is for the time page, it will set the
        // current time to something else  based on the values
        // you provided in  the page .value  string array this
        // this function  will convert  the  string  buffer to
        // relevent data hh:mm:ss

        // this function will not set the value is  your value
        // was invalid time

        int hours = 0, minutes = 0, seconds = 0;


        const char* buf = time_page.value; // am using buf for simplisty

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


    void alarm_apply_time(){ 
        // same funcality as before but this one sets the alarm

        int hours = 0, minutes = 0, seconds = 0;


        const char* buf = alarm_time_page.value; // am using buf for simplisty

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
                size_t value_size = sizeof(alarm_time_page.value);

                // invalid time dont set and re display the previouse correct time
                strncpy(alarm_time_page.value, "                \0", value_size);
                snprintf(alarm_time_page.value, 
                    value_size, 
                    "%02d:%02d", 
                    Clock::get_alarm_hour(), 
                    Clock::get_alarm_mintues()
                ); // write time when we start

                normalize_string_buffer(alarm_time_page.value, value_size); // normlise the string buffer

                // now we can update the screen for the user to see the correct time
                update_page(current_page);

                return;
            }
        }
        else {
            // invalid format dont set
        }
    }




    void on_ultrasound_distance_event(float distance){

        if (ultrasuond_sensor_page.is_editing){ 
            // this if statment is for redundency we dont need it since 
            // this page is not editable
            return;
        }

        int whole = (int)distance;
        int fraction = (int)((distance - whole) * 10);

        int value_buffer_size = sizeof(ultrasuond_sensor_page.value);

        // fill the buffer with white space
        for (int i = 0; i < value_buffer_size - 1; i++) {
            ultrasuond_sensor_page.value[i] = ' ';
        }

        // add the ultra sound data
        snprintf(
            ultrasuond_sensor_page.value, 
            value_buffer_size, 
            "%d.%d", 
            whole, 
            fraction
        );

        // remove the terminator that the snprinf leaves and add it at the end
        normalize_string_buffer(ultrasuond_sensor_page.value, value_buffer_size);
        

        // add the units
        ultrasuond_sensor_page.value[value_buffer_size - 3] = 'c'; 
        ultrasuond_sensor_page.value[value_buffer_size - 2] = 'm';

        // update the page
        update_page(&ultrasuond_sensor_page);
    }


    void on_alarm_event(){

        Clock::reset_alarm(); // we reset the alarm so it  doesnt retrigger later on 
                              // reboot as the clock module will rememeber its state


        // note if you miss your alarm the system will tell you
        // that the alarm went of on boot, we  want that  to be
        // honest, not a bug that a feature

        if (current_page->is_editing){
            // stop editing if we  are editing  the page  we are on
            // note we  dont  apply  the changes  this will  either
            // be over writen if it  runs through  an  event system
            // or will stay the same until they apply it them selfs
            current_page->is_editing = false;
        }

        // make both buttons lead to the page that you where on
        alarm_popup_page.next_page = current_page;
        alarm_popup_page.prev_page = current_page;

        display_page(&alarm_popup_page); // we now display the popup page
    }




    void init(){

        // attach the button functions
        Buttons::register_enter_button_callback(on_enter_button_event);
        Buttons::register_right_button_callback(on_right_button_event);
        Buttons::register_left_button_callback(on_left_button_event);

        // attach encoder function
        Encoder::register_encoder_callback(on_encoder_event);


        // do not set the cursor_col, and cursor_row for the pages i spent
        // 42 mintues debugging it to know why the cursor was top left and
        // it turned out i was  over writing  what was  getting intiatised
        // from the page 


        // we dont need to caulcate them again all the pages have the
        // same structure and buffer size most importantly
        size_t title_size = sizeof(time_page.title); // get the size of the string array
        size_t value_size = sizeof(time_page.value); // get the size of the string array

        //________________________<time page>________________________   
        strncpy(time_page.title, "<     TIME     >\0", title_size);
        strncpy(time_page.value, "                \0", value_size);
        time_page.is_visiable = false;
        time_page.is_editable = true;
        time_page.is_editing = false;
        time_page.apply_function = page_apply_time; // store the apply function
        Clock::register_time_callback(on_time_event); // regester the function for the time module
                                                       // we will update  the values right there in
                                                       // the function


        //________________________<alarm time page>________________________
        strncpy(alarm_time_page.title, "<  ALARM TIME  >\0", title_size);

        // we need to set the time on start we get it from the clock
        
        strncpy(alarm_time_page.value, "                \0", value_size);
        snprintf(alarm_time_page.value, 
            value_size, 
            "%02d:%02d", 
            Clock::get_alarm_hour(), 
            Clock::get_alarm_mintues()
        ); // write time when we start

        normalize_string_buffer(alarm_time_page.value, value_size); // normlise the string buffer

        alarm_time_page.is_visiable = false;
        alarm_time_page.is_editable = true;
        alarm_time_page.is_editing = false;

        alarm_time_page.apply_function = alarm_apply_time;


        // this page doesnt operate on event there is no event that triggers it








        //________________________<ultrasound sensor page>________________________
        strncpy(ultrasuond_sensor_page.title, "<  US SENSOR   >\0", title_size);
        strncpy(ultrasuond_sensor_page.value, "                \0", value_size);
        ultrasuond_sensor_page.is_visiable = false;
        ultrasuond_sensor_page.is_editable = false;
        ultrasuond_sensor_page.is_editing = false;
        Ultrasound::register_ultrasound_callback(on_ultrasound_distance_event);





        //________________________<Alarm Pop up>________________________
        strncpy(alarm_popup_page.title, "< WAKEY  WAKEY >\0", title_size);
        strncpy(alarm_popup_page.value, "TIME FOR SCHOOL\0", value_size);
        alarm_popup_page.is_visiable = false;
        alarm_popup_page.is_editable = false;
        alarm_popup_page.is_editing = false;

        Clock::register_alarm_callback(on_alarm_event);
        
        // this page doesnt link to any but it will link back to the page that
        //  you where on before when it is time for the alarm



        //________________________<Pages Connections>________________________


        //now we attach the pages togather
        time_page.next_page = &alarm_time_page;
        time_page.prev_page = &ultrasuond_sensor_page;

        alarm_time_page.next_page = &ultrasuond_sensor_page;
        alarm_time_page.prev_page = &time_page;

        ultrasuond_sensor_page.next_page = &time_page;
        ultrasuond_sensor_page.prev_page = &alarm_time_page;




        display_page(&time_page); // we pass the pointer to the function to display 
                                  // the starter page

    }

}