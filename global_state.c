#include <stdint.h>
#include <xc.h>
#include "global_state.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"

void auto_mode(void) {
    // Init and Start the auto mode
    // Set the indicators up
    man_LED = 0;
    auto_LED = 1;
    // Turn on the timer
    timer_start();
}

void man_mode(void) {
    // Init and Start the manual mode
    // Set the indicators up
    man_LED = 1;
    auto_LED = 0;
    // Turn off the timer
    timer_stop();
}


uint8_t toggle_mode(void) {
    // Toggle the state variable that stores the current operating mode
    // and call the init functions for the different modes
    if (mode) {
        mode = 0;
        man_mode();
    }
    else {
        mode = 1;
        auto_mode();
    }
    // Return the mode currently operating on.
    return mode;
}