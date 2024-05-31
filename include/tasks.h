/* include/screens.h */
#ifndef _TASKS_H
#define _TASKS_H

#include <stdbool.h>
#include <sys/types.h>

#define MAX_LENGTH 15
#define MAX_TASKS 10

typedef struct task {
	uint id_task;
	char title[MAX_LENGTH];
	bool isDone;
} task;

struct listOfTasks {
	int currentAmount;
	int currentIndex;
	task taskList[MAX_TASKS];
};

// Function prototypes
int init_display();
int display_init_screen();
int add_task(task *t);
int remove_task();
int next_task();
int prior_task();
int mark_task_done();

#endif /* _TASKS_H */
