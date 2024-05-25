/* src/screens.c */
#include "screens.h"
#include "ssd1306.h"

// List of all screens
screen *screen_list;

// display settings, defined in ssd1306.h
ssd1306_t disp;

bool init_display() {
	bool res;
	// display init steps
	disp.external_vcc=false;
	res = ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
	ssd1306_clear(&disp);
	return res;

	// Creates init screen
	
}

void display_init_screen() {
    ssd1306_draw_string(&disp, 8, 24, 1, "Hello world!");
    ssd1306_show(&disp);
}

void add_screen() {

}

void remove_screen() {

}

void next_screen() {

}

void prior_screen() {

}
