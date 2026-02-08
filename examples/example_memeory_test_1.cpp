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


// wiring setup
#define SI4703_RESET 4   // Connect to RST on the module

// Create radio object
Si4703_Breakout radio(SI4703_RESET, A4, A5); // RESET, SDA (A4), SCL (A5)

HTU21D htu;


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

    Wire.begin();

    htu.begin();



    Serial.println("Starting SI4703...");

    // Initialize the radio
    radio.powerOn();
    radio.setVolume(10);   // 0 to 15

    // Tune to starting station
    radio.setChannel(973);

    Serial.println("Radio initialized and tuned.");
    Serial.print("Current frequency: ");
    Serial.print(973 / 10.0);
    Serial.println(" MHz");
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
