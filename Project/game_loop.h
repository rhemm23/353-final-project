#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include "lcd.h"
#include "final_images.h"

#include <stdlib.h>
#include <stdint.h>

#define ASTROID_DENSITY 1000
#define MAX_ASTEROIDS 50

typedef enum {
  PS2_DIR_UP,
  PS2_DIR_DOWN,
  PS2_DIR_LEFT,
  PS2_DIR_RIGHT,
  PS2_DIR_CENTER
} PS2_DIR_t;

typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t height;
  uint16_t width;
	bool draw;
} ENTITY_t;

typedef struct {
  ENTITY_t entity;
  uint16_t health;
} ASTEROID_t;

extern volatile uint16_t ASTEROID_COUNT;
extern volatile ASTEROID_t ASTEROIDS[];
extern volatile ENTITY_t SHIP;
extern volatile ENTITY_t LASER;

//*****************************************************************************
// Resets the game to the starting state
//*****************************************************************************
void init_game(void);

//*****************************************************************************
// Checks if an entity will collide with the boundary if it is moved in the 
// specified direction
//*****************************************************************************
bool check_boundary_collision(volatile ENTITY_t *obj, PS2_DIR_t dir);

//*****************************************************************************
// Checks if two entities are colliding
//*****************************************************************************
bool check_collision(volatile ENTITY_t *obj1, volatile ENTITY_t *obj2);

#endif