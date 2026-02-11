#ifndef PAGE_ULTRASOUND_H
#define PAGE_ULTRASOUND_H

#include "structure.h"
#include "ultrasound.h"

namespace PageUltrasound {

    // The page instance owned by this module
    extern Page page;

    // Initialize the ultrasound page
    void init();

    // Callback used by the ultrasound module to report distance
    void on_ultrasound_distance_event(float distance);

}

#endif // PAGE_ULTRASOUND_H
