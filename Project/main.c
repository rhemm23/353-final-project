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
	char* str = "Ryan";
  uint8_t touch_event;
  GAME_STATE_t state, return_state;
	
  initialize_board();
  state = START;
	
  printf("Running...\n");
  
	// Display High Score on Power Up
	//draw_string(str, 0x0040);
  while(state != EXIT) {
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
    touch_event = ft6x06_read_td_status();
    switch(state) {
      case RUNNING:
        c = uart_rx_poll(UART0_BASE, false);
        if(c == ' ') {
          printf("Paused. Hit space bar to resume...\n");
          return_state = RUNNING;
          state = PAUSED;
        }
        
        // Redraw ship on flag
        if(ALERT_SHIP) {
          lcd_draw_image(SHIP->x, SHIP->width, SHIP->y, 
              SHIP->height, shipBitmaps, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
          ALERT_SHIP = false;
        }
        break;
      
      case PAUSED:
        c = uart_rx_poll(UART0_BASE, true);
        if(c == ' ') {
          printf("Running...\n");
          state = return_state;
        }
        break;
      
      case START:
        // Look for pause
        c = uart_rx_poll(UART0_BASE, false);
        if(c == ' ') {
          printf("Paused. Hit space bar to resume...\n");
          return_state = START;
          state = PAUSED;
        }
        
        // If screen is touched, start the game
        if(touch_event > 0 && touch_event != 0xFF) {
          state = RUNNING;
          init_game();
        }
        break;
        
      case EXIT:
        break;
    }
  }
}
