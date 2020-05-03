#include "game_loop.h"

volatile ENTITY_t *SHIP;
volatile ENTITY_t *ASTEROIDS;
volatile uint16_t ASTEROID_COUNT;

/**
 * Checks if two entities are colliding with each other
 */
bool check_collision(ENTITY_t *obj1, ENTITY_t *obj2) {
  return (obj1->x < obj2->x + obj2->width)
      && (obj1->x + obj1->width > obj2->x)
      && (obj1->y < obj2->y + obj2->height)
      && (obj1->y + obj1->height > obj2->y);
}

void init_game(void) {
  SHIP = malloc(sizeof(ENTITY_t));
  SHIP->x = COLS / 2;
  SHIP->y = ROWS - 20;
  ASTEROIDS = malloc(sizeof(ENTITY_t) * 10);
}