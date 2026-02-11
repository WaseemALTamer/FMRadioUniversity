#ifndef PAGE_CHANNEL_H
#define PAGE_CHANNEL_H

#include "structure.h"
#include "fm_radio.h"

namespace PageChannel {

    // The page instance owned by this module
    extern Page page;

    // Initialize the channel page
    void init();

    // Apply function (called when user confirms edits)
    void frequency_channel_apply();

}

#endif
