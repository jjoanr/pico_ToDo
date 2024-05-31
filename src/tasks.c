/* src/tasks.c */
#include "tasks.h"
#include "ssd1306.h"
#include <string.h>

// display settings structure, defined in ssd1306.h
ssd1306_t disp;

// structure that holds the tasks
struct listOfTasks tasks;

/*
 * Function: init_display
 * ----------------------------
 *   Initializes display settings.
 *
 *   returns: 0 if success, negative otherwise. 
 */
int init_display() {
	bool res;
	
	// load mock tasks
	tasks.currentIndex = 0;
	tasks.currentAmount = 0;

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

	// display init steps
	disp.external_vcc=false;
	res = ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
	ssd1306_clear(&disp);
	return res;
}

/*
 * Function: display_init_screen
 * ----------------------------
 *   Displays the program initial/welcome screen
 *
 *   returns: 0 if success, negative otherwise
 */
int display_init_screen() {
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 38, 16, 1, "ToDo List");
    ssd1306_draw_string(&disp, 10, 30, 1, "Press any button...");
    ssd1306_show(&disp);
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
int add_task(task *t) {
    if(tasks.currentAmount < MAX_TASKS) {
	tasks.taskList[tasks.currentAmount] = *t;
	tasks.currentAmount++;
	return 0;
    }
    return -1;
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
int remove_task() {
    return -1;
}

/*
 * Function: next_task 
 * ----------------------------
 *   Displays the next task available in the screen
 *
 *   returns: 0 if success, negative otherwise. 
 */
int next_task() {
    if(tasks.currentIndex < tasks.currentAmount) {
	ssd1306_clear(&disp);
	ssd1306_draw_string(&disp, 46, 16, 1, tasks.taskList[tasks.currentIndex].title);
	ssd1306_show(&disp);
    } else {
	tasks.currentIndex = 0;
	ssd1306_clear(&disp);
	ssd1306_draw_string(&disp, 46, 16, 1, tasks.taskList[tasks.currentIndex].title);
	ssd1306_show(&disp);
    }
    tasks.currentIndex++;
    return 0;
}

/*
 * Function: prior_task
 * ----------------------------
 *   Displays the previous task
 *
 *   returns: 0 if success, negative otherwise. 
 */
int prior_task() {
    return -1;
}

/*
 * Function: mark_task_done
 * ----------------------------
 *   Marks the current task as done
 *
 *   returns: 0 if success, negative otherwise. 
 */
int mark_task_done() {
    tasks.taskList[tasks.currentIndex].isDone = true;
    return 0;
}
