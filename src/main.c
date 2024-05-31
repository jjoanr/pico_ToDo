/* src/main.c */

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "tasks.h"

// Keeps state of the button pressed
// 0: No press
// 1: Next
// 2: Back
// 3: Done
volatile uint32_t buttonPressed = 0;


// Raspberry Pi Pico GPIO Pins
#define PICO_PIN_SDA 2
#define PICO_PIN_SCL 3
#define BUTTON_NEXT 14
#define BUTTON_BACK 19
#define BUTTON_DONE 15

// Function prototypes
void setup_gpios(void);

//Entry point
int main(void) {
    stdio_init_all();

    // initializes gpio pins/i2c
    setup_gpios();

    // init display
    if(!init_display()) {
        perror("init_display");
    }

    //Display initial screen
    display_init_screen();

    while (true) {
        // Read the button states
        bool buttonNext_pressed = !gpio_get(BUTTON_NEXT);  // Active low
        bool buttonDone_pressed = !gpio_get(BUTTON_DONE);  // Active low
    
        if (buttonNext_pressed) {
            next_task();
            sleep_ms(200);  // Simple debouncing
        }
        if (buttonDone_pressed) {
            mark_task_done();
            sleep_ms(200);  // Simple debouncing
        }
    }

    return 0;
}

void setup_gpios(void) {
    // Initializes i2c
    i2c_init(i2c1, 400000);
    // Sets GPIO function as i2c
    gpio_set_function(PICO_PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PICO_PIN_SCL, GPIO_FUNC_I2C);
    // Sets GPIO pins to be pulled up
    gpio_pull_up(PICO_PIN_SDA);
    gpio_pull_up(PICO_PIN_SCL);

    gpio_init(BUTTON_NEXT);
    gpio_set_dir(BUTTON_NEXT, GPIO_IN);
    gpio_pull_up(BUTTON_NEXT);

    gpio_init(BUTTON_DONE);
    gpio_set_dir(BUTTON_DONE, GPIO_IN);
    gpio_pull_up(BUTTON_DONE);

}
