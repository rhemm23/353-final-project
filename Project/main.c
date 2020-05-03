// Copyright (c) 2015-19, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"

volatile ASTEROID_t CLEAR_ASTEROID_QUEUE[MAX_ASTEROIDS];
volatile uint8_t CLEAR_ASTEROID_COUNT = 0;
volatile uint8_t CHARGE = 0;
volatile uint16_t SCORE = 0;

volatile bool ALERT_GAME_END = false;
volatile bool ALERT_ASTROIDS = true;
volatile GAME_STATE_t GAME_STATE;
volatile bool ALERT_SHIP = true;

//*****************************************************************************
//*****************************************************************************
void DisableInterrupts(void)
{
  __asm {
    CPSID  I
  }
}

//*****************************************************************************
//*****************************************************************************
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

void initialize_board(void) {
  DisableInterrupts();
  initialize_hardware();
  initialize_interrupts();
  EnableInterrupts();
}

//*****************************************************************************
//*****************************************************************************
int main(void) {
  uint8_t high_score;
  int i;
  char c;
  uint8_t touch_event;
  GAME_STATE_t return_state;
	
  initialize_board();
  GAME_STATE = START;
	
  printf("Running...\n");
  
	// Display High Score on Power Up
	start_screen();

  while(GAME_STATE != EXIT) {
    // Check for flag
    if(BLINK_ALIVE_LED) {
      // Blink red LED
      GPIOF->DATA |= RED_M;
      i = 10000;
      while(i-- > 0);
      GPIOF->DATA &= ~RED_M;
      
      // Clear flag
      BLINK_ALIVE_LED = false;
    }
    
    // Check touch events
    touch_event = ft6x06_read_td_status();
    switch(GAME_STATE) {
      case RUNNING:
        // Redraw ship on flag
        if(ALERT_SHIP) {
          ALERT_SHIP = false;
					if (SHIP.draw) {
						lcd_draw_image(SHIP.x, SHIP.width, SHIP.y, 
              SHIP.height, shipBitmaps, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
					}
					if(LASER.draw) {
						if (CHARGE > 8) {
							LASER.x = SHIP.x;
							LASER.y = SHIP.y - (SHIP.height/2);
						}
						lcd_draw_image(LASER.x, LASER.width, LASER.y, LASER.height, 
							laserBitmaps, LCD_COLOR_RED, LCD_COLOR_BLACK);
						CHARGE = 0;
					}
        }
        
        // Redraw asteroids
        if(ALERT_ASTROIDS) {
          ALERT_ASTROIDS = false;
          
          // Clear asteroids
          for(i = 0; i < CLEAR_ASTEROID_COUNT; i++) {
            lcd_draw_image(CLEAR_ASTEROID_QUEUE[i].entity.x, asteroidWidthPixels, CLEAR_ASTEROID_QUEUE[i].entity.y, 
                asteroidHeightPixels, asteroidBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
          }
          
          // Reset clear astroid queue
          CLEAR_ASTEROID_COUNT = 0;
          
          // Draw asteroids
          for(i = 0; i < ASTEROID_COUNT; i++) {
            lcd_draw_image(ASTEROIDS[i].entity.x, asteroidWidthPixels, ASTEROIDS[i].entity.y, 
                asteroidHeightPixels, asteroidBitmaps, LCD_COLOR_GRAY, LCD_COLOR_BLACK);
          }
        }
        
        // End game
        if(ALERT_GAME_END) {
          ALERT_GAME_END = false;
          GAME_STATE = GAME_OVER;
        }
        
        break;
      
      case START:
        // If screen is touched, start the game
        if(touch_event > 0 && touch_event != 0xFF) {
          GAME_STATE = RUNNING;
					lcd_clear_screen(LCD_COLOR_BLACK);
          init_game();
          
          // Set global variables
          SCORE = 0;
          CHARGE = 0;
          CLEAR_ASTEROID_COUNT = 0;
        }
        break;
        
      default:
        break;
    }
    
    // Check for pause
    c = uart_rx_poll(UART0_BASE, false);
    if(c == ' ') {
      if(GAME_STATE == PAUSED) {
        printf("Running...\n");
        GAME_STATE = return_state;
      } else {
        printf("Paused. Hit space bar to resume...\n");
        return_state = GAME_STATE;
        GAME_STATE = PAUSED;
      }
    }
  }
}
