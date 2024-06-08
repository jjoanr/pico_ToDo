/* src/main.c */

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "tasks.h"

// Entry point
int main(void) {
    stdio_init_all();
    // Initializes gpio pins/i2c
    setup_gpios();
    // Init display
    if(!init_display()) {
        perror("init_display");
    }
    // Display initial screen
    display_home_screen();
    // Main loop
    while (true) {
        
    }

    return 0;
}
