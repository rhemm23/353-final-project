// Copyright (c) 2015-16, Joe Krachey
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
#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"
#include "gpio_port.h"
#include "lcd.h"
#include "lcd_images.h"
#include "timers.h"
#include "ps2.h"
#include "launchpad_io.h"
#include "eeprom.h"
#include "ft6x06.h"

#include "project_interrupts.h"
#include "project_hardware_init.h"
#include "kessel_run.h"
#include "final_images.h"
#include "game_loop.h"
#include "io_expander.h"

#define TITLE "Kessel Run"

typedef enum {
  START,
  RUNNING,
  PAUSED,
  GAME_OVER,
  EXIT
} GAME_STATE_t;

typedef enum {
  DEBOUNCE_ONE,
  DEBOUNCE_1ST_ZERO,
  DEBOUNCE_PRESSED
} DEBOUNCE_STATES;

extern volatile uint16_t SCORE;
extern volatile uint8_t CHARGE;
extern volatile bool ALERT_SHIP;
extern volatile bool ALERT_FIRE;
extern volatile bool ALERT_ASTROIDS;
extern volatile bool ALERT_GAME_END;
extern volatile GAME_STATE_t GAME_STATE;

extern volatile uint8_t CLEAR_ASTEROID_COUNT;
extern volatile ASTEROID_t CLEAR_ASTEROID_QUEUE[];

#endif