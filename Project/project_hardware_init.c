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

void initialize_hardware() {
  // Setup alive LED
  gpio_enable_port(GPIOF_BASE);
  gpio_config_digital_enable(GPIOF_BASE, RED_M);
  gpio_config_digital_enable(GPIOF_BASE, SW2_M);
  gpio_config_enable_output(GPIOF_BASE, RED_M);
  gpio_config_enable_input(GPIOF_BASE, SW2_M);
  GPIOF->IM |= SW2_M;
  NVIC_EnableIRQ(GPIOF_IRQn);
  NVIC_SetPriority(GPIOF_IRQn, 4);
  
  
  ft6x06_init();
  lcd_config_gpio();
  lcd_config_screen();
  init_serial_debug(true, true);
	eeprom_init();
 
  // Setup io expander
	io_expander_init();
  io_expander_write_reg(MCP23017_IODIRB_R, 0xFF);
  io_expander_write_reg(MCP23017_IODIRA_R, 0x00);
  io_expander_write_reg(MCP23017_GPPUB_R, 0x0F);
  io_expander_write_reg(MCP23017_GPINTENB_R, 0x0F);
  
  lcd_clear_screen(LCD_COLOR_BLACK);
  ps2_initialize();
}