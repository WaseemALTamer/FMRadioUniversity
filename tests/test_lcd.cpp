#include "encoder.h"
#include "buttons.h"
#include "infrared.h"
#include "structure.h"
#include "ultrasound.h"
#include "clock.h"
#include "lcd_I2C.h"
#include "page_manager.h"

#include "Libraries/SparkFun/SparkFunSi4703.h"
#include "Libraries/SparkFun/SparkFunSi4703.cpp"

#include "Libraries/SparkFun/SparkFunHTU21D.h"
#include "Libraries/SparkFun/SparkFunHTU21D.cpp"



#define LcdDsiplay Lcd_I2C // i call it LcdDisplay so when i import the Lcd without _I2C i dont have
                           // to go through the whole code  just to change  one var  name to another




void setup() {
    // etner point on startup only

    Serial.begin(9600);
    LcdDsiplay::init(); // at home am using the LCD_I2C because thats what i got
    LcdDsiplay::show("hello world\0", "hello world\0");
}




void loop() {
    // main loop enter point
    LcdDsiplay::loop();
}
