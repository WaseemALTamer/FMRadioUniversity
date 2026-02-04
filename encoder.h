// this is a base input class, this class  will not  access any  of the other
// files, other files will include this file this file doesnt need to include
// any other file in this project






#ifndef ENCODER_H // these insure that the file doesnt get imported again
#define ENCODER_H

#include <Arduino.h>

// Encoder namespace to encapsulate everything
namespace Encoder {

    // Initialize the encoder pins and state
    void init();

    // Run inside the main loop to detect encoder changes
    void loop();

    // Register a callback function to be called on encoder rotation
    typedef void (*EncoderCallback)(int delta);
    void register_encoder_callback(EncoderCallback callback);

} // namespace Encoder

#endif // ENCODER_H