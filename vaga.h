#ifndef VAGA_H
#define VAGA_H
#include <stdint.h>

void vaga_init(void);
int32_t vaga_read(void);
void vaga_tare(void);
float vaga_read_grams(void);

#endif 