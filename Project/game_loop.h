#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include "lcd.h"

#include <stdlib.h>
#include <stdint.h>

typedef enum {
  PS2_DIR_UP,
  PS2_DIR_DOWN,
  PS2_DIR_LEFT,
  PS2_DIR_RIGHT,
  PS2_DIR_CENTER
} PS2_DIR_t;

typedef struct {
  int x_pos;
  int y_pos;
} ASTEROID_t;

extern volatile uint16_t SHIP_X_COORD;
extern volatile uint16_t SHIP_Y_COORD;
extern volatile ASTEROID_t *ASTEROIDS;

#endif