// this is a base input class, this class  will not  access any  of the other
// files, other files will include this file this file doesnt need to include
// any other file in this project


// i estimated this  file to take  about 14% of  the arduino memeory
// 1% by my code and 13%  by the  IRremote.hpp library that is being
// used


// we are not using the IRremote 2.6v anymore we are using the 4.5
// it comes  with  better handling  for niose  on it  self, but we
// still need to implement our own 

#include <stdint.h> // this is for the uint32_t data type
#include <Arduino.h>


#include "Libraries/IRremote/IRremote.hpp"





// this class is yet to be tested and it require more noise filtering
// please dont write the noise  filter in  upper layers write it here





namespace Infrared {

    // infrared reciver this uses the <IRremote.hpp> library

    const int infrared_reciver_pin = 5;


    const int reciver_cooldown_ms = 150; // this will ensure each singals should be 150ms apart



    typedef void (*ReciverCallback)(uint16_t address, uint8_t command); // this incldues the address of the remove trying to communcate
                                                                        // and the command that it is trying to excuate

    const int MAX_CALLBACKS = 5; // each array can only hold 5 callbacks if you try to add 
                                 // more than 5 callbacks then what  comes after 5 will be
                                 // ignored

    ReciverCallback callbacks[MAX_CALLBACKS];
    int callbacks_count = 0;




    void on_reciver_event(uint16_t address, uint8_t command) {
        // do not filter the niose at this stage filter the noise
        // in the function that will call this function
        
        for (int i = 0; i < callbacks_count; i++) {
            if (callbacks[i] != nullptr) {
                callbacks[i](address, command);
            }
        }
    }


    bool reciver_event_cooldown_passed() {
        // this will apply a  cool down effect you can have
        // breathing time to navigate and each button press
        // leads to one event

        static unsigned long last_event_time = 0;
        unsigned long now = millis();

        if (now - last_event_time < reciver_cooldown_ms) {
            return false; // ignore event
        }

        last_event_time = now;
        return true; // accept event
    }





    void init(){
        // infrared reciver
        IrReceiver.begin(infrared_reciver_pin, DISABLE_LED_FEEDBACK);
    }



    void loop() {
        if (IrReceiver.decode()) {
            
            if (reciver_event_cooldown_passed()) {
                // TO DO, noise filter later  on down  the line, and dont leak
                // noise into the upper layers it will break the system if you
                // are unsure about a signal just ignore it  and heavly ignore
                // it, it is better  to be  100% sure  in this  section rather
                // later on code will be  logic heavy  and doesnt  care  about
                // filtering     


                uint32_t value = IrReceiver.decodedIRData.decodedRawData;

                // the noise should be filtered here please keep the structure
                // as it is and implement your logic here

                uint16_t address = IrReceiver.decodedIRData.address;
                uint8_t command = IrReceiver.decodedIRData.command;

                // Ignore 0x0 commands (noise / floating pin)
                if (command != 0x0) {
                    on_reciver_event(address, command);
                }
            }

            IrReceiver.resume(); // resume even if we are behind the cool down
        }
    }



    void register_reciver_callback(ReciverCallback callback) {
        if (callbacks_count < MAX_CALLBACKS) {
            callbacks[callbacks_count++] = callback;
        }
    }


}