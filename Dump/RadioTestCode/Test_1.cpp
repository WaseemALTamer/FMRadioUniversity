#include "Libraries/SparkFunSi4703/SparkFunSi4703.h"
#include "Libraries/SparkFunSi4703/SparkFunSi4703.cpp"
#include <Wire.h>

// wiring setup
#define SI4703_RESET 4   // Connect to RST on the module

// Create radio object
Si4703_Breakout radio(SI4703_RESET, A4, A5); // RESET, SDA (A4), SCL (A5)

// Start frequency (in tenths of MHz)
int currentChannel = 973;  // 87.0 MHz

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Starting SI4703...");

  // Initialize the radio
  radio.powerOn();
  radio.setVolume(10);   // 0 to 15

  // Tune to starting station
  radio.setChannel(currentChannel);

  Serial.println("Radio initialized and tuned.");
  Serial.print("Current frequency: ");
  Serial.print(currentChannel / 10.0);
  Serial.println(" MHz");
}

void loop() {
  // Check if data is available on Serial
  if (Serial.available()) {
    char input = Serial.read();

    if (input == '+') {
      // Increase frequency by 0.1 MHz (step = 1 in tenths of MHz)
      currentChannel += 1;
      radio.setChannel(currentChannel);

      Serial.print("Tuned up to: ");
      Serial.print(currentChannel / 10.0);
      Serial.println(" MHz");
    } 
    else if (input == '-') {
      // Decrease frequency by 0.1 MHz
      currentChannel -= 1;
      radio.setChannel(currentChannel);

      Serial.print("Tuned down to: ");
      Serial.print(currentChannel / 10.0);
      Serial.println(" MHz");
    }
  }
}
