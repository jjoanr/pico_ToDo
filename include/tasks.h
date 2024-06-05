/* include/tasks.h */
#ifndef TASKS_H
#define TASKS_H

#include <stdbool.h>
#include <sys/types.h>

#define MAX_LENGTH 42 // CHARS_PER_ROW * 2 rows
#define MAX_TASKS 10
/*
 * 5 bit wide characters
 * 1 bit space between characters
 * 5*8 + 22 spaces = 127bits + 1bit at the end (end has 2 bit separation)
 */
#define CHARS_PER_ROW 21
#define Y_START_ROW_1 24
#define Y_START_ROW_2 34
#define TASK_TEXT_MAX_ROWS 2

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
int display_home_screen(void);
int add_task(const task *t);
int remove_task(int task_id);
int next_task(void);
void display_status(void);
void display_time(uint hour, uint minute);
int prior_task(void);
int mark_task_done(void);
void draw_interface(void);
void draw_cross_task(void);

#endif /* TASKS_H */
