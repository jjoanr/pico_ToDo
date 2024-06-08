/* src/task_manager.c */
#include "task_manager.h"
#include "ssd1306.h"
#include <stdio.h>
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
    strcpy(task1.title, "888888888888888888888312124");
    task1.isDone = false;
    add_task(&task1);

    task task2;
    task2.id_task = 1;
    strcpy(task2.title, "RUNNING");
    task2.isDone = false;
    add_task(&task2);

    task task3;
    task3.id_task = 1;
    strcpy(task3.title, "HOMEWORK");
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
int display_home_screen(void) {
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
 * Cycles through tasks and prints the task description formatted
 *
 * @return SUCCESS if success, ERROR otherwise.
 */
int next_task(void) {
    if(!startedTaskDisplay) {
	startedTaskDisplay = true;
	ssd1306_clear(&disp);
	// Draws interface when starting to display tasks
	draw_interface();
    } else {
	tasks.currentIndex = (tasks.currentIndex + 1) % tasks.currentAmount;
    }
    // Clear text area only:
    //   Starting x,y point: (0,19)
    //   Width: All screen
    //   Height: Up to the next section (which starts at pixel 0 -> 48-19 = 29)
    ssd1306_clear_square(&disp, 0, 19, 128, 29);

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
        ssd1306_draw_string(&disp, 0, yPosition, 1, rowText);
    }
    // Draw task status
    display_status();
    ssd1306_show(&disp);
    return SUCCESS;
}

/**
 * @brief Displays the task status.
 *
 * Shows whether the current task is done or to be done.
 */
void display_status(void) {
    // Clear status area only:
    //   Starting x,y point: (0,51)
    //   Width: All screen
    //   Height: Up to the end of the screen (63-49 = 14)
    ssd1306_clear_square(&disp, 0, 49, 128, 14);
    if(tasks.taskList[tasks.currentIndex].isDone) {
    	ssd1306_draw_string(&disp, 6, 54, 1, "DONE!!!");
	// Draws a "cross" above the task text, to mark it as done
	draw_cross_task();
    } else {
	ssd1306_draw_string(&disp, 6, 54, 1, "To do");
    }
    // currentIndex + '/' + currentAmount
    char str[32];
    snprintf(str, sizeof(str), "%d / %d", tasks.currentIndex + 1, tasks.currentAmount);
    ssd1306_draw_string(&disp, 96, 54, 1, str);
    ssd1306_show(&disp);
}

/**
 * @brief Displays time.
 *
 * @param hour Current hour to be displayed
 * @param minute Current minute to be displayed
 *
 * Displays the current time hour:minute at the top of the screen
 */
void display_time(uint hour, uint minute) {
    // Clear time area only:
    //   Starting x,y point: (0,0)
    //   Width: All screen
    //   Height: Up to the next section (which starts at pixel 18 -> 18-0 = 18)
    ssd1306_clear_square(&disp, 0, 0, 128, 18);
    // hour + ":" + minute
    char str[32];
    snprintf(str, sizeof(str), "%d:%d", hour, minute);
    ssd1306_draw_string(&disp, 50, 6, 1, str);
    ssd1306_show(&disp);
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
    // Toggles between done and to do
    // tasks.taskList[tasks.currentIndex].isDone = tasks.taskList[tasks.currentIndex].isDone ? false : true;
    tasks.taskList[tasks.currentIndex].isDone = true;
    display_status();
    return SUCCESS;
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
void draw_interface(void) {
    // draw time-task separator -> line in Y=18
    ssd1306_draw_line(&disp, 0, 18, 127, 18);
    // draw task-status separator -> line in y=48
    ssd1306_draw_line(&disp, 0, 48, 127, 48);
    display_time(10, 12);
}

/**
 * @brief Draws horizontal lines to mark task as done.
 */
void draw_cross_task(void) {
    // Calculate the coordinates to draw the cross lines over the task text
    int yPosition1 = Y_START_ROW_1 + 1;  // Adjust based on font height and positioning
    int yPosition2 = Y_START_ROW_2 + 1; // Adjust based on font height and positioning
    // Row 1 cross lines
    ssd1306_draw_line(&disp, 0, yPosition1, 127, yPosition1);
    ssd1306_draw_line(&disp, 0, yPosition1 + 4, 127, yPosition1 + 4);
    // Row 2 cross lines
    ssd1306_draw_line(&disp, 0, yPosition2, 127, yPosition2);
    ssd1306_draw_line(&disp, 0, yPosition2 + 4, 127, yPosition2 + 4);
}
