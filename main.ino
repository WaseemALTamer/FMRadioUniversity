#include "encoder.h"
#include "buttons.h"
#include "infrared.h"
#include "structure.h"
#include "ultrasound.h"
#include "clock.h"
#include "lcd_I2C.h"
#include "page_manager.h"





void setup() {
    Serial.begin(9600);


    Buttons::init();
    Infrared::init();
    Clock::init();
    Ultrasound::init();
    Encoder::init();
    Lcd_I2C::init();
    PageManager::init();
}






void loop() {
    Encoder::loop();
    Buttons::loop();
    Infrared::loop();
    Clock::loop();
    Ultrasound::loop();
    Lcd_I2C::loop();
}
