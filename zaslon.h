#ifndef ZASLON_H
#define ZASLON_H
#include <stdint.h>

void zaslon_init(void);
void zaslon_clear(void);
void zaslon_set_cursor(uint8_t row, uint8_t col);
void zaslon_print(char *str);
void zaslon_printint(int32_t n);

#endif 