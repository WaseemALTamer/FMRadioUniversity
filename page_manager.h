#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

// Include necessary dependencies
#include "encoder.h"
#include "buttons.h"
#include "infrared.h"
#include "ultrasound.h"
#include "clock.h"
#include "lcd_I2C.h"
#include "structure.h"


namespace PageManager {

    // rememeber this is the intermediate stage this  is where all the
    // logic lives we dont expose any local function anywhere and also
    // this function only needs  to be  initate, initate  it after you
    // initate all the other modules, this doesnt have a loop function
    // exposed this will only live on events  
    
    void init();

}

#endif