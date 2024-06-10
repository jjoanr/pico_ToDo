/* src/main.c */

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "task_manager.h"
#include "input.h"
#include "screens.h"

// Current screen to be displayed
// 0 -> HOME SCREEN
// 1 -> TASK MANAGER SCREEN
// 2 -> TIMER SCREEN
int current_screen = 0;

// Display config stucture
ssd1306_t disp;

// Entry point
int main(void) {
    stdio_init_all();
    // Initializes gpio pins/i2c
    setup_gpios();
    // Init display
    disp.external_vcc = false;
    if(!ssd1306_init(&disp, 128, 64, 0x3C, i2c1)) {
        perror("init_display");
        return -1;
    }
    // Display initial screen
    display_home_screen(&disp);
    // Main loop
    while (true) {
        
    }

    return 0;
}
