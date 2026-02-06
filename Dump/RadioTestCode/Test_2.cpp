#include "Libraries/Radio/SI4703.h"
#include "Libraries/Radio/SI4703.cpp"
#include "Libraries/Radio/radio.h"
#include "Libraries/Radio/radio.cpp"
#include <Wire.h>


#define RESET_PIN 4
#define MODE_PIN A4

SI4703 radio;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  radio.setup(RADIO_RESETPIN, RESET_PIN);
  radio.setup(RADIO_MODEPIN, MODE_PIN);
  radio.debugEnable(true);
  radio.initWire(Wire);
  radio.setVolume(10);
  radio.setMono(true);  // force mono for weak signals

  Serial.println("Starting FM scan...");
}

void loop() {
  // Scan up in 0.1 MHz steps
  radio.seekUp();
  
  char freq[12];
  radio.formatFrequency(freq, sizeof(freq));
  Serial.print("Trying frequency: ");
  Serial.println(freq);

  delay(1000); // wait 1 sec for signal to settle
}