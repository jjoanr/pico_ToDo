/* include/screens.h */
#ifndef SCREENS_H
#define SCREENS_H

typedef enum {
	SCREEN_HOME,
	SCREEN_TASK_MANAGER,
	SCREEN_TIMER
} ScreenState;

// Function prototypes
void display_home_screen(void);
void display_task_manager_screen(void);
void display_timer_screen(void);
void handle_button_next(void);
void handle_button_done(void);

#endif /* SCREENS_H */
