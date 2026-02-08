#include "encoder.h"
#include "buttons.h"
#include "infrared.h"
#include "structure.h"
#include "ultrasound.h"
#include "clock.h"
#include "lcd_I2C.h"
#include "page_manager.h"





#define LcdDsiplay Lcd_I2C // i call it LcdDisplay so when i import the Lcd without _I2C i dont have
                           // to go through the whole code  just to change  one var  name to another




void setup() {
    // etner point on startup only

    Serial.begin(9600);

    Buttons::init();
    Infrared::init();
    Clock::init();
    Ultrasound::init();
    Encoder::init();
    LcdDsiplay::init(); // at home am using the LCD_I2C because thats what i got
                        // in lab we have the lcd withuot the I2C bus module
    PageManager::init();

}




void loop() {
    // main loop enter point

    Encoder::loop();
    Buttons::loop();
    Infrared::loop();
    Clock::loop();
    Ultrasound::loop();
    LcdDsiplay::loop(); 
}
