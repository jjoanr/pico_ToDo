/* src/screens.c */
#include "screens.h"
#include "task_manager.h"
#include "timer.h"

// Current screen
extern int current_screen;

/**
 * @brief Displays the home screen.
 */
void display_home_screen(ssd1306_t *disp) {
    ssd1306_clear(disp);
    ssd1306_draw_string(disp, 34, 6, 1, "Home Screen");
    ssd1306_draw_string(disp, 20, 24, 1, "1. Task Manager");
    ssd1306_draw_string(disp, 20, 40, 1, "2. Study Timer");
    ssd1306_show(disp);
    current_screen = 0;
}

/**
 * @brief Displays the task manager screen.
 */
void display_task_manager_screen(ssd1306_t *disp) {
    ssd1306_clear(disp);
    display_task_manager(disp);
    current_screen = 1;
}

/**
 * @brief Displays the timer screen.
 */
void display_timer_screen(ssd1306_t *disp) {
    ssd1306_clear(disp);
    // display_timer(disp);
    current_screen = 2;
}

/**
 * @brief Handles screen switch
 */
void switch_screen(int screen_id, ssd1306_t *disp) {
    switch(screen_id) {
        case 0:
            ssd1306_clear(disp);
            display_home_screen(disp);
            break;
        case 1:
            ssd1306_clear(disp);
            display_task_manager_screen(disp);
            break;
        case 2:
            ssd1306_clear(disp);
            display_timer_screen(disp);
            break;
        default:
            break;
    }
}
