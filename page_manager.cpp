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











namespace PageManager{


    
    Page* current_page; // this will be used to track the current page displayed


    Page time_page;
    Page ultrasuond_sensor_page;




    void display_page(Page* page){

        current_page->is_visiable = false; // tells the other code the old page is not visiable
        page->is_visiable = true; // makes the new page visiable
        current_page = page; // sets the current page as current page

        Lcd_I2C::show(
            page->title,
            page->value
        );

    }



    void update_page(Page* page){
        // this function will update the page we are on
        if (page -> is_visiable){
            display_page(page);
        }
    }


    void on_right_button_event(int state){

        if (state){ // mouse release
            display_page(current_page->next_page);
        }
        
    }


    void on_left_button_event(int state){
        if (state){ // mouse release
            display_page(current_page->prev_page);
        }
    }




    void on_time_event(int seconds, int minutes, int hours){
        // this will be triggered by the event from the clock module

        size_t value_size = sizeof(time_page.value); // get the size of the string array
        
        memset(time_page.value, ' ', value_size); // fill entire buffer with spaces
        snprintf(time_page.value, value_size, "%02d:%02d:%02d", hours, minutes, seconds); // write time at the start
        time_page.value[15] = '\0'; // ensure null-termination

        update_page(&time_page); // pass the page to the updator
    }




    void on_ultrasound_distance_event(float distance){

        memset(ultrasuond_sensor_page.value, ' ', sizeof(ultrasuond_sensor_page.value));

        int whole = (int)distance;
        int fraction = (int)((distance - whole) * 10);

        snprintf(ultrasuond_sensor_page.value,
                sizeof(ultrasuond_sensor_page.value),
                "%d.%d cm", whole, fraction);

        ultrasuond_sensor_page.value[sizeof(ultrasuond_sensor_page.value) - 1] = '\0';

       update_page(&ultrasuond_sensor_page);

    }




    void init(){

        // attach the button functions
        Buttons::register_right_button_callback(on_right_button_event);
        Buttons::register_left_button_callback(on_right_button_event);



        // we dont need to caulcate them again all the pages have the
        // same structure and buffer size most importantly
        size_t title_size = sizeof(time_page.title); // get the size of the string array
        size_t value_size = sizeof(time_page.value); // get the size of the string array

        // <time page>   
        strncpy(time_page.title, "<     TIME     >", title_size);
        time_page.title[title_size - 1] = '\0'; // adds the terminator
        strncpy(time_page.value, "                ", value_size);
        time_page.value[value_size - 1] = '\0'; // adds the terminator
        time_page.is_visiable = false;
        time_page.is_editable = false;
        time_page.is_editiing = false;
        time_page.cursor_col  = 0;
        time_page.cursor_row  = 0;
        Clock::register_time_callback(on_time_event); // regester the function for the time module
                                                       // we will update  the values right there in
                                                       // the function




        // <ultrasound sensor page>
        strncpy(ultrasuond_sensor_page.title, "<  US SENSOR   >", title_size);
        ultrasuond_sensor_page.title[title_size - 1] = '\0'; // adds the terminator
        strncpy(ultrasuond_sensor_page.value, "                ", value_size);
        ultrasuond_sensor_page.value[value_size - 1] = '\0'; // adds the terminator
        ultrasuond_sensor_page.is_visiable = false;
        ultrasuond_sensor_page.is_editable = false;
        ultrasuond_sensor_page.is_editiing = false;
        ultrasuond_sensor_page.cursor_col  = 0;
        ultrasuond_sensor_page.cursor_row  = 0;
        Ultrasound::register_ultrasound_callback(on_ultrasound_distance_event);




        // now we attach the pages togather
        time_page.next_page = &ultrasuond_sensor_page;
        time_page.prev_page = &ultrasuond_sensor_page;

        ultrasuond_sensor_page.next_page = &time_page;
        ultrasuond_sensor_page.prev_page = &time_page;


        display_page(&ultrasuond_sensor_page); // we pass the pointer to the function

    }

}