/* include/input.h */
#ifndef INPUT_H
#define INPUT_H

#include <cstdint>

// Function prototypes
void setup_gpios(void);
void button_isr(uint32_t gpio, uint32_t events);

#endif /* INPUT_H */
