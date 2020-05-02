#ifndef __KESSEL_RUN_H__
#define __KESSEL_RUN_H__

#include "main.h"
#include "final_images.h"

#define ADDR_HIGH_BYTE    256
#define ADDR_LOW_BYTE    257
#define NUM_BYTES      20
#define UPPER_CASE_START_A 17
#define LOWER_CASE_START_A 42

void draw_letter (uint16_t x_index, uint16_t y_index, uint8_t character);

void draw_string(char* string, uint16_t y_index);

#endif