#include "game_loop.h"

volatile uint16_t SHIP_X_COORD;
volatile uint16_t SHIP_Y_COORD;
volatile ASTEROID_t *ASTEROIDS;

void init_game(void) {
  SHIP_X_COORD = COLS / 2;
  SHIP_Y_COORD = ROWS - 20;
  ASTEROIDS = malloc(sizeof(ASTEROID_t) * 10);
}