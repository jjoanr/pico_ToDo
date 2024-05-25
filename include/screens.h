/* include/screens.h */
#ifndef _SCREENS_H
#define _SCREENS_H

#include <stdbool.h>
#include <sys/types.h>

/* Define display sections: 128x64 pixels
 * Title section :
 *	X: 0 to 16
 *	Y: 0 to 128
 * Body section :
 *	X: 16 to 48
 *	Y: 0 to 128
 * Status and general info section:
 *	X: 48 to 64
 *	Y: 0 to 128
*/

typedef struct screen {
	uint id_screen;
	

} screen;


// Function prototypes
bool init_display();
void display_init_screen();
void add_screen();
void remove_screen();
void next_screen();
void prior_screen();

#endif /* _SCREENS_H */
