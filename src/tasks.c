/* src/tasks.c */
#include "tasks.h"
#include "ssd1306.h"

// display settings, defined in ssd1306.h
ssd1306_t disp;

bool init_display() {
	bool res;
	// display init steps
	disp.external_vcc=false;
	res = ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
	ssd1306_clear(&disp);
	return res;
}

void display_init_screen() {
    ssd1306_draw_string(&disp, 38, 16, 1, "ToDo List");
    ssd1306_draw_wrapped_text(&disp, 10, 30, "Press any button...");
    ssd1306_show(&disp);
}

void add_task() {

}

void remove_task() {

}

void next_task() {

}

void prior_task() {

}

void mark_task_done() {

}
