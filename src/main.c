#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "ssd1306.h"

void setup_gpios(void);

int main() {
    stdio_init_all();

    printf("configuring pins...\n");
    setup_gpios();

    ssd1306_t disp;
    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    printf("Displaying 'Hello, world!'\n");

    // Display 'Hello, world!'
    ssd1306_draw_string(&disp, 8, 24, 1, "Hello world!");
    ssd1306_show(&disp);

    while (true) {
        // Your main code loop here
    }

    return 0;
}

void setup_gpios(void) {
    i2c_init(i2c1, 400000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
}
