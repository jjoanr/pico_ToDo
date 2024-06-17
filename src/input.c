/* src/input.c */
#include "input.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "task_manager.h"
#include "ssd1306.h"
#include "screens.h"

// Define debounce time (in miliseconds)
#define DEBOUNCE_TIME_MS 100

// Raspberry Pi Pico GPIO Pins
#define PICO_PIN_SDA 2
#define PICO_PIN_SCL 3
#define BUTTON_NEXT 14
#define BUTTON_BACK 19
#define BUTTON_DONE 15

// Current screen
extern int current_screen;
// Display structure
extern ssd1306_t disp;
// Timer structure for debouncing
static repeating_timer_t debounce_timer;
// Stores gpio that caused interrupt
static uint debounce_gpio;

// Function prototypes - static functions
static bool debounce_timer_callback(repeating_timer_t *rt);

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

void button_isr(unsigned int gpio, uint32_t events) {
    // Store the gpio that caused the interrupt
    debounce_gpio = gpio;
    // Debouncing
    add_repeating_timer_ms(-DEBOUNCE_TIME_MS, debounce_timer_callback, NULL, &debounce_timer);
}

static bool debounce_timer_callback(repeating_timer_t *rt) {
    // Check if the button is still pressed
    if (gpio_get(debounce_gpio) == 0) {
        // Check current screen
        switch(current_screen) {
            case 0:
                if (debounce_gpio == BUTTON_NEXT) {
                    home_screen_toggle_selector(&disp);
                } else if (debounce_gpio == BUTTON_DONE) {
                    display_selected_screen(&disp);
                }
                break;
            case 1:
                if (debounce_gpio == BUTTON_NEXT) {
                    next_task(&disp);
                } else if (debounce_gpio == BUTTON_DONE) {
                    mark_task_done(&disp);
                }
                break;
            case 2:
                if (debounce_gpio == BUTTON_NEXT) {
                    // next_task(&disp);
                } else if (debounce_gpio == BUTTON_DONE) {
                    // mark_task_done(&disp);
                }
                break;
            default:
                break;
        }
    }
    // Remove the timer after running
    return false;
}
