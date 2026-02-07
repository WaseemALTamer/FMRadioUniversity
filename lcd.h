#ifndef LCD_I2C_WRAPPER_H
#define LCD_I2C_WRAPPER_H

#include <Arduino.h>
#include "Libraries/LiquidCrystal/LiquidCrystal.h"


namespace Lcd_I2C {


    void show(char* line1, char* line2);

    // Wrapper functions around LiquidCrystal_I2C
    void set_cursor(int col, int row);
    void cursor_on();
    void cursor_off();
    void blink_on();
    void blink_off();
    void print(char* line);

    // Lifecycle
    void init();
    void loop();
}

#endif // LCD_I2C_WRAPPER_H
