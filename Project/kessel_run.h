#ifndef __KESSEL_RUN_H__
#define __KESSEL_RUN_H__


#include "main.h"
#include "final_images.h"
#include "eeprom.h"

#define ADDR_HIGH_BYTE    257
#define ADDR_LOW_BYTE    256
#define NUM_BYTES      20
#define UPPER_CASE_START_A 17
#define LOWER_CASE_START_A 42

void write_high_score(uint16_t score);
uint16_t read_high_score();
void draw_letter(uint16_t x_index, uint16_t y_index, uint8_t character, uint16_t color);

void draw_string(char* string, uint16_t x_start, uint16_t y_index, uint16_t color);
void start_screen();
#endif