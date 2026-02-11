#ifndef PAGE_VOLUME_H
#define PAGE_VOLUME_H

#include "structure.h"
#include "fm_radio.h"

namespace PageVolume {

    // The page instance owned by this module
    extern Page page;

    // Initialize the volume page
    void init();

    // Apply function (called when user confirms edits)
    void volume_apply();

}

#endif // PAGE_VOLUME_H
