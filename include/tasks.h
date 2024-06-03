/* include/tasks.h */
#ifndef TASKS_H
#define TASKS_H

#include <stdbool.h>
#include <sys/types.h>

#define MAX_LENGTH 15
#define MAX_TASKS 10

/*
 * @brief Enum for return values.
 */
typedef enum {
	SUCCESS = 0,
	ERROR = -1,
} return_code_t;

/*
 * @brief Structure that represents a task.
 */
typedef struct task {
	uint id_task;			// Task identifier
	char title[MAX_LENGTH];		// Task text
	bool isDone;			// Task status
} task;

/*
 * @brief Structure that represents a list of tasks.
 */
struct listOfTasks {
	int currentAmount;		// Current # of tasks
	int currentIndex;		// Current task index being displayed
	task taskList[MAX_TASKS];	// Array of tasks
};

// Function prototypes
int init_display(void);
int display_init_screen(void);
int add_task(const task *t);
int remove_task(int task_id);
int next_task(void);
void display_status(void);
void display_time(uint hour, uint minute);
int prior_task(void);
int mark_task_done(void);
void draw_interface(void);

#endif /* TASKS_H */
