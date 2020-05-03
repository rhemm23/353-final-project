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
#include "game_loop.h"
#include "project_interrupts.h"

static volatile uint16_t PS2_X_DATA;
static volatile uint16_t PS2_Y_DATA;

volatile bool BLINK_ALIVE_LED = true;

void initialize_interrupts() {
  // Set timer to blink red LED every 1 sec
  gp_timer_config_32(TIMER1_BASE, TIMER_TAMR_TAMR_PERIOD, 50000000, false, true);
  gp_timer_config_32(TIMER2_BASE, TIMER_TAMR_TAMR_PERIOD, 1200000, false, true);
  gp_timer_config_32(TIMER3_BASE, TIMER_TAMR_TAMR_PERIOD, 500000, false, true);
  gp_timer_config_32(TIMER4_BASE, TIMER_TAMR_TAMR_PERIOD, 500000, false, true);
}

PS2_DIR_t ps2_get_direction(void) {
	// Use ps2 x and y data
	PS2_DIR_t dir = PS2_DIR_CENTER;
	if(PS2_X_DATA > 2979) {
		dir = PS2_DIR_LEFT;
	} else if(PS2_X_DATA < 1055) {
		dir = PS2_DIR_RIGHT;
	} else if(PS2_Y_DATA > 2979) {
		dir = PS2_DIR_UP;
	} else if(PS2_Y_DATA < 1055) {
		dir = PS2_DIR_DOWN;
	}
	return dir;
}

void remove_asteroid(uint8_t index) {
  uint8_t i;
  for(i = index; i < ASTEROID_COUNT - 1; i++) {
    ASTEROIDS[i] = ASTEROIDS[i + 1];
  }
  ASTEROID_COUNT--;
}

ASTEROID_t generate_asteroid() {
  ASTEROID_t asteroid;
  asteroid.entity.x = (rand() % (COLS - asteroidWidthPixels)) + asteroidWidthPixels / 2;
  asteroid.entity.y = asteroidHeightPixels / 2;
  asteroid.entity.height = asteroidHeightPixels;
  asteroid.entity.width = asteroidWidthPixels;
  asteroid.health = (rand() % 3) + 1;
  return asteroid;
}

void TIMER1A_Handler(void)
{
  int i;
  uint8_t data;
  
  // Flag for alive LED to blink
  BLINK_ALIVE_LED = true;
  
  if(GAME_STATE == RUNNING) {
    // Update charge
    if(CHARGE < 9) {
      data = 0x00;
      for(i = 0; i < CHARGE; i++) {
        data |= (1 << i);
      }
      io_expander_write_reg(MCP23017_GPIOA_R, data);
			CHARGE++;
    } else {
			LASER.draw = true;
		}
  }
  
  // Clear the interrupt
  TIMER1->ICR |= TIMER_ICR_TATOCINT;
}

//*****************************************************************************
// TIMER2 ISR is used to determine when to move the asteroids
//*****************************************************************************
void TIMER2A_Handler(void)
{
  uint8_t remove_indices[MAX_ASTEROIDS];
  uint16_t i, min_y, ri;
  min_y = UINT16_MAX;
  ri = 0;
  
  // Update asteroids if running
  if(GAME_STATE == RUNNING) {
    ALERT_ASTROIDS = true;
    // Default remove indices to -1
    for(i = 0; i < MAX_ASTEROIDS; i++) {
      remove_indices[i] = -1;
    }
    
    // Loop through asteroids
    for(i = 0; i < ASTEROID_COUNT; i++) {
      ASTEROIDS[i].entity.y++;
      if(check_collision(&ASTEROIDS[i].entity, &SHIP)) {
        ALERT_GAME_END = true;
      } else if(check_boundary_collision(&ASTEROIDS[i].entity, PS2_DIR_DOWN)) {
        remove_indices[ri++] = i;
        ASTEROIDS[i].entity.y--; // Reset to current position if going to be removed
      }
      
      // Update min
      if(ASTEROIDS[i].entity.y < min_y) {
        min_y = ASTEROIDS[i].entity.y;
      }
    }

    // Remove asteroids touching the bottom
    for(i = 0; i < ri; i++) {
			++SCORE;
      CLEAR_ASTEROID_QUEUE[CLEAR_ASTEROID_COUNT++] = ASTEROIDS[remove_indices[i]];
      remove_asteroid(remove_indices[i]);
    }
    
    // Create new asteroid
    if(ASTEROID_COUNT == 0 || (min_y > (asteroidHeightPixels * 1.5) && ((rand() % ASTROID_DENSITY) < min_y) && ASTEROID_COUNT < MAX_ASTEROIDS)) {
      ASTEROIDS[ASTEROID_COUNT++] = generate_asteroid();
    }
  }
  
	// Clear the interrupt
	TIMER2->ICR |= TIMER_ICR_TATOCINT;
}

//*****************************************************************************
// TIMER3 ISR is used to determine when to move the spaceship
//*****************************************************************************
void TIMER3A_Handler(void)
{
  int i, c;
  PS2_DIR_t dir;
  
  // Update spaceship if running
  if(GAME_STATE == RUNNING) {
    ALERT_SHIP = true;
    dir = ps2_get_direction();
    if(!check_boundary_collision(&SHIP, dir)) {
      switch(dir) {
        case PS2_DIR_LEFT:
          SHIP.x--;
          break;
        
        case PS2_DIR_RIGHT:
          SHIP.x++;
          break;
        
        case PS2_DIR_UP:
          SHIP.y--;
          break;
        
        case PS2_DIR_DOWN:
          SHIP.y++;
          break;
        
        default:
          break;
      }
			if (LASER.draw) {
				--LASER.y;
        c = -1;
        for(i = 0; i < ASTEROID_COUNT; i++) {
          if(check_collision(&ASTEROIDS[i].entity, &LASER)) {
            c = i;
            break;
          }
        }
        
        // Remove asteroid if collision
        if(c > -1) {
          CLEAR_ASTEROID_QUEUE[CLEAR_ASTEROID_COUNT++] = ASTEROIDS[c];
          remove_asteroid(c);
          SCORE += 5;
        }
        
        // Stop drawing laser
				if(c > -1 || LASER.y <= 20) {
					LASER.draw = false;
					lcd_draw_image(LASER.x, LASER.width, LASER.y, LASER.height, laserBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
					LASER.y = SHIP.y;
				}
			}
    }
  }

	// Clear the interrupt
	TIMER3->ICR |= TIMER_ICR_TATOCINT;  
}

//*****************************************************************************
// TIMER4 ISR is used to trigger the ADC
//*****************************************************************************
void TIMER4A_Handler(void)
{
  // Start sample sequencer
  ADC0->PSSI = ADC_PSSI_SS2;
	
  // Clear the interrupt
  TIMER4->ICR |= TIMER_ICR_TATOCINT; 
}

//*****************************************************************************
// ADC0 SS2 ISR
//*****************************************************************************
void ADC0SS2_Handler(void)
{
	// Get raw values
  PS2_X_DATA = ADC0->SSFIFO2 & 0xFFF;
  PS2_Y_DATA = ADC0->SSFIFO2 & 0xFFF;
	
  // Clear the interrupt
  ADC0->ISC |= ADC_ISC_IN2;
}

//*****************************************************************************
// I2C1 ISR
//*****************************************************************************
void GPIOF_Handler(void) {
  uint8_t cap;
  cap = io_expander_read_reg(MCP23017_INTCAPB_R);
  if(cap) {
    
  }
}

