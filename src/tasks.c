/* src/tasks.c */
#include "tasks.h"
#include "ssd1306.h"
#include <string.h>

// Display settings structure, defined in ssd1306.h
static ssd1306_t disp;

// Structure that holds the tasks
static struct listOfTasks tasks;

// Tracks if the task display has started (not in welcome screen)
static bool startedTaskDisplay = false;

/**
 * @brief Initializes the display settings.
 *
 * Initializes the display settings.
 *
 * @return SUCCESS if success, ERROR otherwise.
 */
int init_display(void) {
    bool res;

    // Initialize the task list structure
    tasks.currentIndex = 0;
    tasks.currentAmount = 0;

    // Mock tasks
    task task1;
    task1.id_task = 0;
    strcpy(task1.title, "TASK 1!");
    task1.isDone = false;
    add_task(&task1);

    task task2;
    task2.id_task = 1;
    strcpy(task2.title, "TASK 2!");
    task2.isDone = false;
    add_task(&task2);

    task task3;
    task3.id_task = 1;
    strcpy(task3.title, "TASK 3!");
    task3.isDone = false;
    add_task(&task3);

    // Initialize display
    disp.external_vcc=false;
    res = ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    return res ? SUCCESS : ERROR;
}

/**
 * @brief Displays the program initial/welcome screen.
 *
 * @return SUCCESS if success, ERROR otherwise.
 */
int display_init_screen(void) {
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 38, 16, 1, "ToDo List");
    ssd1306_draw_string(&disp, 10, 30, 1, "Press any button...");
    ssd1306_show(&disp);

    return SUCCESS;
}


/**
 * @brief Adds a new task to the task list.
 *
 * @param t Pointer to the task to be added.
 * @return SUCCESS if success, ERROR otherwise.
 */
int add_task(const task *t) {
    if(tasks.currentAmount < MAX_TASKS) {
	tasks.taskList[tasks.currentAmount++] = *t;
	return SUCCESS;
    }
    return ERROR;
}

/**
 * @brief Removes an existing task from the task list.
 *
 * @param task_id Task identifier to be removed.
 * @return ERROR (todo)
 */
int remove_task(int task_id) {
    //todo
    return ERROR;
}

/**
 * @brief Displays the next task available on the screen.
 *
 * Cycles through tasks.
 *
 * @return SUCCESS if success, ERROR otherwise.
 */
int next_task(void) {
    if(!startedTaskDisplay) {
	startedTaskDisplay = true;
    } else {
	tasks.currentIndex = (tasks.currentIndex + 1) % tasks.currentAmount;
    }
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 46, 16, 1, tasks.taskList[tasks.currentIndex].title);
    display_status();
    ssd1306_show(&disp);
    return 0;
}

/**
 * @brief Displays the task status.
 *
 * Shows whether the current task is done or to be done.
 */
void display_status(void) {
    if(tasks.taskList[tasks.currentIndex].isDone) {
	ssd1306_draw_string(&disp, 50, 48, 1, "DONE!");
    } else {
	ssd1306_draw_string(&disp, 50, 48, 1, "To do");
    }
}


/**
 * @brief Displays the previous task.
 *
 * @return ERROR (todo)
 */
int prior_task(void) {
    // todo
    return ERROR;
}

/**
 * @brief Marks the current task as done.
 *
 * @return SUCCESS if success, ERROR otherwise.
 */
int mark_task_done(void) {
    tasks.taskList[tasks.currentIndex].isDone = true;
    return SUCCESS;
}
