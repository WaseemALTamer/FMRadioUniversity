#include "environment.h"
#include "structure.h"



namespace PageEnviroment {

    Page page;

    void on_environment_event(float temperature, float humidity) {

        int temperature_whole = (int)temperature;
        int temperature_fraction = (int)((temperature - temperature_whole) * 10);

        int humidity_whole = (int)humidity;
        int humidity_fraction = (int)((humidity - humidity_whole) * 10);

        int value_buffer_size = sizeof(page.value);
        snprintf(
            page.value, 
            value_buffer_size, 
            "T:%d.%dC H:%d.%d%     ", 
            temperature_whole, 
            temperature_fraction,
            humidity_whole,
            humidity_fraction
        );
        page.value[sizeof(page.value) - 1] = '\0'; // add the terminator at the end

        // mark the page for update
        page.schedul_update = true;
    }

    void init() {
        strncpy(page.title, "<  ENVIROMNET  >", sizeof(page.title));
        page.title[sizeof(page.title) - 1] = '\0'; // add the terminator at the end

        memset(page.value, ' ', sizeof(page.value)); // make it empty at the start
        page.value[sizeof(page.value) - 1] = '\0'; // add the terminator at the end


        Environment::register_environment_callback(on_environment_event);
    }
}
