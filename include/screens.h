/* include/screens.h */
#ifndef SCREENS_H
#define SCREENS_H
#include "ssd1306.h"

// Function prototypes
void display_home_screen(ssd1306_t *disp);
void home_screen_toggle_selector(ssd1306_t *disp);
void display_selected_screen(ssd1306_t *disp);

#endif /* SCREENS_H */
