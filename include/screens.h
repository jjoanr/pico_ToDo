/* include/screens.h */
#ifndef SCREENS_H
#define SCREENS_H
#include "ssd1306.h"

// Function prototypes
void display_home_screen(ssd1306_t *disp);
void display_task_manager_screen(ssd1306_t *disp);
void display_timer_screen(ssd1306_t *disp);
void switch_screen(int screen_id, ssd1306_t *disp);

#endif /* SCREENS_H */
