/* include/task_manager.h */
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "ssd1306.h"
#include <stdbool.h>
#include <sys/types.h>

/*
 * 5 bit wide characters
 * 1 bit space between characters
 * 5*8 + 22 spaces = 127bits + 1bit at the end (end has 2 bit separation)
 */
#define CHARS_PER_ROW 21
#define Y_START_ROW_1 24
#define Y_START_ROW_2 34
#define TASK_TEXT_MAX_ROWS 2
#define MAX_LENGTH 42 // CHARS_PER_ROW * 2 rows
#define MAX_TASKS 10

#define SUCCESS 0
#define ERROR  -1

/*
 * @brief Structure that represents a task.
 */
typedef struct {
	uint id_task;			// Task identifier
	char title[MAX_LENGTH];		// Task text
	bool isDone;			// Task status
} task;

/*
 * @brief Structure that represents a list of tasks.
 */
typedef struct {
	int currentAmount;		// Current # of tasks
	int currentIndex;		// Current task index being displayed
	task taskList[MAX_TASKS];	// Array of tasks
} listOfTasks;

// Function prototypes
void display_task_manager(ssd1306_t *disp);
int add_task(const task *t);
void next_task(ssd1306_t *disp);
void mark_task_done(ssd1306_t *disp);

#endif /* TASK_MANAGER_H */
