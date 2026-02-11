#ifndef PAGE_ALARM_H
#define PAGE_ALARM_H

#include "structure.h"
#include "clock.h"




namespace PageAlarm {

    // The page instance owned by this module
    extern Page page;

    // Initialize the alarm page
    void init();

    // Apply function (called when user confirms edits)
    void alarm_apply_time();

}

#endif