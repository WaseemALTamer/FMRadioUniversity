#ifndef LCD_I2C_WRAPPER_H
#define LCD_I2C_WRAPPER_H

#include <Arduino.h>
#include "Libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"

namespace Lcd_I2C {

    // Expose the LCD instance (defined in the .cpp)
    extern LiquidCrystal_I2C lcd;

    // Timing / scheduling state (defined in the .cpp)
    extern int show_cool_down_duration_ms;
    extern bool is_show_scheduled;
    extern char* scheduled_line_1;
    extern char* scheduled_line_2;

    // Core scheduling / update helpers
    bool show_cool_down();
    void show(char* line1, char* line2);

    // Wrapper functions around LiquidCrystal_I2C
    void set_cursor(int col, int row);
    void cursorOn();
    void cursor_off();
    void blink_on();
    void blink_off();
    void print(char* line);

    // Lifecycle
    void init();
    void loop();
}

#endif // LCD_I2C_WRAPPER_H
