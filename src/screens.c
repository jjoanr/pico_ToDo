/* src/screens.c */
#include "screens.h"

// Display settings structure, defined in ssd1306.h
static ssd1306_t disp;

// Current screen to be displayed
static ScreenState current_screen = SCREEN_HOME;

/**
 * @brief Initializes the display settings.
 *
 * Initializes the display settings: heigth, width, address
 */
void init_display(void) {
    disp.external_vcc=false;
    if(!ssd1306_init(&disp, 128, 64, 0x3C, i2cl)) {
        perror("init_display");
    }
    ssd1306_clear(&disp);
}

/**
 * @brief Displays the home screen.
 */
void display_home_screen(void) {

}

/**
 * @brief Displays the task manager screen.
 */
void display_task_manager_screen(void) {

}

/**
 * @brief Displays the timer screen.
 */
void display_timer_screen(void) {

}

/**
 * @brief Initializes the display settings.
 *
 * Initializes the display settings: heigth, width, address
 */
void handle_button_next(void) {

}

/**
 * @brief Initializes the display settings.
 *
 * Initializes the display settings: heigth, width, address
 */
void handle_button_done(void) {

}
