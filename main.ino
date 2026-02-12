// base layer
#include "encoder.h"
#include "buttons.h"
#include "infrared.h"
#include "fm_radio.h"
#include "ultrasound.h"
#include "clock.h"
#include "environment.h"


// intermediate layer
#include "page_manager.h"
#include "structure.h"


// output layer
#include "lcd_I2C.h"





#define LcdDsiplay Lcd_I2C // i call it LcdDisplay so when i import the Lcd without _I2C i dont have
                           // to go through the whole code  just to change  one var  name to another






void setup() {
    // etner point on startup only

    Serial.begin(9600);



    // base layer
    Buttons::init();
    Infrared::init();
    Clock::init();
    Ultrasound::init();
    Encoder::init();
    Environment::init();
    FM_Radio::init();
    
    

    // intermediate layer
    PageManager::init();



    // output layer
    LcdDsiplay::init(); // at home am using the LCD_I2C because thats what i got
                        // in lab we have the lcd withuot the I2C bus module

}




void loop() {
    // main loop enter point





    // base layer
    Encoder::loop();
    Buttons::loop();
    Infrared::loop();
    Clock::loop();
    Ultrasound::loop();
    Environment::loop();

    FM_Radio::loop(); // this does nothing right now but later it might do something


    // intermediate layer
    PageManager::loop();


    // ouput layer
    LcdDsiplay::loop(); 
}
