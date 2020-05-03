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
  //gp_timer_config_32(TIMER2_BASE, TIMER_TAMR_TAMR_PERIOD, 2000000, false, true);
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

void TIMER1A_Handler(void)
{
  // Flag for alive LED to blink
  BLINK_ALIVE_LED = true;
  
  // Clear the interrupt
  TIMER1->ICR |= TIMER_ICR_TATOCINT;
}

//*****************************************************************************
// TIMER3 ISR is used to determine when to move the asteroids
//*****************************************************************************
void TIMER2A_Handler(void)
{
  int i;
  for(i = 0; i < ASTEROID_COUNT; i++) {
  }
			
	// Clear the interrupt
	TIMER2->ICR |= TIMER_ICR_TATOCINT;
}

//*****************************************************************************
// TIMER3 ISR is used to determine when to move the spaceship
//*****************************************************************************
void TIMER3A_Handler(void)
{
  PS2_DIR_t dir;
  ALERT_SHIP = true;
  dir = ps2_get_direction();
  if(!check_boundary_collision(SHIP, dir)) {
    switch(dir) {
      case PS2_DIR_LEFT:
        SHIP->x--;
        break;
      
      case PS2_DIR_RIGHT:
        SHIP->x++;
        break;
      
      default:
        break;
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