#include <stdint.h>
#include "global_state.h"


uint8_t toggle_mode(void) {
    // Toggle the state variable that stores the current operating mode
    if (mode)
        mode = 0;
    else
        mode = 1;
    // Call the init functions for the different modes
    
    
    // Return the mode currently operating on.
    return mode;
}