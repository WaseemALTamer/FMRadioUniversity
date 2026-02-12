// this is the intermeadate stage where it takes the base layer and
// connected it  to the  output  laye, there is  no loop layer this
// only works when an event occures




// this file seems long but the structure is linear it doesnt depend on 
// it self each page has its  own logic  it is  just that we have a lot
// of pages each contain  there own  logic and  i put everything in one
// file for the sake of simplisty but it is  now too  long that happens
// a lot in C/C++ code




#include "encoder.h"
#include "buttons.h"
#include "infrared.h"


#include "fm_radio.h"
#include "ultrasound.h"
#include "clock.h"
#include "lcd_I2C.h"


#include "structure.h"


#include "page_time.h"
#include "page_alarm.h"
#include "page_volume.h"
#include "page_channel.h"
#include "page_us_sensor.h"
#include "page_popup_alarm.h"
#include "page_enviroment.h"


#define LcdDsiplay Lcd_I2C // i call it LcdDisplay so when i import the Lcd without _I2C i dont have
                           // to go through the whole code  just to change  one var  name to another



namespace PageManager{


    
    Page* current_page; // this will be used to track the current page displayed

    // add all the pages here
    Page* pages[] = {
        &PageTime::page,
        &PageAlarm::page,
        &PageVolume::page,
        &PageChannel::page,
        &PageUltrasound::page,
        &PagePopupAlarm::page,
        &PageEnviroment::page
    };

    constexpr int pages_number = sizeof(pages) / sizeof(pages[0]); // calcualte the pages count



    void display_page(Page* page){

        // if the current_page is the same as the page then the swap 
        // leads to nothing and this is what we want 

        if(page->is_popup){
            // if the page is a pop up connect it to the current page

            page->next_page = current_page;
            page->prev_page = current_page;
        }


        current_page->is_visiable = false; // tells the other code the old page is not visiable
        page->is_visiable = true; // makes the new page visiable
        current_page = page; // sets the current page as current page

        LcdDsiplay::show(
            page->title,
            page->value
        );

        // place the cursor where it should be
        LcdDsiplay::set_cursor(current_page->cursor_col, current_page->cursor_row); 

        page->schedul_update = false; // reset the schedual update
        page->show_page = false;
    }



    void update_page(Page* page){

        // this function will go from current page to the right page
        // this will also set the  cursor for you at the correct pos

        if (page->is_visiable){
            // we check if the page is visiable to the user and also
            // if the page is not getting edited
            display_page(page);
        }

        page->schedul_update = false; // reset the schedual update
        
    }


    // this section will contain the core functionality for the 

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


                if (current_page->next_page != nullptr) // check if the pointer exist
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

                if (current_page->prev_page != nullptr) // check if the pointer exist
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


    void on_infrared_event(uint16_t address, uint8_t command){

        Serial.println(command);


        // we simulate the function that we created from before nothing special


        // this is hard coding them this needs to change later on down the line
        // make an map inside the infrared header file or cpp file just get rid
        // of it please

        if (command == 28) on_enter_button_event(1);    // OK button

        if (command == 24) on_encoder_event(1);         // up arrow button
        if (command == 82) on_encoder_event(-1);        // down arrow button
        if (command == 90) on_right_button_event(1);    // right arrow button
        if (command == 8) on_left_button_event(1);      // left arrow button
    }









    void init(){

        // attach the button functions
        Buttons::register_enter_button_callback(on_enter_button_event);
        Buttons::register_right_button_callback(on_right_button_event);
        Buttons::register_left_button_callback(on_left_button_event);

        // attach encoder function
        Encoder::register_encoder_callback(on_encoder_event);


        // attach the infrared function

        Infrared::register_reciver_callback(on_infrared_event);

        // do not set the cursor_col, and cursor_row for the pages i spent
        // 42 mintues debugging it to know why the cursor was top left and
        // it turned out i was  over writing  what was  getting intiatised
        // from the page 


        // we dont need to caulcate them again all the pages have the
        // same structure and buffer size most importantly



        // first lets add all the pages to the array

        

        // intialise pages we do it manually
        PageTime::init();
        PageAlarm::init();
        PageVolume::init();
        PageChannel::init();
        PageUltrasound::init();
        PagePopupAlarm::init();
        PageEnviroment::init();
        


        // page connections we do them manyally

        PageTime::page.prev_page = &PageEnviroment::page;
        PageTime::page.next_page = &PageAlarm::page;
        
        PageAlarm::page.prev_page = &PageTime::page;
        PageAlarm::page.next_page = &PageVolume::page;

        PageVolume::page.prev_page = &PageAlarm::page;
        PageVolume::page.next_page = &PageChannel::page;

        PageChannel::page.prev_page = &PageVolume::page;
        PageChannel::page.next_page = &PageUltrasound::page;

        PageUltrasound::page.prev_page = &PageChannel::page;
        PageUltrasound::page.next_page = &PageEnviroment::page;

        PageEnviroment::page.prev_page = &PageUltrasound::page;
        PageEnviroment::page.next_page = &PageTime::page;

        // note we dont connect the popup page

        display_page(&PageTime::page);  // we pass the pointer to the function to display 
                                        // the starter page

    }



    void loop(){
        // this function is added for the manager to loop through
        // the  page that is  displayed and check  if it requires
        // an update

        for (int i = 0; i < pages_number; ++i) {
            if (pages[i] != nullptr && pages[i]->schedul_update){
                update_page(pages[i]); // we update the page
            }
        }

        for (int i = 0; i < pages_number; ++i) {
            if (pages[i] != nullptr && pages[i]->show_page){
                display_page(pages[i]); // we update the page
            }
        }


    }

}