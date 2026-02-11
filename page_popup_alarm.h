#ifndef PAGE_POPUP_ALARM_H
#define PAGE_POPUP_ALARM_H

#include "structure.h"
#include "clock.h"
#include "fm_radio.h"




namespace PagePopupAlarm {

    // The popup page instance
    extern Page page;

    // Initialize the popup alarm page and register callbacks
    void init();

    // Callback called by the clock module when the alarm triggers
    void on_alarm_event();

}

#endif
