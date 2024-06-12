/* src/timer.c */
#include "timer.h"

void display_timer(ssd1306_t *disp) {
    ssd1306_draw_string(disp, 48, 6, 1, "Timer");
    ssd1306_show(disp);
}
