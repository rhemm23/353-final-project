#include "game_loop.h"

int MAX_ASTEROIDS = 10;
volatile ENTITY_t *SHIP;
volatile ASTEROID_t *ASTEROIDS;
volatile uint16_t ASTEROID_COUNT;

/**
 * Checks if two an entity is colliding with the screen boundary
 */
bool check_boundary_collision(volatile ENTITY_t *obj, PS2_DIR_t dir) {
	uint16_t right_edge;
	uint16_t bottom_edge;
	switch(dir) {
		case PS2_DIR_UP:
			// Calculate the top edge of the image
			return obj->y - (obj->height / 2) == 0;
		
		case PS2_DIR_DOWN:
			// Calculate the bottom edge of the image
			bottom_edge = obj->y + (obj->height / 2);
			if((obj->height & 0x01) == 0x00) {
				bottom_edge--;
			}
			return bottom_edge == ROWS;
		
		case PS2_DIR_LEFT:
			// Calculate the left edge of the image
			return obj->x - (obj->width / 2) == 0;
		
		case PS2_DIR_RIGHT:
			// Calculate the right edge of the image
			right_edge = obj->x + (obj->width / 2);
			if((obj->width & 0x01) == 0x00) {
				right_edge--;
			}
			return right_edge == COLS - 1;
		
		default:
			// Case when the direction is center
			return false;
	}
}

/**
 * Checks if two entities are colliding with each other
 */
bool check_collision(volatile ENTITY_t *obj1, volatile ENTITY_t *obj2) {
  return (obj1->x < obj2->x + obj2->width)
      && (obj1->x + obj1->width > obj2->x)
      && (obj1->y < obj2->y + obj2->height)
      && (obj1->y + obj1->height > obj2->y);
}

/**
 * Setups up the game entities
 */
void init_game(void) {
  // Setup spaceship
  SHIP = malloc(sizeof(ENTITY_t));
  SHIP->x = COLS / 2;
  SHIP->y = ROWS - shipHeightPixels - 2;
  SHIP->height = shipHeightPixels;
  SHIP->width = shipWidthPixels;
  
  // Initialize empty asteroid array
  ASTEROIDS = malloc(sizeof(ENTITY_t) * MAX_ASTEROIDS);
}