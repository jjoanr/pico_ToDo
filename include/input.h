/* include/input.h */
#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

// Function prototypes
void setup_gpios(void);
void button_isr(unsigned int gpio, uint32_t events);

#endif /* INPUT_H */
