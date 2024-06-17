/* src/task_manager.c */
#include "task_manager.h"
#include "ssd1306.h"
#include <stdio.h>
#include <string.h>
#include "screens.h"

// Structure that holds the tasks
static listOfTasks tasks;

// Function prototypes - static functions
static void display_status(ssd1306_t *disp);
static void draw_interface(ssd1306_t *disp);
static void draw_cross_task(ssd1306_t *disp);
static void display_time(uint hour, uint minute, ssd1306_t *disp);
static void display_status(ssd1306_t *disp); 

/**
 * @brief Initializes the task manager
 *
 * @param disp pointer to display structure
 */
void display_task_manager(ssd1306_t *disp) {
    // Initialize the task list structure
    tasks.currentIndex = -1;
    tasks.currentAmount = 0;
    tasks.tasksCompleted = 0;

    // Mock tasks
    task task1 = {0, "Task 1", false};
    add_task(&task1);

    task task2 = {1, "Task 2", false};
    add_task(&task2);

    task task3 = {2, "Task 3", false};
    add_task(&task3);

    draw_interface(disp);
    next_task(disp);
    ssd1306_show(disp);
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
 * Cycles through tasks and prints the task description formatted
 */
void next_task(ssd1306_t *disp) {
    tasks.currentIndex = (tasks.currentIndex + 1) % tasks.currentAmount;
    // Clear text area only:
    //   Starting x,y point: (0,19)
    //   Width: All screen
    //   Height: Up to the next section (which starts at pixel 0 -> 48-19 = 29)
    ssd1306_clear_square(disp, 0, 19, 128, 29);

    char *taskText = tasks.taskList[tasks.currentIndex].title;
    size_t textLength = strlen(taskText);
    // Compute number of rows needed, limited to TASK_TEXT_MAX_ROWS (2)
    int rowsNeeded = (textLength + CHARS_PER_ROW - 1) / CHARS_PER_ROW;
    rowsNeeded = rowsNeeded > TASK_TEXT_MAX_ROWS ? TASK_TEXT_MAX_ROWS : rowsNeeded;
    
    for (int row = 0; row < rowsNeeded; ++row) {
        // Initialize the buffer with null characters
	char rowText[CHARS_PER_ROW] = {0};
        strncpy(rowText, taskText + row * CHARS_PER_ROW, CHARS_PER_ROW);
	// Calculate y position based on row
        int yPosition = Y_START_ROW_1 + (row * (Y_START_ROW_2 - Y_START_ROW_1));
        ssd1306_draw_string(disp, 0, yPosition, 1, rowText);
    }
    // Draw task status
    display_status(disp);
    ssd1306_show(disp);
}

/**
 * @brief Displays the task status.
 *
 * Shows whether the current task is done or to be done.
 */
static void display_status(ssd1306_t *disp) {
    // Clear status area only:
    //   Starting x,y point: (0,51)
    //   Width: All screen
    //   Height: Up to the end of the screen (63-49 = 14)
    ssd1306_clear_square(disp, 0, 49, 128, 14);
    if(tasks.taskList[tasks.currentIndex].isDone) {
    	ssd1306_draw_string(disp, 6, 54, 1, "DONE!!!");
	// Draws a "cross" above the task text, to mark it as done
	draw_cross_task(disp);
    } else {
	ssd1306_draw_string(disp, 6, 54, 1, "To do");
    }
    // currentIndex + '/' + currentAmount
    char str[32];
    snprintf(str, sizeof(str), "%d / %d", tasks.currentIndex + 1, tasks.currentAmount);
    ssd1306_draw_string(disp, 96, 54, 1, str);
    ssd1306_show(disp);
}

/**
 * @brief Displays time.
 *
 * @param hour Current hour to be displayed
 * @param minute Current minute to be displayed
 *
 * Displays the current time hour:minute at the top of the screen
 */
static void display_time(uint hour, uint minute, ssd1306_t *disp) {
    // Clear time area only:
    //   Starting x,y point: (0,0)
    //   Width: All screen
    //   Height: Up to the next section (which starts at pixel 18 -> 18-0 = 18)
    ssd1306_clear_square(disp, 0, 0, 128, 18);
    // hour + ":" + minute
    char str[32];
    snprintf(str, sizeof(str), "%d:%d", hour, minute);
    ssd1306_draw_string(disp, 50, 6, 1, str);
    ssd1306_show(disp);
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
void mark_task_done(ssd1306_t *disp) {
    bool taskStatus = tasks.taskList[tasks.currentIndex].isDone;
    // Checks task status
    if(!taskStatus) {
	tasks.taskList[tasks.currentIndex].isDone = true;
	tasks.tasksCompleted++;
    } else {
	tasks.taskList[tasks.currentIndex].isDone = false;
	tasks.tasksCompleted--;
    }

    display_status(disp);
}

/**
 * @brief Draws the interface structure in the display
 *  
 * --------------------------
 * |	  time XX:XX	    |	
 * --------------------------   <--- Y = 18
 * |	      TASK	    |
 * | 	  DESCRIPTION	    |
 * |			    |
 * --------------------------   <--- Y = 48
 * |STATUS   current/amount |
 * --------------------------
 *
 */
static void draw_interface(ssd1306_t *disp) {
    // draw time-task separator -> line in Y=18
    ssd1306_draw_line(disp, 0, 18, 127, 18);
    // draw task-status separator -> line in y=48
    ssd1306_draw_line(disp, 0, 48, 127, 48);
    display_time(10, 12, disp);
}

/**
 * @brief Draws horizontal lines to mark task as done.
 */
static void draw_cross_task(ssd1306_t *disp) {
    // Draw first diagonal line
    ssd1306_draw_line(disp, 0, 19, 127, 48);
    // Draw second diagonal line
    ssd1306_draw_line(disp, 0, 48, 127, 19);

    // Update the display
    ssd1306_show(disp);
}
