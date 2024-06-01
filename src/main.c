/* src/main.c */

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "tasks.h"

// Raspberry Pi Pico GPIO Pins
#define PICO_PIN_SDA 2
#define PICO_PIN_SCL 3
#define BUTTON_NEXT 14
#define BUTTON_BACK 19
#define BUTTON_DONE 15

// Function prototypes
void setup_gpios(void);
void button_isr(uint gpio, uint32_t events);

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
    display_init_screen();
    // Infinite loop
    while (true) {
        // 
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
    // GPIO button next config
    gpio_init(BUTTON_NEXT);
    gpio_set_dir(BUTTON_NEXT, GPIO_IN);
    gpio_pull_up(BUTTON_NEXT);
    // GPIO button done config
    gpio_init(BUTTON_DONE);
    gpio_set_dir(BUTTON_DONE, GPIO_IN);
    gpio_pull_up(BUTTON_DONE);
    // Setup interrupts for buttons
    gpio_set_irq_enabled_with_callback(BUTTON_NEXT, GPIO_IRQ_EDGE_FALL , true, &button_isr);
    gpio_set_irq_enabled_with_callback(BUTTON_DONE, GPIO_IRQ_EDGE_FALL , true, &button_isr);
}

void button_isr(uint gpio, uint32_t events) {
    if(gpio == BUTTON_NEXT) {
        next_task();
    }
    if(gpio == BUTTON_DONE) {
        mark_task_done();
    }

}
