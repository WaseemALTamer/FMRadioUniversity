#ifndef PAGE_TIME_H
#define PAGE_TIME_H

#include "structure.h"
#include "clock.h"




namespace PageTime {

    // the page instance owned by this module
    extern Page page;

    // initialize the page and register callbacks
    void init();

    // apply function (called when user applies edits)
    void page_apply_time();

    // clock callback
    void on_time_event(int seconds, int minutes, int hours);

}

#endif 
