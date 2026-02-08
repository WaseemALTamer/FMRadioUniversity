// this is a base <data provider> class, this class will not access any
// of the other classes it doesnt have an event system  like the others
// because this doesnt need any events


// i estimate this class to be taking 2% of the memeory but the libries
// we are importing wire and  the  SparkFunSi4703 library we are taking 
// 5%



// i import the .cpp file because the .h dont import them and  i get a
// linker error please dont  remove it keep  the libraries unedited as
// much as possible please 


#include "Libraries/SparkFun/SparkFunSi4703.h"
#include "Libraries/SparkFun/SparkFunSi4703.cpp"
#include <Wire.h>



namespace FM_Radio{

    // yes this class is simple you just have to make it work electrically
    // everything else has been already coded for it to work

    int reset_pin = 4;
    Si4703_Breakout radio(reset_pin, A4, A5); // add the rest pin and the SAL and SOA pins


    int current_volume = 0; // we start at 0 volume 
    int current_channel = 970; // this is the bbc channel i think

    // warper functions
    void set_channel(int frequency_mhz_10){
        // this function needs to be changed once we figure out how
        // the fm module actually works
        // frequency_mhz_10 is  basically ("frequency in mhz" * 10)

        // clamp the channels
        if (frequency_mhz_10 < 875) frequency_mhz_10 = 875;
        if (frequency_mhz_10 > 1080) frequency_mhz_10 = 1080;

        current_channel = frequency_mhz_10; // again we store it because  the library doesnt support it
                                            // for some reasons they made the function radio.getChannel
                                            // private which is stuiped dont try to make it public they
                                            // might have a reason for making it private

        radio.setChannel(frequency_mhz_10);
    }



    void set_volume(int volume){
        // this sets the volume


        // we cap the volume
        if (volume < 0) volume = 0;
        if (volume > 15) volume = 15;
        
        current_volume = volume; // store it in the current volume 

        radio.setVolume(volume);
    }


    void set_mono(bool state){
        // this might be better for weak signals
        // radio.setMono(state); // this fnuntion needs to be fixed the library is broken for thsi function
    }



    int get_current_channel(){
        // return frequency in frequency_mhz_10 as what you set

        //radio.getChannel(); //this function is private do not change it

        return current_channel;
    }


    int get_current_volume(){
        // we keep track of the volume our selfs the library
        // doesnt provide the current volume since this chip
        // doesnt support it "i think"
        return current_volume;
    }



    void init(){

        // this will setup the FM module thats about it

        Wire.begin(); // init the wire if it is not intiated from other modules
        radio.powerOn();


        set_volume(current_volume);  // set up the volume at 0 at the start
        set_channel(current_channel); // set the current channel so we start with a channel
    }


    void loop(){
        // this module doesnt need to be ran in a loop 
    }




}
