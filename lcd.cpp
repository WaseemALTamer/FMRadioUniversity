// this class is an output class it is not a bse layer it is what the
// intermedaite layer uses to actually  does what it is suppose to do
// this class doesnt effect the  internal structure it doesnt collide
// with the base layer  and is  just there  as an  ouput  device this
// file will be just a warper  library  for the LiquidCrystal_I2C but
// the base function for the lcd remain the  same across  through out
// this means if we change the lcd later on we  dont have  to  change
// the intermediate layer





#include "Libraries/LiquidCrystal/LiquidCrystal.h"
#include "Libraries/LiquidCrystal/LiquidCrystal.cpp"





namespace Lcd{

    // all pins needs to be connected to gpio apperantly
    // RS, E, D4, D5, D6, D7
    LiquidCrystal lcd(
        0, // RS
        0, // E
        0, // D4
        0, // D5
        0, // D6
        0  // D7
    );



    int show_cool_down_duration_ms = 100; // this mimics fps and caps how many times 
                                          // you call the update a second 


    // READE __importat__  ->  scheduled system  
    // worry if you update and your update does
    // not go through it will  get schedule for
    // in the next time the update is timed out
    // if two get  schedule  consecutively then
    // only the one schedule can  stay and only
    // and the new one will be used if you edit
    // the buffer it self thats fine but do not
    // dispose  of  the buffer  it will lead to
    // errors, and any way  at no  point should
    // you be reallocating  any buffers in this
    // project  

    bool is_show_scheduled = false;
    char* scheduled_line_1;
    char* scheduled_line_2;



    bool show_cool_down() {
        // this avoid internal bounce effect for the buttons

        static unsigned long last_event_time = 0;
        unsigned long now = millis();

        if (now - last_event_time < show_cool_down_duration_ms) {
            return false; // ignore event
        }

        last_event_time = now;
        return true; // accept event
    }




    // those are warpper function
    void set_cursor(int col, int row) {
        lcd.setCursor(col, row);
    }

    void cursor_on() {
        lcd.cursor();
    }

    void cursor_off() {
        lcd.noCursor();
    }

    void blink_on() {
        lcd.blink();
    }

    void blink_off() {
        lcd.noBlink();
    }

    void print(char* line){
        lcd.print(line);
    }
    









    void show(char* line1, char* line2) {

        // note that line 1 should be 16 bytes long only
        // and line 2  should follow  the same structure

        // do not use lcd. clear()  this will  block the
        // thread, avoid it as much as possible

        // this function  does not  set the  cursor back
        // where it was do it your self

        // this will mimic running at certain fps

        if (!show_cool_down()){
            scheduled_line_1 = line1;
            scheduled_line_2 = line2;
            is_show_scheduled = true;
            return;
        }

        set_cursor(0, 0);
        print(line1);

        set_cursor(0, 1);
        print(line2);
    }







    void init(){
        lcd.begin(16, 2);        // Initialize the LCD
        //lcd.backlight();       // Turn on the backlight <- this is only supported on the I2C module
    }


    void loop(){
        // this loop is not  optional it is required
        // you can use  the module  it self  without
        // the loop but the schedule system will not
        // work and then when navigating quickly the
        // screen might not update

        if (is_show_scheduled){
            is_show_scheduled = false;
            show(scheduled_line_1, scheduled_line_2);
        }

    }



}