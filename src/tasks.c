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

/*
 * Function: init_display
 * ----------------------------
 *   Initializes display settings.
 *
 *   returns: 0 if success, negative otherwise. 
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

/*
 * Function: display_init_screen
 * ----------------------------
 *   Displays the program initial/welcome screen
 *
 *   returns: 0 if success, negative otherwise
 */
int display_init_screen(void) {
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 38, 16, 1, "ToDo List");
    ssd1306_draw_string(&disp, 10, 30, 1, "Press any button...");
    ssd1306_show(&disp);

    return SUCCESS;
}


/*
 * Function: add_task
 * ----------------------------
 *   Adds a new task to the taskList structure
 *
 *   t: task structure
 *
 *   returns: 0 if success, negative otherwise. 
 */
int add_task(const task *t) {
    if(tasks.currentAmount < MAX_TASKS) {
	tasks.taskList[tasks.currentAmount++] = *t;
	return SUCCESS;
    }
    return ERROR;
}

/*
 * Function: remove_task
 * ----------------------------
 *   Removes an existing task from the taskList structure
 *
 *   t_id: task identifier
 *
 *   returns: 0 if success, negative otherwise. 
 */
int remove_task(int task_id) {
    //todo
    return ERROR;
}

/*
 * Function: next_task 
 * ----------------------------
 *   Displays the next task available in the screen
 *
 *   returns: 0 if success, negative otherwise. 
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

/*
 * Function: display_status
 * ----------------------------
 *   Displays the task status
 *
 *   returns: void 
 */
void display_status(void) {
    if(tasks.taskList[tasks.currentIndex].isDone) {
	ssd1306_draw_string(&disp, 50, 48, 1, "DONE!");
    } else {
	ssd1306_draw_string(&disp, 50, 48, 1, "To do");
    }
}


/*
 * Function: prior_task
 * ----------------------------
 *   Displays the previous task
 *
 *   returns: 0 if success, negative otherwise. 
 */
int prior_task(void) {
    // todo
    return ERROR;
}

/*
 * Function: mark_task_done
 * ----------------------------
 *   Marks the current task as done
 *
 *   returns: 0 if success, negative otherwise. 
 */
int mark_task_done(void) {
    tasks.taskList[tasks.currentIndex].isDone = true;
    return SUCCESS;
}
