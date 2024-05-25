/* include/screens.h */
#ifndef _TASKS_H
#define _TASKS_H

#include <stdbool.h>
#include <sys/types.h>

typedef struct task {
	uint id_task;

	

} task;


// Function prototypes
bool init_display();
void display_init_screen();
void add_task();
void remove_task();
void next_task();
void prior_task();
void mark_task_done();

#endif /* _TASKS_H */
