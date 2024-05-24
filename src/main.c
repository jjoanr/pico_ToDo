/* src/main.c */

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "screens.h"

// Raspberry Pi Pico GPIO Pins (used for i2c)
#define PICO_PIN_SDA 2
#define PICO_PIN_SCL 3

// Function prototypes
void setup_gpios(void);

//Entry point
int main() {
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
}
