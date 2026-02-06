#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>


struct Page;  // this doesnt yet create the structure but it does 
              // tell the next line to know it will exist

typedef void (*ApplyFunction)(Page& page);  // function to excuate when you  press apply this function
                                            // requires the page pointer  that it  is set to so it can 
                                            // access the variables inside

                                            
                                            // example on how to call the function:
                                            // page->apply_function(*page)
                                            // this line of code will run the function  it will access
                                            // apply function from the  page it  will excuate it while
                                            // passing the  


struct Page {

    // the buffers  are going  to be  used to flash them on the lcd display
    // the display  runs  at certain  fps with a schedule  system to  flash
    // the latest buffers, those two char buffers are not to be reallocated
    // reallocate while it is in schedule and the  output system  breaks be
    // aware if you reallocate the buffers  i  will find  you and  only god
    // know what will happen next 


    // do not change the 17 to 16, yes i understand  that the  lcd  only contain
    // 16 visiable bytes per layer but also the string  char require you to have
    // have a ternminator at the end <\0> so this actually ensure the 16th digit
    // or letter or whatever is actually displayed on the lcd

    char title[17];   // e.g. "Time", "Volume", "Frequency" layer one of the lcd
    char value[17];   // e.g. "12:34", "5", "101.1"         layer two of the lcd




    bool is_visiable = false; // this will tell us if the page is visiaible 

    bool is_editable = true; // this checks if the page is editable and you
                             // can  edit  the values  make sure  that  you
                             // provide apply_function and set this to true
                             // to avoid any errors


    bool is_editiing = false; // this will tell us if we are editing the page

    // these where the cursor will be when you edit the values
    int cursor_col = 0; // the x coor on the layer, 0 is all the way left and 16 is all the way right
    int cursor_row = 0; // top lcd layer is 0, bottom lcd layer is 1


    ApplyFunction apply_function;

    Page* next_page;
    Page* prev_page;
};

#endif // PAGE_H





