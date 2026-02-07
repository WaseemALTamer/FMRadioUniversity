#include "encoder.h"
#include "buttons.h"
#include "infrared.h"
#include "structure.h"
#include "ultrasound.h"
#include "clock.h"
#include "lcd_I2C.h"
#include "page_manager.h"





void setup() {
    // etner point on startup only

    Serial.begin(9600);

    Buttons::init();
    Infrared::init();
    Clock::init();
    Ultrasound::init();
    Encoder::init();
    Lcd_I2C::init(); // at home am using the LCD_I2C because thats what i got
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
    Lcd_I2C::loop(); 
}
