/* src/screens.c */
#include "screens.h"
#include "task_manager.h"
#include "timer.h"
#include "pico/stdlib.h"

// Current screen
extern int current_screen;

// Home screen selector number for option
// 0 -> 1st option
// ...
// N -> (N-1)st option
static int option_selected = 0;

// Static functions prototypes
static void display_task_manager_screen(ssd1306_t *disp);
static void display_timer_screen(ssd1306_t *disp);

/**
 * @brief Displays the home screen.
 */
void display_home_screen(ssd1306_t *disp) {
    ssd1306_clear(disp);
    ssd1306_draw_string(disp, 32, 6, 1, "Home Screen");
    ssd1306_draw_string(disp, 34, 24, 1, "Task Manager");
    ssd1306_draw_string(disp, 34, 40, 1, "Study Timer");
    // Draw option selector for first option
    ssd1306_draw_string(disp, 14, 24, 1, ">>");
    ssd1306_show(disp);
    
    current_screen = 0;
}

/**
 * @brief Toggles between the home screen options
 */
void home_screen_toggle_selector(ssd1306_t *disp) {
    // 2 options for now (thats why %2)
    option_selected = (option_selected + 1) % 2;
    // Clears the selected option character
    ssd1306_clear_square(disp, 14, 24, 18, 24);
    switch(option_selected) {
        case 0:
            ssd1306_draw_string(disp, 14, 24, 1, ">>");
            break;
        case 1:
            ssd1306_draw_string(disp, 14, 40, 1, ">>");
            break;
        default:
            break;
    }
    ssd1306_show(disp);
}

/**
 * @brief Displays the selected screen
 */
void display_selected_screen(ssd1306_t *disp) {
    switch(option_selected) {
        case 0:
            display_task_manager_screen(disp);
            break;
        case 1:
            display_timer_screen(disp);
            break;
        default:
            break;
    }
}

/**
 * @brief Displays the task manager screen.
 */
static void display_task_manager_screen(ssd1306_t *disp) {
    ssd1306_clear(disp);
    display_task_manager(disp);
    current_screen = 1;
}

/**
 * @brief Displays the timer screen.
 */
static void display_timer_screen(ssd1306_t *disp) {
    ssd1306_clear(disp);
    display_timer(disp);
    current_screen = 2;
}
