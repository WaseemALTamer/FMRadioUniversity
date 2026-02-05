#include <Arduino.h>
#include "Clock.h"



void on_time_changed(int seconds, int minutes, int hours) {
    Serial.print("Time: ");
    if (hours < 10) Serial.print('0');
    Serial.print(hours);
    Serial.print(":");
    if (minutes < 10) Serial.print('0');
    Serial.print(minutes);
    Serial.print(":");
    if (seconds < 10) Serial.print('0');
    Serial.println(seconds);
}

void on_date_changed(int day, int month, int year) {
    Serial.print("Date: ");
    if (day < 10) Serial.print('0');
    Serial.print(day);
    Serial.print("/");
    if (month < 10) Serial.print('0');
    Serial.print(month);
    Serial.print("/");
    Serial.println(year); // this is 0–99 from RTC, but fine for testing
}

void on_alarm() {
    Serial.println(">>> ALARM TRIGGERED! <<<");
}



void setup() {
    Serial.begin(9600);
    Clock::init();

    // Register callbacks
    Clock::register_time_callback(on_time_changed);
    Clock::register_date_callback(on_date_changed);
    Clock::register_alarm_callback(on_alarm);

    // set current time this should not be ran when the arduino 
    // starts as the clock keeps track of the time
    Clock::set_time(40, 59, 23);
    Clock::set_date(6, 2, 2026);
    Clock::set_alarm(3, 3);
}



void loop() {
    Clock::loop();
}